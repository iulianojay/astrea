/**
 * @file hash.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Hash functions for astrea units
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
 * @brief Specialization of std::hash for astrea::Unitless.
 */
template <>
struct std::hash<astrea::Unitless> {
    std::size_t operator()(const astrea::Unitless& k) const
    {
        return std::hash<double>()(k.force_numerical_value_in(k.unit));
    }
};

/**
 * @brief Specialization of std::hash for astrea::Distance.
 */
template <>
struct std::hash<astrea::Distance> {
    std::size_t operator()(const astrea::Distance& k) const
    {
        return std::hash<double>()(k.force_numerical_value_in(k.unit));
    }
};

/**
 * @brief Specialization of std::hash for astrea::Angle.
 */
template <>
struct std::hash<astrea::Angle> {
    std::size_t operator()(const astrea::Angle& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};

/**
 * @brief Specialization of std::hash for astrea::Time.
 */
template <>
struct std::hash<astrea::Time> {
    std::size_t operator()(const astrea::Time& a) const
    {
        return (std::hash<double>()(a.numerical_value_ref_in(a.unit)));
    }
};
