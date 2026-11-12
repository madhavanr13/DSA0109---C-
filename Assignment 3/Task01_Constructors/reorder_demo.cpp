#include <iostream>
struct OrderDemo {
    int first;
    int second;
    OrderDemo() : second(2), first(second + 1) { std::cout << first << ' ' << second << '\n'; }
};
int main(){ OrderDemo x; (void)x; }
