# Frame Transformations

Astrea provides a comprehensive coordinate frame transformation system that enables safe and efficient conversion between different reference frames. The transformation system is built on compile-time type safety and supports both static and dynamic frame conversions.

## Transformation Framework

The frame transformation system is built around several key concepts:

- **Compile-time frame safety** through template metaprogramming
- **Automatic transformation detection** based on frame relationships
- **Center offset calculations** for frames with different origins
- **Axis rotation matrices** for frames with different orientations

## Core Transformation Functions

### Center Offset Calculations

For frames with different origins, the system automatically calculates position offsets:

```cpp
#include <astro/frames/transformations.hpp>

// Get offset between Earth and Moon centers
CartesianVector<Distance, ECI> offset = 
    get_center_offset<earth::eci, moon::eci>(epoch);

// Frames with same origin have zero offset
CartesianVector<Distance, ECI> zeroOffset =
    get_center_offset<earth::eci, earth::ecef>(epoch); // Returns zero
```

### Frame Concepts

The system uses C++20 concepts to enforce transformation rules:

```cpp
// Frames with same origin
template<IsFrame auto _frame_, IsFrame auto _frame_u_>
concept HasSameOrigin = /* implementation */;

// Frames with same axis orientation
template<IsFrame auto _frame_, IsFrame auto _frame_u_> 
concept HasSameAxis = /* implementation */;
```

## Transformation Types

### Same Origin, Different Axes

Frames centered at the same body but with different orientations:

```cpp
// Earth-centered frames with different axes
CartesianVector<Distance, ECEF> ecefPos = 
    transform<ECEF, ECI>(eciPosition, epoch);

// Requires rotation matrix calculation
// Accounts for Earth's rotation at the given epoch
```

### Different Origin, Same Axes

Frames with the same orientation but different centers:

```cpp
// Moon-centered inertial vs Earth-centered inertial
CartesianVector<Distance, moon::eci> moonPos =
    transform<moon::eci, earth::eci>(earthPos, epoch);

// Requires center offset calculation
// Uses ephemeris data for relative body positions
```

### Different Origin and Axes

General transformation between arbitrary frames:

```cpp
// Complex transformation: ECI to Moon body-fixed
CartesianVector<Distance, moon::body_fixed> moonBodyPos =
    transform<moon::body_fixed, earth::eci>(eciPos, epoch);

// Combines center offset + rotation transformation
```

## Direction Cosine Matrices

Rotation transformations use direction cosine matrices (DCM):

```cpp
#include <astro/frames/DirectionCosineMatrix.hpp>

// Create rotation matrix
DirectionCosineMatrix dcm = compute_rotation_matrix<ECEF, ECI>(epoch);

// Apply rotation to vector
CartesianVector<Distance, ECEF> rotatedPos = dcm * eciPosition;
```

## Transformation Examples

### Earth-Centered Transformations

```cpp
// ECI to ECEF (accounts for Earth rotation)
Time epoch = epoch_to_julian_date("2024-01-01 12:00:00");

CartesianVector<Distance, ECI> eciPos(7000.0 * km, 0.0 * km, 0.0 * km);
CartesianVector<Distance, ECEF> ecefPos = 
    transform<ECEF, ECI>(eciPos, epoch);

// Velocity transformation includes Coriolis effects
CartesianVector<Velocity, ECI> eciVel(0.0 * km/s, 7.5 * km/s, 1.0 * km/s);
CartesianVector<Velocity, ECEF> ecefVel = 
    transform<ECEF, ECI>(eciVel, epoch, eciPos);
```

### Relative Motion Frames

```cpp
// Transform to Radial-Intrack-Crosstrack (RIC) frame
Keplerian referenceOrbit(7000.0 * km, 0.1, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);

CartesianVector<Distance, RIC> ricPosition = 
    transform<RIC, ECI>(eciPosition, epoch, referenceOrbit);

// RIC frame is centered on reference orbit
// Radial: towards/away from Earth center
// Intrack: along orbit velocity direction  
// Crosstrack: perpendicular to orbital plane
```

### Multi-Body Transformations

```cpp
// Earth to Moon center transformation
AstrodynamicsSystem system(CelestialBodyId::EARTH, {CelestialBodyId::MOON});

// Get Moon position relative to Earth
CartesianVector<Distance, earth::eci> moonPos = 
    system.get_relative_position(epoch, CelestialBodyId::EARTH, CelestialBodyId::MOON);

// Transform spacecraft position to Moon-centered frame
CartesianVector<Distance, moon::eci> moonRelativePos =
    transform<moon::eci, earth::eci>(spacecraftPos, epoch);
```

## Performance Considerations

### Compile-Time Optimization

- Frame compatibility checked at compile time
- Unnecessary transformations eliminated by compiler
- Template specialization for common transformation pairs

### Runtime Efficiency

- Cached rotation matrices for repeated transformations
- Optimized ephemeris computations using Chebyshev polynomials
- Minimal temporary object creation

```cpp
// Efficient repeated transformations
DirectionCosineMatrix cachedDCM = compute_rotation_matrix<ECEF, ECI>(epoch);
for (const auto& position : positions) {
    auto ecefPos = cachedDCM * position; // Reuse cached matrix
}
```

## Error Handling

The transformation system provides robust error handling:

- **Compile-time errors** for incompatible frame types
- **Runtime validation** of transformation parameters
- **Graceful degradation** for missing ephemeris data
- **Numerical stability** checks for extreme cases

This comprehensive transformation framework ensures that coordinate frame conversions are both mathematically correct and computationally efficient, providing the foundation for reliable astrodynamics calculations across diverse reference frames.