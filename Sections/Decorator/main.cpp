#include <iostream>
#include <sstream>
#include "Shapes.h"
#include "DynamicDecorator.h"
#include "StaticDecorator.h"
#include "FunctionalDecorator.h"

void use_dynamic_decorator() {
    Circle circle{5};
    // Decorators extend classes without having to modify them.
    ColoredShape red_square{circle, "red"};
    // Decorators can be used together.
    TransparentShape transparent_square{red_square, 51};
    std::cout << circle.str() << std::endl
              << red_square.str() << std::endl
              << transparent_square.str() << std::endl << std::endl;
    // The limitation of dynamic decorators is that you only have
    // access to common interface methods.
}

void use_static_decorator() {
    // Static decorators have the same use as dynamic decorators,
    // except that they can access class specific members.
    SColoredShape<Circle> green_circle{"green", 5.0};
    green_circle.resize(2); // Can access specific method.
    std::cout << green_circle.str() << std::endl;
    // Static decorators can combine other decorators.
    STransparentShape<SColoredShape<Square>> square{51, "blue", 10.0};
    std::cout << square.str() << std::endl << std::endl;
}

double add(double a, double b) {
    std::cout << a << "+" << b << "=" << (a+b) << std::endl;
    return a+b;
}

void use_functional_decorator() {
    Logger log = Logger([]() { std::cout << "Hello" << std::endl; }, "Hello Function");
    log();
    std::cout << std::endl;

    // Works fine for this version of CLion - typename Func is inferred correctly.
    // This wasn't the case for the instructor.
    auto log2 = Logger2([]() { std::cout << "Hello" << std::endl; }, "Hello Function");
    log2();
    std::cout << std::endl;

    auto log3 = create_logger3(&add, "Superposition Function");
    log3(2, 3);
}

int main() {
    use_dynamic_decorator();
    use_static_decorator();
    use_functional_decorator();
    return 0;
}

/*
Challenge: Use dynamic decorator design pattern.
struct Flower {
    virtual ~Flower() = default;
    virtual string str() = 0;
};

struct Rose : Flower {
    string str() override { return "A rose"; }
};

struct RedFlower : Flower {
    Flower &flower;
    RedFlower(Flower &flower) : flower{flower} {}
    string str() override { return flower.str() + " that is red"; }
};

struct BlueFlower : Flower {
    Flower &flower;
    BlueFlower(Flower &flower) : flower{flower} {}
    string str() override { return flower.str() + " that is blue"; }
};
 */