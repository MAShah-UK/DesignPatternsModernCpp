#include <iostream>
#include "User.h"

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
              << "FWUser 2: " << fwUser2.get_name() << std::endl;
}

int main() {
    create_users();

    return 0;
}