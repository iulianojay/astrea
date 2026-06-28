[[PLACEHOLDER]]

# Numerical Integration

## Overview

Astrea provides a specialized numerical integrator designed specifically for astrodynamics applications. While numerous numerical integration libraries exist with more extensive feature sets, Astrea's integrator offers unique advantages:

- **Type Safety**: Designed for strongly-typed element sets to prevent unit-unsafe operations
- **Numerical Accuracy**: Eliminates hidden numerical errors and implicit unit conversions
- **Transparency**: Provides clear visibility into the integration process
- **Extensibility**: Allows for custom force models and equations of motion

Although this approach may require more explicit configuration compared to other libraries, it ensures computational integrity and provides greater control over the integration process.

## Basic Integration Example

### Initial Setup

The following example demonstrates the fundamental workflow for numerical integration in Astrea:

## State Definition

```cpp
const Date epoch;        // Defaults to J2000
const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
const State state0(elements, epoch);
```

Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing for more flexibility and extensibility for users.

## Vehicles
```cpp
Spacecraft sat; // This can be replaced with a user's custom type
Vehicle vehicle(sat);
```

## Force Models
```cpp
// Build a force model
ForceModel forces;
forces.add<AtmosphericForce>();
forces.add<OblatenessForce, planets::Earth, 10, 10>();
// forces.add<UserDefinedForce>(...); // Users can add their own perturbations to the propagation
```

## Equations of Motion
Build EoMs - these can be selected from pre-built options, or users can create their own by inheriting from the base EquationsOfMotion class. Note that a force or perturbation model is not required.

```cpp
TwoBody twoBodyEom;                       // No forces
J2MeanVop j2MeanEom;                      // Forces assumed
CowellsMethod cowellsEom(forces);         // Regular force model
KeplerianVop keplerianEom(forces, false); // Input options for rounding errors
```

## The Numerical Integrator
Propagation is done using a RKF78 method with a variable step size by default. This can be changed using the integrator setters.
```cpp
Integrator integrator;
integrator.set_abs_tol(1.0e-10);
integrator.set_rel_tol(1.0e-10);
```

## Propagation
Propagation is done with the element representation that the equations of motion expect. This is to avoid unnecessary conversions
```cpp
during the integration process.
bool store = true; // Users can choose to store the state history during propagation, or not

std::cout << "Propagating...";
const StateHistory twoBodyHistory = integrator.propagate(state0, minutes(1), twoBodyEom, vehicle, store);
std::cout << " Two Body Propagation Complete." << std::endl;
vehicle = Vehicle(sat); // reset the vehicle

std::cout << "Propagating...";
const StateHistory j2MeanHistory = integrator.propagate(state0, minutes(1), j2MeanEom, vehicle, store);
std::cout << " J2 Mean Propagation Complete." << std::endl;
vehicle = Vehicle(sat);

std::cout << "Propagating...";
const StateHistory cowellsHistory = integrator.propagate(state0, minutes(1), cowellsEom, vehicle, store);
std::cout << " Cowell's Method Propagation Complete." << std::endl;
vehicle = Vehicle(sat);

std::cout << "Propagating...";
const StateHistory keplerianHistory = integrator.propagate(state0, minutes(1), keplerianEom, vehicle, store);
std::cout << " Keplerian VoP Propagation Complete." << std::endl << std::endl;

std::cout << "Func Evals: " << integrator.n_func_evals() << std::endl;
std::cout << "Two-Body Final State: " << twoBodyHistory.last() << std::endl;
std::cout << "J2-Mean Final State: " << j2MeanHistory.last() << std::endl;
std::cout << "Cowell's Method Final State: " << cowellsHistory.last() << std::endl;
std::cout << "Keplerian VOP Final State: " << keplerianHistory.last() << std::endl;

/* Outputs
Propagating... Two Body Propagation Complete.
Propagating... J2 Mean Propagation Complete.
Propagating... Cowell's Method Propagation Complete.
Propagating... Keplerian VoP Propagation Complete.

Func Evals: 7
Two-Body Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
J2-Mean Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, -7.27284e-12 rad, 5.14268e-12 rad, 0.0378809 rad] (Keplerian)
Cowell's Method Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
Keplerian VOP Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, 0 rad, 0 rad, 0.0378809 rad] (Keplerian)
*/
```

### Vehicle Configuration

```cpp
// Astrea uses a type-erased Vehicle class for flexible state propagation
// This design maintains a stable interface while supporting extensibility
Spacecraft sat;              // Default spacecraft (can be user-defined)
Vehicle vehicle(sat);
```

### Force Model Definition

```cpp
// Construct the perturbation force model
ForceModel forces;
forces.add<AtmosphericForce>();                    // Atmospheric drag
forces.add<OblatenessForce>(sys, 10, 10);         // J2-J10 oblateness terms
// forces.add<UserDefinedForce>(...);              // Custom perturbations
```

### Equations of Motion

Astrea supports multiple equation formulations, each optimized for different scenarios:

```cpp
// Available equation types:
TwoBody twoBodyEom;                                // Keplerian motion only
J2MeanVop j2MeanEom;                              // Mean element variation
CowellsMethod cowellsEom(forces);                 // Cartesian integration
KeplerianVop keplerianEom(forces, false);         // Keplerian elements with VoP
```

### Integration Configuration

```cpp
// Configure the integrator (default: RKF78 with adaptive step size)
Integrator integrator;
integrator.set_abs_tol(1.0e-10);                 // Absolute tolerance
integrator.set_rel_tol(1.0e-10);                 // Relative tolerance

bool store = true;                                // Enable state history storage
```

## Propagation Execution

### Multiple Integration Methods

The following demonstrates propagation using different equation formulations:

```cpp
// Two-Body propagation
std::cout << "Executing two-body propagation..." << std::endl;
const StateHistory twoBodyHistory = integrator.propagate(
    state0, minutes(1), twoBodyEom, vehicle, store);
std::cout << "Two-body propagation complete." << std::endl;

// Reset vehicle for next propagation
vehicle = Vehicle(sat);

// J2 Mean Element propagation
std::cout << "Executing J2 mean element propagation..." << std::endl;
const StateHistory j2MeanHistory = integrator.propagate(
    state0, minutes(1), j2MeanEom, vehicle, store);
std::cout << "J2 mean element propagation complete." << std::endl;
vehicle = Vehicle(sat);

// Cowell's method propagation
std::cout << "Executing Cowell's method propagation..." << std::endl;
const StateHistory cowellsHistory = integrator.propagate(
    state0, minutes(1), cowellsEom, vehicle, store);
std::cout << "Cowell's method propagation complete." << std::endl;
vehicle = Vehicle(sat);

// Keplerian Variation of Parameters
std::cout << "Executing Keplerian VoP propagation..." << std::endl;
const StateHistory keplerianHistory = integrator.propagate(
    state0, minutes(1), keplerianEom, vehicle, store);
std::cout << "Keplerian VoP propagation complete." << std::endl;
```

### Results Analysis

```cpp
// Display integration statistics and final states
std::cout << "\n=== Integration Results ===" << std::endl;
std::cout << "Function evaluations: " << integrator.n_func_evals() << std::endl;
std::cout << "\nFinal States:" << std::endl;
std::cout << "Two-Body:       " << twoBodyHistory.last() << std::endl;
std::cout << "J2-Mean:        " << j2MeanHistory.last() << std::endl;
std::cout << "Cowell's:       " << cowellsHistory.last() << std::endl;
std::cout << "Keplerian VoP:  " << keplerianHistory.last() << std::endl;
```

## Expected Output

When executed, the program produces the following results:

```
Executing two-body propagation...
Two-body propagation complete.
Executing J2 mean element propagation...
J2 mean element propagation complete.
Executing Cowell's method propagation...
Cowell's method propagation complete.
Executing Keplerian VoP propagation...
Keplerian VoP propagation complete.

=== Integration Results ===
Function evaluations: 7

Final States:
Two-Body:       2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
J2-Mean:        2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, -7.27284e-12 rad, 5.14268e-12 rad, 0.0378809 rad] (Keplerian)
Cowell's:       2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
Keplerian VoP:  2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, 0 rad, 0 rad, 0.0378809 rad] (Keplerian)
```

## Key Features

### Type Safety
All operations maintain dimensional consistency through Astrea's type system, preventing common integration errors related to unit mismatches.

### Integration Methods
The example demonstrates four different approaches to orbital propagation:
- **Two-Body**: Pure Keplerian motion
- **J2-Mean**: Mean element theory with secular J2 effects
- **Cowell's Method**: Direct integration of perturbed Cartesian equations
- **Keplerian VoP**: Variation of Parameters in Keplerian elements

### Performance
The low function evaluation count (7) demonstrates the efficiency of the adaptive step-size algorithm for this short-duration propagation.
