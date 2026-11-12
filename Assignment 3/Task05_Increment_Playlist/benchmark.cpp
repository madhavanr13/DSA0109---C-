#include <chrono>
#include <iostream>
struct Counter { long long v=0; __attribute__((noinline)) Counter& operator++(){++v;return *this;} __attribute__((noinline)) Counter operator++(int){Counter old=*this;++v;return old;} };
int main(){
    constexpr int N=10000000; volatile long long sink=0;
    Counter p; auto a=std::chrono::steady_clock::now(); for(int i=0;i<N;++i) ++p; auto b=std::chrono::steady_clock::now(); sink=p.v;
    Counter q; auto c=std::chrono::steady_clock::now(); for(int i=0;i<N;++i) q++; auto d=std::chrono::steady_clock::now(); sink+=q.v;
    std::cout<<"prefix_us="<<std::chrono::duration_cast<std::chrono::microseconds>(b-a).count()<<" postfix_us="<<std::chrono::duration_cast<std::chrono::microseconds>(d-c).count()<<" sink="<<sink<<'\n';
}
