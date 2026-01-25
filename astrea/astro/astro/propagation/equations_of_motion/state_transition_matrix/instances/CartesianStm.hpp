/**
 * @file CartesianStm.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the CartesianStm class.
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

#include <array>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {

class CartesianStm {

    using VelPosPartial   = decltype(Velocity{} / Distance{});
    using VelVelPartial   = decltype(Velocity{} / Velocity{});
    using AccelPosPartial = decltype(Acceleration{} / Distance{});
    using AccelVelPartial = decltype(Acceleration{} / Velocity{});

  public:
    /**
     * @brief Default constructor for CartesianStm.
     */
    CartesianStm() = default;

    /**
     * @brief Constructor for CartesianStm. Uses the provided equations of motion
     *  and state to initialize the STM numerically.
     *
     * @param eom Equations of motion object
     * @param state Current Cartesian state vector
     */
    CartesianStm(const EquationsOfMotion& eom, const Cartesian& state);

    /**
     * @brief Set the STM element at (ii, jj) for ii and jj < 3 to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii < 3 && jj < 3)
    void set(const VelPosPartial& value)
    {
        _dvdr[ii][jj] = value;
    }

    /**
     * @brief Set the STM element at (ii, jj) for ii < 3 and jj >= 3 to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii < 3 && jj >= 3)
    void set(const VelVelPartial& value)
    {
        _dvdv[ii][jj - 3] = value;
    }

    /**
     * @brief Set the STM element at (ii, jj) for ii >= 3 and jj < 3 to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii >= 3 && jj < 3)
    void set(const AccelPosPartial& value)
    {
        _dadr[ii - 3][jj] = value;
    }

    /**
     * @brief Set the STM element at (ii, jj) for ii >= 3 and jj >= 3 to the provided value.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @param value Value to set
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii >= 3 && jj >= 3)
    void set(const AccelVelPartial& value)
    {
        _dadv[ii - 3][jj - 3] = value;
    }

    /**
     * @brief Get the STM element at (ii, jj) for ii and jj < 3.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return VelPosPartial STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii < 3 && jj < 3)
    const VelPosPartial& get() const
    {
        return _dvdr[ii][jj];
    }

    /**
     * @brief Get the STM element at (ii, jj) for ii < 3 and jj >= 3.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return VelVelPartial STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii < 3 && jj >= 3)
    const VelVelPartial& get() const
    {
        return _dvdv[ii][jj - 3];
    }

    /**
     * @brief Get the STM element at (ii, jj) for ii >= 3 and jj < 3.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return AccelPosPartial STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii >= 3 && jj < 3)
    const AccelPosPartial& get() const
    {
        return _dadr[ii - 3][jj];
    }

    /**
     * @brief Get the STM element at (ii, jj) for ii >= 3 and jj >= 3.
     *
     * @tparam ii Row index
     * @tparam jj Column index
     * @return AccelVelPartial STM element at (ii, jj)
     */
    template <std::size_t ii, std::size_t jj>
        requires(ii >= 3 && jj >= 3)
    const AccelVelPartial& get() const
    {
        return _dadv[ii - 3][jj - 3];
    }

    /**
     * @brief Converts the STM to a vector of Unitless values in row-major order.
     *
     * @return std::vector<Unitless> Vector representation of the STM.
     */
    std::vector<Unitless> force_to_vector() const;

    /**
     * @brief Default destructor for CartesianStm.
     */
    ~CartesianStm() = default;

  private:
    /*
      STM = | dvx/dx  dvx/dy  dvx/dz  dvx/dvx  dvx/dvy  dvx/dvz |
            | dvy/dx  dvy/dy  dvy/dz  dvy/dvy  dvy/dvy  dvy/dvz |
            | dvz/dx  dvz/dy  dvz/dz  dvz/dvz  dvz/dvz  dvz/dvz |
            | dax/dx  dax/dy  dax/dz  dax/dvx  dax/dvy  dax/dvz |
            | day/dx  day/dy  day/dz  day/dvx  day/dvy  day/dvz |
            | daz/dx  daz/dy  daz/dz  daz/dvx  daz/dvy  daz/dvz |

          = |   0       0       0        1        0        0    |
            |   0       0       0        0        1        0    |
            |   0       0       0        0        0        1    |
            | dax/dx  dax/dy  dax/dz  dax/dvx  dax/dvy  dax/dvz |
            | day/dx  day/dy  day/dz  day/dvx  day/dvy  day/dvz |
            | daz/dx  daz/dy  daz/dz  daz/dvx  daz/dvy  daz/dvz |
    */

    std::array<std::array<VelPosPartial, 3>, 3> _dvdr{}; // Always zero
    std::array<std::array<VelVelPartial, 3>, 3> _dvdv = { { { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } } };
    std::array<std::array<AccelPosPartial, 3>, 3> _dadr{};
    std::array<std::array<AccelVelPartial, 3>, 3> _dadv{}; // Usually zero but perturbations may depend on velocity
};

} // namespace astro
} // namespace astrea
