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

template <utilities::double_wrapper _N_>
consteval auto f_to_fixed_string()
{
    constexpr auto s          = utilities::f_to_string<_N_>;
    constexpr std::size_t len = s.size() - 1; // exclude null terminator
    return mp_units::basic_fixed_string<char, len>(s.begin(), s.end() - 1);
}

template <auto _q_>
inline consteval auto quantity_to_fixed_string()
{
    return f_to_fixed_string<_q_.numerical_value_in(_q_.unit)>() + " " + _q_.unit._symbol_.portable();
}

template <auto _first_, auto... _rest_>
inline consteval auto quantity_list_to_fixed_string()
{
    if constexpr (sizeof...(_rest_) == 0)
        return quantity_to_fixed_string<_first_>();
    else
        return quantity_to_fixed_string<_first_>() + ", " + quantity_list_to_fixed_string<_rest_...>();
}

template <mp_units::basic_fixed_string _parent_name_, Distance _x_, Distance _y_, Distance _z_>
inline consteval auto compose_name()
{
    return _parent_name_ + " + [" + quantity_list_to_fixed_string<_x_, _y_, _z_>() + "]";
}

template <mp_units::basic_fixed_string _parent_name_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto compose_name()
{
    return _parent_name_ + " + [" + quantity_list_to_fixed_string<_phi_, _theta_, _psi_>() + "]";
}

template <mp_units::basic_fixed_string _parent_name_, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_>
inline consteval auto compose_name()
{
    return _parent_name_ + " + [" + quantity_list_to_fixed_string<_x_, _y_, _z_>() + "; " +
           quantity_list_to_fixed_string<_phi_, _theta_, _psi_>() + "]";
}

template <typename, auto...>
struct FixedOffsetFrame;

template <IsFrame Parent, Distance _x_, Distance _y_, Distance _z_, auto... Args>
struct FixedOffsetFrame<Parent, _x_, _y_, _z_, Args...>
    : Frame<compose_name<Parent::name, _x_, _y_, _z_>(), CelestialBodyId::FIXED_OFFSET, Parent::axis, Parent> {
    static constexpr CartesianVector<Distance, Parent> offset = { _x_, _y_, _z_ }; //!< The fixed offset vector from the parent frame to this frame.
};

template <IsFrame Parent, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<Parent, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<compose_name<Parent::name, _phi_, _theta_, _psi_>(), CelestialBodyId::FIXED_OFFSET, Parent::axis, Parent> {
    static constexpr auto sequence = _sequence_; //!< The rotation sequence for the angular offset.
    static constexpr CartesianVector<Angle, Parent> misalignment = { _phi_, _theta_, _psi_ }; //!< The fixed angular offset dcm from the parent frame to this frame.
};

template <IsFrame Parent, Distance _x_, Distance _y_, Distance _z_, Angle _phi_, Angle _theta_, Angle _psi_, RotationSequence _sequence_, auto... Args>
struct FixedOffsetFrame<Parent, _x_, _y_, _z_, _phi_, _theta_, _psi_, _sequence_, Args...>
    : Frame<compose_name<Parent::name, _x_, _y_, _z_, _phi_, _theta_, _psi_>(), CelestialBodyId::FIXED_OFFSET, Parent::axis, Parent> {
    static constexpr CartesianVector<Distance, Parent> offset = { _x_, _y_, _z_ }; //!< The fixed offset vector from the parent frame to this frame.
    static constexpr auto sequence = _sequence_; //!< The rotation sequence for the angular offset.
    static constexpr CartesianVector<Angle, Parent> misalignment = { _phi_, _theta_, _psi_ }; //!< The fixed angular offset dcm from the parent frame to this frame.
};

template <IsFixedOffsetFrame T>
inline constexpr DirectionCosineMatrix<typename T::parent, T> get_dcm_from_frame()
{
    return DirectionCosineMatrix<typename T::parent, T>::template from_euler_angles<T::sequence>(
        T::misalignment[0], T::misalignment[1], T::misalignment[2]
    );
}

} // namespace astro
} // namespace astrea