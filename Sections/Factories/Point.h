#pragma once

// Represents points which use cartesian coordinates.
// Can be initialised using cartesian or polar coordinates.
class Point {
    class PointFactory {
    public:
        // Solution 3: Factory methods.
        // Ideal solution because it makes construction explicit.
        // Can group into inner class called PointFactory,
        // or keep them separate.
        static Point from_cartesian(double x, double y) {
            return {x, y};
        }
        static Point from_radians(double rho, double theta) {
            double x = rho * cos(theta);
            double y = rho * sin(theta);
            return {x, y};
        }
        static Point from_degrees(double rho, double theta) {
            return from_radians(rho, theta/180 * M_PI);
        }
    };

    static PointFactory factory;
    double x, y;

    // For solution 3.
    // Forces the client to use factory methods.
    Point(double x, double y) : x{x}, y{y} {}
public:
    //Solution 1: Constructors for cartesian/polar initialisation.
//    Point(double x, double y) // Cartesian coordinates initialisation.
//          : x{x}, y{y} {}
//    Point(double rho, double theta) { // Polar coordinates initialisation.
//      // Reasonable constructor, but the signature conflicts with the cartesian constructor.
//    }

    // Solution 2: One constructor with enum to choose coordinate type.
    // Works, but it's ambiguous if a refers to x, y, rho, or theta.
    // Can be made explicit using documentation, but it's still error prone.
//    enum class PointType { Cartesian, Polar };
//    Point(double a, double b, PointType type)  {
//        if(type == PointType::Cartesian) {
//            x = a;
//            y = b;
//        } else {
//            x = a * cos(b);
//            y = a * sin(b);
//        }
//    }

    // Groups factory methods into one convenient inner class.
    // Marking factory class and Point constructor as private
    // limits the client to using this method which makes it
    // easier for them to work with the class.
    static PointFactory get_factory() {
        return factory;
    }
    double get_x() const {
        return x;
    }
    double get_y() const {
        return y;
    }
};

std::ostream &operator<<(std::ostream &lhs, const Point &rhs) {
    lhs << '[' << rhs.get_x() << ',' << rhs.get_y() << ']';
    return lhs;
}

// Can create factory class as long as Point constructor is public.
//class PointFactory {
//public:
//    static Point from_cartesian(double x, double y) {
//        return {x, y};
//    }
//    static Point from_radians(double rho, double theta) {
//        double x = rho * cos(theta);
//        double y = rho * sin(theta);
//        return {x, y};
//    }
//    static Point from_degrees(double rho, double theta) {
//        return from_radians(rho, theta/180 * M_PI);
//    }
//};