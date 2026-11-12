# Task 5 – Pointers to Objects and the this Pointer

## Four access forms
- Direct: `Cart c; c.total();` – simplest automatic lifetime and no null pointer.
- Pointer: `Cart* p = &c; p->total();` – non-owning indirection; can be null and must not outlive `c`.
- Reference: `Cart& r = c; r.total();` – alias with no reseating and normally non-null after initialisation.
- Dynamic: `Cart* p = new Cart; ... delete p;` – dynamic lifetime, but raw ownership requires exactly one matching delete. Prefer `std::unique_ptr<Cart>` in production.

`this` is the implicit pointer to the object on which a non-static member function is invoked. `*this` is that object as an lvalue reference. Returning `*this` by `Cart&` allows chaining without copying. `this->discount` distinguishes the data member from a parameter with the same name.

## Required complete-code output
```text
324.00
```
The sum is 60 + 120 + 180 = 360; a 10% discount leaves 324. Returning `Cart` by value would create a copy at each chain step and later calls would operate on temporaries rather than the original object; it also costs more copying.

## Highest total in an array of pointers
The program builds a pointer array referring to existing cart objects, then scans it and retains the pointer with the largest `total()`. For n carts this takes O(n) time and O(1) extra search space.

## Alternative: vector<Cart>
A vector of objects stores the objects contiguously and owns their lifetimes; a vector of pointers stores one pointer per element but the objects live elsewhere. Both scans are O(n). Vector growth can reallocate its storage and invalidate pointers/references/iterators to vector elements. A vector of pointers does not move the separately allocated objects when the pointer vector reallocates, but the pointed-to objects still need valid ownership/lifetime management.
