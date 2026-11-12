# A1 – Polymorphic bill hierarchy

## Common interface and shared state
Every bill exposes `total() const`, `type() const`, and `print() const`. The common state is the patient identifier/name. `total()` and `type()` are pure virtual so `Bill` is abstract; `print()` is a concrete virtual-friendly operation that calls the virtual functions.

## UML (text form)
```text
                 <<abstract>> Bill
          patient: string
          +total(): double {pure virtual}
          +type(): string {virtual}
          +print(): void
          +~Bill() {virtual}
             /       |       |        \
      OutPatient InPatient DayCareBill EmergencyBill
      total()    total()   total()     total()
      type()     type()    type()      type()
```

## SIMATS-style pseudocode
```text
ALGORITHM CalculateDailyTotal
INPUT: bills[0..n-1] as references/pointers to Bill
OUTPUT: dailyTotal
BEGIN
    SET dailyTotal ← 0
    FOR i ← 0 TO n-1 DO
        CALL bills[i].print()
        SET dailyTotal ← dailyTotal + bills[i].total()
    END FOR
    DISPLAY dailyTotal
END
```

## Alternative: tagged structure + switch
Store a `kind` enum and all possible charge fields in one record; `total()` switches on kind. Both process n bills in O(n) time. A tagged record can waste space because it reserves fields for multiple kinds. Adding a type requires changing the switch and central data structure; virtual dispatch localises the new calculation in a new derived class.
