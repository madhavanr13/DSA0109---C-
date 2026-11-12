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
int main()
{
 Time departure(9, 45), arrival(13, 10);
 std::cout << minutesBetween(departure, arrival) << ' '
 << std::boolalpha << earlier(arrival, departure) << '\n';
}
