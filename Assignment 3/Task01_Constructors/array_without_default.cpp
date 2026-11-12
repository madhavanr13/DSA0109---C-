#include <string>
struct Book { explicit Book(const std::string& title) : title(title) {} std::string title; };
int main(){ Book shelf[2]; } // Intentionally fails: no default constructor.
