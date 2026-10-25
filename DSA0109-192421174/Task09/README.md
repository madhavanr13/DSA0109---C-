## Test evidence
The test harness compares actual paise against expected paise. Cases include all zones, peak/off-peak and boundaries 08:00, 10:00, 17:00, 20:00, plus concession. Unknown zones, negative recharge and nonnumeric hours should be rejected by the input-validation layer; do not cast an unchecked zone index into an enum. A table-driven loop processes t tests in O(t) time and O(t) storage for a table; adding a boundary case is one row. Five sample journeys can be hand-totalled as 1000+2400+3000+3600+3000 = 13000 paise (Rs 130.00), before applying card eligibility.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
