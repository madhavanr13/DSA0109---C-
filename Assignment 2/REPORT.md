# Assignment 2 – CO2 Report

**Name:** `Madhavan R`  **Register No.:** `192421174`  **GitHub:** `Not yet created`
**Compiler:** g++ 13.3.0 (Ubuntu 24.04). **Flags:** `g++ -std=c++17 -Wall -Wextra` (+ `-O0` / `-O2` / `-fsanitize=address` as stated).
Predictions are in each folder's `prediction.txt` and were written before any program was compiled or run. Raw output for every run is in `*.output.txt`.

---

## Q1 – Call by value, reference and pointer

### Predict the output (given program)
| Prediction (written first) | Actual output | Match |
|---|---|---|
| `1 12 13` | `1 12 13` | yes |
| `1 100` | `1 100` | yes |
| `16 13 6 ` | `16 13 6 ` | yes |

**Why.** `change(a,b,&c)`: `a` is a copy so only the local `a` becomes 11; `b` is an alias so `main`'s `b` becomes 12; `c` is reached through its address so it becomes 13. `bigger(a,c)` compares 1 and 13, returns a reference to `c`, and the call on the left of `=` assigns 100 to `c`. `show(1)` uses both defaults (y=5, z=10 → 16); `show(1,2)` uses only the default for z (→ 13); `show(1,2,3)` uses none (→ 6).

### Three implementations (`q1_three_ways.cpp`)
Each fee starts at 45000, concession 10 %. Predicted → observed: value **45000 → 45000**, reference **40500 → 40500**, pointer **40500 → 40500**.

**Inquiry.**
* *By value*: the parameter is a new object in the callee's stack frame (8 bytes for `long long`), initialised from the argument. Changing it changes only the copy. Inside the function it prints 40500, which is why the code "appears to work".
* *By reference*: no new fee object exists; the parameter is another name for the caller's variable (the compiler normally passes the address behind the scenes).
* *By pointer*: the parameter is a new local variable (8 bytes) holding the caller's address; `*fee` reaches the caller's object. It can be null, so it needs a check.
* Only reference and pointer reach the caller's object, so only they change the stored fee.
* A **`const T&`** parameter is used for read-only access to objects that are expensive to copy (e.g. `Student`), or whose copy may be impossible, and it also binds to temporaries. For small built-in types (`int`, `long long`) pass by value.

**Design decision.** I choose **returning the new fee** (`long long applyConcession(long long fee, int percent)`), marked `[[nodiscard]]`. Chained concessions read naturally – `fee = apply(apply(apply(fee,10),15),25)` gave **25819** (45000→40500→34425→25819), identical to three in-place reference calls – and there is no aliasing, the function is pure and trivially testable. In-place is better only when the object is large and updated in bulk. Note the policy question the code cannot answer: with integer truncation the *order* of concessions can change the rupee by a rupee, and sequential (compounding) discounts differ from additive ones (45000×50 % = 22500), so the office must document the rule.

### Complete the Code
`TODO 1`: `fee -= fee * percent / 100;` Output matches the expected output exactly:
```
after call by value : 45000
after call by reference: 40500
```
The call by value leaves 45000 because `applyByValue` changes its own copy of the fee, which is destroyed when the function returns.

### Alternative concept and complexity
| Version | Time | Space copied per call (long long) | Space copied (Student, measured 4136 B) |
|---|---|---|---|
| by value / returns new fee | O(1) | 8 B | **4136 B** |
| by reference / pointer | O(1) | ≈8 B address (0 if inlined) | ≈8 B |
| by const reference | O(1) | ≈8 B | ≈8 B |

Measured (`-O2`, noinline reader, 1 000 000 calls): **by value 34.7 ms vs by const reference 0.68 ms (≈51×)**. All are O(1) in the number of students, but the copy is O(sizeof(object)) – the constant that matters.

---

## Q2 – Return by reference and its dangers
Program: `q2_marks.cpp`. Marks `{56,78,91,67,84}`.

* `highest(marks,5) += 2;` → `56 78 93 67 84` (the returned reference *is* the element).
* `highest(marks,5) = 50;` → `56 78 50 67 84` (call on the left of `=`).
* **Return type comparison.** `int&` – caller can modify the element. `const int&` – alias without permission to modify (`cr += 2` does not compile); no copy. `int` – a copy: `copy += 2` gave 95 while the array stayed 93.

**Compiler warning** (`q2_dangling.cpp`, `-Wall`):
```
warning: reference to local variable 'local' returned [-Wreturn-local-addr]
```
**Why it is undefined behaviour:** `local` lives in the function's stack frame, which ends at `return`; the reference then names an object whose lifetime is over. Any use is UB – the program may print garbage, the old value, or crash. In our run GCC replaced the dangling reference by a null address and the program **segfaulted (exit code 139)**; AddressSanitizer also reported a SEGV at the use.

**Changed condition – `std::vector` that grows.** A vector keeps its elements in one contiguous heap block. When `push_back` exceeds the capacity, it allocates a bigger block, moves the elements and frees the old block; every reference, pointer and iterator into the old block now dangles. Observed: capacity 5 → 160 and `&v[2]` changed address (`old pointer still equals current address? false`). `q2_vector_uaf.cpp` with `-fsanitize=address` produced `ERROR: AddressSanitizer: heap-use-after-free … freed by … _M_deallocate`.

### Alternative concept and complexity
```cpp
marks[highestIndex(marks,n)] += 2;       // index version
*highestPtr(marks,n) += 2;               // pointer version
highest(marks,n) += 2;                   // reference version
```
Time is O(n) for all (one scan) and space O(1). Measured once, `-O2`, n = 10 000 000: reference 13.8 ms, index 6.1 ms, pointer 12.1 ms (single run; the gap is most likely code-generation/noise, not a different complexity – the three scale linearly: 0.06 / 0.67 / 13.8 ms for n = 10⁵ / 10⁶ / 10⁷ by reference).
**Safety when the array becomes a growing vector:** the *index* stays valid across reallocation (it only breaks if elements are erased or reordered); the *pointer* and *reference* are invalidated by any reallocation. Index is therefore the safest to store; reference is the most convenient for an immediate, short-lived use.

---

## Q3 – Default arguments and overloading

**Original code error** (captured in `Q3/q3_ambiguous.output.txt`): `error: call of overloaded 'charge(double)' is ambiguous` (candidates `charge(double)` and `charge(double,bool,bool)`) and `error: call of overloaded 'charge(double, bool)' is ambiguous` (candidates `charge(double,bool)` and `charge(double,bool,bool)`). Default arguments are not considered when ranking: for `charge(2.5)` the one-parameter function and the three-parameter function are both exact matches on the only argument given, so neither is better.

**Redesign** (`q3_charge.cpp`): `charge(int grams, bool express=false, bool insured=false)`, `charge(double kg, bool express=false, bool insured=false)`, `charge(const Parcel&)`. Rate ₹50/kg, express +30, insurance +20.

| # | Call | Predicted function | Observed | Price |
|---|---|---|---|---|
| 1 | `charge(2500)` | grams (int exact) | [grams] | 125.00 |
| 2 | `charge(2)` | grams (int exact – 2 g!) | [grams] | 0.10 |
| 3 | `charge(2.0f)` | kg (float→double promotion beats float→int conversion) | [kg] | 100.00 |
| 4 | `charge(2.5)` | kg | [kg] | 125.00 |
| 5 | `charge(2.5,true,true)` | kg | [kg] | 175.00 |
| 6 | `charge(parcel{1.2,express})` | Parcel | [parcel] | 90.00 |

All six predictions were right. (Output order note: the label `[grams]` appears after `=` because C++17 evaluates `<<` operands left to right.) `charge(2L)` would be ambiguous (long→int and long→double are both conversions), so the design avoids relying on it. `charge(2)` selecting grams is a usability hazard worth documenting; the alternative is to name the functions differently.

**How the compiler chooses.** (1) Collect functions with the name; (2) keep the viable ones (right number of arguments, counting defaults, and implicit conversions exist); (3) for each argument rank the conversion: **exact match** > **promotion** (float→double, short→int) > **conversion** (int→double, double→int, int→bool); (4) the function that is at least as good on every argument and better on one wins; otherwise the call is ambiguous.
**Why defaults from the right:** arguments are matched left to right, so an omitted argument can only be one at the end; a default in the middle (`f(int a=1,int b)`) could never be used, because there is no syntax to skip `a`. The rule is enforced by the compiler: once a parameter has a default, all parameters to its right must have one.

### Alternative concept and complexity (`q3_alt_struct.cpp`, output `125.00 155.00 175.00 65.00`)
```cpp
struct Parcel { double kg=0; bool express=false, insured=false, fragile=false; };
double charge(const Parcel& p);          // one function
charge({.kg=2.5,.express=true});         // C++20 designated initialisers
```
* **New option:** the struct design adds one field and one term in one function (the new `fragile` option took one line); the overload+default design adds another `bool` parameter (positional `charge(2.5,true,false,true)` becomes unreadable) or more overloads – up to 2ⁿ combinations. The struct also makes calls self-documenting.
* A function template `template<class W> double charge(W weight)` would let one body serve int/double, but it removes the deliberate grams-vs-kg distinction (an `int` would become kg unless specialised).
* **Complexity:** overload resolution and template instantiation happen at compile time – zero run-time cost. Space copied per call: `double`+2 bools = 16 B by value for the overload version; the Parcel passes by `const&` (≈8 B address), so the struct version copies less as options grow.

---

## Q4 – Specifying a class with an array inside it
`q4_account.cpp`: private `accNo`, `balance`, `Txn tx[HISTORY]`, `count`, `start`. Defined **inside** the class: constructor, `getBalance()`. Defined **outside** with `SavingsAccount::`: `record`, `deposit`, `withdraw`, `miniStatement`.

**Test:** 11 deposits (100…1100) into a 10-slot account → statement shows 200…1100 (the oldest, 100, was discarded) as predicted; `withdraw(99999)` refused (`false`), `withdraw(250)` shows as the newest entry, balance 11350; 10 entries retained.

**Inquiry.** The array is private so that `count`, `start`, `balance` and the array stay consistent (the statement can only change through `deposit`/`withdraw`; nobody can forge or delete a transaction or put `count` out of range). On the 11th transaction: the **shifting** design moves 9 elements down and writes at the end – O(k) per add; the **circular** design overwrites the oldest slot and advances `start = (start+1)%HISTORY` – O(1).

**Design decision (50 transactions).** The circular design changes least: only the constant `HISTORY` (10 → 50); `record`, `miniStatement` and everything else stay the same. The shifting design also needs only the constant, but costs 5× more per transaction (measured 14.0 ns at K=50 vs 3.6 ns circular at -O2).

### Alternative concept and complexity (`q4_bench.cpp`, 200 000 adds, ns per add)
| K | shift -O2 | circular -O2 | shift -O0 | circular -O0 |
|---|---|---|---|---|
| 10 | 8.4 | 3.6 | 21.6 | 3.8 |
| 50 | 14.0 | 3.6 | 73.8 | 4.1 |
| 100 | 24.4 | 3.6 | 144.5 | 3.7 |
| 1000 | 132.3 | 4.0 | 1393.8 | 3.9 |
| 10 000 | 2943.3 | 3.7 | 13805 | 4.2 |

Both versions produced identical statements. `std::deque` (`push_back`, and `pop_front` when `size()>K`) also gives O(1) amortised add, but allocates on the heap in chunks and has more per-element overhead; a circular buffer in a fixed array has no allocation, O(K) space exactly and one extra `int`. Space: Θ(K) in all three designs (shift: K·sizeof(Txn); circular: K·sizeof(Txn)+4 B; deque: K·sizeof(Txn) + bookkeeping).

---

## Q5 – Static members and arrays of objects

**Design from the principle.** Data belonging to the whole class exists once → `static int issued` (seats given out) and `static const int CAPACITY`. Per-ticket data (`seat`, `name`) are non-static. `static int count()` reports the total without any object.
* A static data member is only **declared** in the class; it must be **defined once**, outside the class, in exactly one source file: `int BusTicket::issued = 0;` (C++17 also allows `static inline`).
* A static member function has no `this` pointer (it is not called on an object), so it cannot name a non-static member or use `this`; it can use only static members.
* **Array of objects:** `BusTicket trip[4] = {BusTicket("Asha"), …}` constructs each element in order (there is no default constructor, so every element must be initialised with arguments; `Token counter[3]` works because `Token` has one).
* **Count in loops/functions:** the static counter lives for the whole program. Objects created in a loop or function increment it, and **destroying them does not decrement it** (no destructor does it).

### Predict the output – Token
Prediction `101 103 104 4` → actual `101 103 104 4` (match). `next` starts at 100 because `int Token::next = 100;` initialises the single shared copy before `main` runs. The constructor ran **4 times** (3 array elements + `extra`); ids 101,102,103,104; `issued()` = 104 − 100 = 4.

### Complete the Code
```
Asha: Seat 1
Bala: Seat 2
Chitra: Seat 3
Dev: Waiting
Issued: 3
```
Identical to the expected output. TODO 1: `if (issued < CAPACITY) { ++issued; seat = issued; }`; TODO 2: `return issued;`.

**Tests.** `q5_array_test.cpp` (7 tickets, capacity 3): seats 1–3, four waiting, `Seats issued: 3, waiting list: 4`. `q5_function_twice.cpp`: first call P1–P3 seated, P4 waiting, Issued 3; **second call** all four "Waiting" even though the first call's tickets no longer exist, and a later `Late` ticket is also Waiting, Issued stays 3 – the static counter persists. If cancellations must free seats, a destructor/free-list is needed (decrementing alone would hand out duplicate seat numbers).

### Alternative concept and complexity
* **Global variable:** works, O(1), one counter, but anyone can modify it, name clashes are possible, and there is exactly one bus.
* **`TicketOffice` object** passed to each ticket (`q5_alt_office.cpp`): two buses at once – output `bus1 issued 2, bus2 issued 1` – and the counter is encapsulated and testable, but every ticket constructor must receive the office. Static member: best encapsulation for one bus with no extra argument but cannot support two buses. Time O(1) and space one counter (an `int`) in all three.

---

## Q6 – Friend functions and inline functions

**Design.** `Time` keeps `h`, `m` private. `minutesBetween(a,b)` and `earlier(a,b)` treat both objects equally, so they are non-member **friend** functions called `earlier(x,y)`; they have no `this`, and may read private members of `Time` (friendship is granted by the class, is not inherited and not mutual). A member function would be called `a.minutesTo(b)`, where `a` is special, and gets `this`. Making `h` and `m` public would lose the invariant (0 ≤ h < 24, 0 ≤ m < 60 – any code could store 99 minutes) and the freedom to change the representation (e.g. to minutes-since-midnight) without breaking every user. (Note: my `Time` constructor does not validate its arguments; a production class should.)

**Inline** is a *request* to the compiler to replace the call with the function body (functions defined inside the class are implicitly inline; `inline` also relaxes the one-definition rule for header definitions). The compiler may ignore it, or inline a function not marked inline. Evidence (`Q6/inline_evidence.txt`): at `-O0` both `minutesInline` and `minutesNoInline` remain real calls; at `-O2` the `inline` one has 0 call sites.

**Complete the Code:** output `205 false` (expected). TODO 1: `abs(ta-tb)` on minutes since midnight; TODO 2: `a.h*60+a.m < b.h*60+b.m`.

**Correctness check** (`q6_tests.cpp`, all 9 PASS): 9:45→13:10 = 205 and 13:10→9:45 = 205; 11:50→12:10 (across noon) = 20; same time twice = 0 and `earlier` false both ways; 12:00↔0:00 = 720; 0:00→23:59 = 1439. Hand check: 13×60+10 = 790; 9×60+45 = 585; 790−585 = 205.

**Growth investigation – 10 000 000 calls, best of 5 runs (ms).**
| Benchmark | -O0 inline | -O0 noinline | -O0 member | -O0 getters | -O2 inline | -O2 noinline | -O2 member | -O2 getters |
|---|---|---|---|---|---|---|---|---|
| A: objects built inside the loop (`q6_bench`) | 80.0 | 81.4 | 82.1 | 155.5 | 32.2 | 31.6 | 32.5 | 32.3 |
| B: pre-built arrays, call isolated (`q6_bench_arrays`) | 46.8 | 63.3 | 62.3 | 136.9 | 6.2 | 10.6 | 6.3 | 6.2 |

**Explanation.** At -O0 nothing is inlined, so inline ≈ noinline in A; the getters cost two extra calls each, hence ~2×. In B at -O0 the friend-`inline` was 1.35× faster than the other real calls although the assembly shows a call in both – I did not find the cause (likely code layout effects). At -O2 the optimiser inlines the small functions (inline, member and getters all equal at 6.2–6.3 ms) while the forced-noinline call costs 1.7× more. **My prediction was only partly right:** I predicted "several times faster" with inlining at -O2; in A there was *no* difference because building two `Time` objects with `%` operations in the loop dominates and the CPU hides the call; in B the gain was 1.7×, not "several".

**Deployment decision.** Keep the two friend functions. They are symmetric operations on two `Time` objects, add no public getters (the interface stays minimal), and after inlining at -O2 they are as fast as members or getters (6.2 vs 6.3 vs 6.2 ms). Members (`a.minutesTo(b)`) would be equally acceptable – performance gives no reason to prefer either – and getters are the weakest encapsulation (the representation becomes part of the public interface) and 2× slower at -O0.

### Alternative concept and complexity
Member version `a.minutesTo(b)`, getters version `abs(b.hours()*60+b.mins()-…)`: each O(1) per call, same machine code after inlining; encapsulation: friend (private data visible to two named functions only) > member (private data visible to all members) > getters (data public through the interface).

---

## Q7 – Diagnose, redesign and validate (selected program: Q4 mini-statement)

**A. Diagnosis (2).** Evidence from Q4 (`-O2`): time per transaction of the shifting design rises from 8.4 ns (K=10) to 14.0 (K=50), 24.4 (K=100), 132 (K=1000) and 2943 ns (K=10 000) – linear in K. Cause: once the history is full, every transaction shifts K−1 elements (`for i in 1..K-1: tx[i-1]=tx[i]`), so the *position of the oldest element is tied to index 0*. At today's K=10 it is cheap (8 ns); the limitation appears when the requirement changes (K=50 already costs 1.7× more than K=10, K=1000 costs 16×).

**B. Objective (2).** Make the cost per transaction independent of K: at K=10 000 time per add ≤ 2× the time at K=10, i.e. ≤ ~10 ns on this machine; ≥100× faster than the original at K=10 000; identical statements on a randomised test; no more than O(1) extra memory (K·sizeof(Txn) + a few bytes).

**C. Redesign (4).** Replace "oldest = tx[0]" by a **start index**: `Txn tx[K]; int count, start;` (array inside a class, private; member functions; `%` operator).
```
class SavingsAccount (private: tx[K], count, start)
add(t,a):  if count < K:  tx[(start+count) % K] = {t,a};  count++
           else:          tx[start] = {t,a};  start = (start+1) % K     // overwrites oldest, O(1)
at(i):     return tx[(start+i) % K]                                    // i-th oldest
```
Extra memory: one `int` (`start`). New trade-offs: a `%` on every access (the divisor can be a power of two to use a mask), elements are no longer contiguous in time order (printing must unwrap, can't `memcpy` the statement), and the code is slightly harder to read/verify.

**D. Prediction (1) (written before implementing).** Time/add flat in K (within ~2×); at K=10 both versions within 2×; ≥100× speed-up at K=10 000; memory unchanged.

**E. Validation (2)** (`q7_compare.cpp`, 200 000 adds; equivalence tested after *every* operation on 5000 random operations for K=10, 50 and 1000: all PASS).
| K | Original ns/add (-O2) | Redesigned ns/add (-O2) | Speed-up -O2 | Speed-up -O0 |
|---|---|---|---|---|
| 10 | 6.7 | 2.7 | 2.5× | 5.3× |
| 50 | 11.1 | 2.9 | 3.8× | 19.8× |
| 100 | 18.3 | 2.8 | 6.5× | 35.3× |
| 1000 | 81.7 | 2.9 | 28.3× | 405.5× |
| 10 000 | 2818.7 | 3.7 | 771× | 3716× |

Prediction check: K=10000 ≥100× – **true (771×)**; flat in K – true (2.7–3.7 ns, ratio 1.35×); memory unchanged – true (K·16 B plus the object's 16 B); K=10 "within 2×" – **wrong: 2.5×** (moving 9 sixteen-byte elements already costs more than one modulo).

**F. Defence (2).** *Objective achieved:* cost per add at K=10 000 is 1.35× that at K=10 (target ≤ 2×), 771× speed-up (target ≥ 100×), identical statements, +4 bytes. *Costs:* modulo arithmetic on every access, unwrapping when printing, a bit more complex invariants. *Where the original may still be preferable:* for the bank's actual size (K = 10–50) the original costs ≤ 14 ns per transaction – irrelevant next to an ATM's latency – and its contiguous, oldest-first layout is simpler to read, print and test; choose the shifting version if K is small and clarity matters. Caveats: one single-core machine; compilers may turn the shift loop into `memmove`, and timings fluctuate by a few percent between runs.

---

## Summary of prediction accuracy
Correct: Q1 (all), Q2 (all), Q3 (all six selections and prices), Q4 (11th transaction behaviour), Q5 (`101 103 104 4`, ticket output), Q6 (`205 false`, test values, -O0 equality), Q7 (≥100×, flat, memory). Wrong or partly wrong: Q4/Q7 K=10 speed-up (predicted <2×, measured 2.3–2.5×); Q6 -O2 (predicted "several times", measured 1.0× in benchmark A and 1.7× in B).
