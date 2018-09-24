#pragma once

#include <cmath>
#include <array>
#include <algorithm>
#include <numeric>

class BadCreature {
    int strength;
    int intelligence;
    int agility;
public:
    // Getters and setters.
    int get_strength() const {
        return strength;
    }
    void set_strength(int strength) {
        BadCreature::strength = strength;
    }
    int get_intelligence() const {
        return intelligence;
    }
    void set_intelligence(int intelligence) {
        BadCreature::intelligence = intelligence;
    }
    int get_agility() const {
        return agility;
    }
    void set_agility(int agility) {
        BadCreature::agility = agility;
    }

    // Aggregates.
    // Bad approach because we have to explicitly list the attributes, and the number of them.
    double sum() const {
        return strength + agility + intelligence;
    }
    double average() const {
        return sum()/3;
    }
    int max() const {
        return std::max(std::max(strength, agility), intelligence);
    }
};

// Array backed properties simplify calculations for aggregate methods.
class Creature {
    // count automatically stores the count of items in the enum since it's the last element,
    // and each element is incremented by 1 starting from 0 - by default.
    // Not using enum class to avoid explicit type conversions.
    enum Abilities {_strength, _agility, _intelligence, _count};
    std::array<int, _count> abilities;
public:
    // Getters and setters.
    int get_strength() const {
        return abilities[_strength];
    }
    void set_strength(int strength) {
        abilities[_strength] = strength;
    }
    int get_intelligence() const {
        return abilities[_intelligence];
    }
    void set_intelligence(int intelligence) {
        abilities[_intelligence] = intelligence;
    }
    int get_agility() const {
        return abilities[_agility];
    }
    void set_agility(int agility) {
        abilities[_agility] = agility;
    }

    // Aggregates.
    // Good approach, each method automatically scales.
    int sum() const {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }
    double average() const {
        return sum()/static_cast<double>(_count);
    }
    int max() const {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};