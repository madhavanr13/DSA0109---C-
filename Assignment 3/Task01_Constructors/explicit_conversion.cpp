#include <string>
struct Label { explicit Label(const std::string&) {} };
int main(){ Label x = std::string("copy-initialization rejected"); (void)x; }
