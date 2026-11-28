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

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/framework/OrbitalElementsInterface.hpp>
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
class KeplerianPartial
    : public OrbitalElementsInterface<KeplerianPartial<_frame_>, Velocity, UnitlessPerTime, AngularVelocity, AngularVelocity, AngularVelocity, AngularVelocity> {

    using BaseType =
        OrbitalElementsInterface<KeplerianPartial<_frame_>, Velocity, UnitlessPerTime, AngularVelocity, AngularVelocity, AngularVelocity, AngularVelocity>;

    friend std::ostream& operator<<(std::ostream& os, KeplerianPartial const& elements)
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

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the KeplerianPartial state vector.
    using BaseType::BaseType;

    /**
     * @brief Default constructor for KeplerianPartial.
     *
     * Initializes the KeplerianPartial with zero values.
     */
    KeplerianPartial() = default;
};

} // namespace astro
} // namespace astrea