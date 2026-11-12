#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { std::cout << "Account destroyed\n"; }
};
class SeniorAccount : public Account {
    double* history_;
public:
    SeniorAccount() : history_(new double[100]{}) {}
    double rate() const override { return 4.0; }
    ~SeniorAccount() override {
        delete[] history_;
        std::cout << "SeniorAccount destroyed\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    for (const auto& account : accounts) std::cout << account->rate() << '\n';
    std::cout << "Slicing demonstration: Account copy = SeniorAccount() copies only Account base state.\n";
}
