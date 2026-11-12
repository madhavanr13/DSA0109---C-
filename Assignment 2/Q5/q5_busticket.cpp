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
 BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"),
 BusTicket("Chitra"), BusTicket("Dev")};
 for (const BusTicket& t : trip) t.print();
 std::cout << "Issued: " << BusTicket::count() << '\n';
}
