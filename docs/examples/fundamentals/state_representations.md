# State Representations

Astrea uses strongly typed element sets to allow an easier user interface
for conversions, and common operators. Currently, there are 3 supported orbital element sets:
- Classical Orbital Elements (Keplerian)
- Modified Equinoctial Elements (Equinoctial)
- Cartesian State Vectors (Cartesian)

as well as a host of angular element sets such as geodetic and spherical coordinates.

```cpp
// Build out a Cartesian element set using strongly typed, united quantities
Cartesian cartesian{
    7000.0 * km, 0.0 * km, 0.0 * km, 0.0 * km / s, 7.5 * km / s, 1.0 * km / s,
};
std::cout << "Cartesian: " << cartesian << std::endl;

// Conversions are done through the constructors for each element set type
GravParam mu = 398600.44189 * pow<3>(km) / pow<2>(s); // Earth
Keplerian keplerian{ cartesian, mu };
Equinoctial equinoctial{ keplerian, mu };

std::cout << "Converted to Keplerian: " << keplerian << std::endl;
std::cout << "Converted to Equinoctial: " << equinoctial << std::endl;
std::cout << "Converted back to Cartesian: " << Cartesian(equinoctial, mu) << std::endl << std::endl;

// Outputs:
// Cartesian: [7000 km, 0 km, 0 km, 0 km/s, 7.5 km/s, 1 km/s] (Cartesian)
// Converted to Keplerian: [7037.95 km, 0.00539276, 0.132552 rad, 0 rad, 0 rad, 0 rad] (Keplerian)
// Converted to Equinoctial: [7037.75 km, 0.00539276, 0, 0.066373, 0, 0 rad] (Equinoctial)
// Converted back to Cartesian: [7000 km, 0 km, 0 km, -0 km/s, 7.5 km/s, 1 km/s] (Cartesian)
```
A state also can hold an optional attitude.
```cpp
const BodyQuaternion orientation{ 1.0, 0.0, 0.0, 0.0 }; // Identity quaternion - no rotation
const BodyAngleVelocities angularVelocity{ 0.0 * deg / s, 0.0 * deg / s, 0.0 * deg / s };
const Attitude attitude(orientation, angularVelocity);
State stateWithAttitude(cartesian, epoch, sys, attitude);
std::cout << "State with Attitude: " << stateWithAttitude << std::endl;
std::cout << "State Attitude: " << stateWithAttitude.get_attitude().value() << std::endl << std::endl;
```

States can be stored in a StateHistory for easy access and containerization.
```cpp
StateHistory history;
std::cout << "StateHistory Size: " << history.size() << std::endl;
history.insert(state);
std::cout << "StateHistory Size: " << history.size() << std::endl;
std::cout << "history(epoch): " << history.get_state_at(epoch) << std::endl;
```