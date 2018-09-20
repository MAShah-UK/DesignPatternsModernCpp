#pragma once

#include <string>
#include <iostream>

class Person {
    class PersonImpl;

    // Needs to be a pointer because you can't declare an incomplete type.
    PersonImpl* impl;
    std::string name;
public:
    Person();
    ~Person();

    void greet();
};
