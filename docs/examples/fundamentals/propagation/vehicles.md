# Vehicles

Astrea provides a comprehensive vehicle modeling system for spacecraft and other astronomical platforms. The vehicle architecture supports mass properties, aerodynamic characteristics, and coordinate frame management.

## Vehicle Class

The `Vehicle` class serves as the primary interface for representing spacecraft and astronomical platforms:

- Mass property management with strongly typed units
- Aerodynamic area definitions for atmospheric modeling
- Coordinate frame attachment and transformation
- Template-based design for flexible vehicle configurations

```cpp
#include <astro/platforms/Vehicle.hpp>

// Vehicle with mass and aerodynamic properties
class Satellite {
public:
    Satellite(Mass mass, Area ramArea) : _mass(mass), _ramArea(ramArea) {}
    
    Mass get_mass(const State& state) const { return _mass; }
    Area get_ram_area() const { return _ramArea; }
    
private:
    Mass _mass;
    Area _ramArea;
};

// Create a satellite instance
Mass satMass = 500.0 * kg;
Area satArea = 2.5 * pow<2>(m);
Satellite satellite(satMass, satArea);
```

## Vehicle Concepts

Astrea uses C++20 concepts to enforce vehicle interface requirements:

### HasGetMass Concept

Ensures vehicles provide mass information:

```cpp
template <typename T>
concept HasGetMass = requires(T vehicle, const State& state) {
    { vehicle.get_mass(state) } -> std::same_as<Mass>;
};
```

### HasGetRamArea Concept  

Enables atmospheric drag calculations:

```cpp
template <typename T>
concept HasGetRamArea = requires(T vehicle) {
    { vehicle.get_ram_area() } -> std::same_as<Area>;
};
```

## Specialized Vehicle Types

The platform system supports various specialized vehicle implementations:

- **Spacecraft**: Standard orbital vehicles with propulsion systems
- **Launch vehicles**: Multi-stage vehicles with variable mass
- **Interplanetary probes**: Long-duration mission platforms
- **Small satellites**: CubeSat and microsatellite configurations

## Vehicle Properties

Vehicles can model comprehensive physical characteristics:

```cpp
class DetailedSatellite {
public:
    // Required mass property
    Mass get_mass(const State& state) const { return _dryMass + _propellantMass; }
    
    // Aerodynamic properties
    Area get_ram_area() const { return _crossSectionalArea; }
    
    // Additional properties
    Inertia get_inertia_tensor() const { return _inertiaTensor; }
    Length get_characteristic_length() const { return _characteristicLength; }
    
private:
    Mass _dryMass;
    Mass _propellantMass;
    Area _crossSectionalArea;
    Inertia _inertiaTensor;
    Length _characteristicLength;
};
```

## Integration with Propagation

Vehicle objects integrate seamlessly with orbit propagation:

- Mass properties affect gravitational and thrust calculations
- Aerodynamic properties enable atmospheric drag modeling  
- Frame definitions ensure consistent coordinate transformations
- Type safety prevents frame mixing errors at compile time

The vehicle system provides the foundation for high-fidelity spacecraft modeling in complex space environments.
