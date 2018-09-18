#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <gtest/gtest.h>

class Database {
public:
    virtual int get_population(const std::string &name) const = 0;
};

class SingletonDatabase : Database {
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

    int get_population(const std::string &name) const override {
        return capitals.at(name);
    }
};

class DummyDatabase : public Database {
    std::map<std::string, int> capitals;
public:
    DummyDatabase() {
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }
    int get_population(const std::string &name) const override {
        return capitals.at(name);
    }
};

// Bad code: tightly coupled with SingletonDatabase and can't easily be
// tested with a custom data set. The database being accessed might
// change at anytime which will make this test fail.
class SingletonRecordFinder {
public:
    int total_population(const std::vector<std::string> &names) {
        auto &db = SingletonDatabase::get();
        int count {};
        for(const auto &city: names) {
            count += db.get_population(city);
        }
        return count;
    }
};

// Good code: supports dependency injection which makes it easier to test.
class ConfigurableRecordFinder {
    Database &db;
public:
    ConfigurableRecordFinder(Database &db)
        : db{db} {}

    int total_population(const std::vector<std::string> &names) {
        int count {};
        for(const auto &city: names) {
            count += db.get_population(city);
        }
        return count;
    }
};

// This is an integration test because it's testing multiple facets
// of the program at once, i.e. SingletonRecordFinder with a live
// database.
TEST(RecordFinderTests, SingletonTotalPopulationTest) {
    SingletonRecordFinder rf;
    std::vector<std::string> names{"Seoul", "Mexico City"};
    int total = rf.total_population(names);
    EXPECT_EQ(17500000+17400000, total);
}

// This is a unit test because it's testing a small section of the code.
TEST(RecordFinderTests, DependantTotalPopulationTest) {
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};
    EXPECT_EQ(3, rf.total_population({"alpha", "beta"}));
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

/*
Challenge: Is factory returning singletons?
struct SingletonTester {
    template <typename T>
    bool is_singleton(function<T*()> factory) {
        T* inst1 = factory();
        T* inst2 = factory();
        return inst1 == inst2;
    }
};
 */