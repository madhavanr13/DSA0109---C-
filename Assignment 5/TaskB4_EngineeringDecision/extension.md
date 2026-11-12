# B4 – Final engineering decision

The implementation adds `EmergencyBill` and `CorporatePayer` without modifying the existing bill and payer interfaces. Earlier OP/IP/day-care classes continue to satisfy the same abstract contracts. The core program uses `unique_ptr`, so bills are reclaimed even if a calculation throws.

**Production decision:** the polymorphic design is suitable where bill and payer types evolve independently and a common heterogeneous list is required. Exceptions are suitable for exceptional invalid input and infrastructure failures, not routine expected business outcomes at high volume. Validate at input boundaries, use typed exceptions for exceptional failures, log once at the service boundary, and preserve audit records. Benchmark results must be taken on production-like hardware before making a throughput claim.

**Plug-in/rule alternative:** load rates and package definitions from validated configuration. Per-bill processing may require rule lookup/interpreting (often O(1) average with hash lookup, or O(log r) with ordered rules); storage is O(r) for r rules. It reduces code deployments but increases configuration validation, versioning and security risks. C++ class extensions provide compile-time type safety but require a build/deployment.
