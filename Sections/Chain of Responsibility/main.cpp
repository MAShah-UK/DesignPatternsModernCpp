#include <iostream>
#include <memory>
#include <forward_list>

class Creature {
    friend std::ostream& operator<<(std::ostream& os, const Creature& other) {
        os << "[name] " << other.name << " [attack] " << other.attack << " [defense] " << other.defense;
        return os;
    }

    std::string name;
    int attack, defense;
public:
    Creature(const std::string &name, int attack, int defense)
        : name(name), attack(attack), defense(defense) {}

    const std::string& getName() const {
        return name;
    }
    void setName(const std::string& name) {
        Creature::name = name;
    }
    int getAttack() const {
        return attack;
    }
    void setAttack(int attack) {
        Creature::attack = attack;
    }
    int getDefense() const {
        return defense;
    }
    void setDefense(int defense) {
        Creature::defense = defense;
    }
};

class CreatureModifier {
public:
    virtual bool handle(Creature& creature) = 0;
};

class CreatureModifiers {
    Creature& creature;
    std::forward_list<std::shared_ptr<CreatureModifier>> modifiers;
public:
    CreatureModifiers(Creature& creature)
        : creature(creature) {}

    void add(std::shared_ptr<CreatureModifier> modifier) {
        modifiers.push_front(modifier);
    }
    bool handle() {
        for(auto ptr : modifiers) {
            bool pass_along = ptr->handle(creature);
            if(!pass_along) {
                break;
            }
        }
        return true;
    }
};

// Maybe if the player picks up a potion.
class DoubleAttackModifier : public CreatureModifier {
public:
    bool handle(Creature& creature) override {
        creature.setAttack(creature.getAttack()*2);
        return true;
    }
};

// Maybe the player is buffed by an ally.
class IncreaseDefenseModifier : public CreatureModifier {
public:
    bool handle(Creature& creature) override {
        if(creature.getAttack() <= 2) {
            creature.setDefense(creature.getDefense()+1);
        }
        return true;
    }
};

// Maybe the player was cursed by an enemy and lost their bonuses.
class NoBonusesModifier : public CreatureModifier {
public:
    bool handle(Creature& creature) override {
        return false;
    }
};

int main() {
    Creature goblin{"Goblin", 1, 1};
    CreatureModifiers root{goblin};
    root.add(std::make_shared<DoubleAttackModifier>()); // 2 1
    root.add(std::make_shared<DoubleAttackModifier>()); // 4 1
    root.add(std::make_shared<IncreaseDefenseModifier>()); // 4 1
    root.add(std::make_shared<NoBonusesModifier>()); // 1 1
    root.handle();
    std::cout << goblin << std::endl;

    return 0;
}