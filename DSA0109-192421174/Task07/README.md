## Comparison
Procedural functions accept a balance reference and fare; callers can still alter the balance directly. SmartCard owns private balance and permits only validated deductions. Both are O(1) time per operation and O(1) memory per card. Private state prevents arbitrary code from setting balance negative or bypassing the Rs 50 minimum. A public balance changes neither asymptotic complexity nor memory, but breaks the invariant. Centralizing MIN_BALANCE makes policy changes easier.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
