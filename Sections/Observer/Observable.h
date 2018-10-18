#pragma once

#include <vector>
#include <memory>
#include <algorithm>

template <typename> class Observer;

template <typename T>
class Observable {
    std::vector<std::shared_ptr<Observer<T>>> observers;
public:
    void notify(T& source, const std::string& field_name) {
        for(auto& observer : observers) {
            observer->field_changed(source, field_name);
        }
    }
    void subscribe(const std::shared_ptr<Observer<T>>& observer) {
        observers.push_back(observer);
    }
    void unsubscribe(const std::shared_ptr<Observer<T>>& observer) {
        observers.erase(
                std::remove(observers.begin(), observers.end(), observer),
                observers.end());
    }
};