// Q2: reference into a std::vector invalidated by growth. Build with -fsanitize=address to see the report.
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v(4, 7);
    int& r = v[0];
    v.push_back(1);          // size==capacity -> reallocation, old buffer freed
    v.push_back(2);
    std::cout << r << '\n';  // use-after-free through the stale reference
}
