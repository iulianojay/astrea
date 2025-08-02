/**
 * @file type_traits.hpp
 * @author your name (you@domain.com)
 * @brief Type traits for waveguide astro library
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstddef>
#include <initializer_list>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace waveguide {
namespace astro {

template <typename T>
using remove_cv_ref = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace astro
} // namespace waveguide