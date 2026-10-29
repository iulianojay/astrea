/**
 * @file StateSpec.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the StateSpec class and its associated methods.
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

#include <atomic>

namespace astrea {
namespace astro {

consteval unsigned assign_id()
{
    static std::atomic<unsigned> counter{ 0 };
    return ++counter;
}

template <typename OrbitalElements_T, typename Attitude_T = void, typename UserDefinedElements_T = void>
struct StateSpec {
    using OrbitalElements     = OrbitalElements_T;
    using Attitude            = Attitude_T;
    using UserDefinedElements = UserDefinedElements_T;

    static constexpr unsigned id = assign_id();
    static constexpr auto frame  = OrbitalElements::frame;

    // ... validate input types ... //

    consteval std::size_t orbital_elements_size() const { return OrbitalElements::size(); }
    consteval std::size_t attitude_size() const { return std::is_same_v<Attitude, void> ? 0 : Attitude::size(); }
    consteval std::size_t user_defined_elements_size() const
    {
        return std::is_same_v<UserDefinedElements, void> ? 0 : UserDefinedElements::size();
    }
    consteval std::size_t size() const
    {
        return orbital_elements_size() + attitude_size() + user_defined_elements_size();
    }
    consteval bool has_attitude() const { return !std::is_same_v<Attitude, void>; }
    consteval bool has_user_defined_elements() const { return !std::is_same_v<UserDefinedElements, void>; }
};

} // namespace astro
} // namespace astrea