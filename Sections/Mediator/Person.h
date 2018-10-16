#pragma once

#include <string>
#include <memory>
#include <vector>

class Chatroom;

class Person {
    std::string name;
    std::shared_ptr<Chatroom> room;
    std::vector<std::string> chat_log;
public:
    Person(const std::string &name);

    const std::string& get_name() const;
    void set_room(std::shared_ptr<Chatroom> room);

    void say(const std::string& message);
    void private_message(const std::string& who,
                         const std::string& message);
    void receive(const std::string& origin,
                 const std::string& message);
};