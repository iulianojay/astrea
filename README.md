<!-- markdownlint-disable MD041 -->
<!-- markdownlint-disable-next-line MD033 -->
<img align="right" height=135px src="docs/assets/images/astrea-transparent.png" alt="logo">

[![GitHub license](https://img.shields.io/github/license/iulianojay/astrea?cacheSeconds=3600&color=informational&label=License)](./LICENSE.LESSER)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue)](https://en.cppreference.com/w/cpp/compiler_support#cpp23)

[![Astrea CI](https://img.shields.io/github/actions/workflow/status/iulianojay/astrea/build-and-test.yml?branch=master&label=Astrea%20CI)](https://github.com/iulianojay/astrea/actions/workflows/build-and-test.yml)
![Code Coverage](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/iulianojay/238a4a61ca19471caa1e39376158d625/raw/coverage.json)

# Astrea

Astrea is an open-source C++ library for astrodynamics modeling and simulation, and aerospace engineering analysis. It is meant to provide the fundamental tools for most common aerospace analysis applications, while also serving as a fast, extensible framework for more complex aerospace projects.

This is a passion project that has largely been developed largely by a single developer. Not all of it is consistently designed, some of the features are incomplete, and tests do not yet cover every feature, but we're on our way!

Documentation is available [here](http://iulianojay.github.io/astrea)

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
- High-fidelity comparisons using NASA's published 6DoF test data

And it's still growing!

## What's coming?

- User-friendly installation
    - cmake packaging
    - compiled deployments
    - support for different environments and operating systems
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
- A GUI for basic analysis and visualization


## Contributing

- We welcome contributions to whatever interests you. If you think we're missing something that isn't there, feel free to make a ticket and start working.
- Please read CONTRIBUTING.md and follow the code of conduct.

## License and acknowledgments

- License: Astrea is licensed under the GNU Lesser General Public License (LGPL). See LICENSE and LICENSE.LESSER for details.
- Built using the follwing open-source libraries and tools:
    * [mp-units](https://github.com/mpusz/mp-units)
    * [googletest](https://github.com/google/googletest)
    * [sqlite-orm](https://github.com/fnc12/sqlite_orm.git)
    * [libcpr](https://github.com/libcpr/cpr.git)
    * [csv-parser](https://github.com/vincentlaucsb/csv-parserhowar) (header only)
    * [date](https://github.com/HowardHinnant/date) (header only)
    * [nlohmann-json](https://github.com/nlohmann/json) (header only)
    * [parallel_hashmap](https://github.com/greg7mdp/parallel-hashmap) (header only)
