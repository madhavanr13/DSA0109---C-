## Analysis
Objects: SmartCard (private stored balance and validation/deduction), Passenger (identity and concession eligibility), Journey (zone/time), Zone (finite category), FareTable (single source of fares). Encapsulation protects balance; abstraction exposes canTravel/deduct; inheritance could specialize Student/Senior passenger; polymorphism could override concession policy. Rules: fare nonnegative, balance after deduction >= Rs 50, exact boundary peak windows [08:00,10:00) and [17:00,20:00), no deduction when denied. Procedural free functions and globals still run O(1) per trip and use O(1) balance storage, but changes are scattered and risk inconsistent rules. OOP centralizes invariants; code-change scope is smaller.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
