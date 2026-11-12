#include <iostream>
#include <stdexcept>
#include <string>

class Event {
    int rows, seatsPerRow;
    char** seats;
    int booked=0;
public:
    Event(int r,int s) : rows(r), seatsPerRow(s), seats(nullptr) {
        if(r<0||s<0) throw std::invalid_argument("negative dimensions");
        if(rows) {
            seats=new char*[rows]{};
            try { for(int i=0;i<rows;++i) seats[i]=new char[seatsPerRow]; }
            catch(...) { for(int i=0;i<rows;++i) delete[] seats[i]; delete[] seats; throw; }
            for(int i=0;i<rows;++i) for(int j=0;j<seatsPerRow;++j) seats[i][j]='.';
        }
        std::cout << "Construct event "<<rows<<'x'<<seatsPerRow<<'\n';
    }
    ~Event() {
        for(int i=0;i<rows;++i) delete[] seats[i];
        delete[] seats;
        std::cout << "Destroy event; booked="<<booked<<'\n';
    }
    bool book(int r,int s) { check(r,s); if(seats[r][s]=='X') return false; seats[r][s]='X'; ++booked; return true; }
    bool cancel(int r,int s) { check(r,s); if(seats[r][s]!='X') return false; seats[r][s]='.'; --booked; return true; }
    void show() const { for(int i=0;i<rows;++i){ for(int j=0;j<seatsPerRow;++j) std::cout<<seats[i][j]<<' '; std::cout<<'\n'; } }
private:
    void check(int r,int s) const { if(r<0||r>=rows||s<0||s>=seatsPerRow) throw std::out_of_range("seat index"); }
};
int main() {
    { Event local(2,3); local.book(0,1); local.book(1,2); local.cancel(0,1); local.show(); }
    Event* heap=new Event(1,2); heap->book(0,0); delete heap;
    Event zero(0,5); zero.show();
}
