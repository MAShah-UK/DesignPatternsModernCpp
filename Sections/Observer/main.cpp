#include <iostream>
#include "Observable.h"
#include "Observer.h"

class Person : public Observable<Person> { // Observable.
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const {
        return age;
    }
    void set_age(int age) {
        if(Person::age == age) {
            return;
        }
        Person::age = age;
        notify(*this, "age");
    }
};

class ConsolePersonObserver : public Observer<Person> {
    void field_changed(Person& source, const std::string& field_name) override {
        std::cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") {
            std::cout << source.get_age();
        }
        std::cout << std::endl;
    }
public:
};

int main() {
    Person person(10);
    auto cpo = std::make_shared<ConsolePersonObserver>();
    person.subscribe(cpo);
    person.set_age(11);
    person.set_age(12);
    person.unsubscribe(cpo);
    person.set_age(13);

    return 0;
}