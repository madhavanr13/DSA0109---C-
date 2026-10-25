#include <array>
#include <iostream>
enum class Zone{Inner,Middle,Outer};constexpr std::array<long long,3> FARE_PAISE{1000,2000,3000};
long long baseFare(Zone z){return FARE_PAISE.at(static_cast<std::size_t>(z));}
int main(){for(Zone z:{Zone::Inner,Zone::Middle,Zone::Outer})std::cout<<baseFare(z)<<' ';std::cout<<"paise; constant-time lookup per journey\n";}
