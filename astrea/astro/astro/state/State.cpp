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

#include <astro/state/State.hpp>

#include <iostream>

namespace astrea {
namespace astro {

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.get_epoch() << ", " << state.get_elements();
    return os;
}


State State::from_vector(const std::vector<Unitless>& vec, const std::size_t idx, const AstrodynamicsSystem& sys)
{
    return State(OrbitalElements::from_vector(vec, idx), Date(), sys);
}

bool State::operator==(const State& other) const
{
    return _epoch == other._epoch && _elements == other._elements && _system == other._system;
}

State State::operator+(const State& other) const
{
    validate_system(other);
    return { _elements + other._elements, _epoch, get_system() };
}

State& State::operator+=(const State& other)
{
    validate_system(other);
    _elements += other._elements;
    return *this;
}

State State::operator-(const State& other) const
{
    validate_system(other);
    return { _elements - other._elements, _epoch, get_system() };
}

State& State::operator-=(const State& other)
{
    validate_system(other);
    _elements -= other._elements;
    return *this;
}

State State::operator*(const Unitless& scalar) const { return { _elements * scalar, _epoch, get_system() }; }

State& State::operator*=(const Unitless& scalar)
{
    _elements *= scalar;
    return *this;
}

State State::operator/(const Unitless& scalar) const { return { _elements / scalar, _epoch, get_system() }; }

State& State::operator/=(const Unitless& scalar)
{
    _elements /= scalar;
    return *this;
}

StatePartial State::operator/(const Time& divisor) const { return { _elements / divisor, _epoch, get_system() }; }

void State::validate_system(const State& other) const
{
    if (&get_system() != &other.get_system()) {
        throw std::runtime_error("States belong to different astrodynamics systems.");
    }
}

State StatePartial::operator*(const Time& time) const
{
    return { _elementPartials * time, _epoch + time, get_system() };
}

const AstrodynamicsSystem& StatePartial::get_system() const { return *_system; }

const Date& StatePartial::get_epoch() const { return _epoch; }

} // namespace astro
} // namespace astrea