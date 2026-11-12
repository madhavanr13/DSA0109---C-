# A2 – Runtime binding

**Early binding:** a non-virtual call is resolved from the static type at compile time. **Late binding:** a virtual call through `Bill*` uses the dynamic object's override. `b->total()` dispatches to `OutPatient::total()` when `b` points to an `OutPatient`.

## Conceptual vtables
```text
Bill vtable:          [~Bill, total (pure), type]
OutPatient vtable:    [~OutPatient, OutPatient::total, OutPatient::type]
InPatient vtable:     [~InPatient, InPatient::total, InPatient::type]
```
Object's hidden vptr selects the derived vtable. A non-virtual `show()` can still call a virtual `total()`; the call inside `show()` is dynamically dispatched.

## Virtual destructor
Deleting a derived object through `Bill*` must run the derived destructor and then the base destructor. A virtual base destructor guarantees this. Without it, deleting through a base pointer is undefined behaviour.

## Predict output before execution
Prediction: `500 ~OPBill ~Bill` followed by a newline. `show()` itself is non-virtual, but its call to virtual `total()` dispatches to `OPBill::total()`. Destruction occurs derived first, then base.

## Alternative
Using `dynamic_cast` to test each of k derived types can require up to k checks per bill; virtual dispatch performs one virtual call. Vptr overhead is typically one pointer per polymorphic object; exact ABI layout is implementation-specific.
