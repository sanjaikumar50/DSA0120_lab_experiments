#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; } // Non-virtual: static binding
    virtual double virtualRate() const { return 3.5; }
    virtual ~Account() = default;
};

class SeniorAccount : public Account {
private:
    double* history;

public:
    SeniorAccount() : history(new double[100]{}) {}
    ~SeniorAccount() override { delete[] history; }

    double rate() const { return 4.0; } // Hides Account::rate()
    double virtualRate() const override { return 4.0; }
};

int main() {
    SeniorAccount senior;
    Account* ptr = &senior;

    // Demonstrates non-virtual binding, virtual dispatch and slicing.
    Account slicedCopy = senior;

    std::cout << ptr->rate() << ' '
              << ptr->virtualRate() << ' '
              << slicedCopy.virtualRate() << '\n';

    // Correct polymorphic storage and automatic memory management.
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());

    std::cout << "Rates stored polymorphically:\n";
    for (const auto& account : accounts) {
        std::cout << account->virtualRate() << '\n';
    }

    return 0;
}
