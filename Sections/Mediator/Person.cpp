#include "Person.h"

Person::Person(const std::string &name) : name(name) {

}

bool Person::operator==(const Person &rhs) const {
    return name == rhs.name;
}

bool Person::operator!=(const Person &rhs) const {
    return !(rhs == *this);
}

const std::string &Person::get_name() const {
    return name;
}

void Person::set_room(std::weak_ptr<ChatRoom> room) {
    this->room = room;
}

void Person::say(const std::string &message) const {

}

void Person::private_message(const std::string &who, const std::string &message) const {

}

void Person::receive(const std::string &origin, const std::string &message) const {

}

