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

void bookGroup(const char* label)
{
 std::cout << "-- " << label << " --\n";
 BusTicket group[4] = {BusTicket("P1"), BusTicket("P2"), BusTicket("P3"), BusTicket("P4")};
 for (const BusTicket& t : group) t.print();
 std::cout << "Issued so far: " << BusTicket::count() << '\n';
} // the tickets are destroyed here, but the static counter is NOT decremented

int main()
{
 bookGroup("first call");
 bookGroup("second call (bus already full)");
 { BusTicket late("Late"); late.print(); }
 std::cout << "Issued at end: " << BusTicket::count() << '\n';
}
