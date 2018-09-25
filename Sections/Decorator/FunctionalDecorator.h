#pragma once

#include <string>
#include <functional>
#include <iostream>

class Logger {
    std::function<void()> func;
    std::string name;
public:
    Logger(const std::function<void()> &func, const std::string &name)
        : func{func}, name{name} {}

    void operator()() const {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

template <typename Func>
class Logger2 { // Template Logger.
    Func func;
    std::string name;
public:
    Logger2(const Func &func, const std::string &name)
            : func{func}, name{name} {}

    void operator()() const {
        std::cout << "Entering " << name << std::endl;
        func();
        std::cout << "Exiting " << name << std::endl;
    }
};

// This helper function was created because the instructor's
// compiler wasn't able to infer Func for Logger2.
template <typename Func>
auto create_logger2(const Func &func, const std::string &name) {
    return Logger2<Func>(func, name);
}

// Logger1 and Logger2 only work when the function has no
// return type and accepts no arguments.
// Logger 3 has both. The return type is commonly denoted by R.
template <typename R, typename... Args>
class Logger3 {
    std::function<R(Args...)> func;
    std::string name;
public:
    Logger3(const std::function<R(Args...)> &func, const std::string &name)
        : func{func}, name{name} {}

    R operator()(Args... args) const  {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }
};

// This won't work with lambdas or function objects / functors.
template <typename R, typename... Args>
auto create_logger3(R (*func)(Args...), const std::string &name) {
    return Logger3<R, Args...>(func, name);
}