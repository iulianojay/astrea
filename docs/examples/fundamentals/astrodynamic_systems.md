# Astrodynamic Systems

Astrea provides a comprehensive astrodynamics system architecture that manages celestial bodies and their gravitational interactions. The system supports both central body dynamics and multi-body perturbations.

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
auto earthGravParam = earthSystem.get_central_body().get_gravitational_parameter();
auto earthRadius = earthSystem.get_central_body().get_radius();
```

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
GravParam mu = earth.get_gravitational_parameter();
Length radius = earth.get_radius();
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
    auto gravParam = body.get_gravitational_parameter();
    // Compute perturbation effects
}
```

## Integration with State Propagation

The astrodynamics system works seamlessly with state representation and propagation modules:

- Provides gravitational field definitions for numerical integrators
- Supplies reference frame origins for coordinate transformations
- Enables accurate modeling of complex space environments

The system architecture ensures that gravitational parameters and celestial body properties are consistently available throughout trajectory analysis workflows.
