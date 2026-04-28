# Astrodynamic Systems

Astrea provides an astrodynamics system architecture that manages celestial bodies and their interactions. The system supports both central body dynamics and multi-body perturbations. The `AstrodynamicsSystem` class serves as a factory for celestial bodies and does some simple calculations for relative position and velocity, namely for n-body perturbations. 

## AstrodynamicsSystem Class

The `AstrodynamicsSystem` class serves as the primary interface for managing astronomical environments:

- Central body definition with customizable gravitational parameters
- Secondary body management for perturbation analysis  
- Celestial body property access and modification
- Coordinate system definitions tied to specific reference bodies

```cpp
#include <astro/systems/AstrodynamicsSystem.hpp>

// Create Earth-centered system with Moon as secondary body
AstrodynamicsSystem earthSystem(CelestialBodyId::EARTH);

// Access central body properties
auto earthGravParam = earthSystem.get_central_body().get_mu();  // get the central body's gravitational parameter
auto mu = earthSystem.get_mu();                                 // shorcut to get the central body's gravitational parameter

const auto& center = earthSystem.get_central_body().get_center(); // rip out a pointer to the central body
auto earthEqRadius = center.get_equitorial_radius();              // and get lots of useful properties
auto earthPolarRadius = center.get_polar_radius();

// You can add secondary bodies for perturbation calculations
earthSystem.add(CelestialBodyId::MOON);   // You can reference predefined bodies by their ID
earthSystem.add(planetary_bodies::Sun()); // Or you can create your own body and add it

// And you can perform some simple calculations with the system
auto rEarth2Moon = earthSystem.get_relative_position(CelestialBodyId::MOON, CelestialBodyId::EARTH, J2000);
auto rootObject = earthSystem.get_system_root(); // Returns CelestialBodyId::SUN_BARYCENTER in this case since Earth, Moon, and Sun are all in the system
```

The current version relies on maps, but future iterations will be completely constexpr to allow for huge compile-time savings when using default systems. Future iterations will also support defining systems around a barycenter instead of central body.

## Celestial Bodies

### CelestialBody Class

Individual celestial bodies are represented using the `CelestialBody` class:

- Gravitational parameter (GM) storage
- Physical radius information  
- Body identification system
- Orbital characteristics for secondary bodies

```cpp
#include <astro/systems/CelestialBody.hpp>

// Access body properties
CelestialBody earth = earthSystem.get_central_body();
GravParam mu = earth.get_mu();
Distance radius = earth.get_equitorial_radius();
```

### Predefined Bodies

Astrea includes predefined celestial bodies with accurate physical constants:

- **Earth**: Standard gravitational parameter and radius
- **Moon**: Lunar gravitational parameter and orbital characteristics
- **Sun**: Solar gravitational parameter for interplanetary dynamics
- Additional planetary bodies available in the `planetary_bodies` module

## Multi-Body Dynamics

The system supports complex gravitational environments:

```cpp
// Multi-body system with Earth, Moon, and Sun
AstrodynamicsSystem earthMoonSunSystem(
    CelestialBodyId::EARTH,
    {CelestialBodyId::MOON, CelestialBodyId::SUN}
);

// Access secondary bodies for perturbation calculations
auto secondaryBodies = earthMoonSunSystem.get_secondary_bodies();
for (const auto& body : secondaryBodies) {
    auto gravParam = body.get_mu();
    // Compute perturbation effects
}
```