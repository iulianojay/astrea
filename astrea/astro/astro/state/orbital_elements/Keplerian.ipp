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

#include <astro/frames/definitions/transformations.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>
#include <math/interpolation.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::LEO()
{
    using mp_units::one;
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    return Keplerian(7000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::LMEO()
{
    using mp_units::one;
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    return Keplerian(10000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::GPS()
{
    using mp_units::one;
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    return Keplerian(22000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::HMEO()
{
    using mp_units::one;
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    return Keplerian(30000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}
template <IsFrame auto _frame_>
Keplerian<_frame_> Keplerian<_frame_>::GEO()
{
    using mp_units::one;
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    return Keplerian(42164.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad);
}

template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Cartesian<_frame_>& elements, const GravParam& mu)
{
    using namespace mp_units;
    using mp_units::angular::acos;
    using mp_units::angular::atan2;

    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::s;

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. Assume NaN results are from singularities and force
        values to be 0.

        No idea how much of this is just wrong.
    */
    static const Unitless tol     = 1.0e-10 * one;
    static const Angle angularTol = 1.0e-10 * rad;
    static const Angle piRad      = 1.0 * (mag<pi> * rad);
    static const Angle twoPiRad   = 2.0 * (mag<pi> * rad);

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
        get_semimajor()           = 0.0 * km;
        get_eccentricity()        = 0.0 * one;
        get_inclination()         = 0.0 * rad;
        get_right_ascension()     = 0.0 * rad;
        get_argument_of_perigee() = 0.0 * rad;
        get_true_anomaly()        = 0.0 * rad;
        return;
    }

    // Specific Relative Angular Momentum
    const SpecificAngularMomentum hx = y * vz - z * vy; // h = cross(r, v)
    const SpecificAngularMomentum hy = z * vx - x * vz;
    const SpecificAngularMomentum hz = x * vy - y * vx;

    const SpecificAngularMomentum normH = sqrt(hx * hx + hy * hy + hz * hz);

    // Setup
    const quantity Nx    = -hy; // N = cross([0 0 1], h)
    const quantity Ny    = hx;
    const quantity normN = sqrt(Nx * Nx + Ny * Ny);

    // Semimajor Axis
    get_semimajor() = 1.0 / (2.0 / R - V * V / mu);

    // Eccentricity
    const quantity<pow<2>(km) / s> dotRV                = x * vx + y * vy + z * vz;
    const quantity<pow<2>(s) / pow<3>(km)> oneOverMu    = (1.0 / mu);
    const quantity<pow<2>(km / s)> vSquaredMinuMuTimesR = (V * V - mu / R);

    const Unitless eccX = oneOverMu * (vSquaredMinuMuTimesR * x - dotRV * vx);
    const Unitless eccY = oneOverMu * (vSquaredMinuMuTimesR * y - dotRV * vy);
    const Unitless eccZ = oneOverMu * (vSquaredMinuMuTimesR * z - dotRV * vz);

    get_eccentricity() = sqrt(eccX * eccX + eccY * eccY + eccZ * eccZ);

    /*
        If the orbit has an _inclination of exactly 0, w is ill-defined, the
        _eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        _eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (get_eccentricity() < tol) { get_eccentricity() = 0.0 * one; }

    // Inclination (rad)
    get_inclination() = acos(hz / normH);
    if (abs(get_inclination() - piRad) < angularTol) { get_inclination() = 0.0 * rad; }

    // Right Ascension of Ascending Node (rad)
    if (get_inclination() == 0.0 * rad) { // No nodal line
        get_right_ascension() = 0.0 * rad;
    }
    else {
        if (Ny > 0.0 * (km * km / s)) { get_right_ascension() = acos(Nx / normN); }
        else {
            get_right_ascension() = twoPiRad - acos(Nx / normN);
        }

        if (abs(get_right_ascension() - twoPiRad) < angularTol) { get_right_ascension() = 0.0 * rad; }
    }

    // True Anomaly (rad)
    if (get_eccentricity() == 0.0 * one) {    // No argument of perigee, use nodal line
        if (get_inclination() == 0.0 * rad) { // No nodal line, use true longitude
            if (vx <= 0.0 * km / s) { get_true_anomaly() = acos(x / R); }
            else {
                get_true_anomaly() = 2 * piRad - acos(x / R);
            }
        }
        else { // Use argument of latitude
            const quantity nDotR = Nx * x + Ny * y;
            if (z >= 0.0 * km) { get_true_anomaly() = acos(nDotR / (normN * R)); }
            else {
                get_true_anomaly() = 2 * piRad - acos(nDotR / (normN * R));
            }
        }
    }
    else {
        const quantity eccDotR = eccX * x + eccY * y + eccZ * z;
        if (dotRV >= 0.0 * (km * km / s)) { get_true_anomaly() = acos(eccDotR / (get_eccentricity() * R)); }
        else {
            get_true_anomaly() = twoPiRad - acos(eccDotR / (get_eccentricity() * R));
        }
    }

    // Argument of Parigee (rad)
    if (get_eccentricity() == 0.0 * one) { // Ill-defined. Assume zero
        get_argument_of_perigee() = 0.0 * rad;
    }
    else if (get_inclination() == 0.0 * rad) { // No nodal line, use ecc vec
        if (hz > 0.0 * (km * km / s)) { get_argument_of_perigee() = atan2(eccY, eccX); }
        else {
            get_argument_of_perigee() = 2 * piRad - atan2(eccY, eccX);
        }
    }
    else {
        const quantity eccDotN = eccX * Nx + eccY * Ny;
        if (eccZ < 0.0 * one) { get_argument_of_perigee() = twoPiRad - acos(eccDotN / (get_eccentricity() * normN)); }
        else {
            get_argument_of_perigee() = acos(eccDotN / (get_eccentricity() * normN));
        }
    }

    // Catch garbage
    if (normN == 0.0 * (km * km / s) || abs(get_argument_of_perigee() - twoPiRad) < angularTol) {
        get_true_anomaly() += get_argument_of_perigee();
        get_argument_of_perigee() = 0.0 * rad;
    }

    if (abs(get_true_anomaly() - twoPiRad) < angularTol) { get_true_anomaly() = 0.0 * rad; }

    wrap_angles();
}


template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Equinoctial<_frame_>& elements, const GravParam& mu)
{
    using mp_units::sqrt;
    using mp_units::angular::atan2;

    const auto& semilatus     = elements.get_semilatus();
    const auto& f             = elements.get_f();
    const auto& g             = elements.get_g();
    const auto& h             = elements.get_h();
    const auto& k             = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Semimajor
    const auto eccSq = f * f + g * g;
    get_semimajor()  = semilatus / (1 - eccSq);

    // Eccentricity
    get_eccentricity() = sqrt(eccSq);

    // Inclination
    const auto hSqPlusKSq = h * h + k * k;
    get_inclination()     = atan2(2.0 * sqrt(hSqPlusKSq), 1 - hSqPlusKSq);

    // Arg perigee
    get_argument_of_perigee() = atan2(g * h - f * k, f * h + g * k);

    // Right ascension
    get_right_ascension() = atan2(k, h);

    // Anomaly
    get_true_anomaly() = trueLongitude - (get_right_ascension() + get_argument_of_perigee());

    wrap_angles();
}

// Copy constructor
template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(const Keplerian<_frame_>& other) :
    Base_T(other._elements)
{
}

// Move constructor
template <IsFrame auto _frame_>
Keplerian<_frame_>::Keplerian(Keplerian<_frame_>&& other) noexcept :
    Base_T(std::move(other._elements))
{
}

// Move assignment operator
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator=(Keplerian<_frame_>&& other) noexcept
{
    if (this != &other) { _elements = std::move(other._elements); }
    return *this;
}

template <IsFrame auto _frame_>
Angle Keplerian<_frame_>::get_mean_anomaly() const
{
    return convert_true_anomaly_to_mean_anomaly(get_true_anomaly(), get_eccentricity());
}

template <IsFrame auto _frame_>
MeanMotion Keplerian<_frame_>::get_mean_motion(const GravParam& mu) const
{
    return sqrt(mu / (get_semimajor() * get_semimajor() * get_semimajor()));
}

template <IsFrame auto _frame_>
Time Keplerian<_frame_>::get_orbital_period(const GravParam& mu) const
{
    const auto meanMotion = get_mean_motion(mu);
    return (2.0 * std::numbers::pi) / meanMotion;
}

// Copy assignment operator
template <IsFrame auto _frame_>
Keplerian<_frame_>& Keplerian<_frame_>::operator=(const Keplerian<_frame_>& other)
{
    return *this = Keplerian(other);
}
template <IsFrame auto _frame_>
Keplerian<_frame_>
    Keplerian<_frame_>::interpolate(const Time& thisTime, const Time& otherTime, const Keplerian<_frame_>& other, const GravParam& mu, const Time& targetTime) const
{
    const std::array<Time, 2> times = { thisTime, otherTime };
    const Distance interpSemimajor =
        math::fast_interpolate<Time, Distance>(times, { get_semimajor(), other.get_semimajor() }, targetTime);
    const Unitless interpEcc =
        math::fast_interpolate<Time, Unitless>(times, { get_eccentricity(), other.get_eccentricity() }, targetTime);
    const Angle interpInc = interpolate_angle(times, { get_inclination(), other.get_inclination() }, targetTime);
    const Angle interpRaan = interpolate_angle(times, { get_right_ascension(), other.get_right_ascension() }, targetTime);
    const Angle interpArgPer = interpolate_angle(times, { get_argument_of_perigee(), other.get_argument_of_perigee() }, targetTime);
    const Angle interpTheta = interpolate_angle(times, { get_true_anomaly(), other.get_true_anomaly() }, targetTime);

    return Keplerian(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

template <IsFrame auto _frame_>
Angle Keplerian<_frame_>::interpolate_angle(const std::array<Time, 2>& times, const std::array<Angle, 2>& angles, const Time& targetTime) const
{
    using mp_units::angular::unit_symbols::deg;
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
void Keplerian<_frame_>::wrap_angles()
{
    get_inclination()         = wrap_angle(get_inclination());
    get_right_ascension()     = wrap_angle(get_right_ascension());
    get_argument_of_perigee() = wrap_angle(get_argument_of_perigee());
    get_true_anomaly()        = wrap_angle(get_true_anomaly());
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
    os << elements.template get<0>() << ", ";
    os << elements.template get<1>() << ", ";
    os << elements.template get<2>() << ", ";
    os << elements.template get<3>() << ", ";
    os << elements.template get<4>() << ", ";
    os << elements.template get<5>();
    os << "] (KeplerianPartial)";
    return os;
}

template <IsFrame auto _frame_>
template <IsFrame auto target_frame>
Keplerian<target_frame> Keplerian<_frame_>::in_frame(const Date& epoch, const GravParam& mu) const
{
    return Keplerian<target_frame>(Cartesian<_frame_>(*this, mu).template in_frame<target_frame>(epoch), mu);
}

} // namespace astro
} // namespace astrea