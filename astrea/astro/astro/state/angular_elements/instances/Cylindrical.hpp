/**
 * @file Cylindrical.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the Cylindrical class and its associated methods.
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
 * @brief Class representing a Cylindrical state vector in astrodynamics.
 *
 * This class encapsulates the position and velocity of a vehicle in Cylindrical coordinates.
 *
 * @tparam _body_ The celestial body NTTP that defines the reference frames.
 */
template <IsCelestialBody auto _body_>
class Cylindrical {

    template <IsCelestialBody auto body>
    friend std::ostream& operator<<(std::ostream&, Cylindrical<body> const&);

  public:
    static constexpr auto body          = _body_; //!< The celestial body of this Cylindrical state.
    static constexpr auto _icrf_frame_  = make_frame(_body_, axes::icrf); //!< Inertial frame for the body.
    static constexpr auto _fixed_frame_ = get_body_fixed_frame<_body_>(); //!< Body-fixed rotating frame.

    /**
     * @brief Default constructor for Cylindrical.
     *
     * Initializes the Cylindrical state vector with zero values.
     */
    Cylindrical(Unitless scale = 0.0 * astrea::detail::unitless) :
        _range(scale * astrea::detail::distance_unit),
        _azimuth(scale * astrea::detail::angle_unit),
        _elevation(scale * astrea::detail::distance_unit)
    {
    }

    /**
     * @brief Constructor for Cylindrical with range, azimuth, and elevation.
     *
     * @param range Range
     * @param azimuth Cylindrical azimuth
     * @param elevation Elevation
     */
    Cylindrical(const Distance& range, const Angle& azimuth, const Distance& elevation) :
        _range(range),
        _azimuth(azimuth),
        _elevation(elevation)
    {
    }

    /**
     * @brief Constructor for Cylindrical from any inertial radius vector centred on the same body.
     *
     * Accepts any frame whose origin matches _body_ and whose axis is the ICRF axis.
     *
     * @tparam _frame_ The inertial frame of the radius vector.
     * @param r Radius vector in an ICRF-axis frame centred on the body.
     * @param date Date for the frame transformation.
     */
    template <auto _frame_>
        requires(equivalent(_frame_, make_frame(_body_, axes::icrf)))
    Cylindrical(const RadiusVector<_frame_>& r, const Date& date);

    /**
     * @brief Constructor for Cylindrical from a body-fixed radius vector.
     *
     * @param r Radius vector in the body-fixed frame
     */
    Cylindrical(const RadiusVector<_fixed_frame_>& r);

    /**
     * @brief Constructor for Cylindrical from orbital elements.
     *
     * @param elements Orbital elements
     * @param date Date for the frame transformation
     */
    template <IsOrbitalElements T>
    Cylindrical(const T& elements, const Date& date)
    {
        static const GravParam mu = get_mu<_body_>();
        *this = Cylindrical<_body_>(Cartesian<T::frame>(elements, mu).get_position().template in_frame<_fixed_frame_>(date));
    }

    /**
     * @brief Copy constructor for Cylindrical.
     */
    Cylindrical(const Cylindrical<_body_>&);

    /**
     * @brief Move constructor for Cylindrical.
     */
    Cylindrical(Cylindrical<_body_>&&) noexcept;

    /**
     * @brief Move assignment operator for Cylindrical.
     */
    Cylindrical<_body_>& operator=(Cylindrical<_body_>&&) noexcept;

    /**
     * @brief Copy assignment operator for Cylindrical.
     */
    Cylindrical<_body_>& operator=(const Cylindrical<_body_>&);

    /**
     * @brief Default destructor for Cylindrical.
     */
    ~Cylindrical() = default;

    bool operator==(const Cylindrical<_body_>& other) const;
    bool operator!=(const Cylindrical<_body_>& other) const;

    Cylindrical<_body_> operator+(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_>& operator+=(const Cylindrical<_body_>& other);
    Cylindrical<_body_> operator-(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_>& operator-=(const Cylindrical<_body_>& other);
    Cylindrical<_body_> operator*(const Unitless& multiplier) const;
    Cylindrical<_body_>& operator*=(const Unitless& multiplier);
    std::vector<Unitless> operator/(const Cylindrical<_body_>& other) const;
    Cylindrical<_body_> operator/(const Unitless& divisor) const;
    Cylindrical<_body_>& operator/=(const Unitless& divisor);

    /**
     * @brief Converts the Cylindrical state to a body-fixed radius vector.
     */
    RadiusVector<_fixed_frame_> get_position() const;

    /**
     * @brief Converts the Cylindrical state to an inertial radius vector.
     *
     * @param date Date for the frame transformation
     */
    RadiusVector<_icrf_frame_> get_position(const Date& date) const;

    const Angle& get_azimuth() const { return _azimuth; }
    const Distance& get_elevation() const { return _elevation; }
    const Distance& get_range() const { return _range; }

    Cylindrical<_body_>
        interpolate(const Time& thisTime, const Time& otherTime, const Cylindrical<_body_>& other, const Time& targetTime) const;

  private:
    Distance _range;     //!< Range
    Angle _azimuth;      //!< Azimuth
    Distance _elevation; //!< Elevation
};


/**
 * @brief Convert a body-fixed radius vector to cylindrical coordinates.
 *
 * @param rFixed The radius vector in the body-fixed frame.
 * @return The range, azimuth, and elevation as a tuple.
 */
template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
std::tuple<Distance, Angle, Distance> convert_body_fixed_to_cylindrical(const RadiusVector<_frame_>& rFixed)
{
    using mp_units::si::unit_symbols::km;
    const Distance range     = rFixed.norm();
    const Distance elevation = rFixed.get_z();
    Angle azimuth = acos(rFixed.get_x() / sqrt(rFixed.get_x() * rFixed.get_x() + rFixed.get_y() * rFixed.get_y()));
    if (rFixed.get_y() < 0.0 * km) { azimuth = -azimuth; }
    return { range, azimuth, elevation };
}


/**
 * @brief Convert cylindrical coordinates to a body-fixed radius vector.
 *
 * @param range The range.
 * @param azimuth The azimuth in radians.
 * @param elevation The elevation.
 * @return The radius vector in the body-fixed frame.
 */
template <IsFrame auto _frame_>
    requires(IsBodyFixedFrame<decltype(_frame_)>)
RadiusVector<_frame_> convert_cylindrical_to_body_fixed(const Distance& range, const Angle& azimuth, const Distance& elevation)
{
    return RadiusVector<_frame_>(range * cos(azimuth), range * sin(azimuth), elevation);
}

} // namespace astro
} // namespace astrea


#include <astro/state/angular_elements/instances/Cylindrical.ipp>
