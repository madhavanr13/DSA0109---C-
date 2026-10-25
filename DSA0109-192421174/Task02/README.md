## Tokens and constants
Keywords: class, enum, constexpr, return. Identifiers: BASE_PAISE, Zone, fare. Constants: 1000, 20, 5000. Operators: =, *, /, ==. Punctuators: ; {} (). constexpr is typed, scoped and compile-time evaluable; #define is textual substitution without type/scope; const is immutable after initialization but not necessarily compile-time. enum class prevents implicit conversion to integers and avoids enumerator name leakage. Use UpperCamelCase types and UPPER_SNAKE_CASE constants. Macro vs constexpr has essentially no runtime or storage cost; constexpr provides safer diagnostics.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
