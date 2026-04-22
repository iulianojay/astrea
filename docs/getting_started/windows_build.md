# Building Astrea on Windows

This guide covers building Astrea on Windows with full functionality including tests, examples, and ephemerides.

## Prerequisites

### Required Tools
- **Visual Studio 2022** (or later) with C++ development tools, OR
- **MinGW-w64** with GCC 14.0 or later
- **CMake 3.28.3** or later
- **Python 3.8** or later (for ephemeris generation)
- **Git** for cloning dependencies

### C++ Standard Support
- Astrea requires **C++23** support
- MSVC 19.30+ (Visual Studio 2022 17.0+) recommended
- GCC 14.0+ for MinGW builds
- Note: Unreal Engine 5 currently supports C++20 maximum. See [UE5 Integration Notes](#unreal-engine-5-integration-notes) below.

## Quick Start

### Using PowerShell Script (Recommended)

The easiest way to build on Windows:

```powershell
# Basic build (Release, no tests/examples)
.\build-windows.ps1

# Build with tests and examples
.\build-windows.ps1 -BuildTests ON -BuildExamples ON

# Full build with all features
.\build-windows.ps1 -BuildTests ON -BuildExamples ON -BuildSun ON -BuildMoon ON -BuildEarth ON

# Debug build
.\build-windows.ps1 -BuildType Debug -BuildTests ON -BuildExamples ON

# Clean build
.\build-windows.ps1 -Clean
```

**Available Parameters:**
- `-BuildType`: Debug, Release, RelWithDebInfo (default: Release)
- `-BuildTests`: ON/OFF (default: OFF)
- `-BuildExamples`: ON/OFF (default: OFF)
- `-BuildStatic`: ON/OFF (default: OFF)
- `-BuildSun`, `-BuildMoon`, `-BuildEarth`: ON/OFF (defaults: ON)
- `-BuildMercury`, `-BuildVenus`, `-BuildMars`, etc.: ON/OFF (defaults: OFF)
- `-Clean`: Clean before building
- `-Parallel`: Number of parallel jobs (default: CPU count)

### Using Batch Script

For simpler command-line usage:

```batch
REM Basic build
build-windows.bat

REM Build with tests and examples
build-windows.bat tests examples

REM Debug build with all celestial bodies
build-windows.bat debug tests examples all-planets

REM Clean build
build-windows.bat clean release tests
```

**Available Options:**
- Build types: `debug`, `release`, `relwithdebinfo`
- Features: `tests`, `examples`, `static`, `clean`
- Celestial bodies: `sun`, `moon`, `earth`, `mercury`, `venus`, `mars`, `jupiter`, `saturn`, `uranus`, `neptune`, `all-planets`

### Using CMake Directly

For complete control:

```powershell
# Configure
cmake -B build -S . `
  -DCMAKE_BUILD_TYPE=Release `
  -DCMAKE_INSTALL_PREFIX=install `
  -DBUILD_TESTS=ON `
  -DBUILD_EXAMPLES=ON `
  -DBUILD_SUN=ON `
  -DBUILD_MOON=ON `
  -DBUILD_EARTH=ON

# Build
cmake --build build --config Release --parallel

# Install
cmake --install build --config Release
```

## Output Files

After building, you'll find:

### DLL Files (Runtime Libraries)
```
build/Release/
├── astro.dll
├── math.dll
├── utilities.dll
└── [dependency DLLs from CPM]
```

### LIB Files (Import Libraries)
```
build/Release/
├── astro.lib
├── math.lib
└── utilities.lib
```

### Headers
```
install/include/
├── astro/
│   ├── astro_export.hpp  (generated export macros)
│   └── [other headers]
├── math/
│   ├── math_export.hpp
│   └── [other headers]
└── utilities/
    ├── utilities_export.hpp
    └── [other headers]
```

## Running Tests

After building with tests enabled:

```powershell
# Navigate to build directory
cd build

# Run all tests
ctest --output-on-failure --parallel -C Release

# Run tests with verbose output
ctest --output-on-failure --verbose -C Release

# Run specific module tests
cd astrea/math/tests
ctest --output-on-failure -C Release
```

**Test Directories:**
- `build/astrea/math/tests` - Math utilities
- `build/astrea/utilities/tests` - General utilities
- `build/astrea/astro/tests` - Astrodynamics core
- `build/astrea/trace/tests` - Tracing utilities

## CMake Build Options

| Option | Description | Default |
|--------|-------------|---------|
| `BUILD_TESTS` | Build test suite | OFF |
| `BUILD_EXAMPLES` | Build example programs | OFF |
| `BUILD_STATIC` | Build static libraries (.lib only) | OFF |
| `BUILD_SUN` | Build Sun ephemeris | ON |
| `BUILD_MOON` | Build Moon ephemeris | ON |
| `BUILD_EARTH` | Build Earth ephemeris | ON |
| `BUILD_MERCURY` | Build Mercury ephemeris | OFF |
| `BUILD_VENUS` | Build Venus ephemeris | OFF |
| `BUILD_MARS` | Build Mars ephemeris | OFF |
| `BUILD_JUPITER` | Build Jupiter ephemeris | OFF |
| `BUILD_SATURN` | Build Saturn ephemeris | OFF |
| `BUILD_URANUS` | Build Uranus ephemeris | OFF |
| `BUILD_NEPTUNE` | Build Neptune ephemeris | OFF |
| `CMAKE_BUILD_TYPE` | Build configuration (Release/Debug/RelWithDebInfo) | Release |

## Export Headers

The build system automatically generates export headers for proper DLL symbol visibility:

- `astro/astro_export.hpp`
- `math/math_export.hpp`
- `utilities/utilities_export.hpp`

These headers define macros like `ASTRO_EXPORT` that handle `__declspec(dllexport)` and `__declspec(dllimport)` automatically.

## Dependencies

Astrea uses [CPM](https://github.com/cpm-cmake/CPM.cmake) to fetch and build dependencies automatically:

- **SQLite3** (v3.47.2) - Database engine (auto-fetched if not found on system)
- **mp-units** (v2.5.0) - Units library with dimensional analysis
- **nlohmann_json** (v3.11.3) - JSON parsing
- **sqlite_orm** (v1.9.1) - SQLite ORM
- **matplotplusplus** (v1.2.2) - Plotting (optional)
- **cpr** (v1.11.0) - HTTP requests
- **gtl** (v1.2.0) - Fast hash maps

Dependencies are fetched during CMake configuration and built alongside Astrea. No manual installation required.

## Troubleshooting

### Common Issues

**CMake not found:**
- Ensure CMake is in your PATH
- Visual Studio users: Use "Developer Command Prompt for VS 2022"
- Or install CMake from https://cmake.org/download/

**Compiler not found:**
- MSVC: Install Visual Studio with "Desktop development with C++" workload
- MinGW: Ensure MinGW bin directory is in PATH
- Check compiler version: GCC requires 14.0+

**Python environment issues:**
- Verify Python is installed: `python --version`
- Python is required for ephemeris file generation
- Ensure Python 3.8 or later is in your PATH

**Build failures:**
- Try a clean build: `.\build-windows.ps1 -Clean` or `build-windows.bat clean`
- Check disk space (>5GB recommended for full build)
- Ensure internet access for dependency downloads

**SQLite3 Automatic Download:**
- SQLite3 is automatically downloaded if not found on system
- Message "SQLite3 not found on system, fetching from source..." is normal

**Missing DLLs at Runtime:**
- Windows builds use shared libraries by default
- Ensure install directory's bin folder is in PATH
- Or copy DLLs to your executable directory
- Or build static libraries: `-BuildStatic ON`

**C++23 Features Not Available:**
- Ensure Visual Studio 2022 17.0+ with latest updates
- For MinGW, use GCC 14.0 or later
- Check compiler version: `g++ --version` or `cl /?`

## Unreal Engine 5 Integration Notes

### C++ Standard Compatibility Issue
**Important:** UE5 currently uses C++20 as its maximum supported standard, but Astrea requires C++23 (primarily for the mp-units dependency). This may cause compatibility issues.

#### Potential Solutions:
1. **Wait for UE5 C++23 support** - Epic Games may add C++23 support in future UE5 versions
2. **Downgrade mp-units** - Find a C++20-compatible version of mp-units (may require significant changes)
3. **Wrapper DLL approach** - Create a C++20-compatible wrapper that isolates C++23 code

### Integration Steps (if compatible)
1. Copy DLLs to `YourProject/Binaries/Win64/`
2. Copy LIBs to `YourProject/ThirdParty/Astrea/Lib/Win64/`
3. Copy headers to `YourProject/ThirdParty/Astrea/Include/`
4. Update your `.Build.cs` file:

```csharp
PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty/Astrea/Include"));
PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty/Astrea/Lib/Win64/astro.lib"));
RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../../Binaries/Win64/astro.dll"));
```

## Advanced: Building Static Libraries

To build static `.lib` files instead of DLLs:

```cmd
cmake -B build -G "Visual Studio 17 2022" -A x64 ^
  -DCMAKE_BUILD_TYPE=Release ^
  -DBUILD_STATIC=ON

cmake --build build --config Release
```

Static libraries will be generated as:
- `astro.a.[version]`
- `math.a.[version]`
- `utilities.a.[version]`

## Build Configurations

### Development Build
For active development with debugging:
```powershell
.\build-windows.ps1 -BuildType Debug -BuildTests ON -BuildExamples ON
```

### Production Build
Optimized for performance:
```powershell
.\build-windows.ps1 -BuildType Release
```

### Profiling Build
With optimizations but debug symbols:
```powershell
.\build-windows.ps1 -BuildType RelWithDebInfo -BuildTests ON
```

### Full Feature Build
Build everything with all celestial bodies:
```powershell
.\build-windows.ps1 -BuildTests ON -BuildExamples ON `
  -BuildSun ON -BuildMoon ON -BuildEarth ON `
  -BuildMercury ON -BuildVenus ON -BuildMars ON `
  -BuildJupiter ON -BuildSaturn ON -BuildUranus ON -BuildNeptune ON
```

Or using batch script:
```batch
build-windows.bat tests examples all-planets
```

## Customizing Ephemerides

To control which celestial body ephemerides are compiled (reduces build time and binary size):

```powershell
# Only Earth and Moon
.\build-windows.ps1 -BuildSun OFF -BuildEarth ON -BuildMoon ON

# All inner planets
.\build-windows.ps1 -BuildMercury ON -BuildVenus ON -BuildEarth ON -BuildMars ON

# All planets using batch script
build-windows.bat all-planets
```

## See Also

- [Installation and Usage](installation_and_usage.md) - General installation guide
- [Getting Started](../index.md) - Project overview
- [CMake Documentation](https://cmake.org/documentation/)
