/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/event_detection/events/Deorbit.hpp>

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/instances/Geodetic.hpp>

using mp_units::si::unit_symbols::km;

namespace astrea {
namespace astro {

Deorbit::Deorbit(const Distance& triggerAltitude) :
    _triggerAltitude(triggerAltitude)
{
}

std::string Deorbit::get_name() const { return "Deorbit"; }

Unitless Deorbit::measure_event(const Time& time, const State& state, const Vehicle& vehicle) const
{
    const Cartesian<frames::earth::icrf> elements = state.in_element_set<Cartesian<frames::earth::icrf>>();

    const CelestialBodyUniquePtr& center = state.get_system().get_central_body();
    const Distance altitude = Geodetic(elements.get_position(), state.get_epoch(), center.get()).get_altitude();

    if (_triggerAltitude != 0.0 * km) { return (altitude - _triggerAltitude) / (1.0 * km); }
    return (altitude - center->get_crash_radius()) / (1.0 * km);
}

bool Deorbit::is_terminal() const { return true; }

} // namespace astro
} // namespace astrea