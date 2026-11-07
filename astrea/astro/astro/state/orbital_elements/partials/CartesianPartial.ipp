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
#pragma once

#include <iomanip>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/si.h>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
CartesianPartial<_frame_> Cartesian<_frame_>::operator/(const Time& time) const
{
    return CartesianPartial<_frame_>(_r / time, _v / time);
}

template <IsFrame auto _frame_>
Cartesian<_frame_> CartesianPartial<_frame_>::operator*(const Time& time) const
{
    return Cartesian<_frame_>(_v * time, _a * time);
}

template <IsFrame auto _frame_>
std::vector<double> CartesianPartial<_frame_>::force_to_double_vector() const
{
    return { _v[0].numerical_value_in(_v[0].unit), _v[1].numerical_value_in(_v[1].unit),
             _v[2].numerical_value_in(_v[2].unit), _a[0].numerical_value_in(_a[0].unit),
             _a[1].numerical_value_in(_a[1].unit), _a[2].numerical_value_in(_a[2].unit) };
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, CartesianPartial<_frame_> const& elements)
{
    os << "[";
    os << elements._v[0] << ", ";
    os << elements._v[1] << ", ";
    os << elements._v[2] << ", ";
    os << elements._a[0] << ", ";
    os << elements._a[1] << ", ";
    os << elements._a[2];
    os << "] (CartesianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea
