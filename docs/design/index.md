# Design

This section provides comprehensive documentation of Astrea's design philosophy, architecture, and implementation details. These documents explain the reasoning behind key design decisions and provide insights for contributors, researchers, and advanced users who want to understand how Astrea works under the hood.

### Overview

The following sections provide in-depth coverage of specific design aspects:
- [Architecture](architecture.md)
- [Type System](type_system.md)
- [Performance](performance.md)
- [Extensibility](extensibility.md)
- [Testing](testing.md)

## Design Principles

### 1. Explicit Over Implicit

Astrea favors explicit operations that make user intent clear over convenient but potentially ambiguous shortcuts.

**Example**: Coordinate frame transformations require explicit specification of source and target frames rather than assuming a "default" frame.
```cpp
auto transformed_state = transform(state, frameA, frameB);       // implicit, unclear after this line
auto state2<frameB> = transform<frameA, frameB>(state1<frameA>); // explicit, clear
```

### 2. Fail Fast and Loud

When errors occur, they should be detected as early as possible (preferably at compile-time) and provide clear, actionable diagnostic information.

**Example**: Unit mismatches in calculations are caught at compile-time with detailed error messages indicating the expected and actual units.
```cpp
double velocityMpS = 7.8;            // implicit, error prone, harder to read
quantity<m/s> velocity = 7.8 * km/s; // explicit, safe, self-documenting
```

### 3. Composition and Type-Erasure Over Inheritance

Astrea uses composition and template-based design patterns rather than deep inheritance hierarchies to achieve flexibility and extensibility.

**Example**: Propagation, event detection, and step watchers, all common classes for users to specialize, are all designed around type-erased containers instead of traditional inheritance.

### 4. Immutability by Default

Data structures are immutable unless mutation is explicitly necessary, reducing the chance of accidental modification and enabling optimization.

**Example**: Functions are set to const by default, and all values are passed-by-reference unless explicitly required. 

## Design Trade-offs

### Compile-time vs. Runtime Flexibility

**Trade-off**: Astrea prioritizes compile-time safety and performance over runtime polymorphism.

**Rationale**: Aerospace calculations typically involve known coordinate systems and unit types at design time, making the compile-time approach more suitable than dynamic typing.

**Implications**: Custom extensions require recompilation but achieve better performance and safety.

### Ease of Use vs. Correctness

**Trade-off**: Astrea sometimes requires more verbose code to ensure correctness.

**Rationale**: In aerospace applications, the cost of errors far outweighs the cost of additional development time.

**Implications**: Learning curve may be steeper, but operational safety is significantly improved.

### Standards Compliance vs. Innovation

**Trade-off**: Astrea balances adherence to aerospace standards with incorporation of modern programming techniques.

**Rationale**: Standards ensure interoperability and familiarity, while modern techniques improve safety and performance.

**Implications**: Some non-standard but beneficial patterns are used where they provide clear advantages.
