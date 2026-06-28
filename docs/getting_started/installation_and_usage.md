# Installation

# Installation and Usage

This guide provides comprehensive instructions for installing Astrea and integrating it into your C++ astrodynamics projects. Astrea is designed to be easy to build and deploy across different platforms while maintaining high performance and reliability.

## Prerequisites

Before installing Astrea, ensure your development environment meets the following requirements:

### System Requirements

- **C++ Compiler**: C++23 compatible compiler
    - GCC 14 or later
- **CMake**: Version 3.20 or later
- **Python**: Version 3.12 or later (for build scripts and code generation)
- **Git**: For dependency management and version control

NOTE: It's possible to downgrade to at least GCC 13 but some functionality needs to be replaced or supplanted around the
inclusion of Howard Hinnat's date library into the official C++ standard chrono library. It's also possible to use earlier versions of Python but a more updated one is used for security.

### Platform Support

Astrea is tested and supported on the following platforms:

| Platform               | Status         |
|------------------------|----------------|
| Ubuntu 20.04+          | ✅ Supported  |
| Windows 10/11          | ✅ Supported  |
| macOS 11.0+            | ❓ Untested   |

Astrea has been tested with the following compilers:

| Compiler               | Version        | Status         |
|------------------------|----------------|----------------|
| GCC                    | 14.0+          | ✅ Supported   |
| Clang                  | 14.0+          | ✅ Supported |
| MSVC                   | 19.30+         | ❌ In Progress |
| Apple Clang            | 14.0+          | ❓ Untested |

MacOS and Apple Clang is currently untested but I expect it works since linux Clang works fine.

Note: I have not extensively tested every compiler version on every platform, so please make an issue if you encounter any problems or have questions about compatibility.

## Installation Methods

### Method 1: Building through Make recipes

For most users, the quickest way to get started is using the provided Makefile automation:

#### 1. Setup Python Environment

Astrea uses Python scripts for code generation and build automation. Create the required environment:

```bash
make python_env
```

This command creates a virtual environment in `.venv/` and installs necessary Python packages.

#### 2. Activate Python Environment

```bash
source ./.venv/bin/activate
```

On Windows (PowerShell):
```powershell
.\.venv\Scripts\Activate.ps1
```

#### 3. Build and Install

It is recommended to use Ninja for faster builds, but it is not required. If you don't have Ninja installed, you may have to play with the make configuration a bit to get it to behave. Otherwise, just run make to build and install with the default settings.

```bash
make
```

This builds Astrea in Release configuration and installs it to the `install/` directory.

#### Development Build with Tests and Examples

```bash
# Build debug configuration with tests and examples
make debug tests examples build

# Install the debug build
make debug install
```

#### Release with Debug Information

```bash
# Build with optimizations but retain debug symbols
make relwithdebinfo tests examples build
make relwithdebinfo install
```

#### Available Build Configurations

| Configuration     | Optimization | Debug Info | Use Case                    |
|-------------------|--------------|------------|-----------------------------|
| `debug`           | None         | Full       | Development and debugging   |
| `release`         | Full         | None       | Production deployment       |
| `relwithdebinfo`  | Full         | Partial    | Performance profiling       |

### Method 3: Manual CMake Build

For complete control over the build process, use CMake directly or configure your own CmakePresets.json file.

```bash
# Configure the build
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=install \
    -DASTREA_BUILD_TESTS=ON \
    -DASTREA_BUILD_EXAMPLES=ON \
    ...

# Build the library
cmake --build build --config Release --parallel

# Install to the specified directory
cmake --install build --config Release
```

## Build Configuration Options

Astrea provides several CMake options to customize the build:

| Option                     | Default | Description                              |
|----------------------------|---------|------------------------------------------|
| `BUILD_TESTS`              | `OFF`   | Build unit tests and integration tests   |
| `BUILD_EXAMPLES`           | `OFF`   | Build example applications               |
| `BUILD_BENCHMARKS`         | `OFF`   | Build benchmark applications             |
| `BUILD_STATIC`             | `OFF`   | Build static library                     |
| `BUILD_PROFILERS`          | `OFF`   | Build profiler tools                     |
| `BUILD_6DOF_CHECKCASES`    | `OFF`   | Build 6DOF checkcase tests               |
 
Example with custom options:
```bash
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_TESTS=ON \
    -DBUILD_EXAMPLES=ON
```

## Verification

### Running Tests

After building with tests enabled, verify the installation:

```bash
# Run all unit tests
make run_tests

# Or manually with CTest
cd build && ctest --output-on-failure --parallel
```

### Running Examples

Test your installation with the provided examples:

```bash
# Run all examples
make run_examples

# Or run individual examples
cd <path_to_example> && . ./bin/example_name
```

## Usage in Your Projects

### CMake Integration

Add Astrea to your CMake project using `find_package`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyAstrodynamicsProject)

# Find Astrea
find_package(astrea REQUIRED)

# Create your executable
add_executable(my_app main.cpp)

# Link against Astrea astro library
target_link_libraries(my_app PRIVATE astrea::astro)

# Set C++ standard
target_compile_features(my_app PRIVATE cxx_std_23)
```

### Using add_subdirectory

If you prefer to include Astrea as a subproject:

```cmake
# Add Astrea as subdirectory
add_subdirectory(extern/astrea/astrea)

# Link against the components you need
target_link_libraries(my_app PRIVATE
    astrea::astro
    astrea::math
    astrea::trace
)

# Or link against the entire library
target_link_libraries(my_app PRIVATE astrea::astrea)
```

It is not recommended to use `add_subdirectory` for production builds, as it can lead to longer build times and larger binaries. Use `find_package` for installed versions of Astrea.

**Python Environment**: If the Python environment fails to activate, try:
```bash
make python_env
```

**Missing Dependencies**: Astrea automatically downloads dependencies via CMake's FetchContent (via CPM). Dependencies
cached locally in the `.cpm-cache`folder and should only be downloaded once. Ensure you have internet access during the
first build.

**Build Failures**: For detailed build output:
```bash
make verbose install
```

## Shrinking the size of Astrea
Astrea is designed to be modular, allowing users to include only the components they need. For example, if you only need the core astrodynamics functionality, you can link against `astrea::astro` without pulling in the access analysis or satellite database components. This helps keep compile times and binary sizes down for users who don't need the full functionality of the project.

To help with binary size, users can also consider using analytic approximations for ephemerides instead of the compiled Chebyshev polynomials, which can be quite large. To control which of the default `CelestialBody`s are compiled with these polynomial files, you can use the CMake `BUILD_<BODY>` options. For example, if you only need Earth ephemerides, you can disable the others:

```bash
cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=install \
    -DASTREA_BUILD_TESTS=OFF \
    -DASTREA_BUILD_EXAMPLES=OFF \
    -DBUILD_SUN=OFF \
    -DBUILD_MOON=OFF
```
By default, Earth, Sun, and Moon are set to `ON` and all others are set to `OFF`. These ephemerides are built into `${CMAKE_INSTALL_PREFIX}/include/astro/ephemerides` by default.

| Option             | Default | Description                              |
|--------------------|---------|------------------------------------------|
| `BUILD_SUN`        | `ON`    | Build Sun ephemerides                    |
| `BUILD_MERCURY`    | `OFF`   | Build Mercury system ephemerides         |
| `BUILD_EARTH`      | `ON`    | Build Earth system ephemerides           |
| `BUILD_MARS`       | `OFF`   | Build Mars system ephemerides            |
| `BUILD_VENUS`      | `OFF`   | Build Venus system ephemerides           |
| `BUILD_JUPITER`    | `OFF`   | Build Jupiter system ephemerides         |
| `BUILD_SATURN`     | `OFF`   | Build Saturn system ephemerides          |
| `BUILD_URANUS`     | `OFF`   | Build Uranus system ephemerides          |
| `BUILD_NEPTUNE`    | `OFF`   | Build Neptune system ephemerides         |

### 6DoF Verification Test Data
For users with a local clone of Astrea, a good chunk of the project size comes from some NASA 6DoF verification test data. Users that are not interested in running this, but would like to keep the source code around can simply delete `./astrea/astro/tests/nasa_6dof_checkcases/data` folder.

## Next Steps

After successful installation:

1. Explore the [Examples](../examples/index.md) to understand common usage patterns
2. Review the [API Documentation](../api/index.md) for detailed interface descriptions
3. Join the community discussions on [GitHub](https://github.com/iulianojay/astrea)