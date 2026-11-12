#include <chrono>
#include <cstring>
#include <iostream>
#include <string>
class Text { char* p; public: Text():p(new char[1]{0}){} Text(const Text& x):p(new char[std::strlen(x.p)+1]){std::strcpy(p,x.p);} ~Text(){delete[] p;} Text& operator+=(const Text& x){auto a=std::strlen(p),b=std::strlen(x.p);char* q=new char[a+b+1];std::memcpy(q,p,a);std::memcpy(q+a,x.p,b+1);delete[] p;p=q;return *this;} Text& appendChar(char c){auto n=std::strlen(p);char* q=new char[n+2];std::memcpy(q,p,n);q[n]=c;q[n+1]=0;delete[] p;p=q;return *this;} std::size_t size()const{return std::strlen(p);} };
int main(){
    constexpr int N=100000; volatile std::size_t sink=0;
    auto a=std::chrono::steady_clock::now(); Text t; for(int i=0;i<N;++i)t.appendChar('x'); auto b=std::chrono::steady_clock::now(); sink=t.size();
    auto c=std::chrono::steady_clock::now(); std::string s; for(int i=0;i<N;++i)s.push_back('x'); auto d=std::chrono::steady_clock::now(); sink+=s.size();
    std::cout<<"custom Text append_us="<<std::chrono::duration_cast<std::chrono::microseconds>(b-a).count()<<" std::string append_us="<<std::chrono::duration_cast<std::chrono::microseconds>(d-c).count()<<" sink="<<sink<<'\n';
}
