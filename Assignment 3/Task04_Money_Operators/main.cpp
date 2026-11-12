#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Money {
    long long paise;
public:
    Money(long long rupees=0,int p=0) : paise(rupees*100+p) {}
    explicit Money(long long totalPaise, bool raw) : paise(raw?totalPaise:totalPaise*100) {}
    Money operator+(const Money& rhs) const { return Money(paise+rhs.paise,true); }
    Money operator-(const Money& rhs) const { return Money(paise-rhs.paise,true); }
    Money& operator+=(const Money& rhs) { paise+=rhs.paise; return *this; }
    bool operator==(const Money& rhs) const { return paise==rhs.paise; }
    bool operator<(const Money& rhs) const { return paise<rhs.paise; }
    friend std::ostream& operator<<(std::ostream& os,const Money& m) {
        long long a=m.paise<0?-m.paise:m.paise;
        if(m.paise<0) os<<"-";
        return os<<"Rs "<<a/100<<'.'<<std::setw(2)<<std::setfill('0')<<a%100<<std::setfill(' ');
    }
    friend std::istream& operator>>(std::istream& is,Money& m) { long long r; int p; if(is>>r>>p) m.paise=r*100+p; return is; }
};
int main() {
    Money a(120,75),b(79,25); Money c=a+b;
    std::cout<<c<<'\n'<<std::boolalpha<<(c==Money(200))<<'\n';
    Money carry=Money(0,75)+Money(0,50); std::cout<<carry<<'\n';
    Money negative=Money(2)-Money(5); std::cout<<negative<<'\n';
    Money total; total+=a; total+=b; std::cout<<"bill="<<total<<'\n';
}
