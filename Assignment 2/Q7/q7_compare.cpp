// Q7: Original (shifting array) vs Redesigned (circular index) - same tests, same measurements.
#include <iostream>
#include <chrono>
#include <random>
struct Txn { char type; long long amount; };
template <int K> struct Original {                 // Q4 design: shift on overflow, O(K)
    Txn* tx = new Txn[K]; int count = 0;
    ~Original() { delete[] tx; }
    void add(char t, long long a) { if (count == K) { for (int i = 1; i < K; ++i) tx[i-1] = tx[i]; --count; } tx[count++] = {t, a}; }
    Txn at(int i) const { return tx[i]; }  int size() const { return count; }
};
template <int K> struct Redesigned {               // circular buffer, O(1)
    Txn* tx = new Txn[K]; int count = 0, start = 0;
    ~Redesigned() { delete[] tx; }
    void add(char t, long long a) { if (count < K) { tx[(start+count)%K] = {t,a}; ++count; } else { tx[start] = {t,a}; start = (start+1)%K; } }
    Txn at(int i) const { return tx[(start+i)%K]; }  int size() const { return count; }
};
template <int K> bool equivalent(int ops) {        // TEST 1: identical statement after every operation
    Original<K> o; Redesigned<K> r; std::mt19937 g(12345);
    for (int n = 0; n < ops; ++n) {
        char t = (g() & 1) ? 'D' : 'W'; long long a = g() % 1000 + 1;
        o.add(t, a); r.add(t, a);
        if (o.size() != r.size()) return false;
        for (int i = 0; i < o.size(); ++i) if (o.at(i).amount != r.at(i).amount || o.at(i).type != r.at(i).type) return false;
    }
    return true;
}
template <int K> void bench(int ops) {             // TEST 2: time per add
    using ms = std::chrono::duration<double, std::milli>;
    Original<K> o; Redesigned<K> r; 
    auto t0 = std::chrono::steady_clock::now(); for (int i = 0; i < ops; ++i) o.add('D', i);
    auto t1 = std::chrono::steady_clock::now(); for (int i = 0; i < ops; ++i) r.add('D', i);
    auto t2 = std::chrono::steady_clock::now();
    double a = ms(t1-t0).count(), b = ms(t2-t1).count();
    volatile long long sink = o.at(0).amount + r.at(0).amount; (void)sink;
    std::cout << "K=" << K << "\toriginal " << a * 1e6 / ops << " ns/add\tredesigned " << b * 1e6 / ops << " ns/add\tspeed-up x" << a / b
              << "\tmemory both = " << K * sizeof(Txn) << " B + " << (sizeof(Original<K>)) << "/" << sizeof(Redesigned<K>) << " B object\n";
}
int main() {
    std::cout << "equivalence K=10:   " << (equivalent<10>(5000)   ? "PASS" : "FAIL") << '\n';
    std::cout << "equivalence K=50:   " << (equivalent<50>(5000)   ? "PASS" : "FAIL") << '\n';
    std::cout << "equivalence K=1000: " << (equivalent<1000>(5000) ? "PASS" : "FAIL") << '\n';
    const int OPS = 200000;
    bench<10>(OPS); bench<50>(OPS); bench<100>(OPS); bench<1000>(OPS); bench<10000>(OPS);
}
