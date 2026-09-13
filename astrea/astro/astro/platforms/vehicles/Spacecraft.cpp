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

#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <algorithm>
#include <iostream>
#include <string>

#include <mp-units/systems/si.h>

#include <math/interpolation.hpp>
#include <units/units.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/orbital_data_formats/GeneralPerturbations.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>


using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

Spacecraft::Spacecraft(const GeneralPerturbations& gp)
{
    // TODO: Add catch/warning for missing values
    _id   = gp.NORAD_CAT_ID;
    _name = gp.OBJECT_NAME.has_value() ? gp.OBJECT_NAME.value() : "UNNAMED";
    if (!gp.SEMIMAJOR_AXIS.has_value() || !gp.ECCENTRICITY.has_value() || !gp.INCLINATION.has_value() ||
        !gp.RA_OF_ASC_NODE.has_value() || !gp.ARG_OF_PERICENTER.has_value() || !gp.MEAN_ANOMALY.has_value()) {
        std::cerr << "Missing GP info. Sad." << std::endl;
    }
    Keplerian<frames::primary> coes(
        gp.SEMIMAJOR_AXIS.value() * km,
        gp.ECCENTRICITY.value() * one,
        gp.INCLINATION.value() * deg,
        gp.RA_OF_ASC_NODE.value() * deg,
        gp.ARG_OF_PERICENTER.value() * deg,
        gp.MEAN_ANOMALY.value() * deg
    );
    Date epoch = gp.EPOCH.has_value() ? Date(gp.EPOCH.value(), "%Y-%m-%dT%H:%M:%S") : J2000;

    store_state(State(coes, epoch));

    _id = utilities::IdProvider::get_next_id<"Platform">();

    // All of these are just default values - TODO: Look into different or better values for approximating these
    // effects, or find how to approximate these
    // _mass
    // _coefficientOfLift
    // _sunArea
    // _liftArea
}

bool Spacecraft::operator==(const Spacecraft& other) const
{
    return (_id == other._id) && (_name == other._name) && (_mass == other._mass) &&
           (_coefficientOfDrag == other._coefficientOfDrag) && (_coefficientOfLift == other._coefficientOfLift) &&
           (_coefficientOfReflectivity == other._coefficientOfReflectivity) && (_ramArea == other._ramArea) &&
           (_sunArea == other._sunArea) && (_liftArea == other._liftArea);
}

// State History Management
void Spacecraft::set_state_history(const StateHistory& history) { _stateHistory = history; }
StateHistory& Spacecraft::get_state_history() { return _stateHistory; }
const StateHistory& Spacecraft::get_state_history() const { return _stateHistory; }
void Spacecraft::store_state(const State& state) { _stateHistory.insert(state); }

// Spacecraft Property Getters
Mass Spacecraft::get_mass(const State& state) const { return _mass; }
InertiaTensor<frames::dynamic::body> Spacecraft::get_inertia_tensor(const State& state) const { return _inertiaTensor; }
Unitless Spacecraft::get_coefficient_of_drag(const State& state) const { return _coefficientOfDrag; }
Unitless Spacecraft::get_coefficient_of_lift(const State& state) const { return _coefficientOfLift; }
Unitless Spacecraft::get_coefficient_of_reflectivity(const State& state) const { return _coefficientOfReflectivity; }
SurfaceArea Spacecraft::get_ram_area(const State& state) const { return _ramArea; }
SurfaceArea Spacecraft::get_solar_area(const State& state) const { return _sunArea; }
SurfaceArea Spacecraft::get_lift_area(const State& state) const { return _liftArea; }

// Thrust
Perturbation Spacecraft::get_control_authority(const State& state) const
{
    // As a first cut, just burn in v direction
    ForceVector<frames::dynamic::ric> totalThrust;
    for (const auto& thruster : get_payloads()) {
        if (!thruster.is_on()) { continue; }
        totalThrust[1] += thruster.get_thrust();
    }

    const Cartesian<frames::primary> elements = state.in_element_set<Cartesian<frames::primary>>();
    const auto ricFrame = frames::dynamic::ric.instantaneous(elements.get_position(), elements.get_velocity());
    return {
        .force = ricFrame.rotate_out_of_this_frame(totalThrust, state.get_epoch()), .torque = {} // first cut
    };
}

// Setters
void Spacecraft::set_mass(const Mass& mass) { _mass = mass; }
void Spacecraft::set_inertia_tensor(const InertiaTensor<frames::dynamic::body>& inertiaTensor)
{
    _inertiaTensor = inertiaTensor;
}

void Spacecraft::set_coefficient_of_drag(const Unitless& cd) { _coefficientOfDrag = cd; }
void Spacecraft::set_coefficient_of_lift(const Unitless& cl) { _coefficientOfLift = cl; }
void Spacecraft::set_coefficient_of_reflectivity(const Unitless& cr) { _coefficientOfReflectivity = cr; }

void Spacecraft::set_ram_area(const SurfaceArea& ramArea) { _ramArea = ramArea; }
void Spacecraft::set_solar_area(const SurfaceArea& solarArea) { _sunArea = solarArea; }
void Spacecraft::set_lift_area(const SurfaceArea& liftArea) { _liftArea = liftArea; }

void Spacecraft::set_name(const std::string& name) { _name = name; }

RadiusVector<frames::primary> Spacecraft::get_position(const Date& date) const
{
    const Cartesian<frames::primary> elements = _stateHistory.get_state_at(date).in_element_set<Cartesian<frames::primary>>();
    return elements.get_position();
}

VelocityVector<frames::primary> Spacecraft::get_velocity(const Date& date) const
{
    const Cartesian<frames::primary> elements = _stateHistory.get_state_at(date).in_element_set<Cartesian<frames::primary>>();
    return elements.get_velocity();
}

} // namespace astro
} // namespace astrea