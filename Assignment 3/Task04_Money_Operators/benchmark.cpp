#include <chrono>
#include <iostream>
#if defined(__GNUC__)
__attribute__((noinline)) long long addPaise(long long a,long long b){return a+b;}
__attribute__((noinline)) double addDouble(double a,double b){return a+b;}
#endif
int main(){
    constexpr int N=1000000; volatile long long integerTotal=0; volatile double doubleTotal=0.0;
    auto a=std::chrono::steady_clock::now(); long long p=0; for(int i=0;i<N;++i)p=addPaise(p,75); integerTotal=p; auto b=std::chrono::steady_clock::now();
    auto c=std::chrono::steady_clock::now(); double dval=0; for(int i=0;i<N;++i)dval=addDouble(dval,0.75); doubleTotal=dval; auto d=std::chrono::steady_clock::now();
    std::cout<<"integer paise total="<<integerTotal<<" time_us="<<std::chrono::duration_cast<std::chrono::microseconds>(b-a).count()<<'\n';
    std::cout<<"double total="<<doubleTotal<<" time_us="<<std::chrono::duration_cast<std::chrono::microseconds>(d-c).count()<<'\n';
}
