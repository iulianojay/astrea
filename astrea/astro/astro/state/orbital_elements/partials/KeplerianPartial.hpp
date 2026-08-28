/**
 * @file KeplerianPartial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the KeplerianPartial class and its associated methods.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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
#include <mp-units/systems/si.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/Keplerian.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a partial derivative of a Keplerian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Keplerian coordinates.
 * It is used to represent the rate of change of the Keplerian elements with respect to time.
 *
 * @note The KeplerianPartial class is typically used in astrodynamics calculations involving orbital mechanics.
 */
template <IsFrame auto _frame_>
class KeplerianPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, KeplerianPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Keplerian partial derivatives.

    /**
     * @brief Default constructor for KeplerianPartial.
     *
     * Initializes the KeplerianPartial with zero values.
     */
    KeplerianPartial() = default;

    /**
     * @brief Constructor for KeplerianPartial with velocity and acceleration components.
     *
     * @param semimajorPartial Semimajor axis partial derivative
     * @param eccentricityPartial Eccentricity partial derivative
     * @param inclinationPartial Inclination partial derivative
     * @param rightAscensionPartial Right ascension partial derivative
     * @param argPerigeePartial Argument of perigee partial derivative
     * @param trueAnomalyPartial True anomaly partial derivative
     */
    KeplerianPartial(
        const Velocity& semimajorPartial,
        const UnitlessPerTime& eccentricityPartial,
        const AngularVelocity& inclinationPartial,
        const AngularVelocity& rightAscensionPartial,
        const AngularVelocity& argPerigeePartial,
        const AngularVelocity& trueAnomalyPartial
    ) :
        _semimajorPartial(semimajorPartial),
        _eccentricityPartial(eccentricityPartial),
        _inclinationPartial(inclinationPartial),
        _rightAscensionPartial(rightAscensionPartial),
        _argPerigeePartial(argPerigeePartial),
        _trueAnomalyPartial(trueAnomalyPartial)
    {
    }

    /**
     * @brief Multiplication operator for KeplerianPartial.
     *
     * This method multiplies the KeplerianPartial by a time value to obtain a Keplerian state vector.
     *
     * @param time Time to multiply the KeplerianPartial by
     * @return Keplerian Resulting Keplerian state vector after multiplication.
     */
    Keplerian<_frame_> operator*(const Time& time) const;

    /**
     * @brief Converts the KeplerianPartial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the components of the KeplerianPartial state vector.
     */
    std::vector<double> force_to_double_vector() const;

  private:
    Velocity _semimajorPartial;             //!< Semimajor axis partial derivative
    UnitlessPerTime _eccentricityPartial;   //!< Eccentricity partial derivative
    AngularVelocity _inclinationPartial;    //!< Inclination partial derivative
    AngularVelocity _rightAscensionPartial; //!< Right ascension partial derivative
    AngularVelocity _argPerigeePartial;     //!< Argument of perigee partial derivative
    AngularVelocity _trueAnomalyPartial;    //!< True anomaly partial derivative
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/partials/KeplerianPartial.ipp>