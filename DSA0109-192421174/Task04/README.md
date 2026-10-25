## Conversion analysis
Prediction before execution: 3.5 3.5? Correction by language rules: a/b performs integer division (3), then converts to double; explicit cast makes 3.5. char 'C' prints C; ch+1 promotes char to int and prints 68. bool initialized from 5 becomes true; default stream prints 1, boolalpha prints true. Comparing signed -1 to unsigned 1 converts -1 to unsigned, so comparison is false and output is s >= u. Full predicted output is recorded in prediction.txt before execution. Use static_cast for intended numeric conversion and brace initialization to reject narrowing. Explicit casts do not materially change runtime or storage; braces catch narrowing at compile time.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
