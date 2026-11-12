#include <iostream>
#include <string>
class BusTicket {
 static int issued; // shared by all BusTicket objects
 static const int CAPACITY = 3;
 int seat;
 std::string name;
public:
 explicit BusTicket(const std::string& n) : seat(0), name(n)
 {
 // TODO 1 (done): if seats remain, take the next seat number; otherwise stay on the waiting list (seat 0)
 if (issued < CAPACITY) { ++issued; seat = issued; }
 }
 static int count()
 {
 // TODO 2 (done): number of seats issued so far
 return issued;
 }
 void print() const
 {
 std::cout << name << ": "
 << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting"))
 << '\n';
 }
};
int BusTicket::issued = 0; // definition of the static data member

int main()
{
 const int N = 7;                       // array larger than the capacity of 3
 BusTicket* all[N]; std::string names[N] = {"A","B","C","D","E","F","G"};
 // BusTicket has no default constructor, so use pointers (or brace-init) for a large array
 for (int i = 0; i < N; ++i) all[i] = new BusTicket(names[i]);
 int waiting = 0;
 for (int i = 0; i < N; ++i) { all[i]->print(); }
 waiting = N - BusTicket::count();
 std::cout << "Seats issued: " << BusTicket::count() << ", waiting list: " << waiting << '\n';
 for (int i = 0; i < N; ++i) delete all[i];
}
