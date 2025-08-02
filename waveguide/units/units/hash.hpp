/**
 * @file hash.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Hash functions for waveguide units
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <functional>

#include <units/typedefs.hpp>

/**
 * @brief Specialization of std::hash for waveguide::Unitless.
 */
template <>
struct std::hash<waveguide::Unitless> {
    std::size_t operator()(const waveguide::Unitless& k) const
    {
        return std::hash<double>()(k.force_numerical_value_in(k.unit));
    }
};

/**
 * @brief Specialization of std::hash for waveguide::Distance.
 */
template <>
struct std::hash<waveguide::Distance> {
    std::size_t operator()(const waveguide::Distance& k) const
    {
        return std::hash<double>()(k.force_numerical_value_in(k.unit));
    }
};

/**
 * @brief Specialization of std::hash for waveguide::Angle.
 */
template <>
struct std::hash<waveguide::Angle> {
    std::size_t operator()(const waveguide::Angle& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};

/**
 * @brief Specialization of std::hash for waveguide::Time.
 */
template <>
struct std::hash<waveguide::Time> {
    std::size_t operator()(const waveguide::Time& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};
