#pragma once

#include <string>
#include <memory>
#include <vector>

class ChatRoom;

class Person {
    std::string name;
    std::weak_ptr<ChatRoom> room;
    std::vector<std::string> chat_log;
public:
    Person(const std::string &name);

    bool operator==(const Person &rhs) const;
    bool operator!=(const Person &rhs) const;

    const std::string& get_name() const;
    void set_room(std::weak_ptr<ChatRoom> room);

    void say(const std::string& message) const;
    void private_message(const std::string& who,
                         const std::string& message) const;
    void receive(const std::string& origin,
                 const std::string& message) const;
};