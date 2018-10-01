#pragma once

#include <string>

class Pingable {
public:
    virtual std::wstring ping(const std::wstring& message) = 0;
};

class Pong : public Pingable {
public:
    std::wstring ping(const std::wstring& message) override {
        return message + L" pong"; // Converts to wchar_t.
    }
};

class RemotePong : public Pingable {
public:
    std::wstring ping(const std::wstring& message) override {
        // ...
        // Simulate data being received from a remote network.
        // ...
        return L" remote-pong";
    }
};