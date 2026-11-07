/**
 * @file CartesianStm.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the CartesianStm class and its associated methods.
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

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
class CartesianStm {
  public:
    static constexpr auto frame = _frame_; //!< The reference frame of the Cartesian STM.

    /**
     * @brief Default constructor for CartesianStm.
     */
    CartesianStm() = default;

    /**
     * @brief Default destructor for CartesianStm.
     */
    ~CartesianStm() = default;

  private:
    /**
     * f(s) = [f0(s), f1(s), ..., fn(s)] where fi is the ith component of the equations of motion
     *
     * df/ds = |df0/ds0, df0/ds1, ..., df0/dsn| where dfi/ds is the partial derivative of the ith component with respect to the state vector
     *         |df1/ds0, df1/ds1, ..., df1/dsn|
     *         | ...                          |
     *         |dfn/ds0, dfn/ds1, ..., dfn/dsn|
     *
     * Cartesian:
     * df/ds = |dVx/dX, dVx/dY, dVx/dZ, dVx/dVx, dVx/dVy, dVx/dVz| = |dv/dr, dv/dv|
     *         |dVy/dX, dVy/dY, dVy/dZ, dVy/dVx, dVy/dVy, dVy/dVz|   |da/dr, da/dv|
     *         |dVz/dX, dVz/dY, dVz/dZ, dVz/dVx, dVz/dVy, dVz/dVz|
     *         |dAX/dX, dAX/dY, dAX/dZ, dAX/dVx, dAX/dVy, dAX/dVz|
     *         |dAY/dX, dAY/dY, dAY/dZ, dAY/dVx, dAY/dVy, dAY/dVz|
     *         |dAZ/dX, dAZ/dY, dAZ/dZ, dAZ/dVx, dAZ/dVy, dAZ/dVz|
     */
    std::array<quantity<one / s>, 9> _dvdr; //!< Partial derivatives of the velocity with respect to position
    std::array<quantity<one>, 9> _dvdv;     //!< Partial derivatives of the velocity with respect to velocity
    std::array<quantity<km / s>, 9> _dadr;  //!< Partial derivatives of the acceleration with respect to position
    std::array<quantity<one / s>, 9> _dadv; //!< Partial derivatives of the acceleration with respect to velocity
};

} // namespace astro
} // namespace astrea