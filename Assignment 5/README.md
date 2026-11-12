# DSA01-192421174-Assignment5

**Student:** Madhavan R  
**Register Number:** 192421174  
**Department:** B.Tech Information Technology  
**Course Outcome:** CO5 – Runtime polymorphism and exception handling  
**Compiler used for initial verification:** g++ (Debian 14.2.0-19) 14.2.0  
**Language:** C++17

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic path/to/main.cpp -o app
./app
```

AddressSanitizer build:

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -fno-omit-frame-pointer path/to/main.cpp -o app
./app
```

Optimised benchmark build:

```bash
g++ -std=c++17 -O2 -Wall -Wextra path/to/main.cpp -o benchmark
./benchmark
```

## Folder guide

- `TaskA1_BillHierarchy`: common interface, UML and SIMATS-style pseudocode.
- `TaskA2_RuntimeBinding`: early/late binding, conceptual vtables, virtual destructor and output prediction program.
- `TaskA3_PayerInterface`: abstract payer design and extension analysis.
- `TaskA4_ExceptionStrategy`: exception taxonomy, noexcept decisions and return-code alternative.
- `TaskA5_Recovery`: stack unwinding, RAII, rethrowing and output prediction program.
- `TaskB1_PolymorphicBilling`: complete integrated billing application and completed TODO program.
- `TaskB2_ExceptionHandling`: completed claim TODO and exception/rethrow prediction program.
- `TaskB3_Performance`: dispatch and exception-cost benchmark programs.
- `TaskB4_EngineeringDecision`: new bill/payer extension and production decision.
- `Assignment_Report.docx`: report covering the design and implementation tasks.

## Task results

The integrated application processes outpatient, inpatient, day-care and emergency bills through `Bill*`/smart pointers. Payer policies are represented by an abstract `Payer` interface. Invalid amounts and rejected claims use typed exceptions. `unique_ptr` ensures automatic cleanup. Benchmark programs print local timings when executed.

## Progressive Git commits

Create at least one commit per task folder, for example:

```bash
git add TaskA1_BillHierarchy && git commit -m "Complete A1 bill hierarchy design"
git add TaskA2_RuntimeBinding && git commit -m "Complete A2 runtime binding analysis"
git add TaskA3_PayerInterface && git commit -m "Complete A3 payer interface design"
git add TaskA4_ExceptionStrategy && git commit -m "Complete A4 exception strategy"
git add TaskA5_Recovery && git commit -m "Complete A5 recovery and rethrow design"
git add TaskB1_PolymorphicBilling && git commit -m "Implement polymorphic billing"
git add TaskB2_ExceptionHandling && git commit -m "Implement exception validation and rethrowing"
git add TaskB3_Performance && git commit -m "Add dispatch and exception benchmarks"
git add TaskB4_EngineeringDecision && git commit -m "Add engineering extension and decision"
```

## Important verification note

Initial source files were compiled with the compiler listed above where compilation succeeded. Run all files again on your own system, execute the AddressSanitizer commands, and save genuine screenshots from your terminal. Performance measurements are machine-dependent and are generated when benchmark programs run; do not report timings from another computer as your own.
