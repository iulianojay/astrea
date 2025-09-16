
[![GitHub license](https://img.shields.io/github/license/iulianojay/astrea?cacheSeconds=3600&color=informational&label=License)](./LICENSE)
[![GitHub license](https://img.shields.io/badge/C%2B%2B-20%2F23-blue)](https://en.cppreference.com/w/cpp/compiler_support#cpp23)
[![Astrea CI](https://img.shields.io/github/actions/workflow/status/iulianojay/astrea/build-and-test.yml?branch=master&label=Astrea%20CI)](https://github.com/iulianojay/astrea/actions/workflows/build-and-test.yml)

# Astrea

Astrea is an open-source C++ library for astrodynamics modeling and simulation, and aerospace engineering analysis. It is meant to provide the fundamental tools for most common aerospace analysis applications, while also serving as a fast, extensible framework for more complex aerospace projects.

This is a passion project that has largely been developed largely by a single developer. Not all of it is consistently designed, some of the features are incomplete, and tests do not yet cover ever feature, but we're on our way! 

## What can it do

- Statically typed units using mp-units
    - Allows for custom units, unit extensions, and compile-time unit conversions
- Statically typed frames and coordinate transformations
- Statically typed orbital element sets, and orbital data formats
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

And it's still growing!

## What's coming?

- User-friendly installation
- SPICE integration
- High fidelity VnV
    - Real world comparisons using GPS data
- Speed guarantees using Google Benchmark
- Safer, more generic frame definitions
- More complete element set definitions and faster transformations
- Maneuvers, and full 6-DoF simulation
    - Statically typed attitude representations
    - Control mechanisms such as reaction wheels
- Cislunar equations of motion, including CR3BP and BC4BM
- SPG4 and SPG8 propagators
- High fidelity atmospheric models
- Transfer optimization utilities
- A Qt GUI for basic analysis

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

To build and install conan easily, simply run
> make

The default recipe builds all targets in release. Building other build types simply requires appending the type
> make debug

> make relwithdebinfo 

Similarly, tests can be built by appending the test command
> make debug tests

Or run with the run_tests command
> make run_tests


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
