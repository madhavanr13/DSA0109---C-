#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_PAISE[] = {1000,2000,3000};
constexpr int PEAK_SURCHARGE_PERCENT=20;
constexpr long long MIN_BALANCE_PAISE=5000;
int main(){Zone z=Zone::Outer; auto base=BASE_PAISE[static_cast<int>(z)]; std::cout<<"Outer base fare: "<<base<<" paise; peak surcharge: "<<PEAK_SURCHARGE_PERCENT<<"%; minimum balance: "<<MIN_BALANCE_PAISE<<" paise\n";}
