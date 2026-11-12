#include <iostream>
class Time {
 int h, m;
public:
 Time(int hh, int mm) : h(hh), m(mm) {}
 friend int minutesBetween(const Time& a, const Time& b);
 friend bool earlier(const Time& a, const Time& b);
};
int minutesBetween(const Time& a, const Time& b)
{
 // TODO 1 (done): absolute difference in minutes using the private members
 int ta = a.h * 60 + a.m, tb = b.h * 60 + b.m;
 return ta > tb ? ta - tb : tb - ta;
}
bool earlier(const Time& a, const Time& b)
{ // TODO 2 (done): true if a is earlier in the day than b
 return a.h * 60 + a.m < b.h * 60 + b.m;
}

static int fails = 0;
void check(const char* name, bool ok) { std::cout << (ok ? "PASS " : "FAIL ") << name << '\n'; if (!ok) ++fails; }
int main()
{
 Time dep(9,45), arr(13,10), a1(11,50), a2(12,10), noon(12,0), mid(0,0), last(23,59);
 check("9:45 -> 13:10 = 205", minutesBetween(dep, arr) == 205);
 check("order does not matter (abs)", minutesBetween(arr, dep) == 205);
 check("11:50 -> 12:10 (across noon) = 20", minutesBetween(a1, a2) == 20);
 check("same time twice = 0", minutesBetween(dep, Time(9,45)) == 0);
 check("same time: earlier() false both ways", !earlier(dep, Time(9,45)) && !earlier(Time(9,45), dep));
 check("11:50 earlier than 12:10", earlier(a1, a2) && !earlier(a2, a1));
 check("12:00 vs 0:00 = 720", minutesBetween(noon, mid) == 720);
 check("0:00 -> 23:59 = 1439", minutesBetween(mid, last) == 1439);
 check("0:00 earlier than 23:59", earlier(mid, last));
 std::cout << (fails ? "SOME TESTS FAILED\n" : "ALL TESTS PASSED\n");
 return fails;
}
