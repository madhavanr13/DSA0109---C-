// Q2: return by reference, const reference, copy; index/pointer alternatives
#include <iostream>
#include <vector>
#include <chrono>

int&       highest(int marks[], int n)            { int k = 0; for (int i = 1; i < n; ++i) if (marks[i] > marks[k]) k = i; return marks[k]; }
const int& highestConst(const int marks[], int n) { int k = 0; for (int i = 1; i < n; ++i) if (marks[i] > marks[k]) k = i; return marks[k]; }
int        highestCopy(const int marks[], int n)  { int k = 0; for (int i = 1; i < n; ++i) if (marks[i] > marks[k]) k = i; return marks[k]; }
// alternatives
int  highestIndex(const int marks[], int n) { int k = 0; for (int i = 1; i < n; ++i) if (marks[i] > marks[k]) k = i; return k; }
int* highestPtr  (int marks[], int n)       { int k = 0; for (int i = 1; i < n; ++i) if (marks[i] > marks[k]) k = i; return &marks[k]; }

void print(const char* label, const int* a, int n) { std::cout << label; for (int i = 0; i < n; ++i) std::cout << ' ' << a[i]; std::cout << '\n'; }

int main() {
    int marks[5] = {56, 78, 91, 67, 84};
    print("original          :", marks, 5);
    highest(marks, 5) += 2;                 // moderation applied directly to the element
    print("after highest()+=2:", marks, 5);
    highest(marks, 5) = 50;                 // call on the left of =
    print("after highest()=50:", marks, 5);

    marks[2] = 93;
    const int& cr = highestConst(marks, 5);  // cr = 93, read-only alias
    // cr += 2;                              // error: assignment of read-only reference
    int copy = highestCopy(marks, 5);        // independent copy
    copy += 2; 
    std::cout << "const ref = " << cr << ", copy changed to " << copy << ", array still has " << marks[2] << '\n';

    // alternatives
    highest(marks, 5) -= 3;                              // reference version
    marks[highestIndex(marks, 5)] += 3;                  // index version
    *highestPtr(marks, 5) += 0;                          // pointer version (dereference)
    print("after ref/index/ptr :", marks, 5);

    // Changed condition: vector that grows
    std::vector<int> v = {56, 78, 91, 67, 84};
    int*    p   = &v[2];
    size_t  idx = 2;
    std::cout << "capacity before growth: " << v.capacity() << ", &v[2] = " << static_cast<void*>(p) << '\n';
    for (int i = 0; i < 100; ++i) v.push_back(i);        // forces reallocation
    std::cout << "capacity after  growth: " << v.capacity() << ", &v[2] = " << static_cast<void*>(&v[2]) << '\n';
    std::cout << "old pointer still equals current address? " << std::boolalpha << (p == &v[2]) << "  (false => dangling)\n";
    std::cout << "index still valid: v[" << idx << "] = " << v[idx] << '\n';

    // timing: O(n) for all three
    for (int n : {100000, 1000000, 10000000}) {
        std::vector<int> big(n); for (int i = 0; i < n; ++i) big[i] = (i * 7919) % 100003;
        long long sink = 0;
        auto t0 = std::chrono::steady_clock::now(); sink += highest(big.data(), n);
        auto t1 = std::chrono::steady_clock::now(); sink += highestIndex(big.data(), n);
        auto t2 = std::chrono::steady_clock::now(); sink += *highestPtr(big.data(), n);
        auto t3 = std::chrono::steady_clock::now();
        using ms = std::chrono::duration<double, std::milli>;
        std::cout << "n=" << n << "  ref " << ms(t1-t0).count() << " ms  index " << ms(t2-t1).count()
                  << " ms  ptr " << ms(t3-t2).count() << " ms  (sink " << sink << ")\n";
    }
}
