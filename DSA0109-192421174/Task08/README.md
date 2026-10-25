## Safe I/O
cin >> is convenient for typed input; if extraction fails, test cin.fail(), call cin.clear(), then ignore through newline using numeric_limits<streamsize>::max(). getline plus stoi processes a line in O(L) time and O(L) buffer space, allows full-line validation and catches invalid_argument/out_of_range; formatted extraction also scans input but token-based recovery needs clearing and discarding. setw sets the next field width; setfill sets padding; fixed/setprecision format decimal output. Always validate hour 0–23 and zone before computing a fare.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
