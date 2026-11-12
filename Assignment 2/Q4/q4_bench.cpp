// Q4/Q7: cost per transaction, shifting array vs circular index, as the history size K grows
#include <iostream>
#include <chrono>
#include <cstdlib>
struct Txn { char type; long long amount; };
template <int K> struct Shift {
    Txn* tx = new Txn[K]; int count = 0;
    ~Shift() { delete[] tx; }
    void add(char t, long long a) { if (count == K) { for (int i = 1; i < K; ++i) tx[i-1] = tx[i]; --count; } tx[count++] = {t, a}; }
    long long checksum() const { long long s = 0; for (int i = 0; i < count; ++i) s = s * 31 + tx[i].amount; return s; }
};
template <int K> struct Circ {
    Txn* tx = new Txn[K]; int count = 0, start = 0;
    ~Circ() { delete[] tx; }
    void add(char t, long long a) { if (count < K) { tx[(start+count)%K] = {t,a}; ++count; } else { tx[start] = {t,a}; start = (start+1)%K; } }
    long long checksum() const { long long s = 0; for (int i = 0; i < count; ++i) s = s * 31 + tx[(start+i)%K].amount; return s; }
};
template <int K> void run(int ops) {
    using ms = std::chrono::duration<double, std::milli>;
    Shift<K> s; Circ<K> c;
    auto t0 = std::chrono::steady_clock::now(); for (int i = 0; i < ops; ++i) s.add('D', i);
    auto t1 = std::chrono::steady_clock::now(); for (int i = 0; i < ops; ++i) c.add('D', i);
    auto t2 = std::chrono::steady_clock::now();
    double a = ms(t1 - t0).count(), b = ms(t2 - t1).count();
    std::cout << "K=" << K << "\tshift " << a << " ms\tcircular " << b << " ms\tspeed-up x" << (b > 0 ? a / b : 0)
              << "\tns/add shift " << a * 1e6 / ops << " circ " << b * 1e6 / ops
              << "\tsame statement: " << (s.checksum() == c.checksum() ? "yes" : "NO") << '\n';
}
int main() {
    const int OPS = 200000;
    run<10>(OPS); run<50>(OPS); run<100>(OPS); run<1000>(OPS); run<10000>(OPS);
}
