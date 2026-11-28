/**
 * @file CartesianPartial.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the CartesianPartial class and its associated methods.
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
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/state/framework/OrbitalElementsInterface.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a partial derivative of a Cartesian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class CartesianPartial
    : public OrbitalElementsInterface<CartesianPartial<_frame_>, Velocity, Velocity, Velocity, Acceleration, Acceleration, Acceleration> {

    using BaseType =
        OrbitalElementsInterface<CartesianPartial<_frame_>, Velocity, Velocity, Velocity, Acceleration, Acceleration, Acceleration>;

    friend std::ostream& operator<<(std::ostream& os, CartesianPartial const& elements)
    {
        os << "[";
        os << elements.get_vx() << ", ";
        os << elements.get_vy() << ", ";
        os << elements.get_vz() << ", ";
        os << elements.get_ax() << ", ";
        os << elements.get_ay() << ", ";
        os << elements.get_az();
        os << "] (CartesianPartial)";
        return os;
    }

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the CartesianPartial state vector.
    using BaseType::BaseType;

    /**
     * @brief Default constructor for CartesianPartial.
     */
    CartesianPartial() = default;

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration vectors.
     *
     * @param v Velocity vector
     * @param a Acceleration vector
     */
    CartesianPartial(const VelocityVector<_frame_>& v, const AccelerationVector<_frame_>& a) :
        BaseType(v[0], v[1], v[2], a[0], a[1], a[2])
    {
    }

    /**
     * @brief Get the vx value of the CartesianPartial state vector.
     *
     * @return Velocity The vx component of the CartesianPartial state vector.
     */
    Velocity get_vx() const { return this->template get<0>(); }

    /**
     * @brief Get the vy value of the CartesianPartial state vector.
     *
     * @return Velocity The vy component of the CartesianPartial state vector.
     */
    Velocity get_vy() const { return this->template get<1>(); }

    /**
     * @brief Get the vz value of the CartesianPartial state vector.
     *
     * @return Velocity The vz component of the CartesianPartial state vector.
     */
    Velocity get_vz() const { return this->template get<2>(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    const Acceleration& get_ax() const { return this->template get<3>(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    const Acceleration& get_ay() const { return this->template get<4>(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    const Acceleration& get_az() const { return this->template get<5>(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    Acceleration& get_ax() { return this->template get<3>(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    Acceleration& get_ay() { return this->template get<4>(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    Acceleration& get_az() { return this->template get<5>(); }
};

} // namespace astro
} // namespace astrea