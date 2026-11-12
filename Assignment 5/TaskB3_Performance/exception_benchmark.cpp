#include <iostream>
#include <chrono>
#include <stdexcept>
#include <vector>
volatile long long sink2=0;
long long run(int n,int invalid,bool useExceptions){auto s=std::chrono::steady_clock::now();long long ok=0;for(int i=0;i<n;++i){bool bad=(i%100)<invalid;if(useExceptions){try{if(bad)throw std::invalid_argument("bad");++ok;}catch(const std::exception&){}}else{if(!bad)++ok;}}sink2=ok;return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-s).count();}
int main(){constexpr int n=1000000;for(int pct:{0,1,50})std::cout<<pct<<"% invalid: return-code="<<run(n,pct,false)<<"us exceptions="<<run(n,pct,true)<<"us\n";}
