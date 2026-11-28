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

#include <iostream>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/framework/OrbitalElementsInterface.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {


/**
 * @brief Class representing a partial derivative of an Equinoctial state vector.
 *
 */
template <IsFrame auto _frame_>
class EquinoctialPartial
    : public OrbitalElementsInterface<EquinoctialPartial<_frame_>, Velocity, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, AngularVelocity> {

    using BaseType =
        OrbitalElementsInterface<EquinoctialPartial<_frame_>, Velocity, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, UnitlessPerTime, AngularVelocity>;

    friend std::ostream& operator<<(std::ostream& os, EquinoctialPartial const& elements)
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

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the EquinoctialPartial state vector.
    using BaseType::BaseType;

    /**
     * @brief Default constructor for EquinoctialPartial.
     *
     * Initializes the EquinoctialPartial with zero values.
     */
    EquinoctialPartial() = default;
};

} // namespace astro
} // namespace astrea