// Q5 alternative: seat counter in a TicketOffice object passed to each ticket -> two buses at once
#include <iostream>
#include <string>
class TicketOffice { int issued = 0; int capacity; public: explicit TicketOffice(int c) : capacity(c) {}
    int nextSeat() { return issued < capacity ? ++issued : 0; } int count() const { return issued; } };
class BusTicket { int seat; std::string name; public:
    BusTicket(const std::string& n, TicketOffice& o) : seat(o.nextSeat()), name(n) {}
    void print() const { std::cout << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; } };
int main() {
    TicketOffice bus1(2), bus2(2);
    BusTicket a("Asha", bus1), b("Bala", bus1), c("Chitra", bus1), d("Dev", bus2);
    a.print(); b.print(); c.print(); d.print();
    std::cout << "bus1 issued " << bus1.count() << ", bus2 issued " << bus2.count() << '\n';
}
