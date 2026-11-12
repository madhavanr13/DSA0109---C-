#include <iostream>
class BadPrescription {
    int* medicine;
public:
    BadPrescription():medicine(new int(7)){}
    ~BadPrescription(){ delete medicine; }
    int value() const { return *medicine; }
};
int main(){ BadPrescription original; { BadPrescription copy=original; std::cout<<copy.value()<<'\n'; } }
