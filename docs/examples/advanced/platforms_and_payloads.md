[[PLACEHOLDER]]

# Platforms and Payloads

Astrea provides a flexible platform and payload architecture that enables modular spacecraft design. The system supports payload attachment, platform management, and integrated vehicle configurations.

## PayloadPlatform Class

The `PayloadPlatform` class template provides the foundation for platforms that can carry multiple payloads:

- Template-based design supporting various payload types
- Dynamic payload attachment and detachment
- Integrated frame reference management
- Parameter collection from attached payloads

```cpp
#include <astro/platforms/PayloadPlatform.hpp>

// Platform that can carry scientific instruments
template<class Payload_T>
class SciencePlatform : public PayloadPlatform<Payload_T> {
public:
    void attach_payload(std::unique_ptr<Payload_T> payload) {
        this->attach_payload(std::move(payload));
    }
    
    auto get_all_payloads() const {
        return this->get_payloads();
    }
};
```

## Payload System

### Payload Interface

Individual payloads implement standardized interfaces:

- Parameter collection for system-level analysis
- Mass and power contribution to platform totals
- Operational state management
- Data product generation

```cpp
#include <astro/platforms/Payload.hpp>

class ScientificInstrument : public Payload {
public:
    ScientificInstrument(Mass mass, Power power) 
        : _mass(mass), _power(power) {}
    
    auto get_parameters() const {
        return PayloadParameters{
            .mass = _mass,
            .power_consumption = _power,
            .operational_state = _state
        };
    }
    
    void set_operational_state(bool active) {
        _state = active;
    }
    
private:
    Mass _mass;
    Power _power;
    bool _state = false;
};
```

### Payload Categories

The system supports various payload types:

- **Scientific instruments**: Cameras, spectrometers, radiometers
- **Communication systems**: Antennas, transponders, data processors  
- **Navigation equipment**: Star trackers, gyroscopes, GPS receivers
- **Propulsion systems**: Thrusters, fuel tanks, control systems

## Integrated Platform Design

Platforms combine vehicle characteristics with payload capabilities:

```cpp
// Combined platform and vehicle system
class MultiPayloadSatellite : 
    public Spacecraft, // Spacecraft has Thruster Payloads
    public PayloadPlatform<Camera>,
    public PayloadPlatform<Spectrometer> {
    
public:
    MultiPayloadSatellite(Mass structuralMass) 
        : _structuralMass(structuralMass) {}
    
    // Vehicle interface implementation
    Mass get_mass() const override {
        Mass payloadMass = calculate_total_payload_mass();
        return _structuralMass + payloadMass;
    }
    
    // Platform-specific methods
    void activate_all_payloads() {
        auto payloads = this->get_payloads();
        for (auto& payload : payloads) {
            payload->set_operational_state(true);
        }
    }
    
private:
    Mass _structuralMass;
    
    Mass calculate_total_payload_mass() const {
        Mass total = 0.0 * kg;
        auto payloads = this->get_payloads();
        for (const auto& payload : payloads) {
            total += payload->get_parameters().mass;
        }
        return total;
    }
};
```

## Platform Configuration

Platforms support dynamic reconfiguration:

```cpp
// Create platform and configure payloads
MultiPayloadSatellite satellite(150.0 * kg);

// Attach scientific instruments
auto camera = std::make_unique<Camera>(5.0 * kg, 15.0 * W);
auto spectrometer = std::make_unique<Spectrometer>(3.2 * kg, 8.5 * W);

satellite.attach_payload(std::move(camera));
satellite.attach_payload(std::move(spectrometer));

// System-level properties automatically updated
Mass totalMass = satellite.get_mass(); // Includes all payloads
satellite.activate_all_payloads();
```

## Frame Reference Integration

Platforms inherit frame reference capabilities:

- Coordinate system definition for payload pointing
- Transformation management between platform and payload frames
- Attitude control integration for payload targeting

```cpp
// Platform with pointing capability
class PointingPlatform : public PayloadPlatform<Instrument>,
{
public:
    void point_payload_at_target(const CartesianVector<ECI>& target) {
        // Calculate required attitude for payload pointing
        auto requiredAttitude = calculate_pointing_attitude(target);
        set_attitude(requiredAttitude);
    }
};
```

## Mission Integration

The platform and payload system enables flexible mission design:

- Modular spacecraft configuration
- Payload-specific operational modes
- Resource management across multiple payloads
- Mission timeline integration with payload operations

This architecture supports everything from simple single-payload satellites to complex multi-instrument platforms for advanced space missions.
