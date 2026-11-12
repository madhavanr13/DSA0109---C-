# A4 – Exception strategy

| Failure | Exception |
|---|---|
| Negative charge/days | `std::invalid_argument` |
| Claim exceeds policy | `ClaimError : BillingError` |
| Unsupported scheme package | `UnknownPackageError : BillingError` |
| Missing patient record | `std::runtime_error` / `BillingError` |
| Allocation failure | `std::bad_alloc` |
| Invalid numeric text | `std::invalid_argument` from `std::stod` |

Potentially throwing: constructors validating input, bill calculations that validate, payer approval, parsing and allocation. Destructors and cleanup should be `noexcept`; a throwing destructor during stack unwinding can terminate the process. Destructors release resources and should not report recoverable errors.

Alternative: return `enum Status` / `optional` plus output parameters or error text. Normal path avoids exception machinery; every caller must inspect and propagate status. Error paths are explicit but can become verbose. Exception propagation centralises exceptional paths.
