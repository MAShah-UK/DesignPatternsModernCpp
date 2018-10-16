#include "Chatroom.h"

void Chatroom::broadcast(const std::string &origin, const std::string &message) {
    for(auto it = people.begin(); it != people.end(); ++it) {
        std::weak_ptr<Person> w_ptr = *it;
        if(w_ptr.expired()) {
            it = people.erase(it);
        } else {
            std::shared_ptr<Person> person = w_ptr.lock();
            if(person->get_name() != origin) {
                person->receive(origin, message);
            }
        }
    }
}

void Chatroom::join(std::shared_ptr<Person> person) {
    person->set_room(shared_from_this());
    people.push_back(person);
    std::string join_msg = person->get_name() + " joined the chat.";
    broadcast("Room", join_msg);
}

void Chatroom::message(const std::string& origin, const std::string& who, const std::string& message) {
    for(auto w_ptr : people) {
        if(!w_ptr.expired()) {
            std::shared_ptr<Person> person = w_ptr.lock();
            if(person->get_name() == who) {
                person->receive(origin, message);
                break;
            }
        }
    }
}
