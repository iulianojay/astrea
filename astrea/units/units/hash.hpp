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

template <auto R, typename Rep>
struct std::hash<mp_units::quantity<R, Rep>> {
    std::size_t operator()(const mp_units::quantity<R, Rep>& q) const
    {
        return (std::hash<Rep>()(q.numerical_value_ref_in(q.unit)));
    }
};
