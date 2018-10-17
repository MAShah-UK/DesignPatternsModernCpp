#pragma once

#include <ostream>
#include <vector>
#include <memory>

// Memento represents a snapshot of an object at a certain point in time.
// It should be immutable as a snapshot by definition shouldn't be changed.
// The problem with this approach is that the bank account's initial state
// can't be stored as it can't return a memento.
class Memento {
    const int balance{};
public:
    Memento(int balance) : balance(balance) {}

    int get_balance() const {
        return balance;
    }
};

class BankAccount {
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Balance: " << account.balance;
        return os;
    }

    int balance{};
public:
    BankAccount(int balance) : balance(balance) {}

    Memento deposit(int amount) {
        balance += amount;
        return {balance};
    }

    void restore(const Memento& memento) {
        balance = memento.get_balance();
    }
};

class BankAccount2 {
    friend std::ostream& operator<<(std::ostream& os, const BankAccount2& account) {
        os << "Balance: " << account.balance;
        return os;
    }

    int balance{};
    std::vector<std::shared_ptr<Memento>> changes;
    size_t current_memento_idx;

    std::shared_ptr<Memento> add_memento() {
        auto memento = std::make_shared<Memento>(balance);
        changes.push_back(memento);
        ++current_memento_idx;
        return memento;
    }
public:
    BankAccount2(int balance) : balance(balance) {
        changes.emplace_back(std::make_shared<Memento>(balance));
        current_memento_idx = 0;
    }

    void restore(const std::shared_ptr<Memento>& memento) {
        if(memento) {
            balance = memento->get_balance();
            changes.push_back(memento);
            current_memento_idx = changes.size()-1;
        }
    }
    std::shared_ptr<Memento> undo() {
        if(current_memento_idx > 0) {
            --current_memento_idx;
            auto memento = changes[current_memento_idx];
            balance = memento->get_balance();
            return memento;
        }
        return {};
    }
    std::shared_ptr<Memento> redo() {
        if(current_memento_idx + 1 < changes.size()) {
            ++current_memento_idx;
            auto memento = changes[current_memento_idx];
            balance = memento->get_balance();
            return memento;
        }
        return {};
    }

    std::shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        return add_memento();
    }
};