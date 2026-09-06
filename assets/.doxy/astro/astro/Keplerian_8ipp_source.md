

# File Keplerian.ipp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**Keplerian.ipp**](Keplerian_8ipp.md)

[Go to the documentation of this file](Keplerian_8ipp.md)


```C++
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
#include <math/operations.hpp>

#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::LEO()
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    return Keplerian(7000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::LMEO()
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    return Keplerian(10000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::GPS()
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    return Keplerian(22000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::HMEO()
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    return Keplerian(30000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::GEO()
{
    using mp_units::one;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    return Keplerian(42164.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}

template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Cartesian<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using mp_units::si::acos;
    using mp_units::si::atan2;

    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    using mp_units::si::unit_symbols::s;

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. Assume NaN results are from singularities and force
        values to be 0.

        No idea how much of this is just wrong.
    */
    static const Unitless TOL      = 1.0e-10 * one;
    static const Angle ANGULAR_TOL = 1.0e-10 * rad;
    static const Angle PI          = std::numbers::pi * rad;
    static const Angle TWO_PI      = 2.0 * PI;

    // Get r and v
    const Distance& x  = elements.get_x();
    const Distance& y  = elements.get_y();
    const Distance& z  = elements.get_z();
    const Velocity& vx = elements.get_vx();
    const Velocity& vy = elements.get_vy();
    const Velocity& vz = elements.get_vz();

    const Distance R = sqrt(x * x + y * y + z * z);
    const Velocity V = sqrt(vx * vx + vy * vy + vz * vz);

    // Catch default/nonsense case
    if (R == 0.0 * km) {
        _semimajor      = 0.0 * km;
        _eccentricity   = 0.0 * one;
        _inclination    = 0.0 * rad;
        _rightAscension = 0.0 * rad;
        _argPerigee     = 0.0 * rad;
        _trueAnomaly    = 0.0 * rad;
        return;
    }

    // Specific Relative Angular Momentum
    const SpecificAngularMomentum hx    = y * vz - z * vy; // h = cross(r, v)
    const SpecificAngularMomentum hy    = z * vx - x * vz;
    const SpecificAngularMomentum hz    = x * vy - y * vx;
    const SpecificAngularMomentum normH = sqrt(hx * hx + hy * hy + hz * hz);

    // Setup
    const SpecificAngularMomentum Nx    = -hy; // N = cross([0 0 1], h)
    const SpecificAngularMomentum Ny    = hx;
    const SpecificAngularMomentum normN = sqrt(Nx * Nx + Ny * Ny);

    // Semimajor Axis
    _semimajor = 1.0 / (2.0 / R - V * V / mu);

    // Eccentricity
    const quantity<pow<2>(km) / s> dotRV                = x * vx + y * vy + z * vz;
    const quantity<pow<2>(s) / pow<3>(km)> oneOverMu    = (1.0 / mu);
    const quantity<pow<2>(km / s)> vSquaredMinuMuTimesR = (V * V - mu / R);

    const Unitless eccX = oneOverMu * (vSquaredMinuMuTimesR * x - dotRV * vx);
    const Unitless eccY = oneOverMu * (vSquaredMinuMuTimesR * y - dotRV * vy);
    const Unitless eccZ = oneOverMu * (vSquaredMinuMuTimesR * z - dotRV * vz);

    _eccentricity = sqrt(eccX * eccX + eccY * eccY + eccZ * eccZ);

    /*
        If the orbit has an _inclination of exactly 0, w is ill-defined, the
        _eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        _eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (_eccentricity < TOL) { _eccentricity = 0.0 * one; }

    // Inclination (rad)
    _inclination = acos(hz / normH);
    if (abs(_inclination - PI) < ANGULAR_TOL) { _inclination = 0.0 * rad; }

    // Right Ascension of Ascending Node (rad)
    if (_inclination == 0.0 * rad) { // No nodal line
        _rightAscension = 0.0 * rad;
    }
    else {
        const Unitless nxOverNMag = math::clamp_within_floating_point_error(Nx / normN, -1.0 * one, 1.0 * one);
        _rightAscension           = (Ny > 0.0 * (km * km / s)) ? acos(nxOverNMag) : TWO_PI - acos(nxOverNMag);
        if (abs(_rightAscension - TWO_PI) < ANGULAR_TOL) { _rightAscension = 0.0 * rad; }
    }

    // True Anomaly (rad)
    if (_eccentricity == 0.0 * one) {    // No argument of perigee, use nodal line
        if (_inclination == 0.0 * rad) { // No nodal line, use true longitude
            const Unitless xOverR = math::clamp_within_floating_point_error(x / R, -1.0 * one, 1.0 * one);
            _trueAnomaly          = (vx <= 0.0 * km / s) ? acos(xOverR) : TWO_PI - acos(xOverR);
        }
        else { // Use argument of latitude
            const Unitless nDotROverMag =
                math::clamp_within_floating_point_error((Nx * x + Ny * y) / (normN * R), -1.0 * one, 1.0 * one);
            _trueAnomaly = (z >= 0.0 * km) ? acos(nDotROverMag) : TWO_PI - acos(nDotROverMag);
        }
    }
    else {
        const Unitless eccDotROverMag =
            math::clamp_within_floating_point_error((eccX * x + eccY * y + eccZ * z) / (_eccentricity * R), -1.0 * one, 1.0 * one);
        _trueAnomaly = (dotRV >= 0.0 * (km * km / s)) ? acos(eccDotROverMag) : TWO_PI - acos(eccDotROverMag);
    }

    // Argument of Parigee (rad)
    if (_eccentricity == 0.0 * one) { // Ill-defined. Assume zero
        _argPerigee = 0.0 * rad;
    }
    else if (_inclination == 0.0 * rad) { // No nodal line, use ecc vec
        _argPerigee = (hz > 0.0 * (km * km / s)) ? atan2(eccY, eccX) : 2 * PI - atan2(eccY, eccX);
    }
    else {
        const Unitless eccDotNOverMag =
            math::clamp_within_floating_point_error((eccX * Nx + eccY * Ny) / (_eccentricity * normN), -1.0 * one, 1.0 * one);
        _argPerigee = (eccZ < 0.0 * one) ? TWO_PI - acos(eccDotNOverMag) : acos(eccDotNOverMag);
    }

    // Catch garbage
    if (normN == 0.0 * (km * km / s) || abs(_argPerigee - TWO_PI) < ANGULAR_TOL) {
        _trueAnomaly += _argPerigee;
        _argPerigee = 0.0 * rad;
    }

    if (abs(_trueAnomaly - TWO_PI) < ANGULAR_TOL) { _trueAnomaly = 0.0 * rad; }

    wrap_angles();
}


template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Equinoctial<_frame_>& elements, const GravParam& mu)
{
    using mp_units::sqrt;
    using mp_units::si::atan2;

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
template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Keplerian<_frame_>& other) :
    _semimajor(other._semimajor),
    _eccentricity(other._eccentricity),
    _inclination(other._inclination),
    _rightAscension(other._rightAscension),
    _argPerigee(other._argPerigee),
    _trueAnomaly(other._trueAnomaly)
{
}

// Move constructor
template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(Keplerian<_frame_>&& other) noexcept :
    _semimajor(std::move(other._semimajor)),
    _eccentricity(std::move(other._eccentricity)),
    _inclination(std::move(other._inclination)),
    _rightAscension(std::move(other._rightAscension)),
    _argPerigee(std::move(other._argPerigee)),
    _trueAnomaly(std::move(other._trueAnomaly))
{
}

// Move assignment operator
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator=(Keplerian<_frame_>&& other) noexcept
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

template <IsFrame auto _frame_>
Angle Keplerian<_frame_>::get_mean_anomaly() const
{
    return convert_true_anomaly_to_mean_anomaly(_trueAnomaly, _eccentricity);
}

template <IsFrame auto _frame_>
MeanMotion Keplerian<_frame_>::get_mean_motion(const GravParam& mu) const
{
    using mp_units::pow;
    return sqrt(mu / pow<3>(_semimajor));
}

template <IsFrame auto _frame_>
Time Keplerian<_frame_>::get_orbital_period(const GravParam& mu) const
{
    const auto meanMotion = get_mean_motion(mu);
    return (2.0 * std::numbers::pi) / meanMotion;
}

template <IsFrame auto _frame_>
SpecificAngularMomentum Keplerian<_frame_>::get_specific_angular_momentum(const GravParam& mu) const
{
    using mp_units::pow;
    return sqrt(mu * _semimajor * (1.0 - pow<2>(_eccentricity)));
}

// Copy assignment operator
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator=(const Keplerian<_frame_>& other)
{
    return *this = Keplerian(other);
}

// Comparitors operators
template <IsFrame auto _frame_>
bool Keplerian<_frame_>::operator==(const Keplerian<_frame_>& other) const
{
    return (
        _semimajor == other._semimajor && _eccentricity == other._eccentricity && _inclination == other._inclination &&
        _rightAscension == other._rightAscension && _argPerigee == other._argPerigee && _trueAnomaly == other._trueAnomaly
    );
}

template <IsFrame auto _frame_>
bool Keplerian<_frame_>::operator!=(const Keplerian<_frame_>& other) const
{
    return !(*this == other);
}


// Mathmatical operators
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::operator+(const Keplerian<_frame_>& other) const
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
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator+=(const Keplerian<_frame_>& other)
{
    _semimajor += other._semimajor;
    _eccentricity += other._eccentricity;
    _inclination += other._inclination;
    _rightAscension += other._rightAscension;
    _argPerigee += other._argPerigee;
    _trueAnomaly += other._trueAnomaly;
    return *this;
}

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::operator-(const Keplerian<_frame_>& other) const
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
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator-=(const Keplerian<_frame_>& other)
{
    _semimajor -= other._semimajor;
    _eccentricity -= other._eccentricity;
    _inclination -= other._inclination;
    _rightAscension -= other._rightAscension;
    _argPerigee -= other._argPerigee;
    _trueAnomaly -= other._trueAnomaly;
    return *this;
}

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::operator*(const Unitless& multiplier) const
{
    return Keplerian(
        _semimajor * multiplier, _eccentricity * multiplier, _inclination * multiplier, _rightAscension * multiplier, _argPerigee * multiplier, _trueAnomaly * multiplier
    );
}
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator*=(const Unitless& multiplier)
{
    _semimajor *= multiplier;
    _eccentricity *= multiplier;
    _inclination *= multiplier;
    _rightAscension *= multiplier;
    _argPerigee *= multiplier;
    _trueAnomaly *= multiplier;
    return *this;
}

template <IsFrame auto _frame_>
KeplerianPartial<_frame_> Keplerian<_frame_>::operator/(const Time& time) const
{
    return KeplerianPartial<_frame_>(
        _semimajor / time, _eccentricity / time, _inclination / time, _rightAscension / time, _argPerigee / time, _trueAnomaly / time
    );
}

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::operator/(const Unitless& divisor) const
{
    return Keplerian(_semimajor / divisor, _eccentricity / divisor, _inclination / divisor, _rightAscension / divisor, _argPerigee / divisor, _trueAnomaly / divisor);
}
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator/=(const Unitless& divisor)
{
    _semimajor /= divisor;
    _eccentricity /= divisor;
    _inclination /= divisor;
    _rightAscension /= divisor;
    _argPerigee /= divisor;
    _trueAnomaly /= divisor;
    return *this;
}

template <IsFrame auto _frame_>
Keplerian<_frame_>
    Keplerian<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Keplerian<_frame_>& other, const GravParam& mu, const Time& targetTime) const
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

template <IsFrame auto _frame_>
Angle Keplerian<_frame_>::interpolate_angle(const std::array<Time, 2>& times, const std::array<Angle, 2>& angles, const Time& targetTime) const
{
    using mp_units::si::unit_symbols::deg;
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

template <IsFrame auto _frame_>
std::vector<double> Keplerian<_frame_>::force_to_double_vector() const
{
    return {
        _semimajor.numerical_value_in(_semimajor.unit),     _eccentricity.numerical_value_in(_eccentricity.unit),
        _inclination.numerical_value_in(_inclination.unit), _rightAscension.numerical_value_in(_rightAscension.unit),
        _argPerigee.numerical_value_in(_argPerigee.unit),   _trueAnomaly.numerical_value_in(_trueAnomaly.unit)
    };
}

template <IsFrame auto _frame_>
void Keplerian<_frame_>::wrap_angles()
{
    _inclination    = wrap_angle(_inclination);
    _rightAscension = wrap_angle(_rightAscension);
    _argPerigee     = wrap_angle(_argPerigee);
    _trueAnomaly    = wrap_angle(_trueAnomaly);
}

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::from_double_vector(const std::vector<double>& vec)
{
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::rad;
    if (vec.size() != 6) {
        throw std::runtime_error("Input vector must have exactly 6 elements to convert to Keplerian.");
    }
    return Keplerian(vec[0] * km, vec[1], vec[2] * rad, vec[3] * rad, vec[4] * rad, vec[5] * rad);
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
std::ostream& operator<<(std::ostream& os, Keplerian<_frame_> const& elements)
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

template <IsFrame auto _frame_>
template <IsFrame auto target_frame>
Keplerian<target_frame> Keplerian<_frame_>::in_frame(const Date& epoch, const GravParam& mu) const
{
    if constexpr (equivalent(frame, target_frame)) { return *this; }
    return Keplerian<target_frame>(Cartesian<_frame_>(*this, mu).template in_frame<target_frame>(epoch), mu);
}

} // namespace astro
} // namespace astrea
```


