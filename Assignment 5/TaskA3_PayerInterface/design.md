# A3 – Abstract payer design

`Payer` is abstract and declares `amountCovered(const Bill&) const`. `SelfPay` covers zero, `Insurance` stores a cover limit and co-payment percentage, and `GovernmentScheme` stores fixed package rates. A new `CorporatePayer` can be added by deriving from `Payer`; existing bill and payer classes remain unchanged.

Alternative: store a function pointer or `std::function<double(const Bill&)>` policy. Calls are O(1) in either approach. A class stores policy data as fields; a function object can capture data (such as limit) in its closure. The abstract class gives a named, extensible type hierarchy; `std::function` is more flexible but may incur type-erasure/storage overhead.
