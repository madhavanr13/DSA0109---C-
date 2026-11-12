#include <string>
struct Label { Label(const std::string&) {} };
int main(){ Label x = std::string("implicit conversion allowed"); (void)x; }
