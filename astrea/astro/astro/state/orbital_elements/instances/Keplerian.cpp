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

#include <astro/state/orbital_elements/instances/Keplerian.hpp>

#include <iomanip>
#include <iostream>

#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

Keplerian Keplerian::LEO() { return Keplerian(7000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::LMEO() { return Keplerian(10000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::GPS() { return Keplerian(22000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::HMEO() { return Keplerian(30000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::GEO() { return Keplerian(42164.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }


Keplerian::Keplerian(const Equinoctial& elements, const GravParam& mu)
{

    const auto& semilatus     = elements.get_semilatus();
    const auto& f             = elements.get_f();
    const auto& g             = elements.get_g();
    const auto& h             = elements.get_h();
    const auto& k             = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Semimajor
    const auto eccSq = f * f + g * g;
    _semimajor       = semilatus / (1 - eccSq);

    // Eccentricity
    _eccentricity = sqrt(eccSq);

    // Inclination
    const auto hSqPlusKSq = h * h + k * k;
    _inclination          = atan2(2.0 * sqrt(hSqPlusKSq), 1 - hSqPlusKSq);

    // Arg perigee
    _argPerigee = atan2(g * h - f * k, f * h + g * k);

    // Right ascension
    _rightAscension = atan2(k, h);

    // Anomaly
    _trueAnomaly = trueLongitude - (_rightAscension + _argPerigee);

    wrap_angles();
}

// Copy constructor
Keplerian::Keplerian(const Keplerian& other) :
    _semimajor(other._semimajor),
    _eccentricity(other._eccentricity),
    _inclination(other._inclination),
    _rightAscension(other._rightAscension),
    _argPerigee(other._argPerigee),
    _trueAnomaly(other._trueAnomaly)
{
}

// Move constructor
Keplerian::Keplerian(Keplerian&& other) noexcept :
    _semimajor(std::move(other._semimajor)),
    _eccentricity(std::move(other._eccentricity)),
    _inclination(std::move(other._inclination)),
    _rightAscension(std::move(other._rightAscension)),
    _argPerigee(std::move(other._argPerigee)),
    _trueAnomaly(std::move(other._trueAnomaly))
{
}

// Move assignment operator
Keplerian& Keplerian::operator=(Keplerian&& other) noexcept
{
    if (this != &other) {
        _semimajor      = std::move(other._semimajor);
        _eccentricity   = std::move(other._eccentricity);
        _inclination    = std::move(other._inclination);
        _rightAscension = std::move(other._rightAscension);
        _argPerigee     = std::move(other._argPerigee);
        _trueAnomaly    = std::move(other._trueAnomaly);
    }
    return *this;
}

Angle Keplerian::get_mean_anomaly() const { return convert_true_anomaly_to_mean_anomaly(_trueAnomaly, _eccentricity); }

MeanMotion Keplerian::get_mean_motion(const GravParam& mu) const
{
    return sqrt(mu / (_semimajor * _semimajor * _semimajor));
}

Time Keplerian::get_orbital_period(const GravParam& mu) const
{
    const auto meanMotion = get_mean_motion(mu);
    return (2.0 * std::numbers::pi) / meanMotion;
}

// Copy assignment operator
Keplerian& Keplerian::operator=(const Keplerian& other) { return *this = Keplerian(other); }

// Comparitors operators
bool Keplerian::operator==(const Keplerian& other) const
{
    return (
        _semimajor == other._semimajor && _eccentricity == other._eccentricity && _inclination == other._inclination &&
        _rightAscension == other._rightAscension && _argPerigee == other._argPerigee && _trueAnomaly == other._trueAnomaly
    );
}

bool Keplerian::operator!=(const Keplerian& other) const { return !(*this == other); }


// Mathmatical operators
Keplerian Keplerian::operator+(const Keplerian& other) const
{
    return Keplerian(
        _semimajor + other._semimajor,
        _eccentricity + other._eccentricity,
        _inclination + other._inclination,
        _rightAscension + other._rightAscension,
        _argPerigee + other._argPerigee,
        _trueAnomaly + other._trueAnomaly
    );
}
Keplerian& Keplerian::operator+=(const Keplerian& other)
{
    _semimajor += other._semimajor;
    _eccentricity += other._eccentricity;
    _inclination += other._inclination;
    _rightAscension += other._rightAscension;
    _argPerigee += other._argPerigee;
    _trueAnomaly += other._trueAnomaly;
    return *this;
}

Keplerian Keplerian::operator-(const Keplerian& other) const
{
    return Keplerian(
        _semimajor - other._semimajor,
        _eccentricity - other._eccentricity,
        _inclination - other._inclination,
        _rightAscension - other._rightAscension,
        _argPerigee - other._argPerigee,
        _trueAnomaly - other._trueAnomaly
    );
}
Keplerian& Keplerian::operator-=(const Keplerian& other)
{
    _semimajor -= other._semimajor;
    _eccentricity -= other._eccentricity;
    _inclination -= other._inclination;
    _rightAscension -= other._rightAscension;
    _argPerigee -= other._argPerigee;
    _trueAnomaly -= other._trueAnomaly;
    return *this;
}

Keplerian Keplerian::operator*(const Unitless& multiplier) const
{
    return Keplerian(
        _semimajor * multiplier, _eccentricity * multiplier, _inclination * multiplier, _rightAscension * multiplier, _argPerigee * multiplier, _trueAnomaly * multiplier
    );
}
Keplerian& Keplerian::operator*=(const Unitless& multiplier)
{
    _semimajor *= multiplier;
    _eccentricity *= multiplier;
    _inclination *= multiplier;
    _rightAscension *= multiplier;
    _argPerigee *= multiplier;
    _trueAnomaly *= multiplier;
    return *this;
}

KeplerianPartial Keplerian::operator/(const Time& time) const
{
    return KeplerianPartial(_semimajor / time, _eccentricity / time, _inclination / time, _rightAscension / time, _argPerigee / time, _trueAnomaly / time);
}

Keplerian Keplerian::operator/(const Unitless& divisor) const
{
    return Keplerian(_semimajor / divisor, _eccentricity / divisor, _inclination / divisor, _rightAscension / divisor, _argPerigee / divisor, _trueAnomaly / divisor);
}
Keplerian& Keplerian::operator/=(const Unitless& divisor)
{
    _semimajor /= divisor;
    _eccentricity /= divisor;
    _inclination /= divisor;
    _rightAscension /= divisor;
    _argPerigee /= divisor;
    _trueAnomaly /= divisor;
    return *this;
}

Keplerian Keplerian::interpolate(const Time& thisTime, const Time& otherTime, const Keplerian& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpSemimajor =
        math::fast_interpolate<Time, Distance>(times, { _semimajor, other.get_semimajor() }, targetTime);
    const Unitless interpEcc =
        math::fast_interpolate<Time, Unitless>(times, { _eccentricity, other.get_eccentricity() }, targetTime);
    const Angle interpInc    = interpolate_angle(times, { _inclination, other.get_inclination() }, targetTime);
    const Angle interpRaan   = interpolate_angle(times, { _rightAscension, other.get_right_ascension() }, targetTime);
    const Angle interpArgPer = interpolate_angle(times, { _argPerigee, other.get_argument_of_perigee() }, targetTime);
    const Angle interpTheta  = interpolate_angle(times, { _trueAnomaly, other.get_true_anomaly() }, targetTime);

    return Keplerian(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

Angle Keplerian::interpolate_angle(const std::array<Time, 2>& times, const std::array<Angle, 2>& angles, const Time& targetTime) const
{
    // These is an assumption on the size of the diff. If the time step is too big, this will cause errors
    // TODO: Catch large interpolation steps
    if (abs(angles[0] - angles[1]) > 300.0 * deg) {
        if (angles[0] > angles[1]) {
            return math::fast_interpolate<Time, Angle>(times, { angles[0], angles[1] + 360.0 * deg }, targetTime);
        }
        return math::fast_interpolate<Time, Angle>(times, { angles[0] + 360.0 * deg, angles[1] }, targetTime);
    }
    return math::fast_interpolate<Time, Angle>(times, { angles[0], angles[1] }, targetTime);
}

std::vector<Unitless> Keplerian::force_to_vector() const
{
    return { _semimajor / _semimajor.unit,     _eccentricity,
             _inclination / _inclination.unit, _rightAscension / _rightAscension.unit,
             _argPerigee / _argPerigee.unit,   _trueAnomaly / _trueAnomaly.unit };
}

void Keplerian::wrap_angles()
{
    _inclination    = wrap_angle(_inclination);
    _rightAscension = wrap_angle(_rightAscension);
    _argPerigee     = wrap_angle(_argPerigee);
    _trueAnomaly    = wrap_angle(_trueAnomaly);
}

Keplerian Keplerian::from_vector(const std::vector<Unitless>& vec)
{
    if (vec.size() != 6) {
        throw std::runtime_error("Input vector must have exactly 6 elements to convert to Keplerian.");
    }
    return Keplerian(
        vec[0] * detail::distance_unit,
        vec[1],
        vec[2] * detail::angle_unit,
        vec[3] * detail::angle_unit,
        vec[4] * detail::angle_unit,
        vec[5] * detail::angle_unit
    );
}


Keplerian KeplerianPartial::operator*(const Time& time) const
{
    return Keplerian(
        _semimajorPartial * time,
        _eccentricityPartial * time,
        _inclinationPartial * time,
        _rightAscensionPartial * time,
        _argPerigeePartial * time,
        _trueAnomalyPartial * time
    );
}

std::vector<Unitless> KeplerianPartial::force_to_vector() const
{
    return { _semimajorPartial / _semimajorPartial.unit,     _eccentricityPartial / _eccentricityPartial.unit,
             _inclinationPartial / _inclinationPartial.unit, _rightAscensionPartial / _rightAscensionPartial.unit,
             _argPerigeePartial / _argPerigeePartial.unit,   _trueAnomalyPartial / _trueAnomalyPartial.unit };
}

std::ostream& operator<<(std::ostream& os, Keplerian const& elements)
{
    os << "[";
    os << elements.get_semimajor() << ", ";
    os << elements.get_eccentricity() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_right_ascension() << ", ";
    os << elements.get_argument_of_perigee() << ", ";
    os << elements.get_true_anomaly();
    os << "] (Keplerian)";
    return os;
}

std::ostream& operator<<(std::ostream& os, KeplerianPartial const& elements)
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