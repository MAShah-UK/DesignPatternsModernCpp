#include "ChatRoom.h"

void ChatRoom::broadcast(const std::string &origin, const std::string &message) {
    for(auto person : people) {
        if(*person != origin) {
            person->receive(origin, message);
        }
    }
}

void ChatRoom::join(std::shared_ptr<Person> person) {
    person->set_room(std::make_shared<ChatRoom>(this));
    std::string join_msg = person->get_name() + " joined the chat.";
    broadcast("room", join_msg);
}
