#pragma once

#include <string>

template <typename T>
class Observer {
public:
    virtual void field_changed(T& source, const std::string& field_name) = 0;
};