# Force Models

Astrea provides a comprehensive force modeling system that enables accurate simulation of perturbations acting on spacecraft. The modular design allows users to combine multiple force sources and create custom perturbation models for high-fidelity orbit propagation.

## Force Model Architecture

The force modeling system is built around several key components:

- **Force Base Class**: Abstract interface for all force implementations
- **ForceModel Container**: Manages multiple forces and computes total acceleration
- **Predefined Forces**: Common astrodynamics perturbations
- **Custom Forces**: User-defined perturbation models

## Force Interface

All forces implement the abstract Force base class:

```cpp
#include <astro/propagation/force_models/PerturbingForce.hpp>

class Force {
public:
    virtual AccelerationVector<frames::earth::icrf>
        compute_perturbation(const State& state, const Vehicle& vehicle) const = 0;
};
```

Currently, a `Force` is defined through polymorphism instead of type-erasure because it was initially designed to be relatively static for users. If more users need custom forces, it may be updated to the more dynamic and user-friendly type-erased model similar to the `Vehicle` and `Event` classes.

Forces compute the acceleration contribution from a specific perturbation based on the current state and vehicle properties, and return the resultant acceleration in `earth::icrf`. This is a current shortcoming of the design, and future iterations will eventually support returning vectors in any of several reference frames.

## ForceModel Container

The ForceModel class manages multiple force sources:

```cpp
#include <astro/propagation/force_models/ForceModel.hpp>

// Create force model container
ForceModel forces;

// Add forces using template syntax
forces.add<AtmosphericForce>(densityModel);
forces.add<OblatenessForce>(system, 10, 10);  // J2 through J10
forces.add<SolarRadiationPressure>(reflectivityCoefficient);

// Compute total acceleration
AccelerationVector<frames::earth::icrf>  totalAccel = forces.compute_acceleration(state, vehicle);
```

The `ForceModel` uses a factory pattern to create, store, and invoke forces. Forces are constructed directly by forwarding the inputs to the ForceModel which are invoked inside propagation to represent the wholistic set of forces acting on a given vehicle.

## Predefined Force Models

### Atmospheric Drag

Models atmospheric drag effects on spacecraft:

```cpp
#include <astro/propagation/force_models/instances/AtmosphericForce.hpp>

// Create atmospheric force model
AtmosphericModel atmosphereModel = /* density model */;
AtmosphericForce dragForce(atmosphereModel);
```

$$
\vec{a}_\text{drag} = -\frac{1}{2} \rho C_d A \frac{|v_\text{rel}|}{m} \vec{v}_\text{rel}
$$

```cpp
AccelerationVector<frames::earth::icrf>  dragAccel = dragForce.compute_perturbation(state, satellite);
```
Currently, the atmospheric force model only supports the Jacchia-Roberts 1971 density model, but future iterations will support additional models and user-defined density profiles.

---
### Gravitational Harmonics

Models gravitational perturbations due to Earth's non-spherical shape:

```cpp
#include <astro/propagation/force_models/instances/OblatenessForce.hpp>

// Create oblateness force with zonal harmonics
constexpr int maxDegree = 10; // Include up to J10
constexpr int maxOrder = 10;  // Include tesseral harmonics
OblatenessForce oblatenessForce<planets::Earth, maxDegree, maxOrder>();
```

The oblateness force computes the acceleration from the Earth's gravity field using spherical harmonic coefficients, accounting for both zonal and tesseral terms according to the standard formulation for gravitational potential:
$$
V = \frac{\mu}{r} \sum_{n=0}^{N} \left( \frac{R_e}{r} \right)^n \sum_{m=0}^{\min(n,M)} P_{nm}(\sin(\phi)) \left( C_{nm} \cos(m\lambda) + S_{nm} \sin(m\lambda) \right)
$$

```cpp
AccelerationVector<frames::earth::icrf> oblatenessAccel = oblatenessForce.compute_perturbation(state, vehicle);
```
Currently, the oblateness force model only supports the EGM2008 gravity field, but future iterations will support additional fields and user-defined spherical harmonic coefficients. There are also stored coefficients for the Moon, Mars, Mercury, and Venus.

---
### Solar Radiation Pressure

Models radiation pressure from solar photons:

```cpp
#include <astro/propagation/force_models/instances/SolarRadiationPressure.hpp>

// Create solar radiation pressure model
SolarRadiationPressure srpForce;
```

$$
\vec{a}_\text{srp} = -P_{solar} η C_{R} \frac{A}{m}
$$

```cpp
AccelerationVector<frames::earth::icrf>  srpAccel = srpForce.compute_perturbation(state, satellite);
```
The solar radiation pressure model currently uses a single averaged value for the solar radiation pressure at 1 AU and a simple umbra/penumbra model, but future iterations will support time-varying solar flux and user-defined radiation pressure values as well as more complex models that account for eclipses and shadowing effects.

---
### N-Body Gravitational Perturbations

Models gravitational effects from third bodies (Moon, Sun, planets):

```cpp
#include <astro/propagation/force_models/instances/NBodyForce.hpp>

// N-body force includes all secondary bodies
NBodyForce nBodyForce<planets::Earth, moons::Moon, stars::Sun>();
```
Computes gravitational acceleration from each perturbing body:
$$
\vec{a}_\text{n-body} = \sum_i^N \mu_i \frac{\vec{r}_i - \vec{r}_\text{sat}}{|\vec{r}_i - \vec{r}_\text{sat}|^3} - \mu_i \frac{\vec{r}_i}{|\vec{r}_i|^3}
$$

where \(\vec{r}_i\) is position of perturbing body \(i\) relative to central body

```cpp
AccelerationVector<frames::earth::icrf>  nBodyAccel = nBodyForce.compute_perturbation(state, vehicle);
```

## Custom Force Implementation

Users can create custom force models by inheriting from the Force base class:

```cpp
// Custom thruster force
class ThrusterForce : public PerturbingForce {
public:
    ThrusterForce(const RadiusVector<frames::earth::icrf>& thrustVector, const Time& startTime, const Time& duration) :
        _thrustVector(thrustVector),
        _startTime(startTime),
        _duration(duration)
    {
    }

    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        Time currentTime = state.get_epoch();

        // Check if thrust is active
        if (currentTime >= _startTime && currentTime <= _startTime + _duration) {
            Mass vehicleMass = vehicle.get_mass(state);
            return _thrustVector / vehicleMass;  // F = ma -> a = F/m
        }

        return AccelerationVector<frames::earth::icrf>(0.0 * m/s/s, 0.0 * m/s/s, 0.0 * m/s/s);
    }

private:
    RadiusVector<frames::earth::icrf> _thrustVector;
    Time _startTime;
    Time _duration;
};

// Add custom force to force model
RadiusVector<frames::earth::icrf> thrust(100.0 * N, 0.0 * N, 0.0 * N);
Time thrustStart = epoch_to_julian_date("2024-01-01 12:00:00");
Time thrustDuration = 300.0 * s;

forces.add<ThrusterForce>(thrust, thrustStart, thrustDuration);
```

## Comprehensive Force Model Example

```cpp
// Create high-fidelity force model for LEO satellite
ForceModel allForces;

allForces.add<OblatenessForce, planets::Earth, 10, 10>(); // Earth gravity field (up to degree order 10)
allForces.add<AtmosphericForce>(); // Atmospheric drag
allForces.add<SolarRadiationPressure>(); // Solar radiation pressure
allForces.add<NBodyForce, planets::Earth, moons::Moon, stars::Sun>(); // Third-body perturbations (Moon and Sun)
allForces.add<ThrusterForce>(thrustVector, startTime, duration); // Custom station-keeping thrusters

// Use with propagation
CowellsMethod equations(allForces);
State finalState = integrator.propagate(initialState, satellite, equations, propagationTime);
```
