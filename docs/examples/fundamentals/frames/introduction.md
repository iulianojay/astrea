# Strongly Typed Frames

Astrea supports a system of strongly typed frames which allows for compile-time checking of frame
transformations, while also being reasonably simple to extend.

The `Frame` class is a compile-time interface that allows rules to be imposed on frame-supporting types,
and frame transformations. A frame in Astrea is defined by an origin (typically a celestial body), and an
axis. Currently, Astrea only supports pre-defined origins for static frames (that is, the center is inertially
fixed), and a series of pre-defined axes. Future releases may allow for completely customized origins and axes.

```cpp
// Astrea provides definitions for many commonly used frames
inline constexpr auto eci  = frames::earth::icrf;        // static
inline constexpr auto ecef = frames::earth::earth_fixed; // static (in code, not in time)
inline constexpr auto ric  = frames::dynamic::ric;       // dynamic
```

The CartesianVector class is a simple wrapper around a 3D vector, templated by the united-type and the frame the vector is defined in (or with respect to, depending). It also hosts several common vector operations, such as dot and cross products.
```cpp
// Some length vector in ECI frame
CartesianVector<Length, eci> rEci{ 1.0 * m, 2.0 * m, 3.0 * m };

auto rEciMag   = rEci.norm();
auto rEciUnit  = rEci.unit();
auto rEciDot   = rEci.dot(rEci);
auto rEciCross = rEci.cross(rEci);

std::cout << "rEci: " << rEci << std::endl;
std::cout << "rEciMag: " << rEciMag << std::endl;
std::cout << "rEciUnit: " << rEciUnit << std::endl;
std::cout << "rEciDot: " << rEciDot << std::endl;
std::cout << "rEciCross: " << rEciCross << std::endl;

// Outputs:
// rEci: [1 m, 2 m, 3 m]
// rEciMag: 3.74166 m
// rEciUnit: [0.267261, 0.534522, 0.801784]
// rEciDot: 14 m²
// rEciCross: [0 m², 0 m², 0 m²]
```

Conversions to/from a static (compile-time) frame, are handled by the `in_frame` method, templated to the frame we'd like to convert to. This frame looks for an acceptable specialization of the `get_dcm` method and uses the output direction cosine matrix to perform the vector transformation in either direction.
```cpp
// Astrea provides many static frame conversions
CartesianVector<Length, ecef> rEcefJ2000 = rEci.in_frame<ecef>(J2000);
CartesianVector<Length, ecef> rEcef = rEci.in_frame<ecef>(J2000 + hours(12));

std::cout << std::endl << "Position in ECI: " << rEci << std::endl;
std::cout << "Position in ECEF @ J2000: " << rEcefJ2000 << std::endl;
std::cout << "Position in ECEF @ J2000 + 12 hours: " << rEcef << std::endl;

// Outputs:
// Position in ECI: [1 m, 2 m, 3 m]
// Position in ECEF @ J2000: [2.14832 m, -0.620261 m, 3 m]
// Position in ECEF @ J2000 + 12 hours: [-2.15358 m, 0.601759 m, 3 m]
```
Implicit frame switches are not allowed, but can be forced in special circumstances
```cpp
// CartesianVector<Length, ecef> rEcefImplicit = rEci; // Compiler will fail!
CartesianVector<Length, ecef> rEcefForced = rEci.force_frame_conversion<ecef>();
```
Users are also able to define their own frames and associated transformations.
```cpp
// Frame are easy to define and can hook directly into the frame transformation system with no additional code
constexpr inline struct my_frame : Frame<"my frame", moons::Titan, axes::j2000> {} my_frame;
CartesianVector<Length, my_frame> rCustom{ 1.0 * m, 2.0 * m, 3.0 * m };
auto rEci = rCustom.in_frame<eci>(J2000);
```

For complex, time-dependent frames, such as those attached to a payload, or vehicle, the frames must be explicitly instantiated to call any vector transformations. They are not required to declare the vector type, however, transformation to/from dynamic frames are not allowed without an instance of the dynamic frame.
Dynamic frames can either be attached to an object (such as a spacecraft), or defined instantaneously at a specific state.

```cpp
// RadiusVector<_frame_> = CartesianVector<Distance, _frame_>
RadiusVector<ric> rRic = { 1.0 * km, 2.0 * km, 3.0 * km };

Spacecraft frameParent;
ric dynamicRicFrame(&frameParent);                              // RIC frame attached to a spacecraft
ric instRicFrame = ric::instantaneous(posVec, velVec); // RIC frame defined at a specific time

// RadiusVector<ECI> rEciFromRic = rRic.in_frame<ECI>(J2000); // No RIC frame at compile time: compiler will fail!
RadiusVector<eci> rotatedrRic   = instRicFrame.rotate_out_of_this_frame(rRic, date); // DCM * r
RadiusVector<eci> convertedrRic = instRicFrame.convert_from_this_frame(rRic, date);  // DCM * r + framePos
RadiusVector<ric> rRic2         = instRicFrame.rotate_into_this_frame(rotatedrRic, date);  // DCM^T * r
RadiusVector<ric> rRic3         = instRicFrame.convert_to_this_frame(convertedrRic, date); // DCM^T * (r - framePos)

std::cout << "RIC frame parent position: " << posECI << std::endl;
std::cout << "RIC frame parent velocity: " << velEci << std::endl;
std::cout << "Position in RIC: " << rRic << std::endl;
std::cout << "Position rotated into ECI: " << rotatedrRic << std::endl;
std::cout << "Position w.r.t ECI: " << convertedrRic << std::endl;
std::cout << "Rotated back into RIC: " << rRic2 << std::endl;
std::cout << "Transformed back w.r.t RIC: " << rRic3 << std::endl << std::endl;

// Outputs:
// RIC frame parent position:   [1 km, 0 km, 0 km]
// RIC frame parent velocity:   [0 km/s, 1 km/s, 0 km/s]
// Position in RIC:             [1 km, 2 km, 3 km]
// Position rotated into ECI:   [1 km, 2 km, 3 km]
// Position w.r.t ECI:          [2 km, 2 km, 3 km]
// Rotated back into RIC:       [1 km, 2 km, 3 km]
// Transformed back w.r.t RIC:  [1 km, 2 km, 3 km]
```