# DSA01-192421174-Assignment2

| | |
|---|---|
| **Name** | `Madhavan R` |
| **Register number** | `192421174` |
| **Course / Assignment** | DSA01 – Assignment 2 (CO2), individual, 50 marks |
| **Compiler** | g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0 |
| **Standard / flags** | `g++ -std=c++17 -Wall -Wextra` plus `-O0`, `-O2` or `-fsanitize=address` as listed per task (`q3_alt_struct.cpp` uses `-std=c++20` for designated initialisers) |
| **GitHub link** | Not yet created |

Full report with predictions, explanations, pseudocode and complexity analysis: **[REPORT.md](REPORT.md)** (also `REPORT.docx`).

## Layout
One folder per task (`Q1` … `Q7`). Each contains the `.cpp` sources, `prediction.txt` (written **before** running), `*.output.txt` (exact compile command + compiler messages + program output) and `screenshots/*.png` (images rendered from those output files).

## How to build and run (example)
```bash
cd Q1
g++ -std=c++17 -Wall -Wextra -O0 q1_complete.cpp -o q1_complete && ./q1_complete
```
Exact command lines used for every program are on the first line of each `*.output.txt`.

## Task summaries
| Task | Programs | Result |
|---|---|---|
| Q1 (6) | `q1_predict`, `q1_complete`, `q1_three_ways` | Prediction `1 12 13 / 1 100 / 16 13 6` was exactly right. By value leaves fee 45000; reference and pointer give 40500. Chained 10/15/25 % → 25819. Passing a 4136-byte object by value cost ~51× more than by const reference. |
| Q2 (4) | `q2_marks`, `q2_dangling`, `q2_vector_uaf` | `highest(m,n)+=2` and `highest(m,n)=50` work. `-Wreturn-local-addr` warning captured; dangling run segfaults (exit 139). vector growth 5→160 moved the buffer; ASan reports heap-use-after-free. |
| Q3 (6) | `q3_ambiguous` (fails), `q3_charge`, `q3_alt_struct` | Both ambiguous calls reproduced. Redesigned set (int grams / double kg / Parcel) selects as predicted, incl. `charge(2)`→grams and `charge(2.0f)`→kg. |
| Q4 (6) | `q4_account`, `q4_bench` | 11th transaction discards the oldest. Circular index flat at ≈3.6 ns/add; shifting grows from 8 ns (K=10) to 2943 ns (K=10000) at -O2. |
| Q5 (7) | `q5_predict`, `q5_busticket`, `q5_function_twice`, `q5_array_test`, `q5_alt_office` | `101 103 104 4` as predicted. Expected BusTicket output reproduced. Count is never reduced when tickets die. |
| Q6 (8) | `q6_time`, `q6_tests`, `q6_bench`, `q6_bench_arrays` | `205 false`, 9/9 tests pass. -O2: inline 6.2 ms vs noinline 10.6 ms per 10 M calls (1.7×) when the call is isolated; no difference at -O0. |
| Q7 (13) | `q7_compare` | Redesign of Q4: circular buffer. Same statement on randomised tests; 771× faster at K=10000 (-O2), same memory. |

## Honest notes
* Three predictions were partly wrong (Q4/Q7 K=10 speed-up, Q6 -O2 magnitude) – they are kept as written and explained in the report.
* Timings come from one machine (single-core Linux container); re-run on your own machine and replace the numbers/screenshots if you wish.
