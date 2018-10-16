#pragma once

#include "Person.h"

class Chatroom : public std::enable_shared_from_this<Chatroom> {
    std::vector<std::weak_ptr<Person>> people;
public:
    void broadcast(const std::string& origin,
                   const std::string& message);
    void join(std::shared_ptr<Person> person);
    void message(const std::string& origin,
                 const std::string& who,
                 const std::string& message);
};