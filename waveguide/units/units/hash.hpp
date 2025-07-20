#pragma once

#include <functional>

#include <units/typedefs.hpp>

template <>
struct std::hash<waveguide::Unitless> {
    std::size_t operator()(const waveguide::Unitless& k) const { return std::hash<double>()(k.force_numerical_value_in(k.unit)); }
};

template <>
struct std::hash<waveguide::Distance> {
    std::size_t operator()(const waveguide::Distance& k) const { return std::hash<double>()(k.force_numerical_value_in(k.unit)); }
};

template <>
struct std::hash<waveguide::Angle> {
    std::size_t operator()(const waveguide::Angle& a) const { return (std::hash<double>()(a.numerical_value_ref_in(a.unit))); }
};