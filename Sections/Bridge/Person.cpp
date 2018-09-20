#include "Person.h"

class Person::PersonImpl {
public:
    void greet(Person* p);
};

void Person::PersonImpl::greet(Person *p) {
    std::cout << "Hello my name is: "
              << p->name << std::endl;
}

Person::Person()
    : impl{new PersonImpl} {
}

Person::~Person() {
    delete impl;
}

void Person::greet() {
    impl->greet(this);
}
