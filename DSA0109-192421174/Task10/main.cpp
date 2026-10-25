#include <climits>
#include <iomanip>
#include <iostream>
int main(){const long long journeys[]={20000,500000,3000000};const long long farePaise=3600;for(long long n:journeys){long long exact=farePaise*n;double approximate=36.0*static_cast<double>(n);std::cout<<n<<" journeys: exact paise="<<exact<<", double rupees="<<std::setprecision(17)<<approximate<<", int-safe="<<(exact<=INT_MAX?"yes":"NO")<<'\n';} }
