#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <variant>
#include <stdexcept>
struct VOP{double c,t;}; struct VIP{double rate;int days;double surgery;};
struct BillRecord{int type;double a,b;int days;};
volatile double sink=0;
double virtualTotal(const VOP&x){return x.c+x.t;} double virtualTotal(const VIP&x){return x.rate*x.days+x.surgery;}
double switchTotal(const BillRecord&x){switch(x.type){case 0:return x.a+x.b;default:return x.a*x.days+x.b;}}
using BillVariant=std::variant<VOP,VIP>;
double visitTotal(const BillVariant&v){return std::visit([](const auto&x)->double{using T=std::decay_t<decltype(x)>;if constexpr(std::is_same_v<T,VOP>)return x.c+x.t;else return x.rate*x.days+x.surgery;},v);}
template<class F> long long bench(F f,int n){auto s=std::chrono::steady_clock::now();double sum=0;for(int i=0;i<n;++i)sum+=f(i);sink=sum;return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-s).count();}
int main(){for(int n:{1000,1000000,10000000}){std::vector<BillRecord> a(n);std::vector<BillVariant> v;v.reserve(n);for(int i=0;i<n;++i){if(i%2){a[i]={1,2500,40000,3};v.emplace_back(VIP{2500,3,40000});}else{a[i]={0,500,1200,0};v.emplace_back(VOP{500,1200});}}auto sw=bench([&](int i){return switchTotal(a[i]);},n);auto va=bench([&](int i){return i%2?virtualTotal(VIP{2500,3,40000}):virtualTotal(VOP{500,1200});},n);auto vr=bench([&](int i){return visitTotal(v[i]);},n);std::cout<<n<<" bills: switch="<<sw<<"us variant="<<vr<<"us virtual-dispatch-proxy="<<va<<"us\n";}}
