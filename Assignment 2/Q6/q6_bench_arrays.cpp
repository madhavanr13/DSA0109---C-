// Q6 (second benchmark): same four variants, but the Time objects are pre-built in arrays so the loop measures only the call.
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    int hours() const { return h; }                       // getters (inline, defined in class)
    int mins()  const { return m; }
    int minutesTo(const Time& o) const { int x = h*60+m, y = o.h*60+o.m; return x > y ? x - y : y - x; }   // member
    friend inline int minutesInline(const Time& a, const Time& b) { int x=a.h*60+a.m,y=b.h*60+b.m; return x>y?x-y:y-x; }
    friend int minutesNoInline(const Time& a, const Time& b);
};
__attribute__((noinline)) int minutesNoInline(const Time& a, const Time& b) { int x=a.h*60+a.m,y=b.h*60+b.m; return x>y?x-y:y-x; }
inline int minutesGetters(const Time& a, const Time& b) { int x=a.hours()*60+a.mins(), y=b.hours()*60+b.mins(); return x>y?x-y:y-x; }

template <class F> double timeit(F f) {
    double best = 1e18;
    for (int r = 0; r < 5; ++r) {
        auto t0 = std::chrono::steady_clock::now();
        long long s = f();
        auto t1 = std::chrono::steady_clock::now();
        volatile long long sink = s; (void)sink;
        best = std::min(best, std::chrono::duration<double, std::milli>(t1 - t0).count());
    }
    return best;
}
int main() {
    const int PAIRS = 4000, REPS = 2500;          // 4000 * 2500 = 10,000,000 calls
    std::vector<Time> A, B;
    for (int i = 0; i < PAIRS; ++i) { A.emplace_back(i % 24, i % 60); B.emplace_back((i * 7) % 24, (i * 13) % 60); }
    auto loop = [&](auto fn) { return [&, fn]() { long long s = 0; for (int r = 0; r < REPS; ++r) for (int i = 0; i < PAIRS; ++i) s += fn(A[i], B[i]); return s; }; };
    std::cout << "calls: " << PAIRS * REPS << "  (pre-built arrays, best of 5 runs, ms)\n";
    std::cout << "friend, inline       : " << timeit(loop([](const Time& a, const Time& b){ return minutesInline(a, b); })) << '\n';
    std::cout << "friend, noinline     : " << timeit(loop([](const Time& a, const Time& b){ return minutesNoInline(a, b); })) << '\n';
    std::cout << "member minutesTo     : " << timeit(loop([](const Time& a, const Time& b){ return a.minutesTo(b); })) << '\n';
    std::cout << "public getters       : " << timeit(loop([](const Time& a, const Time& b){ return minutesGetters(a, b); })) << '\n';
}
