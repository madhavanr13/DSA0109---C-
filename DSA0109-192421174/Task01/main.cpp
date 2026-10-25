#include <iostream>
#include <string>
class SmartCard { long long balance_; public: explicit SmartCard(long long p):balance_(p){} bool canTravel(long long fare,long long minimum=5000) const { return balance_-fare>=minimum; } bool deduct(long long fare,long long minimum=5000){if(fare<0||!canTravel(fare,minimum))return false; balance_-=fare;return true;} long long balance()const{return balance_;}};
struct Passenger { std::string name; bool student=false; bool senior=false; };
struct Journey { int fromZone; int toZone; int hour; };
int main(){SmartCard card(10000); Journey j{1,3,18}; long long fare=3000+(j.hour>=17&&j.hour<20?600:0); std::cout<<"Journey fare (paise): "<<fare<<"\n"<<(card.deduct(fare)?"Accepted":"Denied")<<"; balance (paise): "<<card.balance()<<'\n';}
