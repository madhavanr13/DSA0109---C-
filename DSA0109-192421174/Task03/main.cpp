#include <climits>
#include <iostream>
#include <limits>
int main(){std::cout<<"sizeof(bool)="<<sizeof(bool)<<" sizeof(char)="<<sizeof(char)<<" sizeof(int)="<<sizeof(int)<<" sizeof(long long)="<<sizeof(long long)<<" sizeof(float)="<<sizeof(float)<<" sizeof(double)="<<sizeof(double)<<'\n'; long long perTrip=3600; long long trips=3000000; std::cout<<"Network collection (paise): "<<perTrip*trips<<"\nINT_MAX="<<INT_MAX<<"; LLONG_MAX="<<LLONG_MAX<<'\n'; double rupees=0; for(int i=0;i<3000000;++i) rupees+=0.1; std::cout.precision(17); std::cout<<"Adding Rs 0.10 three million times as double: "<<rupees<<" (expected 300000.0)\n";}
