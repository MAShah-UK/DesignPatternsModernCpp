#pragma once
#include "HotDrink.h"
#include "HotDrinkFactory.h"
#include <map>
#include <functional>

// OOP approach.
class DrinkFactory {
    std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory() {
        hot_factories["coffee"] = std::make_unique<CoffeeFactory>();
        hot_factories["tea"] = std::make_unique<TeaFactory>();
    }

    std::unique_ptr<HotDrink> make_drink(const std::string &name) {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

// Functional approach.
class DrinkWithVolumeFactory {
    std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory() {
        factories["coffee"] = [] {
            auto coffee = std::make_unique<Coffee>();
            coffee->prepare(50);
            return coffee;
        };

        factories["tea"] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
    }

    std::unique_ptr<HotDrink> make_drink(const std::string &name) {
        return factories[name]();
    }
};