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

#include <hermes/sims-flanagan/DeltaV.hpp>

namespace astrea {
namespace hermes {

DeltaV::DeltaV(const astro::VelocityVector<astro::frames::primary>& deltaV) :
    _dv(deltaV)
{
    _id = utilities::IdProvider::get_next_id<"DeltaV">();
}

std::size_t DeltaV::get_id() const { return _id; }

const astro::VelocityVector<astro::frames::primary>& DeltaV::get_delta_v() const { return _dv; }

} // namespace hermes
} // namespace astrea
