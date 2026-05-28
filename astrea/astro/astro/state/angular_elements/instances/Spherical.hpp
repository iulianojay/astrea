/**
 * @file Spherical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Spherical class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <iosfwd>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

// units
#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/system_concepts.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a Spherical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Spherical coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference frames.
 */
template <IsCelestialBody auto _body_>
class Spherical {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Spherical<body> const&);

  public:
    static constexpr auto body          = _body_; //!< The celestial body of this Spherical state.
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); //!< Inertial frame for the body.
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); //!< Body-fixed rotating frame.

    /**
     * @brief Default constructor for Spherical.
     *
     * Initializes the Spherical state vector with zero values.
     */
    Spherical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _inclination(scale * astrea::detail::angle_unit),
        _azimuth(scale * astrea::detail::angle_unit)
    {
    }

    /**
     * @brief Constructor for Spherical with range, inclination, and azimuth.
     *
     * @param range Range
     * @param inclination Inclination
     * @param azimuth Azimuth
     */
    Spherical(const Distance& range, const Angle& inclination, const Angle& azimuth) :
        _range(range),
        _inclination(inclination),
        _azimuth(azimuth)
    {
    }

    /**
     * @brief Constructor for Spherical from any inertial radius vector centred on the same body.
     *
     * Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis.
     *
     * @tparam _frame_ The inertial frame of the radius vector.
     * @param r Radius vector in an ICRF-axis frame centred on the body.
     * @param date Date for the frame transformation.
     */
    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Spherical(const RadiusVector<_frame_>& r, const Date& date);

    /**
     * @brief Constructor for Spherical from a body-fixed radius vector.
     *
     * @param r Radius vector in the body-fixed frame
     */
    Spherical(const RadiusVector<_fixed_frame_>& r);

    /**
     * @brief Constructor for Spherical from orbital elements.
     *
     * @param elements Orbital elements
     * @param date Date for the frame transformation
     */
    template <IsOrbitalElements T>
    Spherical(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Spherical<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    /**
     * @brief Copy constructor for Spherical.
     */
    Spherical(const Spherical<_body_>&);

    /**
     * @brief Move constructor for Spherical.
     */
    Spherical(Spherical<_body_>&&) noexcept;

    /**
     * @brief Move assignment operator for Spherical.
     */
    Spherical<_body_>& operator=(Spherical<_body_>&&) noexcept;

    /**
     * @brief Copy assignment operator for Spherical.
     */
    Spherical<_body_>& operator=(const Spherical<_body_>&);

    /**
     * @brief Default destructor for Spherical.
     */
    ~Spherical() = default;

    bool operator==(const Spherical<_body_>& other) const;
    bool operator!=(const Spherical<_body_>& other) const;

    Spherical<_body_> operator+(const Spherical<_body_>& other) const;
    Spherical<_body_>& operator+=(const Spherical<_body_>& other);
    Spherical<_body_> operator-(const Spherical<_body_>& other) const;
    Spherical<_body_>& operator-=(const Spherical<_body_>& other);
    Spherical<_body_> operator*(const Unitless& multiplier) const;
    Spherical<_body_>& operator*=(const Unitless& multiplier);
    std::vector<Unitless> operator/(const Spherical<_body_>& other) const;
    Spherical<_body_> operator/(const Unitless& divisor) const;
    Spherical<_body_>& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Spherical state to a body-fixed radius vector.
     */
    RadiusVector<_fixed_frame_> get_position() const;

    /**
     * @brief Converts the Spherical state to an inertial radius vector.
     *
     * @param date Date for the frame transformation
     */
    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_azimuth() const { return _azimuth; }
    const Angle& get_inclination() const { return _inclination; }
    const Distance& get_range() const { return _range; }

    Spherical<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Spherical<_body_>& other, const Time& targetTime) const;

  private:
    Distance _range;    //!< Range
    Angle _inclination; //!< Inclination
    Angle _azimuth;     //!< Azimuth
};


/**
 * @brief Convert a body-fixed radius vector to spherical coordinates.
 *
 * @param rFixed The radius vector in the body-fixed frame.
 * @return The range, inclination, and azimuth as a tuple.
 */
template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
std::tuple<Distance, Angle, Angle> convert_body_fixed_to_spherical(const RadiusVector<_frame_>& rFixed)
{
    using mp_units::angular::unit_symbols::rad;
    using mp_units::si::unit_symbols::km;
    const Distance range    = rFixed.norm();
    const Angle inclination = acos(rFixed.get_z() / range);

    const Distance& x = rFixed.get_x();
    const Distance& y = rFixed.get_y();

    Angle azimuth;
    if (x == 0.0 * km && y == 0.0 * km) { azimuth = 0.0 * rad; }
    else {
        azimuth = acos(x / sqrt(x * x + y * y));
        if (y < 0.0 * km) { azimuth = -azimuth; }
    }
    return std::make_tuple(range, inclination, azimuth);
}


/**
 * @brief Convert spherical coordinates to a body-fixed radius vector.
 *
 * @param range The range.
 * @param inclination The inclination in radians.
 * @param azimuth The azimuth in radians.
 * @return The radius vector in the body-fixed frame.
 */
template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
RadiusVector<_frame_> convert_spherical_to_body_fixed(const Distance& range, const Angle& inclination, const Angle& azimuth)
{
    return RadiusVector<_frame_>(range * sin(inclination) * cos(azimuth), range * sin(inclination) * sin(azimuth), range * cos(inclination));
}

} // namespace astro
} // namespace astrea

#include <astro/state/angular_elements/instances/Spherical.ipp>
