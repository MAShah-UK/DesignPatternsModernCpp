#include <iostream>
#include <cmath>
#include <iomanip>
#include "Point.h"

int main() {
    // Factory methods: construct objects in one step.
    Point cartesian {Point::get_factory().from_cartesian(3, 4)};
    Point polar_degrees {Point::get_factory().from_degrees(5, 53.13)};
    Point polar_radians {Point::get_factory().from_radians(5, 53.13/180*M_PI)};

    std::cout << std::fixed << std::setprecision(2)
              << "Cartesian: " << cartesian << std::endl
              << "Polar (degrees): " << polar_degrees << std::endl
              << "Polar (radians): " << polar_radians << std::endl << std::endl;

    return 0;
}