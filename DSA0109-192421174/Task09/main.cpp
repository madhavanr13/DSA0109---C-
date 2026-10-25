#include <iostream>
#include <string>
enum class Zone{Inner,Middle,Outer};
long long calculate(Zone z,int hour,bool concession=false){long long f=(z==Zone::Inner?1000:z==Zone::Middle?2000:3000);if((hour>=8&&hour<10)||(hour>=17&&hour<20))f=f*120/100;if(concession)f=f*50/100;return f;}
int main(){struct Test{const char*name;Zone z;int hour;bool concession;long long expected;};Test tests[]={{"Inner off-peak",Zone::Inner,11,false,1000},{"Middle morning peak",Zone::Middle,8,false,2400},{"Outer 10:00 boundary",Zone::Outer,10,false,3000},{"Outer 17:00 boundary",Zone::Outer,17,false,3600},{"Outer 20:00 boundary",Zone::Outer,20,false,3000},{"Student concession",Zone::Middle,12,true,1000}};int pass=0;for(const auto&t:tests){auto actual=calculate(t.z,t.hour,t.concession);bool ok=actual==t.expected;pass+=ok;std::cout<<t.name<<": expected="<<t.expected<<" actual="<<actual<<" "<<(ok?"PASS":"FAIL")<<'\n';}std::cout<<pass<<'/'<<(sizeof(tests)/sizeof(tests[0]))<<" tests passed\n";}
