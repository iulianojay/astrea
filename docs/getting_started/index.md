# Introduction

**Astrea** is a modern C++ library for astrodynamics modeling and simulation, and aerospace 
engineering analysis. It provides the fundamental tools for most common aerospace analysis 
applications, while also serving as a fast, extensible framework for more complex aerospace 
projects. Built with strongly typed units, coordinate frames, and orbital mechanics at its core, 
Astrea enables safe, high-performance aerospace computations.

## Open Source

**Astrea** is is available under the [LGPL license](https://github.com/iulianojay/astrea/blob/master/LICENSE.LESSER). 
Browse the source, ask questions, report bugs, or suggest improvements at <https://github.com/iulianojay/astrea>.

This license was chosen to allow both open source and commercial use of the library, while ensuring that improvements to the core code are shared back with the community.


## Designed for Aerospace Engineering

**Astrea** is built specifically for astrodynamics and aerospace engineering applications,
with design decisions focused on the unique requirements of orbital mechanics, spacecraft
analysis, and mission planning.

Key design principles include:

- **Strongly typed coordinate systems** that prevent common frame transformation errors
- **Unit-aware calculations** using [mp-units](https://github.com/mpusz/mp-units) to catch dimensional analysis errors at compile-time  
- **Domain-specific abstractions** for orbital elements, spacecraft, and celestial bodies
- **High-performance propagation** with both analytical and numerical methods
- **Extensible architecture** allowing custom force models, integrators, reference frames, and more

!!! important "Important: It's about safety and accuracy"

    Aerospace calculations involve complex coordinate transformations, unit conversions, and
    time system handling where small errors can have catastrophic consequences. Astrea's
    compile-time safety checks and strong typing are designed to catch these errors before
    they impact mission-critical calculations.


## Key Features

Many of the core features of Astrea were built based on experience in the aerospace industry, and many of the major pitfalls that astrodynamics libraries have historically had. The largest and perhaps most important is the issues of unit safety. Hidden unit conversions, implicit transitions between coordinate frames, and the general complexity of astrodynamics calculations can lead to small errors that have catastrophic consequences. By forcing developers to explicitly handle units and frames, Astrea eliminates a large class of these errors and provides a much safer development experience.

Beyond the core principles of safety, performance was a necessary benchmark for Astrea. Optimization is common in most of aerospace and as such, every second can be important. Custom integration, compiled ephemeris files, and fully constexpr system representations are just some of the ways that this library has been optimized for performance. In future releases, Astrea will be built with a set of benchmarks to allow users to test and profile the code on their own systems.

### Type Safety & Units

- **Strongly-typed units** using mp-units with compile-time dimensional analysis
```cpp
  const double timeSeconds = 3600.0;   // unsafe, implicit units, and error-prone
  const quantity<s> time = 3600.0 * s; // safe, explicit, and checked at compile-time
```
- **Custom unit support** with seamless unit conversions and extensions
```cpp
  Date now = Date::now();                         // Custom Julian Date clocks from std::chrono
  Date oneHourAgo = date - std::chrono::hours(1); // Implicit conversion from std::chrono to mp-units time
  Time oneHour = now - oneHourAgo;                // Dates, times, and chrono durations all interoperate 
  std::cout << oneHour.in(s);                     // "3600 s"
```
- **Strongly-typed frames** preventing common transformation errors
```cpp
  std::array<double> positionEci;                          // implicit units, and implicit frame
  CartesianVector<Distance, frames::earth::icrf> position; // explicit, and safe
```

### Astrodynamics Core
- **Multiple orbital element sets**: Cartesian, Keplerian, and Modified Equinoctial
```cpp
  // Cartesian elements
  Cartesian<frames::earth::icrf> cartesian{
    {7000.0 * km, 0.0 * km, 0.0 * km},            // position
    {0.0 * (km/s), 7.546 * (km/s), 0.0 * (km/s)}  // velocity
  };
  // Keplerian elements  
  Keplerian kepler{
    7000.0 * km,  // semimajoraxis
    0.01,         // eccentricity
    98.0 * deg,   // inclination
    0.0 * deg,    // raan
    0.0 * deg,    // arg of perigee
    0.0 * deg     // true anomaly
  };
```
- **Automatic element set conversions** with strongly-typed interfaces
```cpp
  AstrodynamicsSystem sys;

  // Either directly through constructors
  Keplerian kepler{/* ... */};
  Cartesian cartesian(kepler, sys.get_mu());
  Equinoctial equinoctial(cartesian, sys.get_mu());

  // Through a generic container for any element set
  OrbitalElements elements(kepler);
  Cartesian cartesian2 = elements.in_element_set<Cartesian>(sys);
  Equinoctial equinoctial2 = elements.in_element_set<Equinoctial>(sys);

  // Or using the more powerful State container
  State state(Date::now(), elements, sys);
  Cartesian cartesian3 = state.in_element_set<Cartesian>(); // explicit extraction
  Equinoctial equinoctial3 = state.in_element_set<Equinoctial>();

  state.convert_to_set<Cartesian>(); // in-place conversion of state elements
  state.convert_to_set<Equinoctial>(); 
```
- **Advanced propagation algorithms** supporting numerical and analytical methods
```cpp
  ForceModel forces;
  forces.add<AtmosphericForce>();
  forces.add<OblatenessForce>(sys, 100, 100);

  TwoBody twoBodyEom;                          // No forces
  J2MeanVop j2MeanEom;                         // Forces assumed
  CowellsMethod cowellsEom(forces);            // Regular force model
  KeplerianVop keplerianEom(forces, false);    // Input options for rounding errors
  EquinoctialVop equinoctialEom(forces, true); // Input options for singularities
```
- **Custom force models** with extensible equations of motion framework
```cpp
  ForceModel forces;
  forces.add<AtmosphericForce>();       // Add pre-defined forces
  forces.add<SolarRadiationPressure>();
  forces.add<MyCustomForce>(...);       // Or build a custom force model
```
- **Event detection** for user-defined conditions during propagation
```cpp
  Event burnEvent(ImpulsiveBurnAtPerigee()); 
  Event crossingEvent(CrashAtMinAltitude()); 
  // ... //
  integrator.propagate(state0, propTime, eoms, vehicle, store, { 
    burnEvent, 
    crossingEvent, 
    // ... //
  });
```

### Coordinate Systems & Time
- **Common frame transformations** with automatic coordinate conversions
```cpp
  // Position in ICRF frame
  RadiusVector<frames::earth::icrf> posIcrf{7000.0 * km, 0.0 * km, 0.0 * km};
  
  // Automatic transformation to J2000
  RadiusVector<frames::earth::j2000> posJ2000 = posIcrf.in_frame<frames::earth::j2000>(epoch);
  
  // Chain transformations coming soon!
  // auto posMarsIcrf = transform_to<frames::mars::icrf>(posIcrf, epoch);
```
- **Dynamic frame support** for time-varying coordinate systems
```cpp
  CartesianVector<Distance, frames::dynamic::ric> pos{7000.0 * km, 0.0 * km, 0.0 * km};
  frames::dynamic::ric ricFrame = frames::dynamic::ric::instantaneous{state}; // RIC frame defined by current state
  CartesianVector<Distance, frames::earth::icrf> posIcrf = ricFrame.rotate_out_of_this_frame<frames::earth::icrf>(pos, epoch);
```
- **Extensible frame definitions** supporting user-defined coordinate systems
```cpp
  namespace custom_frames {
    // Define spacecraft body frame
    struct SpacecraftBody : public Frame<SpacecraftBody> {
      // ...
      // ooh boy this is sure something right now but you can do it
      // ...
    };
  }
  
  CartesianVector<Thrust, custom_frames::SpacecraftBody> thrust_vector{1.0 * N, 0.0 * N, 0.0 * N};
```
- **Advanced time systems** including Julian Date, UTC, TAI, and other common time standards
```cpp
  Date now = Date::now();   // Current time in Julian Date
  Date utc = now.utc();     // Convert to UTC
  Date tai = now.tai();     // Convert to International Atomic Time
  JulianDate jd = now.jd(); // Get Julian Date
```

### Mission Analysis
- **Access analysis** with revisit calculations and link budget modeling
```cpp
  // Setup
  const Time accessResolution = minutes(5.0);
  const Date startDate = Date::now();
  const Date endDate = startDate + months(3.0);
  AstrodynamicsSystem sys;

  // Build a walker ball
  const Distance semimajor = 7000.0 * km;
  const Angle inclination = 98.0 * deg;
  const std::size_t T = 30;
  const std::size_t P = 6;
  const double F = 1.0;
  Constellation<Viewer> constelaltion(sys, startDate, semimajor, inclination, T, P F);

  // Ground station definition
  GroundStation station{"Denver", 39.7392 * deg, -104.9903 * deg, 1655.0 * m};
  
  // Access analysis
  AccessAnalyzer analyzer(accessResolution, startDate, endDate, sys, true);
  auto accesses = analyzer.find_accesses(constellation, { station }, true);
  
  // Revisit statistics
  const AccessStats stats(accesses); 
```
- **Spacecraft modeling** with vehicles, platforms, and payload definitions
```cpp
  class MySpacecraft : public Vehicle {
    // Custom spacecraft definition with mass properties, geometry, and subsystems
  };
  integrator.propagate(state0, propTime, eoms, { MySpacecraft() }, store);
```
- **Celestial body definitions** with customizable parameters
```cpp
  // Predefined celestial bodies
  auto earth = Earth();
  auto moon = Moon();
  auto mars = Mars();
  
  // Custom body definition
  CelestialBody asteroid{
    .name = "Bennu",
    .gravitational_parameter = 5.2 * (m*m*m / (s*s)),
    .radius = 245.0 * m,
    .rotation_period = 4.297 * h
  };
```

### External Integration
- **SPICE(ish) integration** with fast ephemeris access using compiled Chebyshev polynomials
- **Space-Track data clients** for automated orbital data retrieval
- **NASA validation** using published 6DoF test datasets
- **Mathematical utilities** optimized for dimensional analysis


## Getting Started

Ready to start using Astrea for your aerospace engineering projects? Explore the [Examples](../examples/index.md) to see Astrea in action with real-world scenarios.

For detailed API documentation and advanced usage patterns, visit the
[User's Guide](../users_guide/index.md) which covers everything from basic orbital mechanics
to custom force model development.

!!! tip "New to Astrodynamics?"

    If you're new to orbital mechanics or astrodynamics programming, start with our
    [Examples](../examples/index.md) which demonstrate common aerospace engineering tasks
    with clear explanations and working code.
