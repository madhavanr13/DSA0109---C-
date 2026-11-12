# DSA01-192421174-Assignment4

**Student:** Madhavan R  
**Register Number:** 192421174  
**Department:** B.Tech Information Technology  
**Course:** Object Oriented Programming with C++ (DSA01)  
**Assignment:** Assignment 4 – CO4: Designing Reusable Class Hierarchies

## Compiler and build command
Compiler used in the preparation environment: g++ (Debian 14.2.0-19) 14.2.0.  
Language standard: C++17.

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o program
./program
```

Run the `complete_code.cpp` or `predict_output.cpp` files in their task folder using the same command with the corresponding source filename. The `outputs/` folders contain captured compiler and execution transcripts for the prepared programs.

## Task summary
| Folder | Coverage |
|---|---|
| Task01_Class_Design | Payroll class hierarchy, diagnosis, UML and polymorphic processing |
| Task02_Inheritance_Diamond | Person/Student/Staff/TeachingAssistant, virtual inheritance and access table |
| Task03_Constructors_Members | Base/member construction, destruction order and completed initializer-list code |
| Task04_Polymorphic_Pointers | Virtual dispatch, virtual destructor, slicing and smart-pointer repair |
| Task05_Cart_This_Pointer | Object access forms, `this`, chaining and highest-cart search |
| Task06_Vehicle_Rental | Abstract vehicle hierarchy, rental/return workflow and ElectricBus extension |

## Repository contents
Each task folder includes C++ source, design/analysis notes, an `outputs/` folder and a `screenshots/` folder for your genuine terminal captures. Task 2 includes a no-virtual-inheritance experiment; Task 4 includes the intentionally unsafe original example and its AddressSanitizer diagnostic. The report `Assignment_Report.docx` consolidates the design explanations and task outcomes.

## GitHub progressive commit suggestion
```bash
git init
git add README.md Assignment_Report.docx Task01_Class_Design
git commit -m "Complete Task 1 class design review"
git add Task02_Inheritance_Diamond && git commit -m "Complete Task 2 inheritance diamond"
git add Task03_Constructors_Members && git commit -m "Complete Task 3 constructors and members"
git add Task04_Polymorphic_Pointers && git commit -m "Complete Task 4 polymorphic pointers"
git add Task05_Cart_This_Pointer && git commit -m "Complete Task 5 object pointers and this"
git add Task06_Vehicle_Rental && git commit -m "Complete Task 6 vehicle rental hierarchy"
```

## Verification note
The source programs were compiled and run with the compiler above. The unsafe Task 4 variant intentionally fails under AddressSanitizer because it demonstrates deletion through a non-virtual base destructor; the corrected Task 4 variant is clean. Re-run the programs on your own computer and capture genuine terminal screenshots for your submission. Compiler diagnostics and `sizeof` values can vary by platform/ABI. No fabricated GitHub URL or commit history is included; create the repository and commits in your own GitHub account.

## Execution screenshots
Each task's `screenshots/` folder contains terminal-style PNG evidence generated from the captured compile and run output for every C++ source file in this package. The matching raw text logs are stored in `outputs/` with the suffix `_verified.txt`. These runs were performed with GCC 14.2.0 using C++17, `-Wall -Wextra -pedantic`. Re-run the programs on your own computer and capture local screenshots if your instructor specifically requires screenshots from your own device.
