/**
 * @file FixedOffsetFrame.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a FixedOffsetFrame in astrea.
 * @date 2025-10-02
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

#include <type_traits>

#include <mp-units/ext/fixed_string.h>

#include <units/units.hpp>
#include <utilities/string_util.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/Frame.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

template <utilities::double_wrapper N>
consteval auto f_to_fixed_string()
{
    constexpr auto s          = utilities::f_to_string<N>;
    constexpr std::size_t len = s.size() - 1; // exclude null terminator
    return mp_units::basic_fixed_string<char, len>(s.begin(), s.end() - 1);
}

template <mp_units::basic_fixed_string ParentName, Distance x, Distance y, Distance z>
inline consteval auto compose_name()
{
    return ParentName + " + [" + f_to_fixed_string<x.numerical_value_in(x.unit)>() + " km, " +
           f_to_fixed_string<y.numerical_value_in(y.unit)>() + " km, " + f_to_fixed_string<z.numerical_value_in(z.unit)>() + " km]";
}

template <mp_units::basic_fixed_string ParentName, Angle phi, Angle theta, Angle psi>
inline consteval auto compose_name()
{
    return ParentName + " + [" + f_to_fixed_string<phi.numerical_value_in(phi.unit)>() + " rad, " +
           f_to_fixed_string<theta.numerical_value_in(theta.unit)>() + " rad, " +
           f_to_fixed_string<psi.numerical_value_in(psi.unit)>() + " rad]";
}

template <typename, auto...>
struct FixedOffsetFrame;

template <typename _parent, Distance _x, Distance _y, Distance _z, auto... Args>
struct FixedOffsetFrame<_parent, _x, _y, _z, Args...>
    : Frame<compose_name<_parent::name, _x, _y, _z>(), CelestialBodyId::FIXED_OFFSET, _parent::axis, _parent> {
    static constexpr CartesianVector<Distance, _parent> offset = { _x, _y, _z }; //!< The fixed offset vector from the parent frame to this frame.
};

template <typename _parent, CartesianVector<Distance, _parent> _offset, auto... Args>
struct FixedOffsetFrame<_parent, _offset, Args...>
    : Frame<compose_name<_parent::name, _offset[0], _offset[1], _offset[2]>(), CelestialBodyId::FIXED_OFFSET, _parent::axis, _parent> {
    static constexpr CartesianVector<Distance, _parent> offset =
        _offset; //!< The fixed offset vector from the parent frame to this frame.
};

template <typename _parent, Angle _phi, Angle _theta, Angle _psi, RotationSequence _sequence, auto... Args>
struct FixedOffsetFrame<_parent, _phi, _theta, _psi, _sequence, Args...>
    : Frame<compose_name<_parent::name, _phi, _theta, _psi>(), CelestialBodyId::FIXED_OFFSET, _parent::axis, _parent> {
    static constexpr auto sequence = _sequence; //!< The rotation sequence for the angular offset.
    static constexpr CartesianVector<Angle, _parent> misalignment = { _phi, _theta, _psi }; //!< The fixed angular offset dcm from the parent frame to this frame.
};

template <typename Frame_T>
    requires requires {
        Frame_T::sequence;
        Frame_T::misalignment;
        typename Frame_T::parent;
    }
inline constexpr DirectionCosineMatrix<typename Frame_T::parent, Frame_T> get_dcm_from_frame()
{
    return DirectionCosineMatrix<typename Frame_T::parent, Frame_T>::template from_euler_angles<Frame_T::sequence>(
        Frame_T::misalignment[0], Frame_T::misalignment[1], Frame_T::misalignment[2]
    );
}

} // namespace astro
} // namespace astrea