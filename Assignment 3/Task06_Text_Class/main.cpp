#include <cstring>
#include <iostream>
#include <stdexcept>

class Text {
    char* data;
    static int copies;
public:
    Text(const char* s="") { data=new char[std::strlen(s)+1]; std::strcpy(data,s); }
    Text(const Text& other) { data=new char[std::strlen(other.data)+1]; std::strcpy(data,other.data); ++copies; }
    Text& operator=(const Text& other) { if(this!=&other) { char* fresh=new char[std::strlen(other.data)+1]; std::strcpy(fresh,other.data); delete[] data; data=fresh; } return *this; }
    ~Text(){ delete[] data; }
    Text& operator+=(const Text& rhs) { std::size_t a=std::strlen(data),b=std::strlen(rhs.data); char* fresh=new char[a+b+1]; std::memcpy(fresh,data,a); std::memcpy(fresh+a,rhs.data,b+1); delete[] data; data=fresh; return *this; }
    friend Text operator+(const Text& a,const Text& b) { Text result(a); result+=b; return result; }
    bool operator==(const Text& x) const { return std::strcmp(data,x.data)==0; }
    bool operator!=(const Text& x) const { return !(*this==x); }
    friend std::ostream& operator<<(std::ostream& os,const Text& x) { return os<<x.data; }
    static void resetCopies(){copies=0;} static int copyCount(){return copies;}
};
int Text::copies=0;
int main(){
    Text a("Hello "),b("Cloud"),c(" Computing"); Text::resetCopies();
    Text message=a+b+c; std::cout<<message<<'\n';
    std::cout<<"copies="<<Text::copyCount()<<'\n';
    Text empty; empty=empty; std::cout<<"empty='"<<empty<<"' equal="<<std::boolalpha<<(empty==Text())<<'\n';
    Text longText("This is a longer SMS message used to test dynamic allocation safely."); std::cout<<longText<<'\n';
}
