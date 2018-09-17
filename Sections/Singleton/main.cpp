#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>

class SingletonDatabase {
    std::map<std::string, int> capitals;

    // Make constructor private so that only members can instantiate this class.
    SingletonDatabase() {
        // Simulate loading large data set from database.
        std::cout << "Initialised database... " << std::endl;
        std::ifstream source {"../capitals.txt"};
        std::string city, population_str;
        while(std::getline(source, city)) {
            getline(source, population_str);
            int population {std::stoi(population_str)};
            capitals[city] = population;
        }
    }
public:
    // Prevents copying the one instance of SingletonDatabase.
    SingletonDatabase(const SingletonDatabase &) = delete;
    SingletonDatabase &operator=(const SingletonDatabase &) = delete;

    static SingletonDatabase &get() {
        static SingletonDatabase db; // Creates one instance. Has access to constructor.
        return db; // Always returns the same instance.
    }

    int get_population(const std::string &name) {
        return capitals[name];
    }
public:

};

class SingletonRecordFinder {
public:
    int total_population(std::vector<std::string> names) {
        auto &db = SingletonDatabase::get();
        int count {};
        for(const auto &city: names) {
            count += db.get_population(city);
        }
        return count;
    }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest) {
    SingletonRecordFinder rf;
    std::vector<std::string> names{"Seoul", "Mexico City"};
    int total = rf.total_population(names);
    EXPECT_EQ(17500000+17400000, total);
}

int main(int argc, char* argv[]) {
    // SingletonDatabase create; // Error: Can't publicly access constructor.
    SingletonDatabase &db = SingletonDatabase::get();
    // SingletonDatabase copy = db; // Error: Can't copy object.
    std::cout << "The population of Tokyo is: " << db.get_population("Tokyo") << std::endl
              << "The population of New York is: " << db.get_population("New York") << std::endl;

    // Run unit tests.
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}