/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/state/orbital_elements/OrbitalElements.hpp>

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include <mp-units/math.h>

#include <math/operations.hpp>

using namespace mp_units;

namespace astrea {
namespace astro {

std::ostream& operator<<(std::ostream& os, const OrbitalElements& elements)
{
    std::visit([&os](const auto& x) { os << x; }, elements._elements);
    return os;
}

bool OrbitalElements::operator==(const OrbitalElements& other) const
{
    if (_elements.index() != other.extract().index()) [[unlikely]] { return false; }
    return std::visit(
        [&](const auto& x) -> bool {
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x == y;
        },
        _elements
    );
}

OrbitalElements OrbitalElements::operator+(const OrbitalElements& other) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x + y;
        },
        _elements
    );
}
OrbitalElements& OrbitalElements::operator+=(const OrbitalElements& other)
{
    std::visit(
        [&](auto& x) {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            x += y;
        },
        _elements
    );
    return *this;
}

OrbitalElements OrbitalElements::operator-(const OrbitalElements& other) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x - y;
        },
        _elements
    );
}
OrbitalElements& OrbitalElements::operator-=(const OrbitalElements& other)
{
    std::visit(
        [&](auto& x) {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            x -= y;
        },
        _elements
    );
    return *this;
}

OrbitalElements OrbitalElements::operator*(const Unitless& multiplier) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x * multiplier; }, _elements);
}
OrbitalElements& OrbitalElements::operator*=(const Unitless& multiplier)
{
    std::visit([&](auto& x) { x *= multiplier; }, _elements);
    return *this;
}

OrbitalElementPartials OrbitalElements::operator/(const Time& divisor) const
{
    return std::visit([&](const auto& x) -> OrbitalElementPartials { return x / divisor; }, _elements);
}
OrbitalElements OrbitalElements::operator/(const Unitless& divisor) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x / divisor; }, _elements);
}
OrbitalElements& OrbitalElements::operator/=(const Unitless& divisor)
{
    std::visit([&](auto& x) { x /= divisor; }, _elements);
    return *this;
}

std::vector<double> OrbitalElements::force_to_double_vector() const
{
    return std::visit([&](const auto& x) -> std::vector<double> { return x.force_to_double_vector(); }, _elements);
}

OrbitalElements
    OrbitalElements::interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const GravParam& mu, const Time& targetTime) const
{
    return std::visit(
        [&](const auto& x) -> OrbitalElements {
            if (!std::holds_alternative<std::remove_cvref_t<decltype(x)>>(other._elements)) {
                throw_mismatched_types();
            }
            const auto& y = std::get<std::remove_cvref_t<decltype(x)>>(other._elements);
            return x.interpolate(thisTime, otherTime, y, mu, targetTime);
        },
        _elements
    );
}

const OrbitalElements::ElementVariant& OrbitalElements::extract() const { return _elements; }
OrbitalElements::ElementVariant& OrbitalElements::extract() { return _elements; }

OrbitalElements& OrbitalElements::convert_to_set(const std::size_t idx, const GravParam& mu)
{
    *this = convert_to_set_impl(idx, mu);
    return *this;
}

OrbitalElements OrbitalElements::convert_to_set(const std::size_t idx, const GravParam& mu) const
{
    return convert_to_set_impl(idx, mu);
}

OrbitalElements OrbitalElements::convert_to_set_impl(const std::size_t idx, const GravParam& mu) const
{
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) -> OrbitalElements {
        OrbitalElements result;
        bool found =
            ((Is == idx ? (result = in_element_set<std::variant_alternative_t<Is, ElementVariant>>(mu), true) : false) || ...);
        if (!found) throw std::runtime_error("Unrecognized element set requested.");
        return result;
    }(std::make_index_sequence<std::variant_size_v<ElementVariant>>{});
}

OrbitalElements OrbitalElements::from_double_vector(const std::vector<double>& vec, const std::size_t idx)
{
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) -> OrbitalElements {
        OrbitalElements result;
        bool found =
            ((Is == idx ? (result = OrbitalElements(std::variant_alternative_t<Is, ElementVariant>::from_double_vector(vec)), true) : false) ||
             ...);
        if (!found) throw std::runtime_error("Invalid orbital element set index for from_double_vector.");
        return result;
    }(std::make_index_sequence<std::variant_size_v<ElementVariant>>{});
}


OrbitalElements OrbitalElementPartials::operator*(const Time& time) const
{
    return std::visit([&](const auto& x) -> OrbitalElements { return x * time; }, _elements);
}

std::ostream& operator<<(std::ostream& os, const OrbitalElementPartials& elements)
{
    std::visit([&os](const auto& x) { os << x; }, elements._elements);
    return os;
}

const OrbitalElementPartials::PartialVariant& OrbitalElementPartials::extract() const { return _elements; }

OrbitalElementPartials::PartialVariant& OrbitalElementPartials::extract() { return _elements; }

std::vector<double> OrbitalElementPartials::force_to_double_vector() const
{
    return std::visit([&](const auto& x) -> std::vector<double> { return x.force_to_double_vector(); }, _elements);
}

void throw_mismatched_types()
{
    throw std::runtime_error(
        "Cannot perform operations on orbital elements from different "
        "element sets."
    );
}

} // namespace astro
} // namespace astrea