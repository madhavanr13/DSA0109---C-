#include <iostream>
int main(){ int* seats = new int[100]; seats[0]=1; std::cout << seats[0] << '\n'; /* intentionally omitted delete[] for leak-sanitizer demonstration */ }
