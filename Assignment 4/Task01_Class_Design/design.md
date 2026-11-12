# Task 1 – Class Design Review

## 1.1 Diagnosis
1. `name`, `id`, `basic` and payroll-related fields are duplicated, so changes must be repeated.
2. Public data members allow invalid values to be written without validation.
3. Equivalent fields use inconsistent names (`name`/`nm`, `id`/`code`), complicating common processing.
4. `da` is declared but never used, so the model contains misleading state.
5. `0.42` is a magic number; the allowance policy has no name or central definition.
6. The classes have no common base, so a single collection and polymorphic payroll loop are unavailable.
7. Adding a category requires duplicating common fields and changing client-side processing.

## 1.2 Repaired hierarchy
`Staff` owns common identity and basic-pay data and declares pure virtual `pay()` and `category()`. `Professor`, `LabAssistant`, `GuestFaculty`, and `ResearchFellow` supply category-specific calculations. Common state is protected in this teaching example; a production design could make it private and expose validated accessors. `unique_ptr<Staff>` provides polymorphic ownership.

```text
                 <<abstract>> Staff
             name, id, basic
             +pay() : double [pure virtual]
             +category() : string [pure virtual]
                       |
       +---------------+----------------+----------------+
       |               |                |                |
   Professor      LabAssistant     GuestFaculty    ResearchFellow
   research       (basic only)     hours, rate     fellowship
   +pay()         +pay()           +pay()          +pay()
```

## 1.3 Design defence (under 100 words)
The base class stores identity and defines the payroll contract once. Each staff category implements only its own pay rule. The payroll loop works with `Staff` pointers, so a new category can be added by deriving from `Staff` and overriding the required functions. Existing categories and the loop do not need to change. This reduces duplication and makes extension safer.

## Alternative: type field and switch
A single `Staff` record would hold a category enum plus fields for every possible category; `pay()` would switch on the enum. Both designs take O(1) time per pay calculation and O(1) storage per record, but the single record wastes space on fields unused by most categories. A new type requires changing the enum, the switch, validation and often input/output code. The polymorphic design adds a vtable pointer per object (implementation-dependent) but localises the new behaviour in a new derived class.

## Pseudocode
```text
ALGORITHM CalculatePayroll
INPUT: collection of Staff references
SET grandTotal <- 0
FOR EACH staffMember IN collection
    DISPLAY staffMember.category and staffMember.pay
    grandTotal <- grandTotal + staffMember.pay
END FOR
DISPLAY grandTotal
END ALGORITHM
```

## Complexity
For n staff records, the loop performs n virtual calls: O(n) time and O(1) auxiliary space, excluding storage for the n staff objects. Each individual pay calculation is O(1).
