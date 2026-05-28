/**
 * @file frame_registry_fwd.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Forward declaration of ExtraRegisteredFrames, for use before specializing it.
 * @date 2025-04-22
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

#include <tuple>

namespace astrea {
namespace astro {

/**
 * @brief Trait that users specialize to register additional Cartesian frames.
 *
 * Include this header, provide a specialization, then include frame_registry.hpp.
 * The frame types used in the specialization must already be declared before this point.
 *
 * @code
 * #include <astro/frames/definitions/body_centered_inertial_frames.hpp>
 * #include <astro/frames/framework/frame_registry.fwd.hpp>
 *
 * namespace astrea::astro {
 *   template <>
 *   struct ExtraRegisteredFrames<> {
 *       using type = std::tuple<std::decay_t<decltype(frames::moon::icrf)>,
 *                               std::decay_t<decltype(frames::mars::icrf)>>;
 *   };
 * }
 *
 * #include <astro/frames/framework/frame_registry.hpp>
 * // ... all other astrea headers
 * @endcode
 *
 * The primary template (empty list) is the default — do not modify it.
 */
template <typename = void>
struct ExtraRegisteredFrames {
    using type = std::tuple<>;
};

} // namespace astro
} // namespace astrea
