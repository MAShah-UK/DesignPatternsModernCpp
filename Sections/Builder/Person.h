#pragma once
#include <string>
#include <ostream>

// MULTIPLE BUILDERS / BUILDER FACADE.

class PersonBuilder;

class Person {
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;

    friend std::ostream &operator<<(std::ostream &os, const Person &person);

    std::string street_address, post_code, city;
    std::string company_name, position;
    int annual_income {};
public:
    static PersonBuilder create();
};

