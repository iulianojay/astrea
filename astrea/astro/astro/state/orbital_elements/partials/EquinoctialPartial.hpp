/**
 * @file EquinoctialPartial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the EquinoctialPartial class and its associated methods.
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

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/Equinoctial.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a partial derivative of an Equinoctial state vector.
 *
 */
template <IsFrame auto _frame_>
class EquinoctialPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, EquinoctialPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Cartesian state vector.

    /**
     * @brief Default constructor for EquinoctialPartial.
     *
     * Initializes the EquinoctialPartial with zero values.
     */
    EquinoctialPartial() = default;

    /**
     * @brief Constructor for EquinoctialPartial with velocity and acceleration components.
     *
     * @param semilatusPartial Semilatus rectum partial derivative
     * @param fPartial First component of the eccentricity vector partial derivative
     * @param gPartial Second component of the eccentricity vector partial derivative
     * @param hPartial First component of the planar vector partial derivative
     * @param kPartial Second component of the planar vector partial derivative
     * @param trueLongitudePartial True longitude partial derivative
     */
    EquinoctialPartial(
        const Velocity& semilatusPartial,
        const UnitlessPerTime& fPartial,
        const UnitlessPerTime& gPartial,
        const UnitlessPerTime& hPartial,
        const UnitlessPerTime& kPartial,
        const AngularVelocity& trueLongitudePartial
    ) :
        _semilatusPartial(semilatusPartial),
        _fPartial(fPartial),
        _gPartial(gPartial),
        _hPartial(hPartial),
        _kPartial(kPartial),
        _trueLongitudePartial(trueLongitudePartial)
    {
    }

    /**
     * @brief Multiplication operator for EquinoctialPartial.
     *
     * @param time Time to multiply the EquinoctialPartial by
     * @return Equinoctial Resulting Equinoctial state vector after multiplication.
     */
    Equinoctial<_frame_> operator*(const Time& time) const;

    /**
     * @brief Converts the EquinoctialPartial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the components of the EquinoctialPartial state vector.
     */
    std::vector<double> force_to_double_vector() const;

  private:
    Velocity _semilatusPartial;            //!< Semilatus rectum partial derivative
    UnitlessPerTime _fPartial;             //!< First component of the eccentricity vector partial derivative
    UnitlessPerTime _gPartial;             //!< Second component of the eccentricity vector partial derivative
    UnitlessPerTime _hPartial;             //!< First component of the planar vector partial derivative
    UnitlessPerTime _kPartial;             //!< Second component of the planar vector partial derivative
    AngularVelocity _trueLongitudePartial; //!< True longitude partial derivative
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/partials/EquinoctialPartial.ipp>