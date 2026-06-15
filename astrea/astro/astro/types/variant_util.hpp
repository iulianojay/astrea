/**
 * @file variant_util.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Utility functions for working with std::variant
 * @date 2025-10-09
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

#include <variant>

namespace astrea {
namespace astro {


template <typename VariantType, typename T, std::size_t index = 0>
constexpr std::size_t get_variant_index()
{
    static_assert(std::variant_size_v<VariantType> > index, "Type not found in variant");
    if constexpr (index == std::variant_size_v<VariantType>) { return index; }
    else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return index;
    }
    else {
        return get_variant_index<VariantType, T, index + 1>();
    }
}

/**
 * @brief Checks whether type T is one of the alternatives in VariantType.
 */
template <typename VariantType, typename T, std::size_t index = 0>
constexpr bool variant_contains()
{
    if constexpr (index == std::variant_size_v<VariantType>) { return false; }
    else if constexpr (std::is_same_v<std::variant_alternative_t<index, VariantType>, T>) {
        return true;
    }
    else {
        return variant_contains<VariantType, T, index + 1>();
    }
}


} // namespace astro
} // namespace astrea