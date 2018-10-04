#include <iostream>
#include <vector>

class BankAccount {
    int balance{};
    int overdraft_limit{-500};
public:
    void deposit(int amount) {
        balance += amount;
        std::cout << "Deposited: " << amount
                    << ", balance is: " << balance << std::endl;
    }
    bool withdraw(int amount) {
        if(balance-amount >= overdraft_limit) {
            balance -= amount;
            std::cout << "Withdrew: " << amount
                        << ", balance is: " << balance << std::endl;
            return true;
        }
        return false;
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void call() = 0;
    virtual void undo() = 0;
};

class BankAccountCommand : public Command {
    BankAccount& account;
    int amount;
    bool succeeded;
public:
    enum class Action {deposit, withdraw} action;

    BankAccountCommand(BankAccount &account, Action action, int amount)
        : account(account), action(action), amount(amount) {}

    bool get_succeeded() const {
        return succeeded;
    }
    void set_succeeded(bool succeeded) {
        this->succeeded = succeeded;
    }

    void call() override {
        switch(action) {
            case Action::deposit: {
                account.deposit(amount);
                succeeded = true;
                break;
            }
            case Action::withdraw: {
                succeeded = account.withdraw(amount);
                break;
            }
        }
    }
    void undo() override {
        if(!succeeded) {
            return;
        }
        switch(action) {
            case Action::deposit: {
                account.withdraw(amount);
            }
            case Action::withdraw: {
                account.deposit(amount);
            }
        }
    }
};

class CompositeBankAccountCommand : public Command {
    std::vector<BankAccountCommand> commands;
public:
    CompositeBankAccountCommand(std::initializer_list<BankAccountCommand> commands)
        : commands{commands} {}

    auto& get_commands() {
        return commands;
    }

    void call() override {
        for(BankAccountCommand& command : commands) {
            command.call();
        }
    }
    void undo() override {
        for(auto it{commands.rbegin()}; it != commands.rend(); ++it) {
            for(auto it = commands.rbegin(); it != commands.rend(); ++it) {
                it->undo();
            }
        }
    }
};

class DependantCompositeCommand : public CompositeBankAccountCommand {
public:
    DependantCompositeCommand(const std::initializer_list<BankAccountCommand> &commands)
        : CompositeBankAccountCommand(commands) {}

    void call() override {
        bool ok{true};
        for(auto& command : get_commands()) {
            if(ok) {
                command.call();
                ok = command.get_succeeded();
            } else {
                command.set_succeeded(false);
            }
        }
    }
};

class MoneyTransferCommand : public DependantCompositeCommand {
public:
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
        : DependantCompositeCommand{{from, BankAccountCommand::Action::withdraw, amount},
                                    {to, BankAccountCommand::Action::deposit, amount}} {}
};

void process_transactions() {
    BankAccount account;
    std::vector<BankAccountCommand> commands {
            {account, BankAccountCommand::Action::deposit, 100},
            {account, BankAccountCommand::Action::withdraw, 200}
    };
    for(BankAccountCommand& command : commands) {
        command.call();
    }
    for(auto it = commands.rbegin(); it != commands.rend(); ++it) {
        it->undo();
    }
    std::cout << std::endl;
}

void bank_transfer() {
    BankAccount account1, account2;
    account1.deposit(100);
    MoneyTransferCommand cmd{account1, account2, 50};
    cmd.call();
    cmd.undo();
}

int main() {
    process_transactions();
    bank_transfer();

    return 0;
}