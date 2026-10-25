#include <iomanip>
#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr int BASE_PAISE[]={1000,2000,3000}; constexpr int PEAK_SURCHARGE_PERCENT=20; constexpr long long MIN_BALANCE_PAISE=5000;
long long fare(Zone z,bool peak){int base=0; switch(z){case Zone::Inner:base=BASE_PAISE[0];break;case Zone::Middle:base=BASE_PAISE[1];break;case Zone::Outer:base=BASE_PAISE[2];break;} if(peak)base=base*(100+PEAK_SURCHARGE_PERCENT)/100;return base;}
bool canTravel(long long balance,long long f){return f>=0 && balance-f>=MIN_BALANCE_PAISE;}
int main(){long long balance=10000; struct Trip{Zone zone;bool peak;};Trip trips[]={{Zone::Inner,false},{Zone::Outer,true},{Zone::Middle,false}};for(const Trip&t:trips){long long f=fare(t.zone,t.peak);if(canTravel(balance,f)){balance-=f;std::cout<<"Fare Rs "<<f/100<<'.'<<std::setw(2)<<std::setfill('0')<<f%100<<std::setfill(' ');}else std::cout<<"Denied (low balance)";std::cout<<" balance Rs "<<balance/100<<'\n';}}
