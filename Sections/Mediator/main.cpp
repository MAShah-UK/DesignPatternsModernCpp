#include <iostream>
#include "Chatroom.h"
#include "SportingMatch.h"

void create_chatroom() {
    // Can't create Chatroom in stack memory due to enable_shared_from_this<>.
    auto room = std::make_shared<Chatroom>();

    auto john = std::make_shared<Person>("John");
    auto jane = std::make_shared<Person>("Jane");
    room->join(john);
    room->join(jane);
    john->say("Hi, my name is John.");
    jane->say("Hi John, my name is Jane.");
    auto simon = std::make_shared<Person>("Simon");
    room->join(simon);
    simon->say("Hi everyone.");
    john->private_message("Simon", "Glad you found us.");
}

void score_goals() {
    auto game = std::make_shared<Game>();
    Player player("Sam", game);
    Coach coach(game);
    player.score();
    player.score();
    player.score();
}

int main() {
    create_chatroom();
    std::cout << std::endl;
    score_goals();

    return 0;
}

/*
Challenge: use mediator design pattern.
#include <vector>
using namespace std;

struct IParticipant {
    virtual ~IParticipant() = default;
    virtual void say(int) const = 0;
    virtual void receive(int) = 0;
};

struct Mediator {
    vector<IParticipant*> participants;

    void broadcast(const IParticipant* const origin, int value) {
        for(auto participant : participants) {
            if(participant != origin) {
                participant->receive(value);
            }
        }
    }
};

struct Participant : IParticipant {
    int value{0};
    Mediator& mediator;

    Participant(Mediator& mediator) : mediator(mediator) {
        mediator.participants.push_back(this);
    }

    void say(int value) const override {
        mediator.broadcast(this, value);
    }

    void receive(int value) {
        this->value += value;
    }
};
 */