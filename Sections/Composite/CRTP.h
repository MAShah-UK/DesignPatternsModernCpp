#pragma once
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Base {
public:
    virtual ~Base() = default;
    virtual unique_ptr<Base> clone() = 0;
    // Other virtual methods.
    virtual string name() {
        return "Base";
    }
};

template <typename Self>
class BaseCRTP : public Base {
public:
    unique_ptr<Base> clone() override {
        return make_unique<Self>(*static_cast<Self*>(this));
    }

    string name() override {
        return "BaseCRTP";
    }
};

class Derived : public BaseCRTP<Derived> {
public:
    string name() override {
        return "Derived";
    }
};