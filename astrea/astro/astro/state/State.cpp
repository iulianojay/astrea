/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/state/State.hpp>

#include <iostream>

#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.get_epoch() << ", " << state.get_elements();
    if (state.get_attitude().has_value()) { os << ", " << state.get_attitude().value(); }
    return os;
}

State::State(const StateHistory& history)
{
    if (history.size() != 1) {
        throw std::runtime_error("StateHistory must contain exactly one state to construct a State.");
    }
    const auto& state = history.first();
    *this             = state;
}


State State::from_double_vector(const std::vector<double>& vec, const std::size_t idx)
{
    if (vec.size() == 6) { return State(OrbitalElements::from_double_vector(vec, idx), Date()); }

    const auto elementValues  = std::vector<double>(vec.begin(), vec.begin() + 6);
    const auto attitudeValues = std::vector<double>(vec.begin() + 6, vec.end());
    return State(OrbitalElements::from_double_vector(elementValues, idx), Date(), Attitude::from_double_vector(attitudeValues));
}

bool State::operator==(const State& other) const
{
    return _epoch == other._epoch && _elements == other._elements && _attitude.has_value() == other._attitude.has_value() &&
           (!_attitude.has_value() || _attitude.value() == other._attitude.value());
}

State State::operator+(const State& other) const
{
    return { _elements + other._elements,
             _epoch,
             _attitude.has_value() && other._attitude.has_value() ?
                 std::optional<Attitude>(_attitude.value() + other._attitude.value()) :
                 std::nullopt };
}

State& State::operator+=(const State& other)
{
    _elements += other._elements;
    if (_attitude.has_value() && other._attitude.has_value()) { _attitude.value() += other._attitude.value(); }
    return *this;
}

State State::operator-(const State& other) const
{
    return { _elements - other._elements,
             _epoch,
             _attitude.has_value() && other._attitude.has_value() ?
                 std::optional<Attitude>(_attitude.value() - other._attitude.value()) :
                 std::nullopt };
}

State& State::operator-=(const State& other)
{
    _elements -= other._elements;
    if (_attitude.has_value() && other._attitude.has_value()) { _attitude.value() -= other._attitude.value(); }
    return *this;
}

State State::operator*(const Unitless& scalar) const
{
    return { _elements * scalar, _epoch, _attitude }; // attitude shouldn't scale
}

State& State::operator*=(const Unitless& scalar)
{
    _elements *= scalar;
    return *this;
}

State State::operator/(const Unitless& scalar) const
{
    return { _elements / scalar, _epoch, _attitude }; // attitude shouldn't scale
}

State& State::operator/=(const Unitless& scalar)
{
    _elements /= scalar;
    return *this;
}

StatePartial State::operator/(const Time& divisor) const
{
    return { _epoch,
             _elements / divisor,
             _attitude.has_value() ? std::optional<AttitudePartials>(_attitude.value() / divisor) : std::nullopt };
}

State StatePartial::operator*(const Time& time) const
{
    return { _elementPartials * time,
             _epoch + time,
             _attitudePartial.has_value() ? std::optional<Attitude>(_attitudePartial.value() * time) : std::nullopt };
}

const Date& StatePartial::get_epoch() const { return _epoch; }

} // namespace astro
} // namespace astrea