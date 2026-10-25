## Precedence prediction
Prediction before execution: 11 16; 9 6 4; 6 2; 3 1 -3 -1; 18. Multiplication precedes addition; parentheses override precedence. x++ yields old x=5 then increments; ++y increments 3 to 4 before use, so z=9, x=6, y=4. Conditional chooses max 6; % and * have same precedence and associate left-to-right: (6%4)*2=4. Integer division truncates toward zero, and remainder sign follows dividend: -10/3=-3, -10%3=-1. Loop adds 0+3+6+9=18. Avoid i=i++ because it is error-prone and historically undefined/unsequenced depending on language context. Parenthesize peak ranges for readability.

## Complexity
Fare lookup, peak check, and card eligibility: O(1) time. Per-card state: O(1) space. Batch of n journeys: O(n) time.
