#include <iostream>
#include "User.h"
#include "Flyweight.h"

void create_users() {
    // Inefficient - duplicates data in memory.
    BasicUser bUser1{"John", "Doe"};
    BasicUser bUser2{"Jane", "Doe"};
    std::cout << "Unique names: 4" << std::endl
              << "BasicUser 1: " << bUser1.get_name() << std::endl
              << "BasicUser 2: " << bUser2.get_name() << std::endl << std::endl;

    // Efficient - stores unique data in memory.
    FWUser fwUser1{"John", "Doe"};
    FWUser fwUser2{"Jane", "Doe"};
    std::cout << "Unique names: " << FWUser::unique_names() << std::endl
              << "FWUser 1: " << fwUser1.get_name() << std::endl
              << "FWUser 2: " << fwUser2.get_name() << std::endl << std::endl;
}

void use_flyweight() {
    Flyweight<std::string> name1{"John"}, name2{"Max"}, name3{"Linda"}, name4{"Max"};
    std::cout << "Four strings were added to flyweight: "
                << name1 << " " << name2 << " " << name3 << " " << name4 << std::endl
              << "Of these names, 3 should be unique: "
                << Flyweight<std::string>::unique_count() << std::endl;
    Flyweight<int> age1{15}, age2{20}, age3{15}, age4{20};
    std::cout << "Their ages are: " << age1 << " " << age2 << " " << age3
              << " " << age4 << std::endl
              << "Of these ages, 2 should be unique: " << Flyweight<int>::unique_count()
                << std::endl << std::endl;
}

int main() {
    create_users();
    use_flyweight();

    return 0;
}