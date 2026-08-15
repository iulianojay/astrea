/**
 * @file hash.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Hash functions for astrea units
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

#include <functional>

#include <units/typedefs.hpp>

template <auto R, typename Rep>
struct std::hash<mp_units::quantity<R, Rep>> {
    std::size_t operator()(const mp_units::quantity<R, Rep>& q) const
    {
        return (std::hash<Rep>()(q.numerical_value_ref_in(q.unit)));
    }
};
