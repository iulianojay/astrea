# Design

This section provides comprehensive documentation of Astrea's design philosophy, architecture, and implementation details. These documents explain the reasoning behind key design decisions and provide insights for contributors, researchers, and advanced users who want to understand how Astrea works under the hood.

## Design Philosophy

### Safety-First Approach

Astrea is built around the principle that **correctness and safety are paramount** in aerospace calculations. Small errors in orbital mechanics can have catastrophic consequences in real missions, so the library's design prioritizes preventing errors at compile-time rather than detecting them at runtime.

Key safety mechanisms:
- **Compile-time dimensional analysis** using mp-units to catch unit errors
- **Strong typing for coordinate frames** to prevent reference frame confusion
- **Immutable data structures** where possible to prevent accidental modification
- **Explicit conversions** requiring user intent for potentially lossy operations

### Domain-Driven Design

Astrea's APIs and abstractions directly reflect the conceptual model that aerospace engineers use when thinking about orbital mechanics and mission analysis.

Domain alignment:
- **Natural language mapping** where C++ code reads like aerospace engineering notation
- **Familiar abstractions** that mirror textbook presentations of astrodynamics
- **Intuitive workflows** that follow the logical sequence of aerospace analysis tasks
- **Professional terminology** using standard aerospace engineering vocabulary

## Architectural Overview

Astrea follows a layered architecture where each layer builds upon lower-level foundations while maintaining clear separation of concerns. See the [Project Structure](../getting_started/project_structure.md) and [Architecture](architecture.md) for details on the organization of source code and modules.

## Design Principles

### 1. Explicit Over Implicit

Astrea favors explicit operations that make user intent clear over convenient but potentially ambiguous shortcuts.

**Example**: Coordinate frame transformations require explicit specification of source and target frames rather than assuming a "default" frame.
```cpp
auto transformed_state = transform(state, from_frame, to_frame);             // implicit, unclear
auto state2<to_frame> = transform<from_frame, to_frame>(state1<from_frame>); // explicit, clear
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

## Detailed Design Documents

The following sections provide in-depth coverage of specific design aspects:

### [Architecture](architecture.md)
Detailed component architecture, data flow, and system boundaries. Covers the interaction between different layers and the rationale for the modular design.

### [Type System](type_system.md)
Comprehensive coverage of Astrea's type system, including strong typing for coordinate frames, unit-aware calculations, and compile-time safety mechanisms.

### [Performance](performance.md)
Detailed analysis of performance considerations, optimization strategies, and benchmarking methodologies used to ensure Astrea meets real-time requirements.

### [Extensibility](extensibility.md)
Patterns and interfaces for extending Astrea with custom force models, coordinate frames, propagators, and analysis tools.

### [Testing](testing.md)
Testing philosophy, validation strategies, and quality assurance processes including comparison with reference implementations and real-world data.

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

## Evolution and Future Considerations

### Planned Architecture Changes

- **Modular compilation**: Allow compilation of subsets of functionality to reduce build times
- **Plugin architecture**: Runtime loading of custom extensions for specialized applications
- **Distributed computing**: Support for distributed orbital determination and Monte Carlo analysis
- **GPU acceleration**: CUDA/OpenCL support for computationally intensive operations

### Compatibility Commitments

- **ABI compatibility**: Within minor versions for dynamic linking scenarios
- **Data format stability**: Persistent storage formats remain readable across versions
- **Standard compliance**: Continued adherence to CCSDS and other aerospace standards
