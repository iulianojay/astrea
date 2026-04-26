# Type System

Astrea's type system provides dimensional safety for astrodynamics calculations through compile-time unit checking using the [mp-units](https://github.com/mpusz/mp-units) library. The system ensures unit consistency while maintaining zero runtime overhead.

## Design Philosophy

### 1. Unit Safety
- **Dimensional Analysis**: Prevent unit mismatch errors at compile-time
- **Natural Expressions**: Code reads like mathematical equations
- **Zero Cost**: No runtime performance penalty for type safety
- **Clear Errors**: Helpful compiler messages for unit mismatches

### 2. Practical Design
- **Standard Units**: Built on SI base units with aerospace-specific extensions
- **Simple API**: Straightforward type definitions for common quantities
- **Extensible**: Easy to add new quantity types as needed

## Core Type Definitions

### Physical Quantities

Astrea defines aerospace-specific quantities as type aliases over mp-units:

```cpp
namespace astrea {
    // Basic quantities
    using Distance = mp_units::quantity<detail::distance_unit>;        // kilometers
    using Length = mp_units::quantity<detail::distance_unit>;    // meters
    using Time = mp_units::quantity<detail::time_unit>;               // seconds
    using Angle = mp_units::quantity<detail::angle_unit>;             // radians
    using Velocity = mp_units::quantity<detail::distance_unit / detail::time_unit>;
    using Mass = mp_units::quantity<detail::mass_unit>;               // kilograms
    using Unitless = mp_units::quantity<detail::unitless>;            // dimensionless
    
    // Derived astrodynamics quantities
    using GravParam = mp_units::quantity<mp_units::pow<3>(detail::distance_unit) / 
                                        mp_units::pow<2>(detail::time_unit)>;
    using Acceleration = mp_units::quantity<detail::distance_unit / 
                                           mp_units::pow<2>(detail::time_unit)>;
    using AngularVelocity = mp_units::quantity<detail::angle_unit / detail::time_unit>;
    
    // Specialized quantities
    using Force = mp_units::quantity<detail::mass_unit * detail::distance_unit / 
                                     mp_units::pow<2>(detail::time_unit)>;
    using SpecificAngularMomentum = mp_units::quantity<detail::distance_unit * 
                                                      detail::distance_unit / detail::time_unit>;
}
```

### Unit System Details

The underlying unit definitions use mp-units with SI base units optimized for astrodynamics:

```cpp
namespace astrea::detail {
    // Base units optimized for aerospace calculations
    inline constexpr auto time_unit           = mp_units::si::unit_symbols::s;     // seconds
    inline constexpr auto distance_unit       = mp_units::si::unit_symbols::km;    // kilometers  
    inline constexpr auto distance_unit = mp_units::si::unit_symbols::m;     // meters
    inline constexpr auto angle_unit          = mp_units::angular::unit_symbols::rad; // radians
    inline constexpr auto mass_unit           = mp_units::si::unit_symbols::kg;    // kilograms
    inline constexpr auto unitless            = mp_units::one;                     // dimensionless
}
```

### Type-Safe Calculations

The unit system prevents common astrodynamics errors:

```cpp
// This compiles and produces correct results
auto orbital_velocity(Distance radius, GravParam mu) {
    return sqrt(mu / radius);  // Returns Velocity quantity automatically
}

// This fails to compile - unit mismatch detected
auto invalid_calculation(Distance radius, Time time) {
    return radius + time;  // ERROR: Cannot add distance and time
}

// Automatic unit conversions where appropriate
Distance altitude = 400.0 * astrea::detail::distance_unit;  // 400 km
Length precise_alt = altitude;  // Automatic conversion to meters: 400,000 m
```

## State Representation

### Orbital Elements

In many ways, the OrbitalElements class was one of the original designs in Astrea. The goals was to make orbital element representations strongly typed while providing a layer of flexibility and "common-sense" interfacing. Keplerian elements can be converted to and from Cartesian elements naturally and the type system was meant to reflect that. 

```cpp
// Base orbital elements interface
class OrbitalElements {
    std::variant<Keplerian, Cartesian, ...>
};

// Concrete implementations
class Keplerian {
    Distance _semimajor;      // Semi-major axis
    Unitless _eccentricity;   // Eccentricity
    Angle _inclination;       // Inclination
    Angle _rightAscension;    // RAAN
    Angle _argPerigee;        // Argument of perigee
    Angle _trueAnomaly;       // True anomaly
    
public:
    Keplerian(const Distance& a, const Unitless& e, const Angle& i,
                const Angle& raan, const Angle& argp, const Angle& nu);
    
    // Conversion from other element types
    Keplerian(const OrbitalElements& elements, const GravParam& mu);
    
    // Conversion from other element types
    Keplerian(const Cartesian& elements, const GravParam& mu);
    // ... //
};

class Cartesian {
    // Position and velocity vectors
    // ... //
};

class Equinoctial {
    // Modified equinoctial elements for near-circular orbits
    // ... //
};
```
The difficulty in defining the OrbitalElements interface came from a few conflicting problems, 1) sum classes don't exist in C++ (yet), 2) the ability to seamlessly translate between different elements sets is not possible with type-erasure, and 3) over-eager templating can easily polute a library. The solution was a variant container with custom dispatches to element constructors as a hold-over for a more direct system. While this makes the interface potentially slower (marginally), it makes it easy to work with without muddying the code-base with endless templates.

```cpp
// Instead of  
template<typename Element_T> // And everything underneath it is templated
Element_T foo(Elemene_T) {}  // possibly decltype for outputs, etc.
Keplerian elements = cartesian_to_keplerian(cartesian, mu)

// We have
OribtalElements foo(OrbitalElements) {} // And conversions between these sets is seamless
Keplerian elements = ObrbitalElements.to_element_set<Cartesian>(mu)
```

The obvious drawback here is extensibility. Adding new orbital element types is no small task as it must play nice with the OrbitalElements class and be able to dispatch to all the required functions. This author believes that the drawback is work the benefits. Users typically won't need extra orbital element types and those that they might need can be added as needs arise. 

#### Orbits
A common question is why no `Orbit` container exists or why the more verbose `OrbitalElements` was used instead. The latter was chosen speficically to avoid the ambiguities surrounding the term. Is an orbit defined around a specfic body? In a specific frame? Is an orbit a set of fixed elements or osculating ones? Is an orbit a vector of ephemerides? Are cislunar orbits "orbits" or should they be some special separate class? What about transfers?

People often mean different things when they use the term and the context shifts can be subtle and confusing. The term "OrbitalElements" leaves no confusion - these are elements one might use to construct an orbit, not the orbit itself. 

### State Management

The `State` class is meant to be a total physical representation of an orbital simulation for a single dynamic object. It includes the orbital elements, the epoch, a reference to the system those are defined in, and an optional attitude. This gives the full required 14 states values needed to anchor a dynamic object in space (3 for position, 3 for velocity, 3 for orientation, 3 for angular rate, 1 for time, and 1 for the celestial reference).

```cpp
class State {
    OrbitalElements _elements;
    Date _epoch;
    const AstrodynamicsSystem* _system;
    std::optional<Attitude> _attitude;
    //...//
};
```
Since the `State` is built on-top of the `OrbitalElements` machinery, but also contains the system information, it can trivially convert element sets and act as a read-only vehicle for the astrodynamics system used in a given simulation.

```cpp
State state(Keplerian::LEO(), Date::J2000(), AstrodynamicsSystem());
Keplerian kep = state.in_element_set<Keplerian>();
Cartesian kep = state.in_element_set<Cartesian>();
Equinoctial kep = state.in_element_set<Equinoctial>();
```

It can also provide a nice utility wrapper for frame transformations.

```cpp
// Instead of the cumbersome
RadiusVector<ecef> rEcef = state.get_position().in_frame<ecef>(state.get_epoch());

// we can just ask the state to do it
rEcef = state.get_position_in_frame<ecef>();
```

And much more. The `State` class is an extremely convenient and powerful container in Astrea and it strongly recomended that users rely on it to simplify their code.

## Time Handling

Astrea uses a simplified `Date` class for time management that leans on the `std::chrono` clock system.

```cpp
class Date {
    JulianDate _julianDate;
    //...//    
};

// Utility functions
JulianDate epoch_to_julian_date(const std::string& epoch, 
                                const std::string format = "%Y-%m-%d %H:%M:%S");

```

This means that the `Date` class can be constructed from any clock system whatsoever as long as the clock is a properly defined chrono clock. The also has the added benefit of inheriting the ability to keep precise time without much work; if `chrono` supports it, Astrea can understand it. So far, Astrea supports the built in system clocks, including gps, tai, and any arbitrary system clock, as well as a custom `JulianDateClock` and `TerrestialTimeClock`. Future versions will support the more complex UT1 and leap-second time systems that are common in astrodynamics applications.

## Coordinate Vectors

To the author's knowledge, no other astrodynamics library provides type-safe vector representations for different coordinate frames. Astrea provides a template system for defining vectors in specific frames that ensures unit safety and frame consistency while still being flexible and allowing users to define their own custom frames.

### Typed Vector System

The `CartesianVector` is the core of Astrea's strongly-typed frame system. Is is a wrapper around an array that defines both the type of value contained and the frame it's defined in. Frame are represented by statically-typed classes and can be used to ensure that users are not improperly or illegally using two vectors in different frames. 

```cpp
// Template for typed vectors in specific frames
template<typename Quantity, typename Frame>
class CartesianVector {
    std::array<Quantity, 3> components_;
    //...//
};

// Common vector type aliases
template<typename Frame>
using RadiusVector = CartesianVector<Distance, Frame>;

template<typename Frame>
using VelocityVector = CartesianVector<Velocity, Frame>;

template<typename Frame>
using AccelerationVector = CartesianVector<Acceleration, Frame>;

template<typename Frame>
using UnitVector = CartesianVector<Unitless, Frame>;
```

Current capabilities are pretty blunt as the frame system is not complete, but the most common use-cases are still possible.

```cpp
// Constructors are strict about disallowing implicit frame or unit switches
RadiusVector<frames::earth::icrf> rEci = {...};
VelocityVector<frames::earth::icrf> vEci = rEci;         // Compile-time failure
VelocityVector<frames::earth::earth_fixed> rEcef = rEci; // Compile-time failure

// Operators, similarly, only work on compatible frames
auto r = rEcef + rEci;  // Compile-time failure
auto v = vEci1 - vEci2; // Works!

// Common vector operators are also available
auto h = r.cross(v); // Resultant units are deduced as decltype(r.unit{} * v.unit{})
```

While this basis is strong and covers most cases, some conversions should be allowed. For example, relative position vectors can switch between different frames with the same axis without any conversion.
```cpp
// i.e. This should be allowed, but currently isn't
RadiusVector<frames::earth::icrf> rEci = {...};
RadiusVector<frames::mars::icrf> rMci = rEci; // Conversion under the hood
```

These implicit transformations are currently being designed and will be included in a future release of Astrea. For now, users can use 
```cpp 
RadiusVector<frames::mars::icrf> rMci = rEci.force_frame_conversion<frames::mars::icrf>; // Potentially risky
```
as long as they are confident the result is correct.

### Frame Instances

Frames in Astrea are statically defined by their center, generally some celestial body or barycenter, and their axis. Currently, Astrea only offers a few combinations of these, but more will be implemented soon. A design is currently being worked on to allow frames to be defined as fixed-offsets of another, according to sime time-table, and many more features. More to come soon!

#### Existing Frames

Astrea currently defines frames as a center and an axis:
```cpp
template <CelestialBodyId origin, FrameAxis axis>
struct Frame;
```

where the CelestialBodyId is an enum of the most common bodies in the solar system and the FrameAxis is an enum of the most common axes (inertial, body-fixed, etc.). This allows for a simple and intuitive way to define frames while still being flexible enough to cover most use-cases.

An inertial frame, for example, is constrained by templates to use an inertially-defined axis, such as the ICRF axis, or the J2000 axis. A body-fixed frame, similarly, must be centered on a celestial body and is expected to rotate with that body. This common-sense approach makes the frame system easier to understand intuitively without sacrificing extensibility and without requiring heavy runtime checks or passing frame infrormation around at runtime.




*Astrea's type system provides practical dimensional safety for astrodynamics while maintaining the performance characteristics required for mission-critical applications.*
