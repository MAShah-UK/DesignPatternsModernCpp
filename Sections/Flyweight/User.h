#pragma once
#include <set>

// Stores user/player information for an MMORPG.
// Inefficient, because multiple users may have
// the same name. We will end up storing
// duplicate information in memory.
class BasicUser {
    std::string first_name, last_name;
public:
    BasicUser(const std::string &first_name, const std::string &last_name)
        : first_name{first_name}, last_name{last_name} {}

    std::string get_name() const {
        return first_name + " " + last_name;
    }
};

class FWUser { // FlyweightUser
    static std::set<std::string> names;
    decltype(names.begin()) first_name, last_name;
public:
    static auto unique_names() {
        return names.size();
    }

    static auto add_name(const std::string &name) {
        return names.insert(name).first;
    }

    FWUser(const std::string &first_name, const std::string &last_name)
            : first_name{add_name(first_name)},
              last_name{add_name(last_name)} {}

    std::string get_name() const {
        return *first_name + " " + *last_name;
    }
};

std::set<std::string> FWUser::names {};