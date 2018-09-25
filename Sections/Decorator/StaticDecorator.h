#pragma once

#include "Shapes.h"

// Static decorator using mixin inheritance.
// Mixins are when a class inherits from a template argument.
// Static decorators have access to class specific methods.
template <typename T>
class SColoredShape : public T {
    // Not needed, but ensures T is a Shape.
    static_assert(std::is_base_of<Shape, T>::value,
                  "Template argument must be a Shape.");

    std::string color;
public:
    template <typename...Types>
    SColoredShape(const std::string &color, Types...args)
            : T{std::forward<Types>(args)...}, color{color} {}

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

template <typename T>
class STransparentShape : public T {
    uint8_t transparency;
public:
    template<typename...Args>
    STransparentShape(const uint8_t transparency, Args...args)
            : T{std::forward<Args>(args)...}, transparency{transparency} {}

    std::string str() const override {
        std::ostringstream oss;
        double percentage = static_cast<double>(transparency) / 255 * 100;
        oss << T::str() << " has transparency " << percentage << '%';
        return oss.str();
    }
};