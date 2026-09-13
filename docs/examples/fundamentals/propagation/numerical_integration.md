# Numerical Integration

## Overview

Astrea provides a specialized numerical integrator designed specifically for astrodynamics applications. While numerous numerical integration libraries exist with more extensive feature sets, Astrea's integrator offers unique advantages:

- **Type Safety**: Designed for strongly-typed element sets to prevent unit-unsafe operations
- **Numerical Accuracy**: Eliminates hidden numerical errors and implicit unit conversions
- **Transparency**: Provides clear visibility into the integration process
- **Extensibility**: Allows for custom force models and equations of motion

Although this approach may require more explicit configuration compared to other libraries, it ensures computational integrity and provides greater control over the integration process.

At core, propagation is about predicting the future state of a system based on its current state and the forces acting upon it. In astrodynamics, this involves integrating some equations of motion over time. Exactly which model to use depends on the problem and can vary greatly between use cases. A user may need only a simple J2 for long-term revisit analysis. Another may need the bleeding-edge accuracy to use in orbit determination. Some users may want to use a simple two-body model for the dynamics, but want full kinematic perturbations.

The goal of Astrea's numerical integrator is to provide a flexible and extensible framework that allows users to define their own equations of motion, force models, and state representations while maintaining a consistent interface for propagation.

## Setup

#### State Definition
The state is meant to encompass everything that is needed to completely define a dynamic object. As of now, this includes the epoch, the orbital elements, and an optional attitude. A design is currently being worked on to arbitrarily extend this definition for any arbitrary user-defined state representation. 
```cpp
const Date epoch("2028-06-23 12:10:45.000");
const Keplerian orbit0(
    10000.0 * km, // semi-major axis
    0.0 * one,    // eccentricity
    45.0 * deg,   // inclination
    0.0 * deg,    // right ascension of ascending node
    0.0 * deg,    // argument of periapsis
    0.0 * deg     // true anomaly
);
const OrbitalElements elements(orbit0); // Generic container
const State state0(elements, epoch);
```

#### Vehicles
Astrea uses a type-erased Vehicle class to propagate states. This keeps the interface more static while allowing for more flexibility and extensibility for users.

```cpp
Spacecraft sat; // This can be replaced with a user's custom type
Vehicle vehicle(sat);
```

#### Force Models
The `ForceModel` class is a factory for building a collection of forces that can be applied to the propagation. Users can add their own perturbations to the propagation by inheriting from the base `PerturbingForce` class and adding it to the `ForceModel`. The following is an example of how to build a force model with atmospheric drag and 10x10 Oblateness.
```cpp
// Build a force model
ForceModel forces;
forces.add<AtmosphericForce, planets::Earth, EarthAtmosphereModel::JACCHIA_ROBERTS>();
forces.add<OblatenessForce, planets::Earth, 10, 10>();
// forces.add<UserDefinedForce>(...); // Users can add their own perturbations to the propagation
```

The force model also holds and distributes space weather data to the forces via the `SpaceWeatherProvider` interface. Users can provide their own space weather data files or use the default one provided by Astrea. The data can be specified directly through the `SpaceWeatherData` class, or the machinery will forward the construction arguments as needed.
```cpp
// Build the data directly
SpaceWeatherData spaceWeatherData("path/to/space_weather_data_file.txt");
SpaceWeatherProvider spaceWeatherProvider(spaceWeatherData);
forces.set_space_weather_provider(spaceWeatherProvider);

// Or just let the provider do it
SpaceWeatherProvider spaceWeatherProvider("path/to/space_weather_data_file.txt");
forces.set_space_weather_provider(spaceWeatherProvider);
```
This indirection is meant to allow future updates to Astrea to support hot-swapping of space weather data during propagation, as well as the ability to use different space weather data for different forces.

#### Equations of Motion
Equations of motion are the mathematical representation of how a system evolves over time. Astrea provides several built-in equations of motion, and users can define their own by inheriting from the base `EquationsOfMotion` class. These follow the same strong-typing as the various orbital element representations and require a specific orbital-element partial derivative type as their output. For example, the `TwoBody` equations of motion take in a `Cartesian` state and output a `CartesianPartial`. The integrator manages the conversions to make sure the math behind the propagation stays consistent. 

```cpp
TwoBody twoBodyEom;                       // No forces
J2MeanVop j2MeanEom;                      // Forces assumed
CowellsMethod cowellsEom(forces);         // Regular force model
KeplerianVop keplerianEom(forces, false); // Input options for rounding errors
EquinoctialVop equinoctialEom(forces);    // Fast, and stable
```

#### The Numerical Integrator
The `Integrator` class takes all of the inputs we've discussed here and propagates them through time. It is stateful and owns the equations of motion, but it has been tested to work in multi-threaded environments. 

Options for the integrator can be set on construction, or modified later, but, since the integrator is stateful, it generally can't be made constant.
```cpp
Integrator integrator({
    .absTol=1.0e-10,
    .relTol=1.0e-10,
    // other options // 
    .equationsOfMotion=eoms
});
```

Propagation can be set for a duration or to a specific epoch. 
```cpp
auto history = integrator.propagate(state0, propTime, vehicle);
auto history = integrator.propagate(state0, endEpoch, vehicle);
```
Propagation can be variable step, for speed, or fixed step if users want to control the output. 
```cpp
integrator.set_fixed_step(10.0 * sec);
```

The integrator will return a `StateHistory` object that contains the propagated states at each time step. If faster propagation is desired, the integrator will only return the final `State` when calling the `propagate_no_storage` methods. These explicit methods were chosen over settings to avoid confusion about what is being returned. 
```cpp
auto finalState = integrator.propagate_no_storage(state0, propTime, vehicle);
auto finalState = integrator.propagate_no_storage(state0, endEpoch, vehicle);
```

#### Event Handling
Astrea's integrator supports event handling, allowing users to define specific conditions that trigger events during propagation. Events can be used for simple detection, or to stop a bad run early, but they can also be used to send instructions to the vehicle, or to update the integration `State` directly. This can be a nice way to modify the propagation without introducing a complex control law in the loop. Users can define their own events by inheriting from the base `Event` class and implementing the required methods. The integrator will check for events at each time step and handle them accordingly.

```cpp
Event someEvent(SpecificEventClass); // The Event is type-erased, similar to the Vehicle class
integrator.add_event(someEvent);
```

Events are currently only checked between successful integration steps. There is currently no mechanisms in place to iterate over steps to converge on event times, nor is there any logic to hand events that occur multiple times in a single step. This is a known limitation and will be addressed in future releases.

Because of this limitation, events can trigger slightly after the event has occurred. The best way to bypass this issue at the moment is to simple use a fixed-step integration, or to the `Schedule`. 

#### Scheduling
The `Schedule` class allows users to trigger events at exact times during the propagation. This is useful for scenarios where specific actions need to be taken at predetermined times, such as maneuver execution or data collection. Users can define a schedule by specifying the times and corresponding events.

```cpp
Schedule schedule;
schedule.add_event(epoch + 1.0 * h, startCollectionEvent); 
schedule.add_event(epoch + 2.0 * h, endCollectionEvent); 
schedule.add_event(epoch + 2.0 * h, turnThrustersOnEvent);
schedule.add_event(epoch + 4.0 * h, turnThrustersOffEvent); 
integrator.set_schedule(schedule);
```

The schedule will tell the integrator to propagate n times, once between each event, and then stop, trigger each event at that time, and then continue to the next event or the end of the propagation. This allows for precise control over the propagation process and ensures that events are handled at the correct times.

#### Step Watchers
Step watchers allow users to monitor the integration process at each step. This can be useful for logging, debugging, or implementing custom behaviors based on the current state of the integrator.

```cpp
StepWatcher someWatcher(SpecificStepWatcherClass); // The StepWatcher is type-erased, similar to the Vehicle class
integrator.add_step_watcher(someWatcher);
```