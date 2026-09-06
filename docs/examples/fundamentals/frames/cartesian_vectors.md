# Cartesian Vectors

The `CartesianVector` class is the fundamental vector type in Astrea, providing strongly-typed 3D vectors with compile-time unit and frame safety. This class prevents common errors in astrodynamics calculations by enforcing unit consistency and coordinate frame awareness simultaneously. The `CartesianVector` coupled with Astrea's frame system and the mp-units library, creates a one-of-a-kind vector type that handles the hard problems of frame and unit conversions and consistency automatically, while still allowing users to perform complex vector operations with ease.

## Template Design

Cartesian vectors are templated on both value type and frame:

```cpp
template <class Value_T, IsFrame auto _frame_>
class CartesianVector;
```

- **Value_T**: The physical quantity type (e.g., `Distance`, `Velocity`, `Acceleration`)
- **_frame_**: The coordinate frame (e.g., `ECI`, `ECEF`, `RIC`)

The `Value_T` template parameter is not explicitly constrained to be an mp-units `Quantity` type, but it is more or less implicitly enforced. It doesn't make sense to use a frame-aware vector with a non-physical quantity type since frames necessarily imply a physical value. Similarly, much of the frame handling relies on checking the units at compile-time to ensure that the frame transformations are handled properly. Rotating a position vector into another frames only requires the frame itself, but changing the frame of velocities or accelerations requires accounting for frame aberrations. By removing the physical quantity, it becomes difficult to know how to perform a given transformation, and more work that might be implicitly understood, is then left to the user.

The `_frame_` of a `CartesianVector` is a compile-time NTPP that holds some basic information about the frame (name, parent frame, origin, etc.) and provides the compiler the necessary information to ensure that frame transformations are handled correctly. Right now, the frame attached to the vector is assumed to be the frame that the vector is defined with respect to. It is possible to rotate a vector into another frame without performing the full frame transformation, but there's currently no support to denote that the vector is defined in one frame and expressed in another. This support may be added in the future but was initially left out to lower the clutter and complexity of the code surrounding the `CartesianVector` class. 

## Basic Usage

### Vector Creation

Any `mp_units::quantity` type can be used as the value type for a `CartesianVector` but Astrea generally prefers its shortcut types. The frame can be any frame that is defined in the Astrea frame system (or that the user defines). 

```cpp
#include <astro/frames/CartesianVector.hpp>

using namespace mp_units::si::unit_symbols;

// Position vector in Earth-Centered Inertial frame
RadiusVector<frames::earth::icrf> position(
    7000.0 * km,  // x component  
    0.0 * km,     // y component
    0.0 * km      // z component
);

// Velocity vector in the same frame
CartesianVector<Velocity, frames::earth::icrf> velocity(
    0.0 * km / s,
    7.5 * km / s, 
    1.0 * km / s
);
```

### Frame Safety

The class explicitly prevents accidental frame mixing by enforcing frame consistency at compile time. For example, attempting to assign a vector from one frame to another without an explicit transformation will result in a compilation error:

```cpp
// This will NOT compile - frame mismatch
RadiusVector<frames::earth::icrf> eciPos(7000.0 * km, 0.0 * km, 0.0 * km);
RadiusVector<frames::earth::ecef> ecefPos = eciPos; // Compilation error!
```
Frames are checked via equivalence, not identity. This means that two frames that are expressed explicitly via different types, but share the same axis and origin, are considered equivalent, and thus safe to implicitly convert between. 

```cpp
inline constexpr struct frame1 : Frame<"frame1", earth, icrf> {} frame1;
inline constexpr struct frame2 : Frame<"frame2", earth, icrf> {} frame2;

static_assert(frame1 != frame2); // Different types
static_assert(equivalent(frame1, frame2)); // Same axes and origin
```

Transformations to other frames must be explicitly called:
```cpp
// Explicit frame transformation required
auto ecefPos = eciPos.in_frame<frames::earth::ecef>(epoch);
auto ecefVel = eciVel.in_frame<frames::earth::ecef>(epoch, eciPos);
auto ecefAccel = eciAccel.in_frame<frames::earth::ecef>(epoch, eciPos, eciVel);
```
Note that the `in_frame` method requires an epoch for the transformation, and for velocity vectors, it also requires the position vector in the same frame as the velocity vector and so on. This is because the higher time derivative transformations depend on the position of the object in the original frame. If you want to purely rotate the velocity vector into another frame without performing the full frame transformation, you can use the `rotate_vector_into_frame` method instead. This is useful for simple rotations between frames that share the same origin and axes, but it does not account for frame aberrations.

```cpp
// Pure rotation of velocity vector into another frame
auto ecefVel = rotate_vector_into_frame<frames::earth::ecef>(eciVel);
```

*Warning: This function is generally considered unsafe since Astrea does not mark the defining frame of a vector and other operations with the resultant vector may be incorrect.*

### Dynamic Frame Transformations

Frame transformations are roughly divided into two categories: static and dynamic. Static transformations are those that can be defined at compile time and do not depend on any external information besides the date of the transformation. This would include any transformations between inertial frames, between fixed-offset frames, frames with well-defined time-dependent behavior (such as the ITRF or other body-fixed frames). These frames compose the system of basic transformations in Astrea and can statically chain to and from one another at compile time. Dynamic transformations, on the other hand, are those that depend on some external information, such as the position of a parent object or the date of the transformation. These are transformations to frames like RIC, LVLH, etc. These depend on runtime values and thus, require more user input to perform the transformation. The `in_frame` method is only available for static transformations, while dynamic transformations require an explicit instance of the frame object.

```cpp
// Create an instantaneous RIC frame from a state
ric instantaneousRicFrame = ric::instantaneous(position, velocity);
RadiusVector<ric> ricPosition = instantaneousRicFrame.rotate_into_this_frame(position, date);
position = instantaneousRicFrame.rotate_out_of_this_frame(ricPosition, date);
```

Cartesian vectors can still be tagged normally with a dynamic frame type, but the user must provide an instance of the frame to perform any transformations. 

### Vector Operations

Cartesian vectors support standard mathematical operations, access operations, and other simple utilities. The operations are strongly typed and will not compile if the units or frames are incompatible.

```cpp
// Access with getters
Distance x = position.get_x();
Distance y = position.get_y();
Distance z = position.get_z();

// Access via array indexing
Distance x = position[0];
Distance y = position[1];
Distance z = position[2];
```

### Arithmetic Operations

A vector is a vector is a vector. Cartesian vectors support standard arithmetic operations such as addition, subtraction, and scalar multiplication. These operations are only valid for vectors of the same frame and value type. Astrea does not use the somewhat common convention of defining distinct types for difference vectors since there is no physical difference between, for example, a position vector and a displacement vector (the position is just displacement from the frame origin in some different frame).

Largely, these utilities keep the vector objects more "mathy" and easier to read and work with. It is left to the user to ensure that the physical interpretation of the vector operations is meaningful. 

```cpp
// Vector addition (same frame and type)
auto totalPos = position1 + position2;

// Scalar multiplication
auto scaledVel = velocity * 2.0;

// Vector subtraction
auto deltaPos = finalPos - initialPos;

// Dot product
auto dotProduct = velocity1.dot(velocity2);

// Cross product
auto angularMom = position.cross(velocity); // output unit is (km * km/s)

// Magnitude
auto radius = position.norm();
auto speed = velocity.norm();

// Normalization
auto unitVector = position.direction();
```

## Integration with Physical Quantities

All operations preserve dimensional analysis and integrate smoothly with the mp-units library.

```cpp
// Position times velocity gives the wrong dimensions - won't compile
// Distance position2 = position * velocity; // Error!

// Correct dimensional operations
auto energy = 0.5 * mass * velocity.dot(velocity); // Kinetic energy
auto momentum = mass * velocity;                   // Momentum vector
```