@echo off
REM Copyright (c) 2025 Jay Iuliano
REM
REM This file is part of Astrea.
REM Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
REM as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
REM Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
REM of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
REM have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.

REM Simple batch script to build Astrea on Windows
REM For advanced options, use build-windows.ps1

setlocal EnableDelayedExpansion

REM Default values
set BUILD_TYPE=Release
set BUILD_TESTS=OFF
set BUILD_EXAMPLES=OFF
set BUILD_STATIC=OFF
set BUILD_SUN=ON
set BUILD_MOON=ON
set BUILD_EARTH=ON
set BUILD_MERCURY=OFF
set BUILD_VENUS=OFF
set BUILD_MARS=OFF
set BUILD_JUPITER=OFF
set BUILD_SATURN=OFF
set BUILD_URANUS=OFF
set BUILD_NEPTUNE=OFF
set CLEAN_BUILD=0

REM Parse command line arguments
:parse_args
if "%~1"=="" goto end_parse
if /i "%~1"=="debug" set BUILD_TYPE=Debug
if /i "%~1"=="release" set BUILD_TYPE=Release
if /i "%~1"=="relwithdebinfo" set BUILD_TYPE=RelWithDebInfo
if /i "%~1"=="tests" set BUILD_TESTS=ON
if /i "%~1"=="examples" set BUILD_EXAMPLES=ON
if /i "%~1"=="static" set BUILD_STATIC=ON
if /i "%~1"=="sun" set BUILD_SUN=ON
if /i "%~1"=="moon" set BUILD_MOON=ON
if /i "%~1"=="earth" set BUILD_EARTH=ON
if /i "%~1"=="mercury" set BUILD_MERCURY=ON
if /i "%~1"=="venus" set BUILD_VENUS=ON
if /i "%~1"=="mars" set BUILD_MARS=ON
if /i "%~1"=="jupiter" set BUILD_JUPITER=ON
if /i "%~1"=="saturn" set BUILD_SATURN=ON
if /i "%~1"=="uranus" set BUILD_URANUS=ON
if /i "%~1"=="neptune" set BUILD_NEPTUNE=ON
if /i "%~1"=="all-planets" (
    set BUILD_MERCURY=ON
    set BUILD_VENUS=ON
    set BUILD_MARS=ON
    set BUILD_JUPITER=ON
    set BUILD_SATURN=ON
    set BUILD_URANUS=ON
    set BUILD_NEPTUNE=ON
)
if /i "%~1"=="clean" set CLEAN_BUILD=1
if /i "%~1"=="--help" goto show_help
if /i "%~1"=="-h" goto show_help
shift
goto parse_args
:end_parse

REM Define paths
set BUILD_DIR=%~dp0build
set INSTALL_DIR=%~dp0install

REM Clean if requested
if %CLEAN_BUILD%==1 (
    echo Cleaning build directories...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
    if exist "%INSTALL_DIR%" rmdir /s /q "%INSTALL_DIR%"
)

REM Create build directory
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

echo.
echo ========================================
echo   Astrea Windows Build Script
echo ========================================
echo   Build Type: %BUILD_TYPE%
echo   Tests: %BUILD_TESTS%
echo   Examples: %BUILD_EXAMPLES%
echo   Static: %BUILD_STATIC%
echo   Ephemerides:
echo     Sun=%BUILD_SUN% Moon=%BUILD_MOON% Earth=%BUILD_EARTH%
echo     Mercury=%BUILD_MERCURY% Venus=%BUILD_VENUS% Mars=%BUILD_MARS%
echo     Jupiter=%BUILD_JUPITER% Saturn=%BUILD_SATURN%
echo     Uranus=%BUILD_URANUS% Neptune=%BUILD_NEPTUNE%
echo ========================================
echo.

REM Configure
echo Configuring...
cmake -B "%BUILD_DIR%" -S "%~dp0" ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% ^
    -DBUILD_TESTS=%BUILD_TESTS% ^
    -DBUILD_EXAMPLES=%BUILD_EXAMPLES% ^
    -DBUILD_STATIC=%BUILD_STATIC% ^
    -DBUILD_SUN=%BUILD_SUN% ^
    -DBUILD_MOON=%BUILD_MOON% ^
    -DBUILD_EARTH=%BUILD_EARTH% ^
    -DBUILD_MERCURY=%BUILD_MERCURY% ^
    -DBUILD_VENUS=%BUILD_VENUS% ^
    -DBUILD_MARS=%BUILD_MARS% ^
    -DBUILD_JUPITER=%BUILD_JUPITER% ^
    -DBUILD_SATURN=%BUILD_SATURN% ^
    -DBUILD_URANUS=%BUILD_URANUS% ^
    -DBUILD_NEPTUNE=%BUILD_NEPTUNE%

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: CMake configuration failed!
    exit /b %ERRORLEVEL%
)

REM Build
echo.
echo Building...
cmake --build "%BUILD_DIR%" --config %BUILD_TYPE% --parallel

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Build failed!
    exit /b %ERRORLEVEL%
)

REM Install
echo.
echo Installing...
cmake --install "%BUILD_DIR%" --config %BUILD_TYPE%

if %ERRORLEVEL% neq 0 (
    echo.
    echo ERROR: Installation failed!
    exit /b %ERRORLEVEL%
)

echo.
echo ========================================
echo   Build completed successfully!
echo ========================================
echo   Build directory: %BUILD_DIR%
echo   Install directory: %INSTALL_DIR%
echo.

if /i "%BUILD_TESTS%"=="ON" (
    echo To run tests:
    echo   cd "%BUILD_DIR%"
    echo   ctest --output-on-failure --parallel -C %BUILD_TYPE%
    echo.
)

goto :eof

:show_help
echo.
echo Astrea Windows Build Script
echo.
echo Usage: build-windows.bat [options]
echo.
echo Build Types:
echo   debug               - Debug build
echo   release             - Release build (default)
echo   relwithdebinfo      - Release with debug info
echo.
echo Build Options:
echo   tests               - Build tests
echo   examples            - Build examples
echo   static              - Build static libraries
echo   clean               - Clean before building
echo.
echo Ephemeris Options:
echo   sun                 - Enable Sun ephemeris (default ON)
echo   moon                - Enable Moon ephemeris (default ON)
echo   earth               - Enable Earth ephemeris (default ON)
echo   mercury             - Enable Mercury ephemeris
echo   venus               - Enable Venus ephemeris
echo   mars                - Enable Mars ephemeris
echo   jupiter             - Enable Jupiter ephemeris
echo   saturn              - Enable Saturn ephemeris
echo   uranus              - Enable Uranus ephemeris
echo   neptune             - Enable Neptune ephemeris
echo   all-planets         - Enable all planetary ephemerides
echo.
echo Examples:
echo   build-windows.bat
echo   build-windows.bat debug tests examples
echo   build-windows.bat release tests sun moon earth
echo   build-windows.bat clean tests examples all-planets
echo.
goto :eof