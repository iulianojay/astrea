# Copyright (c) 2025-2026 Jay Iuliano
#
# This file is part of Astrea.
# Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
# have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

<#
.SYNOPSIS
    Build script for Astrea on Windows
.DESCRIPTION
    PowerShell script to configure and build Astrea with various options on Windows platforms.
    Supports MSVC and MinGW compilers with flexible configuration options.
.PARAMETER BuildType
    Build configuration: Debug, Release, or RelWithDebInfo (default: Release)
.PARAMETER BuildTests
    Enable building tests (default: OFF)
.PARAMETER BuildExamples
    Enable building examples (default: OFF)
.PARAMETER BuildStatic
    Enable building static libraries (default: OFF)
.PARAMETER BuildSun
    Enable Sun ephemeris (default: ON)
.PARAMETER BuildMoon
    Enable Moon ephemeris (default: ON)
.PARAMETER BuildEarth
    Enable Earth ephemeris (default: ON)
.PARAMETER BuildMercury
    Enable Mercury ephemeris (default: OFF)
.PARAMETER BuildVenus
    Enable Venus ephemeris (default: OFF)
.PARAMETER BuildMars
    Enable Mars ephemeris (default: OFF)
.PARAMETER BuildJupiter
    Enable Jupiter ephemeris (default: OFF)
.PARAMETER BuildSaturn
    Enable Saturn ephemeris (default: OFF)
.PARAMETER BuildUranus
    Enable Uranus ephemeris (default: OFF)
.PARAMETER BuildNeptune
    Enable Neptune ephemeris (default: OFF)
.PARAMETER Clean
    Clean build directory before building
.PARAMETER Install
    Install after building (default: true)
.PARAMETER Parallel
    Number of parallel build jobs (default: number of processors)
.EXAMPLE
    .\build-windows.ps1
    # Build with default settings (Release, no tests/examples)
.EXAMPLE
    .\build-windows.ps1 -BuildType Debug -BuildTests ON -BuildExamples ON
    # Build debug configuration with tests and examples
.EXAMPLE
    .\build-windows.ps1 -BuildTests ON -BuildSun ON -BuildMoon ON -BuildEarth ON
    # Build with tests and all default celestial bodies
.EXAMPLE
    .\build-windows.ps1 -Clean
    # Clean and rebuild
#>

param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo")]
    [string]$BuildType = "Release",

    [ValidateSet("ON", "OFF")]
    [string]$BuildTests = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildExamples = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildStatic = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildSun = "ON",

    [ValidateSet("ON", "OFF")]
    [string]$BuildMoon = "ON",

    [ValidateSet("ON", "OFF")]
    [string]$BuildEarth = "ON",

    [ValidateSet("ON", "OFF")]
    [string]$BuildMercury = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildVenus = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildMars = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildJupiter = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildSaturn = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildUranus = "OFF",

    [ValidateSet("ON", "OFF")]
    [string]$BuildNeptune = "OFF",

    [switch]$Clean,

    [switch]$Install = $true,

    [int]$Parallel = $env:NUMBER_OF_PROCESSORS
)

# Set error action preference
$ErrorActionPreference = "Stop"

# Get script directory
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $ScriptDir

# Define paths
$BuildDir = Join-Path $ScriptDir "build"
$InstallDir = Join-Path $ScriptDir "install"

# Clean if requested
if ($Clean) {
    Write-Host "Cleaning build directories..." -ForegroundColor Yellow
    if (Test-Path $BuildDir) {
        Remove-Item -Recurse -Force $BuildDir
    }
    if (Test-Path $InstallDir) {
        Remove-Item -Recurse -Force $InstallDir
    }
}

# Create build directory
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

Write-Host "Configuring Astrea..." -ForegroundColor Cyan
Write-Host "  Build Type: $BuildType" -ForegroundColor Gray
Write-Host "  Tests: $BuildTests" -ForegroundColor Gray
Write-Host "  Examples: $BuildExamples" -ForegroundColor Gray
Write-Host "  Ephemerides: Sun=$BuildSun Moon=$BuildMoon Earth=$BuildEarth" -ForegroundColor Gray

# Configure CMake
$CMakeArgs = @(
    "-B", $BuildDir,
    "-S", $ScriptDir,
    "-DCMAKE_BUILD_TYPE=$BuildType",
    "-DCMAKE_INSTALL_PREFIX=$InstallDir",
    "-DBUILD_TESTS=$BuildTests",
    "-DBUILD_EXAMPLES=$BuildExamples",
    "-DBUILD_STATIC=$BuildStatic",
    "-DBUILD_SUN=$BuildSun",
    "-DBUILD_MOON=$BuildMoon",
    "-DBUILD_EARTH=$BuildEarth",
    "-DBUILD_MERCURY=$BuildMercury",
    "-DBUILD_VENUS=$BuildVenus",
    "-DBUILD_MARS=$BuildMars",
    "-DBUILD_JUPITER=$BuildJupiter",
    "-DBUILD_SATURN=$BuildSaturn",
    "-DBUILD_URANUS=$BuildUranus",
    "-DBUILD_NEPTUNE=$BuildNeptune"
)

Write-Host "`nRunning: cmake $($CMakeArgs -join ' ')" -ForegroundColor DarkGray

& cmake @CMakeArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed!"
    exit $LASTEXITCODE
}

# Build
Write-Host "`nBuilding Astrea..." -ForegroundColor Cyan
$BuildArgs = @(
    "--build", $BuildDir,
    "--config", $BuildType,
    "--parallel", $Parallel
)

Write-Host "Running: cmake $($BuildArgs -join ' ')" -ForegroundColor DarkGray

& cmake @BuildArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed!"
    exit $LASTEXITCODE
}

# Install if requested
if ($Install) {
    Write-Host "`nInstalling Astrea..." -ForegroundColor Cyan
    $InstallArgs = @(
        "--install", $BuildDir,
        "--config", $BuildType
    )

    Write-Host "Running: cmake $($InstallArgs -join ' ')" -ForegroundColor DarkGray

    & cmake @InstallArgs
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Installation failed!"
        exit $LASTEXITCODE
    }
}

Write-Host "`nBuild completed successfully!" -ForegroundColor Green
Write-Host "Build directory: $BuildDir" -ForegroundColor Gray
Write-Host "Install directory: $InstallDir" -ForegroundColor Gray

# If tests were built, provide instructions
if ($BuildTests -eq "ON") {
    Write-Host "`nTo run tests:" -ForegroundColor Cyan
    Write-Host "  cd $BuildDir" -ForegroundColor Gray
    Write-Host "  ctest --output-on-failure --parallel -C $BuildType" -ForegroundColor Gray
}