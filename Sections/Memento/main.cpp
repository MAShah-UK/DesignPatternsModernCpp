#include <iostream>
#include "BankAccount.h"

void external_memento() {
    BankAccount ba{100};
    auto m1 = ba.deposit(50); // 150
    auto m2 = ba.deposit(25); // 175
    std::cout << ba << std::endl;

    ba.restore(m1);
    std::cout << "Back to m1: " << ba << std::endl;

    ba.restore(m2);
    std::cout << "Back to m2: " << ba << std::endl;
}

void stored_memento() {
    BankAccount2 ba{100};
    ba.deposit(50); // 150
    ba.deposit(25); // 175
    std::cout << "Current: " << ba << std::endl;

    ba.undo();
    std::cout << "Undo 1: " << ba << std::endl;

    ba.undo();
    std::cout << "Undo 2: " << ba << std::endl;

    ba.redo();
    std::cout << "Redo once: " << ba << std::endl;
}

int main() {
    external_memento();
    std::cout << std::endl;
    stored_memento();

    return 0;
}

/*
Challenge: use memento design pattern.
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token {
    int value;

    Token(int value) : value(value) {}
};

class Memento {
    const vector<shared_ptr<Token>> tokens;
public:
    Memento(const vector<shared_ptr<Token>>& tokens)
    : tokens(tokens) {}

    const vector<shared_ptr<Token>>& get_tokens() const {
        return tokens;
    }
};

struct TokenMachine {
    vector<shared_ptr<Token>> tokens;

    Memento add_token(int value) {
        return add_token(make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the
    // snapshot of the entire system
    Memento add_token(const shared_ptr<Token>& token) {
        tokens.push_back(make_shared<Token>(*token.get()));
        return {tokens};
    }

    // reverts the system to a state represented by the token
    void revert(const Memento& m) {
        tokens = m.get_tokens();
    }
};
 */