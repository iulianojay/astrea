# Equations of Motion

Astrea provides a flexible framework for implementing equations of motion in various orbital element representations. The system supports both Cartesian and classical orbital element formulations, enabling users to choose the most appropriate representation for their specific applications.

## Base Interface

All equations of motion inherit from the `EquationsOfMotion` base class:

```cpp
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>

class EquationsOfMotion {
public:
    virtual OrbitalElementPartials operator()(const State& state, const Vehicle& vehicle) const = 0;
    virtual StateTransitionMatrix compute_stm(const State& state, const Vehicle& vehicle) const = 0;
    virtual constexpr std::size_t get_expected_set_id() const = 0;
};
```

## Available Formulations

### Cowell's Method (Cartesian)

Direct integration of Cartesian position and velocity:

```cpp
#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>

// Cartesian equations of motion
CowellsMethod cartesianEOM;

// Initial Cartesian state
Cartesian cartesianElements(
    7000.0 * km, 0.0 * km, 0.0 * km,     // Position
    0.0 * km/s, 7.5 * km/s, 1.0 * km/s   // Velocity
);

State state(cartesianElements, epoch, system);
Vehicle spacecraft(satelliteParams);

// Compute state derivatives
CartesianPartials derivatives = cartesianEOM(state, spacecraft);
```

**Advantages:**
- Direct physical interpretation
- No singularities for any orbit type
- Simple force model application

**Disadvantages:**
- Accumulates numerical errors for long-term integration
- Less efficient for nearly circular orbits

### Keplerian Variation of Parameters

Integration using classical orbital elements:

```cpp
#include <astro/propagation/equations_of_motion/KeplerianVop.hpp>

// Keplerian variation of parameters
KeplerianVop keplerianEOM;

// Initial Keplerian state
Keplerian keplerianElements(
    7000.0 * km,    // Semi-major axis
    0.1,            // Eccentricity  
    45.0 * deg,     // Inclination
    0.0 * deg,      // RAAN
    0.0 * deg,      // Argument of perigee
    0.0 * deg       // True anomaly
);

State state(keplerianElements, epoch, system);

// Compute element rate derivatives
KeplerianPartials derivatives = keplerianEOM(state, spacecraft);
```

**Advantages:**
- Excellent for nearly circular orbits
- Physical meaningful parameters
- Reduced numerical error growth

**Disadvantages:**
- Singularities at zero eccentricity and inclination
- Complex force transformation required

### Equinoctial Variation of Parameters

Singularity-free orbital element representation:

```cpp
#include <astro/propagation/equations_of_motion/EquinoctialVop.hpp>

// Modified Equinoctial elements (singularity-free)
EquinoctialVop equinoctialEOM;

// Equinoctial elements automatically avoid singularities
Equinoctial equinoctialElements(
    7000.0 * km,    // Semi-parameter
    0.05,           // f component (e*cos(w))
    0.05,           // g component (e*sin(w))  
    0.1,            // h component (tan(i/2)*cos(Ω))
    0.1,            // k component (tan(i/2)*sin(Ω))
    0.0 * deg       // True longitude
);

State state(equinoctialElements, epoch, system);
EquinoctialPartials derivatives = equinoctialEOM(state, spacecraft);
```

**Advantages:**
- No singularities for any orbit type
- Efficient for all eccentricities and inclinations
- Reduced numerical errors compared to Cartesian

**Disadvantages:**
- Less intuitive physical interpretation
- Complex element-to-Cartesian conversions

### Specialized Formulations

#### J2 Mean Elements

Analytical solution for J2 perturbations:

```cpp
#include <astro/propagation/equations_of_motion/J2MeanVop.hpp>

// J2-averaged equations of motion
J2MeanVop j2meanEOM;

// Suitable for mean element propagation with J2 effects
Keplerian meanElements = /* initial elements */;
State meanState(meanElements, epoch, system);

// Propagates mean elements with J2 secular effects
KeplerianPartials meanDerivatives = j2meanEOM(meanState, spacecraft);
```

#### Two-Body Problem

Pure Keplerian motion (no perturbations):

```cpp
#include <astro/propagation/equations_of_motion/TwoBody.hpp>

// Unperturbed two-body motion
TwoBody twoBodyEOM;

// For baseline comparison or initial orbit design
CartesianPartials keplerianDerivatives = twoBodyEOM(state, spacecraft);
```

## Force Model Integration

Equations of motion work seamlessly with force models:

```cpp
// Create comprehensive force model
ForceModel forces;
forces.add<AtmosphericForce>(densityModel);
forces.add<OblatenessForce>(system, 10, 10);  // J2 through J10
forces.add<SolarRadiationPressure>(spacecraft.get_ram_area());
forces.add<NBodyForce>(system.get_secondary_bodies());

// Force model automatically integrates with any EOM formulation
CowellsMethod eom(forces);
CartesianPartials derivatives = eom(state, spacecraft);
```

## State Transition Matrix

All formulations support state transition matrix computation:

```cpp
// Compute state transition matrix for uncertainty propagation
StateTransitionMatrix stm = eom.compute_stm(state, spacecraft);

// Use for covariance propagation
CovarianceMatrix propagatedCovariance = stm * initialCovariance * stm.transpose();
```

## Numerical Integration

Equations of motion interface with numerical integrators:

```cpp
#include <astro/propagation/numerical/RungeKutta.hpp>

// Set up integration
RungeKutta4 integrator;
TimeSpan propagationTime = 24.0 * hour;

// Propagate using chosen equations of motion
State finalState = integrator.propagate(initialState, spacecraft, eom, propagationTime);
```

## Choosing the Right Formulation

### Orbit Type Considerations

| Orbit Type | Recommended EOM | Reason |
|------------|-----------------|--------|
| Circular | Equinoctial VOP | No eccentricity singularities |
| Elliptical | Keplerian VOP | Physical element interpretation |
| Highly Eccentric | Cartesian | Avoids VOP numerical issues |
| Inclined | Equinoctial VOP | No inclination singularities |
| Equatorial | Equinoctial VOP | No RAAN singularities |
| Transfer Orbits | Cartesian | Handles large eccentricity changes |

### Application-Specific Recommendations

- **Mission Design**: Keplerian VOP for intuitive element changes
- **Precise Propagation**: Cartesian for highest accuracy
- **Long-Term Analysis**: Equinoctial VOP for numerical stability
- **Mean Element Propagation**: J2 Mean VOP for averaged motion
- **Orbit Determination**: Cartesian for observation modeling

This flexible equations of motion framework enables users to select the most appropriate formulation for their specific astrodynamics applications while maintaining consistent interfaces and type safety throughout the system.