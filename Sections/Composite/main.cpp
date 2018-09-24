#include <iostream>
#include <vector>
#include "Graphic.h"
#include "Neuron.h"
#include "CRTP.h"
#include "Creature.h"

void use_graphics() {
    GraphicsGroup root("root");

    Circle c1, c2;
    root.add_graphic(&c1);
    root.add_graphic(&c2);

    GraphicsGroup subgroup("subgroup");
    Circle c3;
    subgroup.add_graphic(&c3);
    root.add_graphic(&subgroup);

    Renderer renderer;
    renderer.draw_to_screen(&root); // Can pass one graphic, or a group of graphics.
}

void use_neurons() {
    Neuron n1, n2;
    n1.connect_to(n2);
    std::cout << n1 << n2 << std::endl;

    NeuronLayer layer1 {2}, layer2{3};
}

void cloner(unique_ptr<Base> &&base) {
    std::cout << "Class name before clone: " << base->name() << std::endl;
    // unique_ptr<Base> clone = std::make_unique<Base>(*base); // Will only copy Base due to object slicing.
    unique_ptr<Base> clone = base->clone();
    std::cout << "Class name after clone: " << clone->name();
}

void make_creatures() {
    Creature orc;
    orc.set_agility(11);
    orc.set_intelligence(9);
    orc.set_strength(16);

    std::cout << "The orc has an average stat of: " << orc.average() << std::endl
              << "The orc has a max stat of: " << orc.max() << std::endl
              << "The orc has a total stat of: " << orc.sum();
}

int main() {
    use_graphics();
    std::cout << std::endl;

    use_neurons();

    unique_ptr<Derived> derived = make_unique<Derived>();
    cloner(move(derived));
    std::cout << std::endl << std::endl;

    make_creatures();
    std::cout << std::endl;

    return 0;
}

/*
Challenge: Use composite design pattern.
Exercise.h:
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

struct ContainsIntegers {
    virtual int get_sum() const = 0;
};

struct SingleValue : ContainsIntegers {
    int value{};

    SingleValue() = default;
    explicit SingleValue(const int value)
        : value{value} {}

    int get_sum() const override {
        return value;
    }
};

struct ManyValues : ContainsIntegers {
    vector<int> values;

    int get_sum() const override {
        return accumulate(values.begin(), values.end(), 0);
    }

    void add(int value) {
        values.emplace_back(value);
    }
};

int sum(const vector<ContainsIntegers*> &items);

exercise.cpp:
#include "exercise.h"

int sum(const vector<ContainsIntegers*> &items) {
    int sum{};
    for(const ContainsIntegers * const item : items) {
        sum += item->get_sum();
    }
    return sum;
}
 */