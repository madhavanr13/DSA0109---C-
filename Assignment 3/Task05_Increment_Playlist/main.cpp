#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;
public:
    explicit Time(int s=0):seconds(s) { if(s<0) throw std::invalid_argument("negative time"); }
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old=*this; ++seconds; return old; }
    bool operator==(const Time& x) const { return seconds==x.seconds; }
    bool operator<(const Time& x) const { return seconds<x.seconds; }
    int value() const { return seconds; }
    friend std::ostream& operator<<(std::ostream& os,const Time& t) { return os<<t.seconds<<" sec"; }
};
class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> x):tracks(x){}
    std::string& operator[](int i) { if(i<0||i>=static_cast<int>(tracks.size())) throw std::out_of_range("playlist index"); return tracks[i]; }
    const std::string& operator[](int i) const { if(i<0||i>=static_cast<int>(tracks.size())) throw std::out_of_range("playlist index"); return tracks[i]; }
    int size() const { return static_cast<int>(tracks.size()); }
};
int main() {
    Time t(10); Time a=t++; Time b=++t;
    std::cout<<a<<' '<<b<<' '<<t<<'\n';
    Time rollover(3599); ++rollover; std::cout<<"rollover="<<rollover<<'\n';
    Playlist p{"Track A","Track B","Track C"}; std::cout<<p[1]<<'\n';
    try { std::cout<<p[-1]; } catch(const std::out_of_range& e) { std::cout<<"Range error: "<<e.what()<<'\n'; }
    const Playlist& cp=p; std::cout<<cp[2]<<'\n';
}
