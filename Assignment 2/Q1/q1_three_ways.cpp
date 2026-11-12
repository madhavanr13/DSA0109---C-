// Q1: Hostel fee concession - value / reference / pointer / return-new-value, plus cost of copying.
#include <iostream>
#include <chrono>
#include <cstring>

struct Student {                 // a "large" object, to compare copy cost
    char name[32];
    long long fee;
    char notes[4096];
};

// 1. By value  -> parameter is a local copy on the callee's stack
void concessionValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    std::cout << "  inside (value)    : " << fee << '\n';   // looks right here ...
}
// 2. By reference -> parameter is an alias (usually implemented as a hidden address)
void concessionRef(long long& fee, int percent) { fee -= fee * percent / 100; }
// 3. By pointer -> parameter is a local variable holding the caller's address
void concessionPtr(long long* fee, int percent) { if (fee) *fee -= *fee * percent / 100; }
// 4. Return the new fee (pure function) - best for chaining several concessions
long long concessionReturn(long long fee, int percent) { return fee - fee * percent / 100; }

// copy-cost test functions (noinline so the optimiser cannot remove the copy)
__attribute__((noinline)) long long readByValue(Student s)        { return s.fee; }
__attribute__((noinline)) long long readByCref (const Student& s) { return s.fee; }

int main() {
    const int MERIT = 10, SPORTS = 15, SINGLE_PARENT = 25;
    long long f1 = 45000, f2 = 45000, f3 = 45000;

    concessionValue(f1, MERIT);
    concessionRef(f2, MERIT);
    concessionPtr(&f3, MERIT);
    std::cout << "stored fee after value   : " << f1 << '\n';
    std::cout << "stored fee after ref     : " << f2 << '\n';
    std::cout << "stored fee after pointer : " << f3 << '\n';

    // Design decision: several concessions -> return new fee, compose calls
    long long fee = 45000;
    long long stepwise = concessionReturn(concessionReturn(concessionReturn(fee, MERIT), SPORTS), SINGLE_PARENT);
    std::cout << "merit+sports+single-parent (chained, returned) : " << stepwise << '\n';
    long long inplace = 45000;
    concessionRef(inplace, MERIT); concessionRef(inplace, SPORTS); concessionRef(inplace, SINGLE_PARENT);
    std::cout << "same chain, in place via reference              : " << inplace << '\n';

    // Cost of passing a large object
    std::cout << "sizeof(long long) = " << sizeof(long long) << ", sizeof(Student) = " << sizeof(Student) << " bytes\n";
    Student st{}; std::strcpy(st.name, "Asha");
    const int N = 1000000;
    long long sink = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { st.fee = i; sink += readByValue(st); }
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { st.fee = i; sink += readByCref(st); }
    auto t2 = std::chrono::steady_clock::now();
    using ms = std::chrono::duration<double, std::milli>;
    std::cout << N << " calls by value      : " << ms(t1 - t0).count() << " ms\n";
    std::cout << N << " calls by const ref  : " << ms(t2 - t1).count() << " ms\n";
    std::cout << "(checksum " << sink << ")\n";
}
