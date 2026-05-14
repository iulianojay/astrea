/**
 * @file frame_registry.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Registration point for Cartesian frames used across astrea.
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
#include <variant>

#include <astro/frames/Frame.hpp>
#include <astro/frames/frames.hpp>
#include <astro/frames/transformations.hpp>
#include <astro/systems/planets.hpp>

namespace astrea {
namespace astro {

namespace frames {

using primary       = earth::icrf;
using primary_fixed = earth::earth_fixed;

} // namespace frames

static_assert(IsInertialFrame<frames::primary>, "The primary frame must be inertial.");

/**
 * @brief The built-in set of Cartesian frames known to astrea.
 *
 * Add new built-in frames here as additional tuple elements.
 */
using AutomaticallyRegisteredFrames = std::tuple<frames::primary>;

/**
 * @brief Trait that users specialize to register additional Cartesian frames.
 *
 * Specialize this struct **before** including any header that uses the registry
 * (e.g. OrbitalElements.hpp):
 *
 * @code
 * // my_mission.hpp  (included before any astrea headers that depend on the registry)
 * #include <astro/frames/frame_registry.hpp>
 *
 * namespace astrea::astro {
 *   template <>
 *   struct ExtraRegisteredFrames<> {
 *       using type = std::tuple<frames::moon::icrf, frames::mars::icrf>;
 *   };
 * }
 * @endcode
 *
 * The primary template (empty list) is the default — do not modify it.
 */
template <typename = void>
struct ExtraRegisteredFrames {
    using type = std::tuple<>;
};

namespace detail {

// Concatenate two tuples into one tuple
template <typename TupleA, typename TupleB>
struct tuple_cat_types;

template <typename... As, typename... Bs>
struct tuple_cat_types<std::tuple<As...>, std::tuple<Bs...>> {
    using type = std::tuple<As..., Bs...>;
};

// Apply a class template T<> to every element of a tuple
template <template <typename> class T, typename Tuple>
struct apply_template;

template <template <typename> class T, typename... Frames>
struct apply_template<T, std::tuple<Frames...>> {
    using type = std::tuple<T<Frames>...>;
};

// Convert a tuple of types + extra types into a std::variant
template <typename Tuple, typename... Extra>
struct tuple_to_variant;

template <typename... Ts, typename... Extra>
struct tuple_to_variant<std::tuple<Ts...>, Extra...> {
    using type = std::variant<Ts..., Extra...>;
};

/**
 * @brief Alias for the full tuple of registered frames (built-in + user-registered).
 */
using AllRegisteredFrames = typename tuple_cat_types<AutomaticallyRegisteredFrames, typename ExtraRegisteredFrames<>::type>::type;

} // namespace detail


// Concept: true if Frame_T is one of the types in AllRegisteredFrames
template <IsFrame auto Frame_T>
concept IsRegisteredFrame = []<std::size_t... I>(std::index_sequence<I...>) {
    return (std::same_as<Frame_T, std::tuple_element_t<I, detail::AllRegisteredFrames>> || ...);
}(std::make_index_sequence<std::tuple_size_v<detail::AllRegisteredFrames>>{});

// Enforce: all ExtraRegisteredFrames can be transformed into frames::primary
template <typename Tuple, typename Primary, std::size_t... I>
constexpr bool all_have_valid_transformation_impl(std::index_sequence<I...>)
{
    return (frames::HasValidFrameTransformation<std::tuple_element_t<I, Tuple>, Primary> && ...);
}

template <typename Tuple, typename Primary>
constexpr bool all_have_valid_transformation()
{
    return all_have_valid_transformation_impl<Tuple, Primary>(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
}

static_assert(all_have_valid_transformation<ExtraRegisteredFrames<>::type, frames::primary>(), "All ExtraRegisteredFrames must be transformable into frames::primary (HasValidFrameTransformation).");

} // namespace astro
} // namespace astrea
