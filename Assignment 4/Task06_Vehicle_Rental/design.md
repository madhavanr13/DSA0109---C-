# Task 6 – Vehicle Rental Fleet Design Challenge

## Stage 1: Requirements and entities
Entities: `Vehicle` (registration, daily rate, rental state), `Bicycle`, `TwoWheeler`, `Car`, `ElectricCar`, and extension `ElectricBus`. Differing behaviour: type description and energy charge. Motor vehicles track fuel or charge; cars additionally track seating capacity; electric vehicles are billed by kWh. Testable requirements: each vehicle can be listed; an available vehicle can be rented once; a rented vehicle can be returned; invalid state transitions and invalid day counts are rejected; base pointers invoke the correct derived calculation; a late day adds 1.5 times the daily rate; adding a new type does not modify existing classes.

## Stage 2: Hierarchy
```text
                 <<abstract>> Vehicle
 registration, dailyRate, rented
 +rent(), +returnVehicle(), +type() [pure]
 +energyCharge() [pure], +printDetails() [pure]
       |             |           |            |              |
    Bicycle      TwoWheeler      Car       ElectricCar    ElectricBus
                  fuel         seats+fuel   seats+kWh      capacity+kWh
```
All derived relationships are public single inheritance. There is no additional member class required by the supplied requirements; registration could be wrapped in a value-type `Registration` class if validation grows.

## Stage 3: Critical decisions
`Vehicle` owns shared identity, rate and rental state. Derived classes own only category-specific data and implement pure virtual operations. The fleet is `vector<unique_ptr<Vehicle>>`, a safer growable equivalent of an array of base-class pointers. The virtual destructor ensures correct cleanup. `override` catches signature mistakes.

## Stage 4: Pseudocode
```text
ALGORITHM RentVehicle(vehicle)
IF vehicle.rented = TRUE THEN
    RAISE RentalStateError
END IF
SET vehicle.rented <- TRUE
END ALGORITHM

ALGORITHM ReturnVehicle(vehicle, daysUsed, lateDays)
IF vehicle.rented = FALSE OR daysUsed < 1 OR lateDays < 0 THEN
    RAISE InvalidRentalError
END IF
SET vehicle.rented <- FALSE
SET charge <- daysUsed * vehicle.dailyRate
              + lateDays * vehicle.dailyRate * 1.5
              + vehicle.energyCharge()
RETURN charge
END ALGORITHM
```

## Stage 5: Implementation and extension
`main.cpp` rents and returns one of each required type and the added `ElectricBus`. The new type derives from `Vehicle` and implements the virtual interface; no existing class is changed. The sample energy rates are explicit demonstration assumptions: fuel Rs.105/L and electricity Rs.8/kWh. They are not stated by the question and can be changed to the faculty's chosen rates.

## Alternative: type code and switch
A single `Vehicle` record would need fields for every possible vehicle type and a switch in `charge()`. Both approaches have O(1) charge calculation time and O(1) storage per object asymptotically. The switch record wastes space for irrelevant fields; the polymorphic object carries an implementation-dependent vptr. Adding a new type requires editing the switch and validation paths, while the hierarchy adds a new derived class. For n fleet vehicles, listing is O(n); memory is O(n).
