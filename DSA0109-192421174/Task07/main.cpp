#include <iostream>
// Procedural version
bool procCanTravel(long long balance,long long fare){return fare>=0&&balance-fare>=5000;}
bool procDeduct(long long& balance,long long fare){if(!procCanTravel(balance,fare))return false;balance-=fare;return true;}
class SmartCard{long long balance_;public:explicit SmartCard(long long b):balance_(b){}bool canTravel(long long f)const{return f>=0&&balance_-f>=5000;}bool deduct(long long f){if(!canTravel(f))return false;balance_-=f;return true;}long long balance()const{return balance_;}};
int main(){long long balance=10000;std::cout<<"Procedural accepted: "<<procDeduct(balance,3000)<<", balance="<<balance<<'\n';SmartCard card(10000);std::cout<<"OOP accepted: "<<card.deduct(3000)<<", balance="<<card.balance()<<'\n';std::cout<<"Oversized fare rejected: "<<(!card.deduct(6000))<<", balance="<<card.balance()<<'\n';}
