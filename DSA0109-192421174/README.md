# DSA01-REGISTERNUMBER-Assignment1

**Student name:** ADD YOUR NAME  
**Register number:** ADD YOUR REGISTER NUMBER  
**Course:** DSA / C++ Assignment 1 — CO1  
**GitHub repository:** `DSA01-RegisterNumber-Assignment1` (replace placeholder with your register number)

## Compiler and commands
Test environment: GNU g++ 14.2.0, C++17. Standard compile command: `g++ -std=c++17 -Wall -Wextra -Wconversion main.cpp -o main`. Run from each task folder with `./main` (Windows MinGW: `main.exe`).

## Task summary
1. OOP objects and journey invariants.
2. Tokens, constexpr constants and enum class.
3. Type sizes, integer paise and overflow/precision.
4. Implicit conversions; prediction stored before run.
5. Operator precedence; prediction stored before run.
6. Pseudocode and completed switch-based fare program.
7. Procedural and SmartCard designs.
8. Validated input and money formatting.
9. Table-driven tests for fare and boundary conditions.
10. Collection totals and integer range comparison.
11. Final design recommendation.
12. Airport zone, weekend discount and monthly pass.

## Build and run all tasks
From repository root, compile and run each task:
```bash
for d in Task*; do (cd "$d" && g++ -std=c++17 -Wall -Wextra -Wconversion main.cpp -o main && ./main); done
```

## Evidence and report
Each task folder contains `main.cpp`, a task-specific `README.md`, captured output (`output.txt`) and a terminal-style output image (`output.png`) after the build script runs. `prediction.txt` in Tasks 4 and 5 is the written prediction prepared before execution. See `REPORT.md` for the assignment report.

## Before submission
Replace the placeholders with your actual name/register number. Create the remote repository on GitHub, push this repository, verify access, and submit the URL and report in Google Classroom. Do not claim remote submission until it is actually completed.
