#include <iostream>
#include <cmath>
#include <iomanip>
#include "Point.h"
#include "HotDrink.h"
#include "DrinkFactory.h"

// How a drink would have to be instantiates without abstract factories.
std::unique_ptr<HotDrink> make_drink(std::string type) {
    std::unique_ptr<HotDrink> drink;
    if(type == "tea") {
        drink = std::make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = std::make_unique<Coffee>();
        drink->prepare(50);
    }
}

int main() {
    // Factory methods: construct objects in one step.
    Point cartesian {Point::get_factory().from_cartesian(3, 4)};
    Point polar_degrees {Point::get_factory().from_degrees(5, 53.13)};
    Point polar_radians {Point::get_factory().from_radians(5, 53.13/180*M_PI)};

    std::cout << std::fixed << std::setprecision(2)
              << "Cartesian: " << cartesian << std::endl
              << "Polar (degrees): " << polar_degrees << std::endl
              << "Polar (radians): " << polar_radians << std::endl << std::endl;

    DrinkFactory drink_factory;
    drink_factory.make_drink("coffee");

    return 0;
}

/*
Challenge: Use factory design pattern.
struct Person {
    int id;
    string name;
};
class PersonFactory {
    int id {};
public:
    Person create_person(const string& name) {
        return {id++, name};
    }
};
 */