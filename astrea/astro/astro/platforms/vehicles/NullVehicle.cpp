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

#include <astro/platforms/vehicles/NullVehicle.hpp>

#include <mp-units/systems/si.h>

#include <units/units.hpp>

namespace astrea {
namespace astro {

using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

NullVehicle::NullVehicle(const Mass& mass) :
    _mass(mass)
{
}

NullVehicle* NullVehicle::clone() const { return new NullVehicle(*this); }

Mass NullVehicle::get_mass() const { return _mass; }

std::string NullVehicle::get_name() const { return "NullVehicle"; }

} // namespace astro
} // namespace astrea
