#include <array>
#include <iostream>
#include <string>
enum class Zone:std::size_t{Inner,Middle,Outer,Airport,Count};
constexpr std::array<long long,static_cast<std::size_t>(Zone::Count)> BASE{1000,2000,3000,6000};
long long fare(Zone z,int hour,bool weekend){long long f=BASE.at(static_cast<std::size_t>(z));bool peak=(hour>=8&&hour<10)||(hour>=17&&hour<20);if(weekend)f=f*90/100;else if(peak)f=f*120/100;return f;}
class MonthlyPass{Zone first_,second_;public:MonthlyPass(Zone a,Zone b):first_(a),second_(b){}bool covers(Zone z)const{return z==first_||z==second_;}};
int main(){std::cout<<"Airport weekday off-peak: "<<fare(Zone::Airport,12,false)<<" paise\n";std::cout<<"Airport weekday peak: "<<fare(Zone::Airport,18,false)<<" paise\n";std::cout<<"Airport weekend peak-hour (weekend discount only): "<<fare(Zone::Airport,18,true)<<" paise\n";MonthlyPass pass(Zone::Inner,Zone::Airport);std::cout<<"Pass covers Inner: "<<pass.covers(Zone::Inner)<<"; Middle: "<<pass.covers(Zone::Middle)<<"; Airport: "<<pass.covers(Zone::Airport)<<'\n';}
