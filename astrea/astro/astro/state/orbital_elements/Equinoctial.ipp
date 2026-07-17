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

#include <iomanip>
#include <iostream>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>

#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::LEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::LEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::LMEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::LMEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::GPS(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::GPS(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::HMEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::HMEO(), mu);
}
template <IsFrame auto _frame_>
Equinoctial<_frame_> Equinoctial<_frame_>::GEO(const GravParam& mu)
{
    return Equinoctial(Keplerian<_frame_>::GEO(), mu);
}

template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(const Keplerian<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using namespace mp_units::si;
    using namespace mp_units::angular;

    // Get r and v
    const auto& a      = elements.get_semimajor();
    const auto& ecc    = elements.get_eccentricity();
    const auto& inc    = elements.get_inclination();
    const auto& raan   = elements.get_right_ascension();
    const auto& argPer = elements.get_argument_of_perigee();
    const auto& theta  = elements.get_true_anomaly();

    // Semilatus rectum
    get_semilatus() = a * (1 - ecc * ecc);

    // Non-dimensionalized parameters
    get_f() = ecc * cos(argPer + raan);
    get_g() = ecc * sin(argPer + raan);
    get_h() = tan(inc / 2.0) * cos(raan);
    get_k() = tan(inc / 2.0) * sin(raan);

    // True longitude
    get_true_longitude() = wrap_angle(raan + argPer + theta);
}

// Copy constructor
template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(const Equinoctial<_frame_>& other) :
    Base_T(other._elements)
{
}

// Move constructor
template <IsFrame auto _frame_>
Equinoctial<_frame_>::Equinoctial(Equinoctial<_frame_>&& other) noexcept :
    Base_T(std::move(other._elements))
{
}

// Move assignment operator
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator=(Equinoctial<_frame_>&& other) noexcept
{
    if (this != &other) { _elements = std::move(other._elements); }
    return *this;
}

// Copy assignment operator
template <IsFrame auto _frame_>
Equinoctial<_frame_>& Equinoctial<_frame_>::operator=(const Equinoctial<_frame_>& other)
{
    return *this = Equinoctial(other);
}

template <IsFrame auto _frame_>
Equinoctial<_frame_>
    Equinoctial<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial<_frame_>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpSemimajor =
        math::fast_interpolate<Time, Distance>(times, { get_semilatus(), other.get_semilatus() }, targetTime);
    const Unitless interpEcc    = math::fast_interpolate<Time, Unitless>(times, { get_f(), other.get_f() }, targetTime);
    const Unitless interpInc    = math::fast_interpolate<Time, Unitless>(times, { get_g(), other.get_g() }, targetTime);
    const Unitless interpRaan   = math::fast_interpolate<Time, Unitless>(times, { get_h(), other.get_h() }, targetTime);
    const Unitless interpArgPer = math::fast_interpolate<Time, Unitless>(times, { get_k(), other.get_k() }, targetTime);
    const Angle interpTheta =
        math::fast_interpolate<Time, Angle>(times, { get_true_longitude(), other.get_true_longitude() }, targetTime);

    return Equinoctial(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, Equinoctial<_frame_> const& elements)
{
    os << "[";
    os << elements.get_semilatus() << ", ";
    os << elements.get_f() << ", ";
    os << elements.get_g() << ", ";
    os << elements.get_h() << ", ";
    os << elements.get_k() << ", ";
    os << elements.get_true_longitude();
    os << "] (Equinoctial)";
    return os;
}

template <IsFrame auto _frame_>
std::ostream& operator<<(std::ostream& os, EquinoctialPartial<_frame_> const& elements)
{
    os << "[";
    os << elements.template get<0>() << ", ";
    os << elements.template get<1>() << ", ";
    os << elements.template get<2>() << ", ";
    os << elements.template get<3>() << ", ";
    os << elements.template get<4>() << ", ";
    os << elements.template get<5>();
    os << "] (EquinoctialPartial)";
    return os;
}

template <IsFrame auto _frame_>
template <IsFrame auto target_frame>
Equinoctial<target_frame> Equinoctial<_frame_>::in_frame(const Date& epoch, const GravParam& mu) const
{
    return Equinoctial<target_frame>(Cartesian<_frame_>(*this, mu).template in_frame<target_frame>(epoch), mu);
}

} // namespace astro
} // namespace astrea