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

#include <iomanip>
#include <iostream>

#include <math/interpolation.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
EquinoctialPartial<_frame_> Equinoctial<_frame_>::operator/(const Time& time) const
{
    return EquinoctialPartial<_frame_>(_semilatus / time, _f / time, _g / time, _h / time, _k / time, _trueLongitude / time);
}

template <IsFrame auto _frame_>
Equinoctial<_frame_> EquinoctialPartial<_frame_>::operator*(const Time& time) const
{
    return Equinoctial<_frame_>(_semilatusPartial * time, _fPartial * time, _gPartial * time, _hPartial * time, _kPartial * time, _trueLongitudePartial * time);
}

template <IsFrame auto _frame_>
std::vector<double> EquinoctialPartial<_frame_>::force_to_double_vector() const
{
    return { _semilatusPartial.numerical_value_in(_semilatusPartial.unit),
             _fPartial.numerical_value_in(_fPartial.unit),
             _gPartial.numerical_value_in(_gPartial.unit),
             _hPartial.numerical_value_in(_hPartial.unit),
             _kPartial.numerical_value_in(_kPartial.unit),
             _trueLongitudePartial.numerical_value_in(_trueLongitudePartial.unit) };
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, EquinoctialPartial<_frame_> const& elements)
{
    os << "[";
    os << elements._semilatusPartial << ", ";
    os << elements._fPartial << ", ";
    os << elements._gPartial << ", ";
    os << elements._hPartial << ", ";
    os << elements._kPartial << ", ";
    os << elements._trueLongitudePartial;
    os << "] (EquinoctialPartial)";
    return os;
}

} // namespace astro
} // namespace astrea