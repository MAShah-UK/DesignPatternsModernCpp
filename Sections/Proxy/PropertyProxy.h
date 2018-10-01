#pragma once

// Works similar to a property in C#.
// This is a proxy pattern because you work with Property<T> variables as if they're
// normal variables, but you can introduce custom functionality in the getter and setter.
template <typename T>
class Property {
    T value;
public:
    Property(const T& value) {
        *this = value;
    }
    // Setter.
    Property& operator=(const T& value) {
        std::cout << "Assignment: " << value << std::endl;
        this->value = value;
        return *this;
    }
    // Getter.
    operator T() const {
        return value;
    }
};

class Creature {
public:
    Property<int> strength{10};
    Property<int> agility{10};
};