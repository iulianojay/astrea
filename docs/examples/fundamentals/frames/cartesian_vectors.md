# Cartesian Vectors

The `CartesianVector` class is the fundamental vector type in Astrea, providing strongly-typed 3D vectors with compile-time unit and frame safety. This class prevents common errors in astrodynamics calculations by enforcing unit consistency and coordinate frame awareness.

## Template Design

Cartesian vectors are templated on both value type and frame:

```cpp
template <class Value_T, IsFrame auto _frame_>
class CartesianVector;
```

- **Value_T**: The physical quantity type (e.g., `Distance`, `Velocity`, `Acceleration`)
- **Frame_T**: The coordinate frame (e.g., `ECI`, `ECEF`, `RIC`)

## Basic Usage

### Vector Creation

```cpp
#include <astro/frames/CartesianVector.hpp>

using namespace mp_units::si::unit_symbols;

// Position vector in Earth-Centered Inertial frame
CartesianVector<Distance, ECI> position(
    7000.0 * km,  // x component  
    0.0 * km,     // y component
    0.0 * km      // z component
);

// Velocity vector in the same frame
CartesianVector<Velocity, ECI> velocity(
    0.0 * km / s,
    7.5 * km / s, 
    1.0 * km / s
);
```

## Frame Safety

The class explicitly prevents accidental frame mixing through deleted copy/move constructors:

```cpp
// This will NOT compile - frame mismatch
CartesianVector<Distance, ECI> eciPos(7000.0 * km, 0.0 * km, 0.0 * km);
CartesianVector<Distance, ECEF> ecefPos = eciPos; // Compilation error!
```

Frame transformations must be explicit:

```cpp
// Explicit frame transformation required
CartesianVector<Distance, ECEF> ecefPos = eciPos.in_frame<ECEF>(epoch);
```

## Vector Operations

Cartesian vectors support standard mathematical operations:

### Component Access

```cpp
Distance x = position.x();
Distance y = position.y();
Distance z = position.z();

// Access via array indexing
Distance x_alt = position[0];
```

### Arithmetic Operations

```cpp
// Vector addition (same frame and type)
auto totalPos = position1 + position2;

// Scalar multiplication
auto scaledVel = velocity * 2.0;

// Vector subtraction
auto deltaPos = finalPos - initialPos;
```

### Vector Products

```cpp
// Dot product
Auto dotProduct = velocity1.dot(velocity2);

// Cross product
CartesianVector<AngularMomentum, ECI> angularMom = position.cross(velocity);

// Magnitude
Distance radius = position.norm();
Velocity speed = velocity.norm();
```

## Integration with Physical Quantities

All operations preserve dimensional analysis:

```cpp
// Position times velocity gives the wrong dimensions - won't compile
position = position * velocity; // Error!

// Correct dimensional operations
auto energy = 0.5 * mass * velocity.dot(velocity); // Kinetic energy
auto momentum = mass * velocity;                   // Momentum vector
```

## Frame Transformations

Transformations between coordinate frames require explicit calls:

```cpp
// Transform from ECI to ECEF at a specific epoch
CartesianVector<Distance, ECEF> ecefPosition = eciPosition.in_frame<ECEF>(epoch);
```

But this type of transformation is only available for simple frames with date-dependent transformations. More complex frame transformations (e.g., RIC to ECI) require an explicit instance of the frame object. There are two ways to accomplish this: 1) Create an instance of the frame that's instantaneous and can be constructed from a given state, or 2) create a dynamic frame instance that attaches to a parent object which supplies it with position and velocity information over a given date range.

```cpp
// Create an instantaneous RIC frame from a state
RIC instantaneousRicFrame = RIC::instantaneous(position, velocity);
CartesianVector<Distance, RIC> ricPosition = instantaneousRicFrame.rotate_into_this_frame(position, date);
position = instantaneousRicFrame.rotate_out_of_this_frame(ricPosition, date);

// Create a dynamic RIC frame that attaches to a parent object
RIC dynamicRicFrame(parentObject);
ricPosition = dynamicRicFrame.rotate_into_this_frame(position, date);
position = dynamicRicFrame.rotate_out_of_this_frame(ricPosition, date);
```

Currently, only simple rotations are available (instead of transformations with respect to the frame for non-positional vectors and non-inertial frames). As such, the method name reflects this specifically. The more generic `convert_to_frame`/`convert_from_frame` method is reserved for more complex transformations that will be added in the future.

## Type Safety Benefits

The strongly-typed design prevents common astrodynamics errors:

1. **Unit errors**: Mixing meters and kilometers caught at compile time
2. **Frame errors**: Using wrong coordinate system caught at compile time  
3. **Dimensional errors**: Invalid mathematical operations caught at compile time
4. **Assignment errors**: Accidentally assigning incompatible vector types prevented

This design philosophy enables confident development of complex astrodynamics algorithms with compile-time verification of physical correctness.

Currently, there are only a few hard checks on what kinds of value types or frames can be used. This is because the compiler may create intermediate types during operations that are not explicitly defined or might be difficult to type by hand. Operations such as cross products may yield intuitive units that are difficult to contrain to a strict `Quantity` type. As such, the generality of the `CartesianVector` templating was left alone in favor of flexibility and legibility.