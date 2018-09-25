#pragma once

#include "Shapes.h"

// Assume that a color property needs to be added.
// One way is to use inheritance and create
// ColoredCircle, ColoredSquare, etc but this is not
// scalable, instead use the dynamic decorator pattern.
// This way only one class is needed.
class ColoredShape : public Shape {
    Shape &shape;
    std::string color;
public:
    ColoredShape(Shape &shape, const std::string &color)
            : shape{shape}, color{color} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

class TransparentShape : public Shape {
    Shape &shape;
    uint8_t transparency;
public:
    TransparentShape(Shape &shape, uint8_t transparency)
            : shape{shape}, transparency{transparency} {}

    std::string str() const override {
        std::ostringstream oss;
        double percentage = static_cast<double>(transparency) / 255 * 100;
        oss << shape.str() << " has transparency " << percentage << '%';
        return oss.str();
    }
};