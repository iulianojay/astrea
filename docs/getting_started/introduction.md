# Introduction

**Astrea** is a modern C++ library for astrodynamics modeling and simulation, and aerospace 
engineering analysis. It provides the fundamental tools for most common aerospace analysis 
applications, while also serving as a fast, extensible framework for more complex aerospace 
projects. Built with strongly typed units, coordinate frames, and orbital mechanics at its core, 
Astrea enables safe, high-performance aerospace computations.

## Open Source

**Astrea** is is available under the [LGPL license](https://github.com/iulianojay/astrea/blob/master/LICENSE.LESSER). Browse the source, ask questions, report bugs, or suggest improvements at <https://github.com/iulianojay/astrea>.


## Designed for Aerospace Engineering

**Astrea** is built specifically for astrodynamics and aerospace engineering applications,
with design decisions focused on the unique requirements of orbital mechanics, spacecraft
analysis, and mission planning.

Key design principles include:

- **Strongly typed coordinate systems** that prevent common frame transformation errors
- **Unit-aware calculations** using [mp-units] to catch dimensional analysis errors at compile-time  
- **Domain-specific abstractions** for orbital elements, spacecraft, and celestial bodies
- **High-performance propagation** with both analytical and numerical methods
- **Extensible architecture** allowing custom force models, integrators, reference frames, and more

!!! important "Important: It's about safety and accuracy"

    Aerospace calculations involve complex coordinate transformations, unit conversions, and
    time system handling where small errors can have catastrophic consequences. **Astrea's
    compile-time safety checks and strong typing are designed to catch these errors before
    they impact mission-critical calculations.**

[mp-units]: https://github.com/mpusz/mp-units


## Key Features

### Astrodynamics Core

- **Orbital mechanics** with support for multiple element sets (Keplerian, Cartesian, Equinoctial, etc.)
- **Coordinate frame transformations** with compile-time safety and automatic conversions
- **Time systems** supporting Julian Date, UTC, TT, and other common aerospace time standards
- **Celestial body definitions** with built-in models for Earth, Moon, and planets
- **SPICE integration** with Chebyshev polynomial ephemerides for fast, accurate computations

### Propagation and Analysis

- **Multiple propagation methods** including analytical (Kepler, J2) and numerical integrators
- **Force model framework** supporting user-defined perturbations and environmental effects
- **Event detection** during propagation for apogee/perigee, eclipse, and custom events
- **Access analysis** with link budget calculations and interference modeling
- **Trajectory optimization** tools for maneuver planning and mission design

### Safety and Performance

- **Compile-time unit safety** preventing dimensional analysis errors
- **Strong typing** for frames to catch tricky coordinate transformation errors
- **Zero-overhead abstractions** with performance matching hand-optimized code
- **Memory-efficient** data structures optimized for real-time applications

### Data Integration

- **Spacetrack.org client** for automated TLE downloads and orbital data management
- **Standard format support** for CCSDS OEM/OPM, and NASA test data formats
- **Database integration** for efficient storage and retrieval of orbital data
- **CSV and JSON I/O** for interoperability with other aerospace tools

### Extensible Architecture

- **Custom spacecraft definitions** with configurable mass, area, and other properties
- **User-defined force models** following a common interface pattern
- **Modular integration** supporting both fixed and adaptive step-size methods

### Real-World Validation

- **NASA test data comparisons** ensuring accuracy against published 6-DoF benchmarks
- **High-fidelity SPICE comparisons** validating ephemeris calculations
- **Comprehensive test suite** covering edge cases and numerical stability


## Getting Started

Ready to start using Astrea for your aerospace engineering projects? Check out our
[Quick Start Guide](./quick_start.md) or explore the [Examples](../examples/) to see
Astrea in action with real-world scenarios.

For detailed API documentation and advanced usage patterns, visit the
[User's Guide](../users_guide/) which covers everything from basic orbital mechanics
to custom force model development.

!!! tip "New to Astrodynamics?"

    If you're new to orbital mechanics or astrodynamics programming, start with our
    [Examples](../examples/) which demonstrate common aerospace engineering tasks
    with clear explanations and working code.
