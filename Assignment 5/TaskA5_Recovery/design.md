# A5 – Recovery and rethrowing

Catch at the layer that can add useful context. A repository/service boundary may log and use `throw;` to preserve the original exception; the application boundary catches `std::exception` and reports a safe message. Do not catch and silently ignore errors.

Stack unwinding destroys automatic objects in reverse construction order while an exception propagates. RAII objects (`std::vector`, `std::unique_ptr`, file streams) release resources automatically.

## Prediction
`~f ~main caught 42` then newline. `Guard g("f")` is destroyed while unwinding out of `f`; then `Guard m("main")` is destroyed as the handler exits the try scope. `not printed` is skipped because `throw` transfers control to a handler.

Manual `delete` in every catch path duplicates cleanup and creates leak-prone paths. RAII has the same asymptotic cleanup cost but substantially less error-prone code.
