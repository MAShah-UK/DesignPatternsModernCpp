#pragma once

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
    Person &person;
public:
    PersonBuilderBase(Person &person);

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

    operator Person() {
        return std::move(person);
    }
};

class PersonBuilder : public PersonBuilderBase {
    Person person;
public:
    PersonBuilder();
};