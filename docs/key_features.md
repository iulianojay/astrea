
## Key Features

Many of the core features of Astrea were built based on experience in the aerospace industry, and many of the major pitfalls that astrodynamics libraries have historically had. The largest and perhaps most important is the issues of unit safety. Hidden unit conversions, implicit transitions between coordinate frames, and the general complexity of astrodynamics calculations can lead to small errors that have catastrophic consequences. By forcing developers to explicitly handle units and frames, Astrea eliminates a large class of these errors and provides a much safer development experience.

Beyond the core principles of safety, performance was a necessary benchmark for Astrea. Optimization is common in most of aerospace and as such, every second can be important. Custom integration, compiled ephemeris files, and fully compile-time system representations are just some of the ways that this library has been optimized for performance. In future releases, Astrea will be built with a set of benchmarks to allow users to test and profile the code on their own systems.

* **Type Safety & Units**
  - Strongly-typed units using mp-units with compile-time dimensional analysis
  - Custom unit support with built-in unit conversions and extensions
  - Strongly-typed frames preventing common transformation errors
  - Extensible frame definitions supporting user-defined coordinate systems
  - Automatic, compile-time frame transformations with support for time-varying frames

* **Astrodynamics Core**
  - Multiple strongly-typed, frame-aware orbital element sets: Cartesian, Keplerian, and Modified Equinoctial
  - Automatic element set conversions with strongly-typed interfaces
  - Advanced propagation algorithms supporting numerical and analytical methods
  - Custom force models with extensible equations of motion framework
  - Event detection for user-defined conditions during propagation

* **Coordinate Systems & Time**
  - Common frame transformations with automatic coordinate conversions
  - Dynamic frame support for time-varying coordinate systems
  - Extensible frame definitions supporting user-defined coordinate systems
  - Advanced time systems including Julian Date, UTC, TAI, and other common time standards

* **Mission Analysis**
  - Access analysis with revisit calculations and link budget modeling
  - Spacecraft modeling with vehicles, platforms, and payload definitions
  - Celestial body definitions with customizable parameters
  
* **External Integration**
  - SPICE(ish) integration with fast ephemeris access using compiled Chebyshev polynomials
  - Space-Track data clients for automated orbital data retrieval
  - NASA validation using published 6DoF test datasets
  - Mathematical utilities optimized for dimensional analysis

* **Recent Additions**
  - Event Detection and Scheduling: User-defined events during propagation with callback support
  - Automatic Frame Translations: Time-varying coordinate systems with automatic transformations
  - Custom Step Watchers: User-defined callbacks for monitoring and modifying propagation steps
  - Improved Installation: CMake packaging and cross-platform deployment
  - 6-DoF Simulation: Complete attitude dynamics with control system modeling
  - Performance Benchmarks: Google Benchmark integration with speed guarantees
  - Comprehensive Frame Transformations: Support for a wide range of celestial bodies and dynamic frames
  - Cislunar Dynamics: CR3BP propagator and synodic frame support


### Examples: Type Safety & Units
*Note: The code below is pseudo-code and is meant to demonstrate the capabilities of Astrea. It is not guaranteed to compile or run as-is, but is meant to illustrate the features of the library.*
```cpp
  const double timeSeconds = 3600.0;   // unsafe, implicit units, and error-prone
  const quantity<s> time = 3600.0 * s; // safe, explicit, and checked at compile-time
```
```cpp
  Date now = Date::now();                         // Custom Julian Date clocks from std::chrono
  Date oneHourAgo = date - std::chrono::hours(1); // Implicit conversion from std::chrono to mp-units time
  Time oneHour = now - oneHourAgo;                // Dates, times, and chrono durations all interoperate 
  std::cout << oneHour.in(s);                     // "3600 s"
```
```cpp
  std::array<double> positionEci;                                      // implicit units, and implicit frame
  RadiusVector<icrf> position;                                         // explicit, and safe
  // RadiusVector<j2000> positionJ2000 = position;                     // Compile-time error!
  RadiusVector<j2000> positionJ2000 = position.in_frame<j2000>(epoch); // explicit frame transformation
```

### Examples: Astrodynamics Core
```cpp
  // Cartesian elements
  Cartesian<earth::icrf> cartesian{
    {7000.0 * km, 0.0 * km, 0.0 * km},            // position
    {0.0 * (km/s), 7.546 * (km/s), 0.0 * (km/s)}  // velocity
  };
  // Keplerian elements  
  Keplerian<earth::icrf> kepler{
    7000.0 * km,  // semimajoraxis
    0.01,         // eccentricity
    98.0 * deg,   // inclination
    0.0 * deg,    // raan
    0.0 * deg,    // arg of perigee
    0.0 * deg     // true anomaly
  };
```
```cpp
  // Either directly through constructors
  Keplerian<earth::icrf> keplerian{/* ... */};
  Cartesian<earth::icrf> cartesian(keplerian, mu);
  Equinoctial<earth::icrf> equinoctial(cartesian, mu);

  // Through a generic container for any element set
  OrbitalElements elements(keplerian);
  auto cartesian2 = elements.in_element_set<Cartesian<earth::icrf>>(mu);
  auto equinoctial2 = elements.in_element_set<Equinoctial<earth::icrf>>(mu);

  // Or using the more powerful State container
  State state(Date::now(), elements);
  auto cartesian3 = state.in_element_set<Cartesian<earth::icrf>>();     // explicit extraction
  auto equinoctial3 = state.in_element_set<Equinoctial<earth::icrf>>(); // automatic element conversion
  auto keplerian3 = state.in_element_set<Keplerian<earth::itrf>>();     // automatic frame transformation

  state.convert_to_set<Cartesian<earth::icrf>>(); // in-place conversion of state elements
  state.convert_to_set<Equinoctial<earth::icrf>>(); 
```
```cpp
  ForceModel forces;
  forces.add<AtmosphericForce>();
  forces.add<OblatenessForce, planets::Earth, 100, 100>();
  // ... //

  TwoBody twoBodyEom;                          // No forces
  J2MeanVop j2MeanEom;                         // Forces assumed
  CowellsMethod cowellsEom(forces);            // Regular force model
  KeplerianVop keplerianEom(forces, false);    // Input options for rounding errors
  EquinoctialVop equinoctialEom(forces, true); // Input options for singularities
```
```cpp
  ForceModel forces;
  forces.add<AtmosphericForce>();       // Add pre-defined forces
  forces.add<SolarRadiationPressure>();
  forces.add<MyCustomForce>(...);       // Or build a custom force model
```
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

### Examples: Coordinate Systems & Time
```cpp
  // Build an earth-fixed position vector
  RadiusVector<earth::itrf> posEcef{7000.0 * km, 0.0 * km, 0.0 * km};
  
  // Transformation to ICRF built at compile time
  RadiusVector<earth::icrf> posIcrf = posEcef.in_frame<earth::icrf>(epoch);
  
  // Transformations can also be chained automatically
  RadiusVector<mars::icrf> posMarsIcrf = posEcef.in_frame<mars::icrf>(epoch); 

  // Even automatically transformation velocity and acceleration vectors while handling aberrations
  AccelerationVector<earth::icrf> accIcrf{
    0.0 * (km/s/s), -0.001 * (km/s/s), 0.0 * (km/s/s)
  };

  // Handles velocity/accel aberrations for non-inertial frames
  auto accJ2000 = accIcrf.in_frame<earth::j2000>(epoch, r1, v1); 
```
```cpp
  // The frame system can also interact with dynamic (runtime) frames, such as RIC frames
  RadiusVector<dynamic::ric> pos{7000.0 * km, 0.0 * km, 0.0 * km};
  dynamic::ric ricFrame = dynamic::ric::instantaneous{state}; 
  RadiusVector<earth::icrf> posIcrf = ricFrame.rotate_out_of_this_frame<earth::icrf>(pos, epoch);
```
```cpp
  // Adding a custom frame is as simple as defining a new struct and inheriting from the Frame base class
  constexpr inline struct SpacecraftBody : public Frame<"MySpacecraftFrame", SpacecraftOrigin, DynamicAxis> {
  } SpacecraftBody;
  
  ForceVector<SpacecraftBody> thrust_vector{1.0 * N, 0.0 * N, 0.0 * N};
```
```cpp
  Date now = Date::now();   // Current time in Julian Date
  Date utc = now.utc();     // Convert to UTC
  Date tai = now.tai();     // Convert to International Atomic Time
  JulianDate jd = now.jd(); // Get Julian Date
```

### Examples: Mission Analysis
```cpp
  // Setup
  const Time accessResolution = minutes(5.0);
  const Date startDate = Date::now();
  const Date endDate = startDate + months(3.0);

  // Build a walker ball
  const Distance semimajor = 7000.0 * km;
  const Angle inclination = 98.0 * deg;
  const std::size_t T = 30;
  const std::size_t P = 6;
  const double F = 1.0;
  Constellation<Viewer> constelaltion(startDate, semimajor, inclination, T, P, F);

  // Ground station definition
  GroundStation station{"Denver", 39.7392 * deg, -104.9903 * deg, 1655.0 * m};
  
  // Access analysis
  AccessAnalyzer analyzer(accessResolution, startDate, endDate, sys, true);
  auto accesses = analyzer.find_accesses(constellation, { station }, true);
  
  // Revisit statistics
  const AccessStats stats(accesses); 
```
```cpp
  class MySpacecraft : public Vehicle {
    // Custom spacecraft definition with mass properties, geometry, and subsystems
  };
  integrator.propagate(state0, propTime, { MySpacecraft() });
```
```cpp
  // Many pre-defined celestial bodies
  using earth = planets::Earth;
  using moon = moons::Moon;
  using mars = planets::Mars;
  
  // Custom body definitions that seemlessly hook into the frame system
  inline constexpr inline constexpr struct Bennu final : 
    CelestialBody<"Bennu", barycenters::SolarSystemBarycenter> {
  } Bennu;

  // Overload a single function to provide custom parameters for your body
  template <>
  inline consteval CelestialBodyParameters get_celestial_body_parameters<Bennu>() {
  return {
      .name = "Bennu",
      .gravitational_parameter = 5.2 * (m*m*m / (s*s)),
      .radius = 245.0 * m,
      .rotation_period = 4.297 * h
    };
  }

  // Now we can build a frame, centered on our custom body with an axis of our choice
  inline constexpr struct BennuICRF : public Frame<"BennuICRF", Bennu, axes::icrf> {
  } BennuICRF;

  // And even chain transformations to other bodies with no extra work
  RadiusVector<BennuICRF> posBennu{1000.0 * m, 0.0 * m, 0.0 * m};
  RadiusVector<earth::icrf> posEarth = posBennu.in_frame<earth::icrf>(epoch);
```