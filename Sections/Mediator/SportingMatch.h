#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <functional>

template <typename>
class Signal;

template <typename R, typename...Args>
class Signal<R(Args...)> {
    using types = R(Args...); // TODO: Not using return type. Remove?
    std::vector<std::function<types>> funcs;
public:
    void operator()(const Args&...args) {
        for(const auto& func : funcs) {
            func(args...);
        }
    }

    void connect(const std::function<types>& func) {
        funcs.push_back(func);
    }
};

class EventData {
public:
    virtual void print() const = 0;
};

class PlayerScoredData : public EventData {
    std::string player_name;
    int goals_scored {};
public:
    PlayerScoredData(const std::string& player_name, int goals_scored)
    : player_name(player_name), goals_scored(goals_scored) {

    }

    const std::string &get_name() const {
        return player_name;
    }
    int get_goals() const {
        return goals_scored;
    }

    void print() const override {
        std::cout << player_name << " has scored " << goals_scored << " goals." << std::endl;
    }
};

// Mediator that ties different components together with 'event handling'/'observer pattern'.
class Game {
public:
    Signal<void(std::shared_ptr<EventData>)> events;
};

class Player {
    std::string name;
    int goals_scored{};
    std::shared_ptr<Game> game;
public:
    Player(const std::string& name, std::shared_ptr<Game> game)
    : name(name), game(game) {}

    void score() {
        ++goals_scored;
        auto data = std::make_shared<PlayerScoredData>(name, goals_scored);
        game->events(data); // Signals that an event has occurred.
    }
};

class Coach {
    std::shared_ptr<Game> game;
public:
    Coach(std::shared_ptr<Game> game) : game(game) {
        auto fp = std::bind(&Coach::player_scored, *this, std::placeholders::_1);
        game->events.connect(fp);
    }

    void player_scored(std::shared_ptr<EventData> event_data) {
        auto player_data = std::dynamic_pointer_cast<PlayerScoredData>(event_data);
        if(player_data && player_data->get_goals() == 3) {
            std::cout << "Coach: well done " << player_data->get_name()
                      << ". You scored a hat-trick." << std::endl;
        }
    }
};