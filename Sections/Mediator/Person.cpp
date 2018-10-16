#include <iostream>
#include "Person.h"
#include "Chatroom.h"

Person::Person(const std::string &name) : name(name) {

}

const std::string& Person::get_name() const {
    return name;
}

void Person::set_room(std::shared_ptr<Chatroom> room) {
    this->room = room;
}

void Person::say(const std::string& message) {
    receive(name, message); // Store record of sent message.
    room->broadcast(name, message);
}

void Person::private_message(const std::string& who, const std::string& message) {
    receive(name, message);
    room->message(name, who, message);
}

void Person::receive(const std::string& origin, const std::string& message) {
    std::string output = "[" + origin + "->" + name + "] " + message;
    std::cout << output << std::endl;
    chat_log.emplace_back(output);
}

