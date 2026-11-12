// Q3: redesigned courier charge calculator - no ambiguity
#include <iostream>
#include <iomanip>

struct Parcel { double kg; bool express = false; bool insured = false; };

const double RATE_PER_KG = 50.0, EXPRESS_FEE = 30.0, INSURANCE_FEE = 20.0;

double charge(int grams, bool express = false, bool insured = false) {            // weight in grams (int)
    std::cout << "[grams]  ";
    return grams * (RATE_PER_KG / 1000.0) + (express ? EXPRESS_FEE : 0) + (insured ? INSURANCE_FEE : 0);
}
double charge(double kg, bool express = false, bool insured = false) {            // weight in kg (double)
    std::cout << "[kg]     ";
    return kg * RATE_PER_KG + (express ? EXPRESS_FEE : 0) + (insured ? INSURANCE_FEE : 0);
}
double charge(const Parcel& p) {                                                   // whole Parcel object
    std::cout << "[parcel] ";
    return p.kg * RATE_PER_KG + (p.express ? EXPRESS_FEE : 0) + (p.insured ? INSURANCE_FEE : 0);
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    Parcel p{1.2, true, false};
    std::cout << "charge(2500)          = " << charge(2500)          << '\n';
    std::cout << "charge(2)             = " << charge(2)             << '\n';
    std::cout << "charge(2.0f)          = " << charge(2.0f)          << '\n';
    std::cout << "charge(2.5)           = " << charge(2.5)           << '\n';
    std::cout << "charge(2.5,true,true) = " << charge(2.5, true, true) << '\n';
    std::cout << "charge(parcel)        = " << charge(p)             << '\n';
    // extra checks
    std::cout << "charge(2, true)       = " << charge(2, true)       << '\n';
    std::cout << "charge(2L) would be ambiguous (long->int vs long->double): not used\n";
}
