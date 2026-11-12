#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex():re(0),im(0){}
    Complex(double r):re(r),im(0){}
    Complex(double r,double i):re(r),im(i){}
    Complex operator+(const Complex& z) const { return {re+z.re,im+z.im}; }
    Complex operator-(const Complex& z) const { return {re-z.re,im-z.im}; }
    Complex operator*(const Complex& z) const { return {re*z.re-im*z.im,re*z.im+im*z.re}; }
    Complex operator/(const Complex& z) const { double d=z.re*z.re+z.im*z.im; if(d==0.0) throw std::domain_error("division by zero impedance"); return {(re*z.re+im*z.im)/d,(im*z.re-re*z.im)/d}; }
    bool operator==(const Complex& z) const { return std::abs(re-z.re)<1e-9 && std::abs(im-z.im)<1e-9; }
    double magnitude() const { return std::hypot(re,im); }
    friend std::ostream& operator<<(std::ostream& os,const Complex& z) { os<<std::fixed<<std::setprecision(3)<<z.re<<(z.im<0?" - j":" + j")<<std::abs(z.im); return os; }
};
int main(){
    constexpr double pi=3.141592653589793; const double f=50.0,w=2*pi*f,L=0.1,C=100e-6;
    Complex resistor(10,0),inductor(0,w*L),capacitor(0,-1.0/(w*C));
    Complex series=resistor+inductor+capacitor;
    Complex z1=resistor+inductor,z2=capacitor;
    Complex parallel=(z1*z2)/(z1+z2);
    std::cout<<"Series RLC impedance: "<<series<<" |Z|="<<series.magnitude()<<'\n';
    std::cout<<"Parallel impedance: "<<parallel<<" |Z|="<<parallel.magnitude()<<'\n';
    try { Complex bad=series/Complex(); (void)bad; } catch(const std::domain_error& e) { std::cout<<"Safe error: "<<e.what()<<'\n'; }
}
