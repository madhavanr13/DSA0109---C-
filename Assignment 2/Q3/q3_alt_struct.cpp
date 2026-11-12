// Q3 alternative: ONE function taking a Parcel with optional fields (no overloads)
#include <iostream>
#include <iomanip>
struct Parcel { double kg = 0; bool express = false; bool insured = false; bool fragile = false; /* new option: add a field only */ };
double charge(const Parcel& p) {
    return p.kg * 50.0 + (p.express ? 30 : 0) + (p.insured ? 20 : 0) + (p.fragile ? 15 : 0);
}
int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << charge({2.5}) << ' ' << charge({2.5, true}) << ' ' << charge({.kg = 2.5, .express = true, .insured = true}) << ' '
              << charge({.kg = 1.0, .fragile = true}) << '\n';
}
