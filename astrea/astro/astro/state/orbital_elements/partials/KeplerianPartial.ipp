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

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
KeplerianPartial<_frame_> Keplerian<_frame_>::operator/(const Time& time) const
{
    return KeplerianPartial<_frame_>(
        _semimajor / time, _eccentricity / time, _inclination / time, _rightAscension / time, _argPerigee / time, _trueAnomaly / time
    );
}

template <IsFrame auto _frame_>
Keplerian<_frame_> KeplerianPartial<_frame_>::operator*(const Time& time) const
{
    return Keplerian<_frame_>(
        _semimajorPartial * time,
        _eccentricityPartial * time,
        _inclinationPartial * time,
        _rightAscensionPartial * time,
        _argPerigeePartial * time,
        _trueAnomalyPartial * time
    );
}

template <IsFrame auto _frame_>
std::vector<double> KeplerianPartial<_frame_>::force_to_double_vector() const
{
    return { _semimajorPartial.numerical_value_in(_semimajorPartial.unit),
             _eccentricityPartial.numerical_value_in(_eccentricityPartial.unit),
             _inclinationPartial.numerical_value_in(_inclinationPartial.unit),
             _rightAscensionPartial.numerical_value_in(_rightAscensionPartial.unit),
             _argPerigeePartial.numerical_value_in(_argPerigeePartial.unit),
             _trueAnomalyPartial.numerical_value_in(_trueAnomalyPartial.unit) };
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, KeplerianPartial<_frame_> const& elements)
{
    os << "[";
    os << elements._semimajorPartial << ", ";
    os << elements._eccentricityPartial << ", ";
    os << elements._inclinationPartial << ", ";
    os << elements._rightAscensionPartial << ", ";
    os << elements._argPerigeePartial << ", ";
    os << elements._trueAnomalyPartial;
    os << "] (KeplerianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea