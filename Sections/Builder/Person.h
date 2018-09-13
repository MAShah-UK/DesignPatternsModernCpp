#pragma once
#include <string>
#include <ostream>

// MULTIPLE BUILDERS / BUILDER FACADE.

class PersonBuilder;

class Person {
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;

    std::string street_address, post_code, city;
    std::string company_name, position;
    int annual_income {};
public:
    static PersonBuilder create();

    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

