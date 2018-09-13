#pragma once

#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase {
    using Self = PersonAddressBuilder;
public:
    PersonAddressBuilder(Person &person)
        : PersonBuilderBase{person} {};

    Self &at(const std::string &street_address) {
        person.street_address = street_address;
        return *this;
    }
    Self &with_postcode(const std::string &post_code) {
        person.post_code = post_code;
        return *this;
    }
    Self &in(const std::string &city) {
        person.city = city;
        return *this;
    }
};