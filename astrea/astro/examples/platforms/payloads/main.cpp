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

using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

// Astrea provides an interface for generically defining Payloads. The goal
// of the payload design is to allow users to define and attach objects to a
// spacecraft, while being flexible and extensible, and keeping boilerplate code
// to a minimum.

// First we define a payload and it's parameters
struct MyPayloadParameters : public PayloadParameters {
    MyPayloadParameters(const Mass& mass) :
        PayloadParameters(),
        _mass(mass)
    {
    }
    Mass get_mass(const State& state) const { return _mass; }

  private:
    Mass _mass;
};

// The payload uses CRTP to generate an "interface" that provides more generic container-like methods for the platform.
// This comes with the drawbacks of nasty pointers, lifetime issues, structural requirements for parent objects, and a
// wash of other annoying things. For now, it works, but it will likely be redesigned in the future.
struct MyPayload : public Payload<MyPayload, MyPayloadParameters> {
    template <typename Parent_T>
        requires(std::is_base_of_v<PayloadPlatform<MyPayload>, Parent_T>)
    MyPayload(const Parent_T& parent, const MyPayloadParameters& parameters) :
        Payload(parent, parameters),
        _id(utilities::IdProvider::get_next_id<"MyPayload">())
    {
    }

    std::size_t get_id() const { return _id; }

    Mass get_mass(const State& state) const { return get_parameters().get_mass(state); }

  private:
    std::size_t _id;
};

// Finally, we use the PayloadPlatform to attach our payload to a platform
struct MySpacecraft : public PayloadPlatform<MyPayload> {
    std::size_t get_id() const { return 0; }
    std::string get_name() const { return "MySpacecraft"; }
    CartesianVector<Distance, frames::earth::icrf> get_position(const Date& date) const
    {
        return { 0.0 * km, 0.0 * km, 0.0 * km };
    }
    CartesianVector<Velocity, frames::earth::icrf> get_velocity(const Date& date) const
    {
        return { 0.0 * km / s, 0.0 * km / s, 0.0 * km / s };
    }
};

int main()
{
    // Now we can build our spacecraft and attach as many payloads as we like
    MySpacecraft spacecraft;
    spacecraft.attach_payload({ 100.0 * kg });
    spacecraft.attach_payload({ 200.0 * kg });
    const auto payloads = spacecraft.get_payloads();
    for (const auto& payload : payloads) {
        std::cout << "Payload ID: " << payload.get_id() << ", Mass: " << payload.get_mass(State()) << std::endl;
    }
    return 0;
}

// The goals was to avoid writing dozens of boilerplate classes awash with methods such
// as get/set_thruster, get/set_reaction_wheel, get/set_sensor, etc. While this design works, it's currently
// overdone and needlessly fragile. By making it generic and compatible with multiple inheritance, the supporting
// code is hard to work with and extensibility is technically possible but difficult. This structure also currently
// depends on CRTP, which can cause issues on some compilers.