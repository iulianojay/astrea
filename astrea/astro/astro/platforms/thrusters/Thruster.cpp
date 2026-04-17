/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/platforms/thrusters/Thruster.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::s;

std::size_t Thruster::get_id() const { return _id; }

Velocity Thruster::get_impulsive_delta_v() const
{
    return get_parameters().get_thrust() / get_parent()->get_mass() * s;
}

std::size_t Thruster::generate_id() const
{
    static std::size_t idCounter = 0;
    return idCounter++;
}

Thrust Thruster::get_thrust() const { return get_parameters().get_thrust(); }

void Thruster::switch_on() { get_parameters().switch_on(); }

void Thruster::switch_off() { get_parameters().switch_off(); }

bool Thruster::is_on() const { return get_parameters().is_on(); }

} // namespace astro
} // namespace astrea