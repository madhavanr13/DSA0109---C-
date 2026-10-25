## Recommendation
Use enum class Zone, constexpr integer-paise fares, long long balances/totals, a private SmartCard balance and centralized fare/peak functions. Define peak intervals explicitly as half-open ranges. Fare revision changes one table/constant and requires regression tests. Limitations: compile-time fare updates require rebuilding; concession rules and monthly passes need explicit policy; persistence, concurrency, audit logging and transaction rollback are outside this small model. O(1) work per journey remains appropriate for millions of journeys. A configuration file adds O(z) startup reading and O(z) memory but avoids recompilation for fare-only revisions; validate file contents before opening gates.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
