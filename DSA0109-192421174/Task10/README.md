## Measurements and comparison
Run with g++ -std=c++17 -Wall -Wextra -Wconversion. At 3,000,000 journeys × Rs 36, total = Rs 108,000,000 (10,800,000,000 paise). This exceeds INT_MAX on a common 32-bit int, so signed int overflow is not safe (signed overflow is undefined behavior). long long safely holds this total; double can represent this integer-sized total with ample precision for ordinary use, but decimal fractional additions can introduce rounding. Per-addition time is O(1); int usually 4 bytes, long long and double commonly 8 bytes. Record actual warnings from the compiler used; warnings can differ by compiler/version.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
