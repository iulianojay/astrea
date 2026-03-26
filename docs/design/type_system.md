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
    using Length = mp_units::quantity<detail::minor_distance_unit>;    // meters
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
    inline constexpr auto minor_distance_unit = mp_units::si::unit_symbols::m;     // meters
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

Astrea provides multiple orbital element representations through a unified interface:

```cpp
namespace astrea::astro {
    // Base orbital elements interface
    class OrbitalElements {
        // Virtual interface for different element types
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
    };
    
    class Cartesian {
        // Position and velocity vectors
    };
    
    class Equinoctial {
        // Modified equinoctial elements for near-circular orbits
    };
}
```

### State Management

The `State` class combines orbital elements with epoch and system information:

```cpp
namespace astrea::astro {
    class State {
        OrbitalElements _elements;
        Date _epoch;
        const AstrodynamicsSystem* _system;
        
    public:
        State(const OrbitalElements& elements, const Date& epoch, 
              const AstrodynamicsSystem& sys);
        
        const OrbitalElements& get_elements() const { return _elements; }
        const Date& get_epoch() const { return _epoch; }
        const AstrodynamicsSystem& get_system() const { return *_system; }
        
        // Element conversion while preserving epoch and system
        template<typename ElementType>
        State convert_to() const;
    };
}
    
    template<typename Frame = frames::ICRF, typename TimeScale = TT>
    using KeplerianState = State<Keplerian, Frame, TimeScale>;
}
```

## Time Handling

### Date Class

Astrea uses a simplified `Date` class for time management:

```cpp
namespace astrea::astro {
    class Date {
        JulianDate julian_date_;
        
    public:
        Date();  // Defaults to J2000.0 epoch
        explicit Date(const JulianDate& jd);
        
        // Time arithmetic
        Date operator+(const Time& duration) const;
        Date operator-(const Time& duration) const;
        Time operator-(const Date& other) const;
        
        // Conversions
        JulianDate get_julian_date() const { return julian_date_; }
        std::string to_string(const std::string& format = "%Y-%m-%d %H:%M:%S") const;
    };
    
    // Utility functions
    JulianDate epoch_to_julian_date(const std::string& epoch, 
                                   const std::string format = "%Y-%m-%d %H:%M:%S");
}
```

## Coordinate Vectors

### Typed Vector System

Astrea provides type-safe vector representations:

```cpp
namespace astrea::astro {
    // Template for typed vectors in specific frames
    template<typename Quantity, typename Frame>
    class CartesianVector {
        std::array<Quantity, 3> components_;
        
    public:
        // Component access
        Quantity x() const { return components_[0]; }
        Quantity y() const { return components_[1]; }  
        Quantity z() const { return components_[2]; }
        
        // Vector operations
        auto magnitude() const -> Quantity;
        auto normalize() const -> CartesianVector<Unitless, Frame>;
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
}
```

### Frame Instances

The actual frame types implemented in Astrea:

```cpp
namespace astrea::astro::frames {
    // Local coordinate frames
    struct EastNorthUp {};        // East-North-Up topocentric frame
    struct LocalHorizontal {};    // Local horizontal frame
    struct RadialInTrackCrossTrack {};  // RIC frame for relative motion
    struct VelocityNormalBinormal {};   // VNB orbital frame
    
    // Inertial frames (body-centered)
    struct EarthCenteredInertial {};    // ECI frame
    struct MoonCenteredInertial {};     // Selenocentric inertial
    
    // Body-fixed frames
    struct EarthFixed {};               // ECEF-type frame
}
```

## Example Usage

### Complete Orbit Definition

```cpp
// Create orbital state with type safety
Distance sma = 7000.0 * astrea::detail::distance_unit;     // 7000 km
Unitless ecc = 0.1 * astrea::detail::unitless;             // 0.1 eccentricity  
Angle inc = 45.0 * astrea::detail::angle_unit;             // 45 degrees

auto elements = astrea::astro::Keplerian(
    sma, ecc, inc, 
    0.0 * astrea::detail::angle_unit,  // RAAN
    0.0 * astrea::detail::angle_unit,  // Argument of perigee
    0.0 * astrea::detail::angle_unit   // True anomaly
);

auto epoch = astrea::astro::Date();  // J2000.0
auto system = astrea::astro::AstrodynamicsSystem();  // Earth-Moon system
auto state = astrea::astro::State(elements, epoch, system);

// Type-safe element conversions
auto cartesian_elements = astrea::astro::Cartesian(elements, system.get_mu());
```

### Gravitational Parameter Calculations

```cpp
// Type-safe orbital mechanics calculations
auto calculate_orbital_period(Distance semi_major_axis, GravParam mu) -> Time {
    // Kepler's third law calculation with automatic unit checking
    auto period_squared = 4.0 * M_PI * M_PI * mp_units::pow<3>(semi_major_axis) / mu;
    return sqrt(period_squared);
}

// Usage example
auto earth_mu = 398600.4418 * mp_units::pow<3>(astrea::detail::distance_unit) / 
                             mp_units::pow<2>(astrea::detail::time_unit);
auto period = calculate_orbital_period(sma, earth_mu);  // Returns Time quantity
```

## Performance Characteristics

### Zero Runtime Overhead

The type system adds no runtime cost:

```cpp
// Type information is compile-time only
static_assert(sizeof(Distance) == sizeof(double));
static_assert(sizeof(astrea::astro::Keplerian) == 6 * sizeof(mp_units::quantity<double>));

// No virtual function overhead in quantity types
static_assert(std::is_trivially_copyable_v<Distance>);
static_assert(std::is_trivially_copyable_v<Velocity>);
```

### Compile-Time Benefits

- **Error Prevention**: Unit mismatches caught at compile-time
- **Optimization**: Compilers can optimize knowing exact types  
- **Documentation**: Types serve as self-documenting code
- **Refactoring Safety**: Type checking prevents breaking changes

## Integration with mp-units

Astrea leverages the mp-units library for its foundation:

- **Standards Compliance**: Based on SI units and ISO standards
- **Performance**: Zero-runtime-cost with compile-time checking
- **Extensibility**: Easy to add domain-specific quantities
- **Interoperability**: Compatible with standard mathematical operations

---

*Astrea's type system provides practical dimensional safety for astrodynamics while maintaining the performance characteristics required for mission-critical applications.*
