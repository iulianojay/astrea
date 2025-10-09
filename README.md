
[![GitHub license](https://img.shields.io/github/license/iulianojay/astrea?cacheSeconds=3600&color=informational&label=License)](./LICENSE.LESSER)
[![GitHub license](https://img.shields.io/badge/C%2B%2B-23-blue)](https://en.cppreference.com/w/cpp/compiler_support#cpp23)
[![Astrea CI](https://img.shields.io/github/actions/workflow/status/iulianojay/astrea/build-and-test.yml?branch=master&label=Astrea%20CI)](https://github.com/iulianojay/astrea/actions/workflows/build-and-test.yml)
![Code Coverage](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/iulianojay/238a4a61ca19471caa1e39376158d625/raw/coverage.json)

# Astrea

Astrea is an open-source C++ library for astrodynamics modeling and simulation, and aerospace engineering analysis. It is meant to provide the fundamental tools for most common aerospace analysis applications, while also serving as a fast, extensible framework for more complex aerospace projects.

This is a passion project that has largely been developed largely by a single developer. Not all of it is consistently designed, some of the features are incomplete, and tests do not yet cover ever feature, but we're on our way! 

## What can it do

- Strongly typed units using mp-units
    - Allows for custom units, unit extensions, and compile-time unit conversions
- Strongly typed frames and coordinate transformations
    - Numerous utilities for automatic frame transformations
    - Extensible framework for user-defined frames
    - Dynamic frame support
- Strongly typed orbital element sets, and orbital data formats
    - Simple transformations between each
- Utility classes for automatic conversions to and from Julian Date, UTC, TT, and other common time systems.
- Clients for pulling Spacetrack data
- Access analysis (revisit) including link budget, and basic interference calculations 
- Extensible definitions for:
    - Vehicles, spacecraft, and payloads
    - Frames, orbital elements, and orbital data formats
    - Celestial bodies, and system definitions
    - Custom force models, integrators, equations of motion, event detection, and analytic solvers
- Custom mathamatics routines that work with mp-units types
- In house propagation with user-defined event detection
    - Numerical and analytic propagation methods supported 
    - Framework for user-defined forces, and equations of motion
- Impulsive and continuous thrust support
- Partial SPICE integration 
    - Chebyshev polynomials compiled directly for planets and the Moon
    - Fast ephemris access with SPICE accuracy

And it's still growing!

## Examples
Astrea relies on the mp-units library to handle units. This allows for strong typing of physical quantities, and compile-time unit checking, while also forcing developers to be explicit about units. This process helps avoid hard-to-see coversion issues, implicit units declarations, and inconsistencies in rounding and precision.

```cpp
// In general, the mp-units library is highly generalized for any united quantity, but Astrea uses simple type wrappers for consistency and convenience. 
quantity<s> t = 1.0 * s; // mp-units explicit style
Time time     = 1.0 * s; // Astrea implicit style

std::cout << "Quantity Time: " << t << std::endl;
std::cout << "Astrea Time: " << time << std::endl;

// Outputs:
// Quantity Time: 1 s
// Astrea Time: 1 s
```

Astrea uses strongly typed element sets to allow an easier user interface
for conversions, and common operators. Currently, there are 3 supported orbital element sets:
- Classical Orbital Elements (Keplerian)
- Modified Equinoctial Elements (Equinoctial)
- State Vectors (Cartesian)

but the framework is extensible for user-defined sets as well.

```cpp
// Build out a Cartesian element set using strongly typed, united quantities
Cartesian cartesian{
    7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s,
};
std::cout << "Cartesian: " << cartesian << std::endl;

// Conversions are done through the constructors for each element set type
GravParam mu = 398600.44189 * pow<3>(km) / pow<2>(s); // Earth
Keplerian keplerian{ cartesian, mu };
Equinoctial equinoctial{ keplerian, mu };

std::cout << "Converted to Keplerian: " << keplerian << std::endl;
std::cout << "Converted to Equinoctial: " << equinoctial << std::endl;
std::cout << "Converted back to Cartesian: " << Cartesian(equinoctial, mu) << std::endl << std::endl;

// Outputs:
// Cartesian: [7000 km, 0 km, 0 km, 0 km/s, 7.5 km/s, 1 km/s] (Cartesian)
// Converted to Keplerian: [7037.95 km, 0.00539276, 0.132552 rad, 0 rad, 0 rad, 0 rad] (Keplerian)
// Converted to Equinoctial: [7037.75 km, 0.00539276, 0, 0.066373, 0, 0 rad] (Equinoctial)
// Converted back to Cartesian: [7000 km, 0 km, 0 km, -0 km/s, 7.5 km/s, 1 km/s] (Cartesian)
```

Astrea supports a system of strongly typed frames which allows for compile-time checking of frame
transformations, while also being reasonably simple to extend.

The `Frame` class is a compile-time interface that allows rules to be imposed on frame-supporting types,
and frame transformations. A frame in Astrea is defined by an origin (typically a celestial body), and an
axis. Currently, Astrea only supports pre-defined origins for static frames (that is, the center is inertially
fixed), and a series of pre-defined axes. Future releases may allow for completely customized origins and axes.

```cpp
// Astrea provides definitions for many commonly used frames
using ECI  = frames::earth::icrf;        // static
using ECEF = frames::earth::earth_fixed; // static (in code, not in time)
using RIC  = frames::dynamic::ric;       // dynamic
```

The CartesianVector class is a simple wrapper around a 3D vector, templated by the united-type and the frame the vector is defined in (or with respect to, depending). It also hosts several common vector operations, such as dot and cross products.
```cpp
// Some length vector in ECI frame
CartesianVector<Length, ECI> rEci{ 1.0 * m, 2.0 * m, 3.0 * m }; 

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
CartesianVector<Length, ECEF> rEcefJ2000 = rEci.in_frame<ECEF>(J2000);
CartesianVector<Length, ECEF> rEcef = rEci.in_frame<ECEF>(J2000 + hours(12));

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
// CartesianVector<Length, ECEF> rEcefImplicit = rEci; // Compiler will fail!
CartesianVector<Length, ECEF> rEcefForced = rEci.force_frame_conversion<ECEF>();
```
Users are also able to define their own frames and associated transformations.
```cpp
// Frames do not necessarily need to be fully defined to be used
class MyFrame;
CartesianVector<Length, MyFrame> rCustom{ 1.0 * m, 2.0 * m, 3.0 * m };

// But the definition needs to be complete to use frame transformations
// CartesianVector<Length, ECI> rEcef = rCustom.in_frame<ECI>(J2000); // Compiler will fail!
```

For complex, time-dependent frames, such as those attached to a payload, or vehicle, the frames must be explicitly instantiated to call any vector transformations. They are not required to declare the vector type, however, transformation to/from dynamic frames are not allowed without an instance of the dynamic frame. 
Dynamic frames can either be attached to a FrameReference object (such as a spacecraft), or defined instantaneously at a specific state.

```cpp
// RadiusVector<Frame_T> = CartesianVector<Distance, Frame_T>
RadiusVector<RIC> rRic = { 1.0 * m, 2.0 * m, 3.0 * m };

Spacecraft frameParent;
RIC dynamicRicFrame(&frameParent);                              // RIC frame attached to a spacecraft
RIC instantaneousRicFrame = RIC::instantaneous(posVec, velVec); // RIC frame defined at a specific time

// RadiusVector<ECI> rEciFromRic = rRic.in_frame<ECI>(J2000); // No RIC frame instance at compile time: compiler will fail!
RadiusVector<ECI> convertedrRic = instantaneousRicFrame.convert_from_this_frame(rRic, J2000); // frame instance handles the conversion

std::cout << "Position in RIC: " << rRic << std::endl;
std::cout << "Position in instantaneous RIC: " << convertedrRic << std::endl;

// Outputs:
// Position in RIC: [0.001 km, 0.002 km, 0.003 km]
// Position in instantaneous RIC: [0.00474166 km, 0.002 km, 0.003 km]
```

Astrea hosts it's own Integrator. While many numerical integrators exist, with far more robust implementations, Astrea's integrator is designed specifically for integrating the strongly typed element sets that Astrea uses without potentially dangerous unit-unsafe operations. This also helps to avoid hidden numerical errors, rounding issues, or possible implicit unit conversions. As such, the integration process is less complete, and more difficult to work with than some libraries, but also more transparent, and more extensible. For most users, integration will be no more difficult than that when using a more sophisticated integration library.

```cpp
// Setup initial state
AstrodynamicsSystem sys; // Defaults to Earth-Moon
const Date epoch;        // Defaults to J2000
const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
const State state0(elements, epoch, sys);

// Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing for more flexibility and extensibility for users.
Spacecraft sat(state0); // This can be replaced with a user's custom type
Vehicle vehicle(sat);

// Build a force model
ForceModel forces;
forces.add<AtmosphericForce>();
forces.add<OblatenessForce>(sys, 10, 10);
// forces.add<UserDefinedForce>(...); // Users can add their own perturbations to the propagation

// Build EoMs - these can be selected from pre-built options, or users can create their own by inheriting from the base EquationsOfMotion class. Note that a force or perturbation model is not required.
TwoBody twoBodyEom(sys);                       // No forces
J2MeanVop j2MeanEom(sys);                      // Forces assumed
CowellsMethod cowellsEom(sys, forces);         // Regular force model
KeplerianVop keplerianEom(sys, forces, false); // Input options for rounding errors

// Propagation is done using a RKF78 method with a variable step size by default. This can be changed using the integrator setters.
Integrator integrator;
integrator.set_abs_tol(1.0e-10);
integrator.set_rel_tol(1.0e-10);

bool store = true; // Users can choose to store the state history during propagation, or not
Interval propInterval{ seconds(0), minutes(1) }; // A propagation interval relative to the epoch. Intervals can also be negative for backwards propagation.

// Propagation is done with the element representation that the equations of motion expect. This is to avoid unnecessary conversions during the integration process.
std::cout << "Propagating...";
const StateHistory twoBodyHistory = integrator.propagate(epoch, propInterval, twoBodyEom, vehicle, store);
std::cout << " Two Body Propagation Complete." << std::endl;
vehicle = Vehicle(sat); // reset the vehicle

std::cout << "Propagating...";
const StateHistory j2MeanHistory = integrator.propagate(epoch, propInterval, j2MeanEom, vehicle, store);
std::cout << " J2 Mean Propagation Complete." << std::endl;
vehicle = Vehicle(sat);

std::cout << "Propagating...";
const StateHistory cowellsHistory = integrator.propagate(epoch, propInterval, cowellsEom, vehicle, store);
std::cout << " Cowell's Method Propagation Complete." << std::endl;
vehicle = Vehicle(sat);

std::cout << "Propagating...";
const StateHistory keplerianHistory = integrator.propagate(epoch, propInterval, keplerianEom, vehicle, store);
std::cout << " Keplerian VoP Propagation Complete." << std::endl << std::endl;

std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
std::cout << "Two-Body Final State: " << twoBodyHistory.last() << std::endl;
std::cout << "J2-Mean Final State: " << j2MeanHistory.last() << std::endl;
std::cout << "Cowell's Method Final State: " << cowellsHistory.last() << std::endl;
std::cout << "Keplerian VOP Final State: " << keplerianHistory.last() << std::endl;

// Outputs
// Propagating... Two Body Propagation Complete.
// Propagating... J2 Mean Propagation Complete.
// Propagating... Cowell's Method Propagation Complete.
// Propagating... Keplerian VoP Propagation Complete.

// Func Evals: 7
// Two-Body Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
// J2-Mean Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, -7.27284e-12 rad, 5.14268e-12 rad, 0.0378809 rad] (Keplerian)
// Cowell's Method Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
// Keplerian VOP Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, 0 rad, 0 rad, 0.0378809 rad] (Keplerian)
```

Examples have been built out more completely for the astro tool in Astrea (astrea/astro/examples). 

## What's coming?

- User-friendly installation
    - cmake packaging
    - compiled deployments
    - support for different environments and operating systems
- High fidelity VnV
    - Real world comparisons using GPS data
- Speed guarantees using Google Benchmark
- More complete element set definitions and faster transformations
- Maneuvers, and full 6-DoF simulation
    - Strongly typed attitude representations
    - Control mechanisms such as reaction wheels
- Cislunar equations of motion, including CR3BP and BC4BM
- SPG4 and SPG8 propagators
- Schedulers
- High fidelity atmospheric models
- Transfer optimization utilities
- A Qt GUI for basic analysis and visualization

## Requirements and dependencies

The following are required to run all features in Astrea. The version requirements have not been thoroughly tested so many features will likely work with older versions. 
 * cmake 3.31.6 
 * conan 2.13.0
 * g++ 13.1.0 
 * make 4.3 - (only required to use the Makefile directly)
 * curl 7.81.0 - (only required to use snapshot features)
 * sqlite3 3.37.2 - (only required to use snapshot features)
 * python3 3.10.12 - (only required to use plotting features)

Astrea uses numerous open-source libraries to solve various problems. Many of the dependencies are stored locally in header-only versions for convenience and simplicity. The only dependency that currently requires manual installation on your system is [mp-units](https://github.com/mpusz/mp-units). 

Conan is used to build mp-units and its dependencies and otherwise links into Astrea's cmake system to build everything else. 

## Build and install

Since conan is used to build mp-units and it's dependencies, users must have conan profiles setup for the build process to work. To simplify this, required conan files are stored in the repo root directory in `.conan2`. Move this folder to the your home directory after installing conan, overwritting any equivalent files, and Astrea should build out of the box.

To build and install easily, simply run the default make commmand. The default recipe builds all targets in release. Building other build types simply requires appending the type

```bash
make debug install
```
```bash
make relwithdebinfo install 
```

Similarly, tests can be built by appending the test command
```bash
make debug tests
```

Or run with the run_tests command
```bash
make run_tests
```

On build, files should be installed locally in the `install` folder. This process is fully customizable with standard cmake commands if you want a different build process, install location, etc. See the recipes in the Makefile for more details.

## Contributing

- We welcome contributions to whatever interests you. If you think we're missing something that isn't there, feel free to make a ticket and start working.
- Please read CONTRIBUTING.md and follow the code of conduct.

## License and acknowledgments

- License: See LICENSE
- Built using the follwing open-source libraries and tools:
    * [mp-units](https://github.com/mpusz/mp-units)
    * [googletest](https://github.com/google/googletest)
    * [sqlite-orm](https://github.com/fnc12/sqlite_orm.git)
    * [libcpr](https://github.com/libcpr/cpr.git)
    * [csv-parser](https://github.com/vincentlaucsb/csv-parserhowar) (header only)
    * [date](https://github.com/HowardHinnant/date) (header only)
    * [nlohmann-json](https://github.com/nlohmann/json) (header only)
    * [parallel_hashmap](https://github.com/greg7mdp/parallel-hashmap) (header only)
