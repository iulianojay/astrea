/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

struct MyVehicleStatePartial;

// Beyond simple dynamics or kinematics, it is often useful to propagate other states through time. Astrea provides
// a user-defined state extension to allow users to define their own states and propagate them alongside the orbital
// elements and attitude. A user-defined state (UDS) is an arbitrary class that can be injected into the State class
// and is managed through a type-erased interface. This allows users to define their own states without needing to
// modify the core Astrea codebase, while still allowing for full integration with the rest of the Astrea framework.
// A UDS requires a few basic methods to be defined, including a method to convert the state to and from a double
// vector, as well as standard arithmetic operators.
struct MyVehicleState {
    Mass fuelMass;

    // The UDS must be able to convert to and from a double vector for integration purposes. The integrator will use
    // these methods to convert the heterogeneous values in a state to a homogeneous vector of doubles only for
    // comparing relative errors values during propagation.
    std::vector<double> force_to_double_vector() const { return { fuelMass.numerical_value_in(fuelMass.unit) }; }

    static MyVehicleState from_double_vector(const std::vector<double>& vec) { return { vec.at(0) * kg }; }

    // The UDS requires basic arithmetic and comparison operations
    MyVehicleState operator+(const MyVehicleState& other) const { return { fuelMass + other.fuelMass }; }
    MyVehicleState& operator+=(const MyVehicleState& other)
    {
        fuelMass += other.fuelMass;
        return *this;
    }
    MyVehicleState operator-(const MyVehicleState& other) const { return { fuelMass - other.fuelMass }; }
    MyVehicleState& operator-=(const MyVehicleState& other)
    {
        fuelMass -= other.fuelMass;
        return *this;
    }
    bool operator==(const MyVehicleState& other) const { return fuelMass == other.fuelMass; }

    // It also requires scalar multiplication and division operators for integration purposes
    MyVehicleState operator*(const Unitless scalar) const { return { fuelMass * scalar }; }
    MyVehicleState& operator*=(const Unitless scalar)
    {
        fuelMass *= scalar;
        return *this;
    }
    MyVehicleState operator/(const Unitless scalar) const { return { fuelMass / scalar }; }
    MyVehicleState& operator/=(const Unitless scalar)
    {
        fuelMass /= scalar;
        return *this;
    }

    // The UDS also needs division with Time operators for integration. This should produce a sister class that
    // represents the partial derivative of the UDS with respect to time
    MyVehicleStatePartial operator/(const Time& time) const;

    // It requires support for streaming to an output stream for logging and debugging purposes
    friend std::ostream& operator<<(std::ostream& os, const MyVehicleState& state)
    {
        os << "[" << state.fuelMass << "] (MyVehicleState)";
        return os;
    }
};

// The UDS can then be propagated through time by defining a user-defined state partial (UDSP) that computes the
// partial derivative of the UDS with respect to time. The UDSP is then used by the integrator to propagate the UDS
// alongside the orbital elements and attitude. It requires many of the same methods as the UDS.
struct MyVehicleStatePartial {
    decltype(Mass{} / Time{}) massFlowRate;

    std::vector<double> force_to_double_vector() const
    {
        return { massFlowRate.numerical_value_in(massFlowRate.unit) };
    }

    static MyVehicleStatePartial from_double_vector(const std::vector<double>& vec) { return { vec.at(0) * kg / s }; }

    MyVehicleStatePartial operator+(const MyVehicleStatePartial& other) const
    {
        return { massFlowRate + other.massFlowRate };
    }
    MyVehicleStatePartial& operator+=(const MyVehicleStatePartial& other)
    {
        massFlowRate += other.massFlowRate;
        return *this;
    }
    MyVehicleStatePartial operator-(const MyVehicleStatePartial& other) const
    {
        return { massFlowRate - other.massFlowRate };
    }
    MyVehicleStatePartial& operator-=(const MyVehicleStatePartial& other)
    {
        massFlowRate -= other.massFlowRate;
        return *this;
    }
    bool operator==(const MyVehicleStatePartial& other) const { return massFlowRate == other.massFlowRate; }

    MyVehicleStatePartial operator*(const Unitless scalar) const { return { massFlowRate * scalar }; }
    MyVehicleStatePartial& operator*=(const Unitless scalar)
    {
        massFlowRate *= scalar;
        return *this;
    }
    MyVehicleStatePartial operator/(const Unitless scalar) const { return { massFlowRate / scalar }; }
    MyVehicleStatePartial& operator/=(const Unitless scalar)
    {
        massFlowRate /= scalar;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyVehicleStatePartial& state)
    {
        os << "[" << state.massFlowRate << "] (MyVehicleStatePartial)";
        return os;
    }

    // The only key difference between the UDS and UDSP is that the UDSP requires a multiplication operator with Time to produce a UDS.
    MyVehicleState operator*(const Time& time) const { return { massFlowRate * time }; }
};

inline MyVehicleStatePartial MyVehicleState::operator/(const Time& time) const { return { fuelMass / time }; }

int main()
{
    // In order to hook into the integration properly, the user will also have to define the equation(s) of motion of the UDS.
    // This is done either by defining a new EquationsOfMotion class that overrides the compute_user_defined_state_partials
    // method, or by setting a user-defined state partial function on an existing EquationsOfMotion class. The latter is
    // often easier for simple UDSs since it does not require defining a new class.
    auto myUdspFunc = [](const State& state, const Vehicle& vehicle, const Perturbation& perts, const Perturbation& control) -> UserDefinedStatePartial {
        // The UDS can be extracted from the state using the in_user_defined_state method. This will throw an exception
        // if the state does not contain a UDS of the expected type.
        const UserDefinedState& uds   = state.get_user_defined_state().value(); // extract from optional wrapper
        const MyVehicleState& myState = *uds.extract<MyVehicleState>();         // convert to my UDS type

        // The vehicle can be used to compute the partial derivative of the UDS with respect to time. In this case, we
        // simply return a constant mass flow rate for demonstration purposes.
        return UserDefinedStatePartial(MyVehicleStatePartial{ -0.1 * kg / s });
    };

    // Then we can attach it to whatever our eoms are
    TwoBody eoms;
    eoms.set_user_defined_state_partial_function(myUdspFunc);

    // Setup initial state
    const Date epoch; // Defaults to J2000
    const Keplerian<frames::earth::icrf> elements(10000.0 * km, 0.0 * one, 45.0 * deg, 0.0 * deg, 0.0 * deg, 0.0 * deg);
    const MyVehicleState myState{ 1000.0 * kg };
    State state0(elements, epoch);
    state0.set_user_defined_state(UserDefinedState(myState));

    // Build our vehicle
    Spacecraft sat;
    Vehicle vehicle(sat);

    // Propagate
    Integrator integrator;
    integrator.set_equations_of_motion(eoms);

    // Propagation is done with the element representation that the equations of motion expect. This is to avoid
    // unnecessary conversions during the integration process.
    std::cout << "Propagating Two-Body Mechanics with Custom State Extensions...";
    Time propTime              = minutes(1); // Propagation time can also be negative for backwards propagation.
    const StateHistory history = integrator.propagate(state0, propTime, vehicle);

    std::cout << " Propagation Complete." << std::endl;

    std::cout << "Initial State: " << state0 << std::endl;
    std::cout << "State History: " << std::endl;
    for (const auto& state : history) {
        std::cout << state << std::endl;
    }

    // While this is a heavy bit of boilerplate, it is only required once for each UDS and UDSP. Once defined, the UDS
    // can be used in any State and propagated through time using any Equations of Motion that support user-defined
    // states. Future iterations will provide interfaces for the boilerplate code for UDS and UDSP classes, but
    // for now, it has to be done manually.

    return 0;
}