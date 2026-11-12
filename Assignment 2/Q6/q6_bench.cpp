// Q6: 10,000,000 calls - friend inline / friend noinline / member / getters. Build with -O0 and -O2.
#include <iostream>
#include <chrono>
#include <algorithm>
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
    const int N = 10000000;
    auto loop = [&](auto fn) { return [=]() { long long s = 0; for (int i = 0; i < N; ++i) { Time a(i % 24, i % 60), b((i * 7) % 24, (i * 13) % 60); s += fn(a, b); } return s; }; };
    std::cout << "calls: " << N << "  (best of 5 runs, ms)\n";
    std::cout << "friend, inline       : " << timeit(loop([](const Time& a, const Time& b){ return minutesInline(a, b); })) << '\n';
    std::cout << "friend, noinline     : " << timeit(loop([](const Time& a, const Time& b){ return minutesNoInline(a, b); })) << '\n';
    std::cout << "member minutesTo     : " << timeit(loop([](const Time& a, const Time& b){ return a.minutesTo(b); })) << '\n';
    std::cout << "public getters       : " << timeit(loop([](const Time& a, const Time& b){ return minutesGetters(a, b); })) << '\n';
}
