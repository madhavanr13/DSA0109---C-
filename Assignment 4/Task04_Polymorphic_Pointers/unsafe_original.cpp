#include <iostream>
class Account {
public:
    double rate() const { return 3.5; } // not virtual
    ~Account() { std::cout << "Account destructor\n"; } // not virtual
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    double rate() const { return 4.0; }
    ~SeniorAccount() { delete[] history; std::cout << "SeniorAccount destructor\n"; }
};
int main() {
    Account* accounts[2] = {new Account, new SeniorAccount};
    for (Account* a : accounts) std::cout << a->rate() << '\n';
    for (Account* a : accounts) delete a; // undefined behaviour: base destructor is not virtual
    Account copy = SeniorAccount(); // object slicing
    (void)copy;
}
