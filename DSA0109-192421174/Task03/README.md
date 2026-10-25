## Type choices
Use long long for aggregate paise and card balances; int for hour, zone index and percentage; bool for peak/concession; enum class Zone for zones; size_t for array indices; string for names. sizeof output is platform/compiler-specific; run the program to record local sizes. Money in integer paise avoids binary floating-point representation error. <climits> supplies INT_MAX/LLONG_MAX. At 3,000,000 journeys × 3,600 paise, total is 10,800,000,000 paise, beyond a typical 32-bit int; long long is appropriate. double addition remains O(1), 8 bytes on this system, but repeated fractional additions can drift.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
