// Q2: returning a reference to a LOCAL variable (undefined behaviour). Compile with -Wall to see the warning.
#include <iostream>
int& bad() { int local = 42; return local; }          // warning: reference to local variable returned
int main() {
    int& r = bad();                                   // r refers to a dead stack slot
    std::cout << "value through dangling reference: " << r << '\n';   // UB: may print 42, garbage or crash
}
