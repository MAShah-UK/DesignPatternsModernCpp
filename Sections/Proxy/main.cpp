#include <iostream>
#include <memory>
#include "PropertyProxy.h"
#include "VirtualProxy.h"
#include "CommunicationProxy.h"

void property_proxy() {
    Creature c;
    c.strength = 11;
    int strength {c.strength};
    std::cout << std::endl;
}

void virtual_proxy() {
    // LazyBitmap is a proxy because by replacing Bitmap with LazyBitmap,
    // the interface is unchanged.
    LazyBitmap bmp{"pokemon.png"};// Bitmap bmp{"pokemon.png"};
    bmp.draw();
    std::cout << std::endl << std::endl;
}

void communication_proxy() {
    class Inner {
    public:
        static void output(Pingable& pingable) {
            std::wcout << pingable.ping(L"ping") << std::endl;
        }
    };

    // RemotePong is a proxy because by replacing Pong with RemotePong,
    // the interface is unchanged.
    RemotePong pong; // Pong pong;
    for(int i{}; i<3; i++) {
        Inner::output(pong);
    }
}

int main() {
    property_proxy();
    virtual_proxy();
    communication_proxy();
    return 0;
}

/*
Challenge: Use proxy design pattern.
class Person {
    friend class ResponsiblePerson;
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const { return age; }
    void set_age(int age) { this->age=age; }

    string drink() const { return "drinking"; }
    string drive() const { return "driving"; }
    string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson {
    Person& person;
public:
    ResponsiblePerson(Person& person) : person{person} {}

    int get_age() const { return person.get_age(); }
    void set_age(int age) { person.set_age(age); }

    string drink() const { return get_age() >= 18 ? "drinking" : "too young" ;}
    string drive() const { return get_age() >= 16 ? "driving" : "too young"; }
    string drink_and_drive() const { return "dead"; }
};
 */