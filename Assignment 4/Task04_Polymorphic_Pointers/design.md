# Task 4 – Pointers to Derived Classes: Forensics

## 4.1 Defects
- `rate()` is non-virtual in the original code, so `Account*` calls `Account::rate()` (static binding) even when it points to a `SeniorAccount`.
- The base destructor is non-virtual. Deleting a derived object through `Account*` is undefined behaviour; derived cleanup is not guaranteed. The `history` allocation can leak and the program may trigger sanitizer diagnostics.
- `Account copy = SeniorAccount();` performs object slicing: only the `Account` base subobject is copied; the derived portion is discarded.
- The original raw-pointer ownership has no automatic cleanup if an exception or early return occurs.

## 4.2 Evidence and safe repair
`main.cpp` repairs the design using virtual dispatch, `override`, a virtual destructor, and `std::unique_ptr<Account>`. The senior destructor releases `history_`. `predict_output.cpp` isolates the binding/slicing question.

## Given prediction
```text
3.5 4 3.5
```
`p->rate()` is statically bound to `Account::rate()` because it is non-virtual. `p->vrate()` is dynamically dispatched to `SeniorAccount::vrate()`. `copy` is a sliced standalone `Account`, so its virtual call uses `Account::vrate()`.

## 4.4 Prevention rules
1. Give polymorphic base classes a public virtual destructor.
2. Mark derived overrides with `override`, and store polymorphic objects by pointer/reference (prefer smart pointers), not by value in a base-class container.

## Alternative: vector of unique_ptr
`std::vector<std::unique_ptr<Account>>` owns each dynamic object and automatically deletes it. Processing n accounts remains O(n), with O(1) virtual dispatch per account and O(n) pointer storage. It prevents manual-delete omissions and ensures derived destruction through the virtual destructor. It does not make non-virtual functions virtual and does not prevent slicing if code separately copies an object by value.
