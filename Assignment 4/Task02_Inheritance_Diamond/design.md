# Task 2 – From Requirement to Hierarchy

## 2.1 Relationships and inheritance types
- `Student is-a Person`: public single inheritance.
- `Staff is-a Person`: public single inheritance.
- `TeachingAssistant is-a Student` and `is-a Staff`: public multiple inheritance. Since both paths share `Person`, the overall structure is hybrid inheritance with a diamond.
- `ResearchScholar is-a Student`: public multilevel inheritance (`Person -> Student -> ResearchScholar`).
- Address/contact details, if expanded into a separate `Address` type, are has-a relationships and should be represented by member objects (composition), not inheritance.

## 2.2 Diamond problem
Without virtual inheritance, a `TeachingAssistant` contains two independent `Person` subobjects: one through `Student`, another through `Staff`. Access to `name` or `id` is ambiguous and the common identity is duplicated. Declaring both intermediate classes as `virtual public Person` makes the most-derived object contain one shared virtual `Person` subobject. The most-derived constructor (`TeachingAssistant`) is responsible for initialising it.

## 2.3 Class design
The source file implements `Person`, `Student`, `Staff`, `TeachingAssistant`, and `ResearchScholar`. Public inheritance expresses substitutability: a student or staff member can be used wherever a person is expected. `Person` data is protected for concise demonstration; private data with protected/public accessors is preferable in a larger system. `TeachingAssistant` explicitly initialises the virtual base.

## 2.4 Access table for `Person` member access through `Student`
| Member in Person | public inheritance | protected inheritance | private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | not directly accessible | not directly accessible | not directly accessible |

## Given prediction
For the provided virtual-inheritance example, the output is:
```text
Person Student Staff TA
```
`Person` is constructed once because it is a shared virtual base. Virtual bases are constructed before non-virtual direct bases; direct bases follow their declaration order (`Student`, then `Staff`), then the derived constructor body runs. Without `virtual`, two `Person` constructors run, producing `Person Student Person Staff TA` (the order follows the two inheritance paths).

## Alternative: composition
`TeachingAssistant` could contain `Student student; Staff staff;`. This is a has-a model, not an is-a model. Each member contains its own `Person` subobject, so there are two identities unless the design is refactored to share a `Person` member. Access becomes `ta.student.name` or `ta.staff.name`, not simply `ta.name`. Composition removes base-class ambiguity but does not automatically share common state. `sizeof` is implementation-dependent and includes both members plus alignment; virtual inheritance can add implementation-specific pointer/offset metadata.

## Complexity
Member access and inheritance-based access are O(1). Object storage is O(1) per object; exact byte counts depend on compiler, ABI, alignment, string representation and virtual-inheritance implementation. The program prints `sizeof` values in its experiment rather than assuming fixed sizes.
