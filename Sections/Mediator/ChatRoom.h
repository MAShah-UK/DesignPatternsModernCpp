#pragma once

#include "Person.h"

class ChatRoom {
    std::vector<std::shared_ptr<Person>> people;
public:
    void broadcast(const std::string& origin,
                   const std::string& message);
    void join(std::shared_ptr<Person> person);
};