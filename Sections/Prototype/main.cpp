#include <iostream>
#include <memory>

struct Address {
    friend std::ostream &operator<<(std::ostream &os, const Address &address) {
        os << "Address: " << address.suite << ", " << address.street << ", "
           << address.city;
        return os;
    }

    int suite;
    std::string street, city;
};

struct Contact {
    friend std::ostream &operator<<(std::ostream &os, const Contact &contact) {
        os << "Name: " << contact.name << " " << contact.address;
        return os;
    }

    std::string name;
    Address address;
};

class EmployeeFactory {
    static std::unique_ptr<Contact> new_employee(const std::string &name,
                                                 int suite,
                                                 const Contact &prototype)
    {
        auto result = std::make_unique<Contact>(prototype);
        result->name = name;
        result->address.suite = suite;
        return result;
    }
public:
    static std::unique_ptr<Contact> new_main_office_employee
        (const std::string &name, int suite) {
        static Contact contact {"", Address {0, "123 East Dr", "London"}};
        return new_employee(name, suite, contact);
    }
};

int main() {
    Contact john{"John Doe", {123, "123 East Dr", "London"}};

    // Problem: Need to create a new contact that has similar state to an existing contact.
    // Solution 1: works, but contains repeated information.
    Contact jane1{"Jane Smith", {103, "123 East Dr", "London"}};
    // Solution 2: works, but creates an unnecessary copy of information.
    Contact jane2 = john;
    jane2.name = "Jane Smith";
    jane2.address.suite = 103;
    // Solution 3: could store the address as a pointer, but this will create a shallow
    // copy that changes information for all owners. Doesn't work.

    std::cout << john << std::endl
              << jane1 << std::endl
              << jane2 << std::endl;

    return 0;
}

/*
Challenge: Use prototype design pattern.
struct Point {
  int x{}, y{};

  Point() {}
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line {
    Point *start, *end;

    Line(Point* const start, Point* const end)
        : start(start), end(end) {

    }
    ~Line() {
        delete start;
        delete end;
    }

    Line deep_copy() const {
        return {new Point(*start), new Point(*end)};
    }
};
 */