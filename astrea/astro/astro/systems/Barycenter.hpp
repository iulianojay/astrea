/**
 * @file Barycenter.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Barycenter class, which represents a barycenter in an astrodynamics system.
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

#include <mp-units/framework/symbol_text.h>

#include <units/units.hpp>

#include <astro/frames/Axis.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/Origin.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct BarycenterBase {};

} // namespace detail

/**
 * @brief Type-list used to attach member bodies to a Barycenter.
 *
 * Types in the list may be incomplete (forward-declared) at the point where the
 * Barycenter is instantiated, which avoids circular inclusion between Barycenter.hpp
 * and the individual planet headers.  Because CelestialBodyTypePack<> has no data members it is a
 * structural type and can therefore be passed as a non-type template parameter.
 */
template <typename...>
struct CelestialBodyTypePack {};

template <mp_units::symbol_text, auto...>
struct Barycenter;

/// No parent, no members.
template <mp_units::symbol_text _name_>
struct Barycenter<_name_> : Origin<_name_>, detail::BarycenterBase {};

/// With parent, no members.
template <mp_units::symbol_text _name_, IsOrigin auto _parent_>
struct Barycenter<_name_, _parent_> : Origin<_name_, _parent_>, detail::BarycenterBase {};

} // namespace astro
} // namespace astrea
