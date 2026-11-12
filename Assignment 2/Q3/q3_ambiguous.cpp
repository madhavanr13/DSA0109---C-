// Q3: the ORIGINAL developer design - does not compile (ambiguous calls)
#include <iostream>
double charge(double weight)                                   { return weight * 50; }
double charge(double weight, bool express)                     { return weight * 50 + (express ? 30 : 0); }
double charge(double weight, bool express = false, bool insured = false) { return weight * 50 + (express ? 30 : 0) + (insured ? 20 : 0); }
int main() {
    std::cout << charge(2.5) << '\n';          // ambiguous: (double) vs (double,bool=,bool=)
    std::cout << charge(2.5, true) << '\n';    // ambiguous: (double,bool) vs (double,bool,bool=)
}
