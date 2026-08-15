/**
 * @file IdProvider.hpp
 * @author your name (you@domain.com)
 * @brief ID provider utility functions for generating and managing unique IDs.
 * @date 2025-10-09
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

#include <atomic>

#include <mp-units/framework/symbol_text.h>

namespace astrea {
namespace utilities {

class IdProvider {
  public:
    /**
     * @brief Deleted constructor to prevent instantiation of IdProvider.
     */
    IdProvider() = delete;

    /**
     * @brief Get the next unique ID.
     *
     * @tparam name A string literal representing the type of ID being generated (e.g., "Spacecraft", "Plane", etc.).
     * @return std::size_t The next unique ID.
     */
    template <mp_units::symbol_text name>
    static std::size_t get_next_id()
    {
        static std::atomic<std::size_t> _idCounter{ 0 };
        return _idCounter++;
    }
};

} // namespace utilities
} // namespace astrea
