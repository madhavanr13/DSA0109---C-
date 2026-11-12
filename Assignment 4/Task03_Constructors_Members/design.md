# Task 3 – Constructors in Derived Classes and Member Classes

## Base constructor arguments
A derived constructor initialises its direct base in the member-initialiser list, for example `Student(...) : Person(name, age), ...`. A virtual base is initialised only by the most-derived class. An intermediate class's virtual-base initialiser is ignored when constructing a more-derived object, because only the final object knows the single shared virtual-base state that is required.

## Member classes
`Person` has an `Address` object and `Student` has a `Course` object. These are composition relationships. The member constructors run automatically from the owner's initializer list. This avoids manual `new`/`delete` and gives deterministic lifetime.

## Construction/destruction rules
1. Virtual base classes first (if present; order determined by depth-first, left-to-right traversal of the inheritance graph).
2. Non-virtual direct base classes in the order listed in the class declaration.
3. Data members in their declaration order, regardless of initializer-list order.
4. Constructor body.
Destruction is the reverse: destructor body, members in reverse declaration order, then base classes in reverse construction order. In the supplied experiment, `Student` and `Staff` use virtual inheritance, so `TeachingAssistant` contains one shared `Person` subobject. The most-derived `TeachingAssistant` constructor initialises that virtual base directly.

## Given Engine/Vehicle/Car prediction
```text
Vehicle Engine Car | ~Car ~Engine ~Vehicle
```
The base `Vehicle` is constructed before member `Engine`, then `Car`'s body. On scope exit the derived destructor body runs first, then member `Engine`, then base `Vehicle`.

## Complete Code
`complete_code.cpp` prints the required `192311001 Kavya (19) Salem-636001`. Reordering initializer-list entries does not change actual initialization order; compilers may issue `-Wreorder` when the list order conflicts with declaration order.

## Alternative: pointer to Address
With `Address* home`, the constructor must allocate the object, the destructor must delete it, and copy construction/assignment must define deep-copy or shared-ownership behaviour. A raw pointer adds pointer storage and a separate allocation; allocation adds runtime overhead and introduces leak/double-delete risks. Prefer a value member or `std::unique_ptr<Address>` unless dynamic lifetime is genuinely required.

## Complexity
Construction/destruction of the fixed number of members is O(1), excluding dynamic string allocation. Address formatting is O(city-name length). The object stores its member objects inline; dynamic strings may own separate buffers.
