# Vehicles

Astrea propagates states by referencing physical information about the propagated object via the `Vehicle` class. This class is a type-erased container that provides a common interface for the integrator and related processes to access the vehicle properties. It can determine it's mass, areas, and other physical properties at any given time during the propagation based on the integration state, and it can even provide a dynamic control authority during the propagation.

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

// Bind the satellite to a Vehicle interface
Vehicle vehicle(satellite);

// Integrate the vehicle's state over time
const auto state = Keplerian::LEO(get_mu<planets::Earth>());
const auto duration = 10.0 * day;
const auto states = integrator.integrate(state, duration, vehicle);
```

## User-Defined Vehicles (UDV)

Astrea uses C++20 concepts to enforce vehicle interface requirements. A user-defined vehicle (UDV) is any class that satisfies the `IsUserDefinedVehicle` concept. This means that the UDV must implement certain methods to, for example, provide the necessary physical properties for propagation without restricting the design of those vehicles too much.

#### Required User-Defined Vehicle Methods

Currently, the Vehicle only requires a `get_mass` method to be defined by the user. This method must return the mass of the vehicle at a given state.

```cpp
Mass get_mass(const State& state) const;
```

#### Optional User-Defined Vehicle Methods

The Vehicle interface, however, supports numerous optional methods that can be defined to provide additional physical properties. In general, if the UDV does not define these methods, they return default (zero) values. The following methods are optional:

```cpp
InertiaTensor<frames::dynamic::body> get_inertia_tensor(const State& state) const;
SurfaceArea get_ram_area(const State& state) const;
SurfaceArea get_lift_area(const State& state) const;
SurfaceArea get_solar_area(const State& state) const;
Unitless get_coefficient_of_drag(const State& state) const;
Unitless get_coefficient_of_lift(const State& state) const;
Unitless get_coefficient_of_reflectivity(const State& state) const;
Perturbation get_control_authority(const State& state) const;
```

How these methods are defined is up to the user, but it should be noted that _not_ defining these methods will functionally result in many dynamic perturbations being ignored.