<!-- markdownlint-disable MD041 -->
<!-- markdownlint-disable-next-line MD033 -->
<img align="right" height=135px src="docs/assets/images/astrea-transparent.png" alt="logo">

<br>

[![GitHub license](https://img.shields.io/github/license/iulianojay/astrea?cacheSeconds=3600&color=informational&label=License)](./LICENSE.LESSER)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue)](https://en.cppreference.com/w/cpp/compiler_support#cpp23)
[![Astrea CI](https://img.shields.io/github/actions/workflow/status/iulianojay/astrea/build-and-test.yml?branch=main&label=Astrea%20CI)](https://github.com/iulianojay/astrea/actions/workflows/build-and-test.yml)
![Code Coverage](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/iulianojay/238a4a61ca19471caa1e39376158d625/raw/coverage.json)

<br>

# Astrea: A Modern C++ Astrodynamics Library

Astrea is a high-performance, type-safe astrodynamics library designed for mission design, analysis, and aerospace applications. Built with modern C++23 features, Astrea provides a strongly-typed foundation with compile-time unit checking and coordinate frame safety, enabling developers to build robust and efficient astrodynamics software.

## Overview

This library features a comprehensive type system that prevents common errors in astrodynamics calculations through compile-time checks - namely a strongly typed units system developed on top of mp-units, strongly typed orbital elements with in-place conversions and type-erased containers, and a independently developed system of strongly-typed frames. All of these features offer a high level of performance and safety, while also providing a flexible and extensible architecture for custom applications.

## Installation

Astrea requires C++23 and uses CMake for building. A conan package is in development and some effort has been put into Windows compatibility, but not much has been tested outside of Linux. Detailed installation instructions are available in our [Getting Started Guide](https://iulianojay.github.io/astrea/getting_started/installation_and_usage/).

## Documentation

Documentation is available online at <https://iulianojay.github.io/astrea/>, but is still a work in progress. Please be patient as we continue to expand and improve the documentation, and feel free to contribute improvements or ask questions in the GitHub repository.

- **[Getting Started](https://iulianojay.github.io/astrea/getting_started/)** - Installation and basic usage
- **[Key Features](https://iulianojay.github.io/astrea/key_features/)** - Overview of Astrea's core features
- **[Examples](https://iulianojay.github.io/astrea/examples/)** - Code examples
- **[Roadmap](https://iulianojay.github.io/astrea/roadmap/)** - Planned features and future development
- **[API Reference](https://iulianojay.github.io/astrea/astro/links/)** - Detailed API documentation
- **[Design Documentation](https://iulianojay.github.io/astrea/design/)** - Architecture and design principles


## Contributing

Astrea is currently developed and maintained largely by a single developer, so help is welcomed. Please see the [contributing guidelines](getting_started/contributing.md) for information on how to get involved.

## License

Astrea is licensed under the [GNU Lesser General Public License v3.0](LICENSE.LESSER), enabling both open-source and commercial use. It is safe for use in proprietary software and projects in general.
Direct modifications, derivatives, forks, or extensions of the library must be released under the same license, but applications that link against Astrea can be licensed independently.