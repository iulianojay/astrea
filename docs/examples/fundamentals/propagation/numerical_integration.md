# Numerical Integration

Astrea hosts it's own Integrator. While many numerical integrators exist, with far more robust implementations, Astrea's integrator is designed specifically for integrating the strongly typed element sets that Astrea uses without potentially dangerous unit-unsafe operations. This also helps to avoid hidden numerical errors, rounding issues, or possible implicit unit conversions. As such, the integration process is less complete, and more difficult to work with than some libraries, but also more transparent, and more extensible. For most users, integration will be no more difficult than that when using a more sophisticated integration library.

```cpp
// Setup initial state
AstrodynamicsSystem sys; // Defaults to Earth-Moon
const Date epoch;        // Defaults to J2000
const Keplerian elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
const State state0(elements, epoch, sys);

// Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing for more flexibility and extensibility for users.
Spacecraft sat; // This can be replaced with a user's custom type
Vehicle vehicle(sat);

// Build a force model
ForceModel forces;
forces.add<AtmosphericForce>();
forces.add<OblatenessForce>(sys, 10, 10);
// forces.add<UserDefinedForce>(...); // Users can add their own perturbations to the propagation

// Build EoMs - these can be selected from pre-built options, or users can create their own by inheriting from the base EquationsOfMotion class. Note that a force or perturbation model is not required.
TwoBody twoBodyEom;                       // No forces
J2MeanVop j2MeanEom;                      // Forces assumed
CowellsMethod cowellsEom(forces);         // Regular force model
KeplerianVop keplerianEom(forces, false); // Input options for rounding errors

// Propagation is done using a RKF78 method with a variable step size by default. This can be changed using the integrator setters.
Integrator integrator;
integrator.set_abs_tol(1.0e-10);
integrator.set_rel_tol(1.0e-10);

bool store = true; // Users can choose to store the state history during propagation, or not

// Propagation is done with the element representation that the equations of motion expect. This is to avoid unnecessary conversions during the integration process.
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

// Outputs
// Propagating... Two Body Propagation Complete.
// Propagating... J2 Mean Propagation Complete.
// Propagating... Cowell's Method Propagation Complete.
// Propagating... Keplerian VoP Propagation Complete.

// Func Evals: 7
// Two-Body Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
// J2-Mean Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, -7.27284e-12 rad, 5.14268e-12 rad, 0.0378809 rad] (Keplerian)
// Cowell's Method Final State: 2000-01-01 12:01:00.000, [9992.83 km, 267.794 km, 267.794 km, -0.239103 km/s, 4.4611 km/s, 4.4611 km/s] (Cartesian)
// Keplerian VOP Final State: 2000-01-01 12:01:00.000, [10000 km, 0, 0.785398 rad, 0 rad, 0 rad, 0.0378809 rad] (Keplerian)
```
