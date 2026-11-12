#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const std::string& t) : Book(t, "Unknown", 0) {}
    Book(const std::string& t, int c) : Book(t, "Unknown", c) {}
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c) {
        if (copies < 0) throw std::invalid_argument("copies cannot be negative");
    }
    void print() const { std::cout << title << " | " << author << " | copies=" << copies << '\n'; }
};

int main() {
    Book empty;
    Book donated("The Alchemist");
    Book partial("Clean Code", 4);
    Book full("The C++ Programming Language", "Bjarne Stroustrup", 3);
    empty.print(); donated.print(); partial.print(); full.print();
    try { Book invalid("Invalid", "Test", -2); invalid.print(); }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}
