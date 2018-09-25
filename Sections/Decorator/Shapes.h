#pragma once

// Assume these classes already exist.

#include <sstream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string str() const = 0;
};

class Circle : public Shape {
    double radius{};
public:
    Circle() {}
    Circle(double radius) : radius{radius} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }

    void resize(double factor) {
        radius *= factor;
    }
};

class Square : public Shape {
    double side;
public:
    Square() {}
    Square(double side) : side{side} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << "A square with side length " << side;
        return oss.str();
    }
};