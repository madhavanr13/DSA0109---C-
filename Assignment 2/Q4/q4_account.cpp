// Q4: SavingsAccount with a mini-statement of the last N transactions.
//  - SavingsAccount      : circular index  (O(1) per transaction)  <- final design
//  - SavingsAccountShift : shifting array  (O(N) per transaction)  <- for comparison
#include <iostream>
#include <iomanip>

struct Txn { char type; long long amount; };       // 'D' deposit, 'W' withdrawal

class SavingsAccount {
    static constexpr int HISTORY = 10;             // <-- change to 50 and nothing else changes
    long accNo;
    long long balance;
    Txn tx[HISTORY];                               // private: only the class may keep it consistent
    int count;                                     // transactions currently stored (<= HISTORY)
    int start;                                     // index of the OLDEST stored transaction
    void record(char t, long long a);              // defined outside
public:
    SavingsAccount(long no, long long opening) : accNo(no), balance(opening), count(0), start(0) {}   // inside
    long long getBalance() const { return balance; }                                                 // inside
    void deposit(long long amt);                   // outside
    bool withdraw(long long amt);                  // outside
    void miniStatement() const;                    // outside
};
void SavingsAccount::record(char t, long long a) {
    if (count < HISTORY) { tx[(start + count) % HISTORY] = {t, a}; ++count; }
    else { tx[start] = {t, a}; start = (start + 1) % HISTORY; }          // overwrite oldest: O(1)
}
void SavingsAccount::deposit(long long amt) { if (amt <= 0) return; balance += amt; record('D', amt); }
bool SavingsAccount::withdraw(long long amt) {
    if (amt <= 0 || amt > balance) return false;
    balance -= amt; record('W', amt); return true;
}
void SavingsAccount::miniStatement() const {
    std::cout << "Account " << accNo << "  (last " << count << " transactions, oldest first)\n";
    for (int i = 0; i < count; ++i) {
        const Txn& t = tx[(start + i) % HISTORY];
        std::cout << "  " << (t.type == 'D' ? "Deposit   " : "Withdrawal") << std::setw(8) << t.amount << '\n';
    }
    std::cout << "  Balance: " << balance << '\n';
}

class SavingsAccountShift {
    static constexpr int HISTORY = 10;
    long accNo; long long balance; Txn tx[HISTORY]; int count;
    void record(char t, long long a) {
        if (count == HISTORY) { for (int i = 1; i < HISTORY; ++i) tx[i - 1] = tx[i]; --count; }   // shift: O(N)
        tx[count++] = {t, a};
    }
public:
    SavingsAccountShift(long no, long long opening) : accNo(no), balance(opening), count(0) {}
    void deposit(long long amt) { balance += amt; record('D', amt); }
    void miniStatement() const {
        std::cout << "[shift] Account " << accNo << '\n';
        for (int i = 0; i < count; ++i) std::cout << "  " << tx[i].type << std::setw(8) << tx[i].amount << '\n';
    }
};

int main() {
    SavingsAccount a(1001, 5000);
    for (int i = 1; i <= 11; ++i) a.deposit(i * 100);        // 11 deposits: 100..1100, the first is discarded
    a.miniStatement();
    std::cout << "withdraw 99999 -> " << std::boolalpha << a.withdraw(99999) << " (refused, balance unchanged)\n";
    a.withdraw(250);
    a.miniStatement();
    SavingsAccountShift s(1002, 5000);
    for (int i = 1; i <= 11; ++i) s.deposit(i * 100);
    s.miniStatement();
}
