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

#include <iosfwd>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a partial derivative of a Cartesian state vector.
 *
 * This class encapsulates the velocity and acceleration components of a vehicle in Cartesian coordinates.
 */
template <IsFrame auto _frame_>
class CartesianPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, CartesianPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Cartesian state vector.

    /**
     * @brief Default constructor for CartesianPartial.
     */
    CartesianPartial() = default;

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration components.
     *
     * @param vx X component of velocity
     * @param vy Y component of velocity
     * @param vz Z component of velocity
     * @param ax X component of acceleration
     * @param ay Y component of acceleration
     * @param az Z component of acceleration
     */
    CartesianPartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _v(vx, vy, vz),
        _a(ax, ay, az)
    {
    }

    /**
     * @brief Constructor for CartesianPartial with velocity and acceleration vectors.
     *
     * @param v Velocity vector
     * @param a Acceleration vector
     */
    CartesianPartial(const VelocityVector<_frame_>& v, const AccelerationVector<_frame_>& a) :
        _v(v),
        _a(a)
    {
    }

    /**
     * @brief Get the vx value of the CartesianPartial state vector.
     *
     * @return Velocity The vx component of the CartesianPartial state vector.
     */
    Velocity get_vx() const { return _v.get_x(); }

    /**
     * @brief Get the vy value of the CartesianPartial state vector.
     *
     * @return Velocity The vy component of the CartesianPartial state vector.
     */
    Velocity get_vy() const { return _v.get_y(); }

    /**
     * @brief Get the vz value of the CartesianPartial state vector.
     *
     * @return Velocity The vz component of the CartesianPartial state vector.
     */
    Velocity get_vz() const { return _v.get_z(); }

    /**
     * @brief Get the ax value of the CartesianPartial state vector.
     *
     * @return Acceleration The ax component of the CartesianPartial state vector.
     */
    Acceleration get_ax() const { return _a.get_x(); }

    /**
     * @brief Get the ay value of the CartesianPartial state vector.
     *
     * @return Acceleration The ay component of the CartesianPartial state vector.
     */
    Acceleration get_ay() const { return _a.get_y(); }

    /**
     * @brief Get the az value of the CartesianPartial state vector.
     *
     * @return Acceleration The az component of the CartesianPartial state vector.
     */
    Acceleration get_az() const { return _a.get_z(); }

    /**
     * @brief Multiplication operator for CartesianPartial.
     *
     * @param time Time to multiply the CartesianPartial by
     * @return Cartesian Resulting Cartesian state vector after multiplication.
     */
    Cartesian<_frame_> operator*(const Time& time) const;

    /**
     * @brief Converts the CartesianPartial state vector to a vector of unitless values.
     *
     * @return std::vector<Unitless> Vector containing the components of the CartesianPartial state vector.
     */
    std::vector<double> force_to_double_vector() const;

  private:
    VelocityVector<_frame_> _v;     //!< Velocity vector
    AccelerationVector<_frame_> _a; //!< Acceleration vector
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/partials/CartesianPartial.ipp>