# Event Detection

Astrea provides a comprehensive event detection system that enables monitoring and responding to specific conditions
during orbit propagation. Events can trigger actions, halt propagation, or record state information when user-defined
conditions are met.


Fundamentally, events are functions that allow users to find zero-crossings during propagation. Astrea uses type-erasure
to allow users to define their own events while keeping a static internal interface. Events use two main functions, one
to measure the event value and look for zero-crossings, and another to trigger a post-event action by modifying the
current vehicle or state.

Currently, Astrea only defines a single event, an ImpulsiveBurn which triggers at perigee crossing and always burns in
the velocity direction. The impulsive burn event uses the thrust of all attached thrusters in a simple instantaneous
impulse. Future releases will support direct event scheduling, and more event types.

## Event System Architecture

The event system is built around several key concepts:

- **Event Interface**: Defines condition detection and response behavior
- **Event Detector**: Manages event monitoring during propagation
- **Event Types**: Predefined and user-defined event conditions
- **Event Actions**: Responses triggered when events occur

## Event Interface

All events implement a standardized interface using C++20 concepts:

```cpp
#include <astro/propagation/event_detection/Event.hpp>

// Event detection concept
template <typename T>
concept HasMeasureEvent = requires(const T event, const Time& time, const State& state, const Vehicle& vehicle) {
    { event.measure_event(time, state, vehicle) } -> std::same_as<Unitless>;
};

// Event naming concept
template <typename T>
concept HasGetName = requires(const T event) {
    { event.get_name() } -> std::same_as<std::string>;
};

// Terminal event concept
template <typename T>
concept HasIsTerminal = requires(const T event) {
    { event.is_terminal() } -> std::same_as<bool>;
};
```

## Basic Event Implementation

Custom events inherit from the Event base class:

```cpp
class AltitudeEvent : public Event {
public:
    AltitudeEvent(Distance targetAltitude, bool isTerminal = false)
        : _targetAltitude(targetAltitude), _terminal(isTerminal) {}

    // Measure event condition (negative when condition is met)
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        Distance currentAltitude = state.get_altitude();
        return (currentAltitude - _targetAltitude) / (1.0 * km); // Normalized difference
    }

    std::string get_name() const override {
        return "Altitude Event";
    }

    bool is_terminal() const override {
        return _terminal;
    }

private:
    Distance _targetAltitude;
    bool _terminal;
};
```

## Event Detector

The EventDetector manages event monitoring during propagation:

```cpp
#include <astro/propagation/event_detection/EventDetector.hpp>

// Create event detector
EventDetector detector;

// Add events to monitor
auto altitudeEvent = AltitudeEvent(300.0 * km, true);  // Terminal
auto apoapsisEvent = ApoapsisEvent();                  // Non-terminal

detector.add_event(altitudeEvent);
detector.add_event(apoapsisEvent);
```

## Common Event Types

### Altitude Events

```cpp
// Monitor specific altitude
class AltitudeEvent : public Event {
public:
    AltitudeEvent(Distance altitude, EventType type = EventType::CROSSING)
        : _targetAltitude(altitude), _type(type) {}

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        Distance currentAlt = magnitude(state.get_position()) - EARTH_RADIUS;

        switch(_type) {
            case EventType::CROSSING:
                return (currentAlt - _targetAltitude) / (1.0 * km);
            case EventType::MINIMUM:
                return (_targetAltitude - currentAlt) / (1.0 * km);  // Detect minimum
            case EventType::MAXIMUM:
                return (currentAlt - _targetAltitude) / (1.0 * km);  // Detect maximum
        }
    }
};
```

### Orbital Element Events

```cpp
// Apoapsis detection
class ApoapsisEvent : public Event {
public:
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        // True anomaly derivative - zero at apoapsis
        auto elements = state.get_elements<Keplerian>();
        return elements.get_true_anomaly_rate() / (1.0 * rad / s);
    }

    std::string get_name() const override { return "Apoapsis"; }
    bool is_terminal() const override { return false; }
};

// Periapsis detection
class PeriapsisEvent : public Event {
public:
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        auto elements = state.get_elements<Keplerian>();
        return elements.get_true_anomaly_rate() / (1.0 * rad / s);
    }

    std::string get_name() const override { return "Periapsis"; }
    bool is_terminal() const override { return false; }
};
```

### Time-Based Events

```cpp
// Absolute time event
class AbsoluteTimeEvent : public Event {
public:
    AbsoluteTimeEvent(const Time& targetTime)
        : _targetTime(targetTime) {}

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        return (time - _targetTime) / (1.0 * s);
    }

    std::string get_name() const override { return "Absolute Time"; }
    bool is_terminal() const override { return true; }

private:
    Time _targetTime;
};

// Duration event
class DurationEvent : public Event {
public:
    DurationEvent(const Time& startTime, const Time& duration)
        : _startTime(startTime), _duration(duration) {}

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        return ((time - _startTime) - _duration) / (1.0 * s);
    }

    std::string get_name() const override { return "Duration"; }
    bool is_terminal() const override { return true; }

private:
    Time _startTime;
    Time _duration;
};
```

### Geometric Events

```cpp
// Eclipse detection
class EclipseEvent : public Event {
public:
    EclipseEvent()
        : _system(system) {}

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        // Calculate sun angle relative to Earth shadow
        CartesianVector<Distance, ECI> sunPos = get_position<star::Sun>(state.get_epoch());
        CartesianVector<Distance, ECI> satPos = state.get_position();

        // Shadow cone calculation
        double shadowAngle = calculate_shadow_angle(sunPos, satPos);
        return shadowAngle; // Negative when in eclipse
    }

    std::string get_name() const override { return "Eclipse"; }
    bool is_terminal() const override { return false; }
};
```

## Event Actions

Events can trigger custom actions when detected:

```cpp
class ManeuverEvent : public Event {
public:
    ManeuverEvent(const CartesianVector<Acceleration, ECI>& deltaV)
        : _deltaV(deltaV) {}

    // Event action triggered after detection
    void trigger_action(State& state, Vehicle& vehicle) const override {
        // Apply instantaneous velocity change
        auto currentVel = state.get_velocity();
        auto newVel = currentVel + _deltaV * (1.0 * s); // Convert acceleration to velocity
        state.set_velocity(newVel);

        std::cout << "Maneuver executed: ΔV = " << magnitude(_deltaV) << std::endl;
    }

    std::string get_name() const override { return "Maneuver"; }
    bool is_terminal() const override { return false; }

private:
    CartesianVector<Acceleration, ECI> _deltaV;
};
```

## Integration with Propagation

Events integrate seamlessly with numerical propagators:

```cpp
#include <astro/propagation/numerical/RungeKutta.hpp>

// Set up propagator with event detection
RungeKutta4 integrator;
EventDetector detector;

// Add events
detector.add_event(AltitudeEvent(200.0 * km, true));
detector.add_event(EclipseEvent(system));
detector.add_event(ManeuverEvent(deltaVVector));

// Propagate with event monitoring
State initialState = /* ... */;
Time propagationTime = 2.0 * day;

PropagationResult result = integrator.propagate_with_events(
    initialState, spacecraft, equations, detector, propagationTime
);

// Check which events were detected
for (const auto& detectedEvent : result.detected_events) {
    std::cout << "Event detected: " << detectedEvent.name
              << " at time: " << detectedEvent.time << std::endl;
}
```

## Event Timing Accuracy

The event detector uses root-finding algorithms for precise timing:

```cpp
// Configure event detection accuracy
detector.set_tolerance(1e-12);           // Root-finding tolerance
detector.set_max_iterations(100);        // Maximum iterations
detector.set_time_precision(0.001 * s);  // Time precision
```

## Advanced Event Features

### Composite Events

```cpp
// Multiple condition events
class CompositeEvent : public Event {
public:
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        Distance altitude = state.get_altitude();
        Angle latitude = state.get_latitude();

        // Event occurs when both conditions are satisfied
        bool altitudeCondition = altitude > 400.0 * km;
        bool latitudeCondition = abs(latitude) < 30.0 * deg;

        // Return negative when both conditions are true
        return altitudeCondition && latitudeCondition ? -1.0 : 1.0;
    }
};
```

### State-Dependent Events

```cpp
// Events that depend on vehicle state
class FuelDepletionEvent : public Event {
public:
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const override {
        Mass currentFuelMass = vehicle.get_fuel_mass();
        Mass minFuelMass = 10.0 * kg;

        return (currentFuelMass - minFuelMass) / (1.0 * kg);
    }

    std::string get_name() const override { return "Fuel Depletion"; }
    bool is_terminal() const override { return true; }
};
```

This event detection system provides powerful capabilities for monitoring complex orbital conditions and automatically responding to mission-critical events during propagation.
