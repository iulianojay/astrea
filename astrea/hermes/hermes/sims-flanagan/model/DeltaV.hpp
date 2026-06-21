/**
 * @file DeltaV.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the DeltaV module
 * @date 2026-04-24
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
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

#include <astro/astro.hpp>
#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

namespace astrea {
namespace hermes {

/**
 * @brief A class representing an impulsive burn
 */
class DeltaV {
  public:
    /**
     * @brief Default constructor for the DeltaV class
     */
    DeltaV() = default;

    /**
     * @brief Construct a new DeltaV object
     *
     * @param deltaV The change in velocity vector in the primary frame of reference
     */
    DeltaV(const astro::VelocityVector<astro::frames::primary>& deltaV);

    /**
     * @brief Default destructor for the DeltaV class
     */
    ~DeltaV() = default;

    /**
     * @brief Get the unique identifier for this DeltaV instance
     *
     * @return std::size_t The unique identifier for this DeltaV instance
     */
    std::size_t get_id() const;

    /**
     * @brief Get the change in velocity vector for this DeltaV instance
     *
     * @return const astro::VelocityVector<astro::frames::primary>& The change in velocity vector for this DeltaV instance
     */
    const astro::VelocityVector<astro::frames::primary>& get_delta_v() const;

  private:
    std::size_t _id;                                   //!< Unique identifier for this DeltaV instance
    astro::VelocityVector<astro::frames::primary> _dv; //!< The change in velocity vector for this DeltaV instance
};

} // namespace hermes
} // namespace astrea