## Pseudocode
BEGIN
  READ zone, hour, balance
  SELECT zone: Inner→1000; Middle→2000; Outer→3000; otherwise reject
  peak ← (hour >= 8 AND hour < 10) OR (hour >= 17 AND hour < 20)
  IF peak THEN fare ← fare × 120 / 100
  IF balance − fare >= 5000 THEN deduct fare and print fare/balance ELSE deny
END
Switch is clear for finite zones; if-else suits range checks; ?: suits short value selection. A counted for loop suits a known trip array; range-for is safest for arrays/containers; while suits input retry. break exits a loop/switch; continue skips invalid trips. No matching switch case means no action unless default handles invalid values. Both switch and array lookup are O(1); array uses space for zone entries and scales by adding an entry, while switch needs another case.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
