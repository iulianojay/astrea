/**
 * @file Origin.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definition for a Origin in astrea.
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

#include <astro/frames/frame_concepts.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

namespace detail {

struct OriginBase {};

} // namespace detail

template <mp_units::basic_fixed_string _name_, IsOrigin auto _parent_ = void>
inline constexpr struct Origin {
    static constexpr auto name   = _name_;   //!< The name of the origin.
    static constexpr auto parent = _parent_; //!< The parent origin of this origin, if any.
} Origin;

namespace origins {

/*
NOTE: This hierarchy is pulled from SPICE
*/

inline constexpr struct SolarSystemBarycenter : Origin<"Solar System Barycenter"> {
} SolarSystemBarycenter;
inline constexpr struct MercuryBarycenter : Origin<"Mercury Barycenter", SolarSystemBarycenter> {
} MercuryBarycenter;
inline constexpr struct VenusBarycenter : Origin<"Venus Barycenter", SolarSystemBarycenter> {
} VenusBarycenter;
inline constexpr struct EarthMoonBarycenter : Origin<"Earth-Moon Barycenter", SolarSystemBarycenter> {
} EarthMoonBarycenter;
inline constexpr struct MarsBarycenter : Origin<"Mars Barycenter", SolarSystemBarycenter> {
} MarsBarycenter;
inline constexpr struct JupiterBarycenter : Origin<"Jupiter Barycenter", SolarSystemBarycenter> {
} JupiterBarycenter;
inline constexpr struct SaturnBarycenter : Origin<"Saturn Barycenter", SolarSystemBarycenter> {
} SaturnBarycenter;
inline constexpr struct UranusBarycenter : Origin<"Uranus Barycenter", SolarSystemBarycenter> {
} UranusBarycenter;
inline constexpr struct NeptuneBarycenter : Origin<"Neptune Barycenter", SolarSystemBarycenter> {
} NeptuneBarycenter;

inline constexpr struct Sun : Origin<"Sun", SolarSystemBarycenter> {
} Sun;
inline constexpr struct Mercury : Origin<"Mercury", SolarSystemBarycenter> {
} Mercury;
inline constexpr struct Venus : Origin<"Venus", SolarSystemBarycenter> {
} Venus;
inline constexpr struct Earth : Origin<"Earth", EarthMoonBarycenter> {
} Earth;
inline constexpr struct Moon : Origin<"Moon", Earth> {
} Moon;
inline constexpr struct Mars : Origin<"Mars", SolarSystemBarycenter> {
} Mars;
inline constexpr struct Phobos : Origin<"Phobos", Mars> {
} Phobos;
inline constexpr struct Deimos : Origin<"Deimos", Mars> {
} Deimos;
inline constexpr struct Jupiter : Origin<"Jupiter", SolarSystemBarycenter> {
} Jupiter;
inline constexpr struct Io : Origin<"Io", Jupiter> {
} Io;
inline constexpr struct Europa : Origin<"Europa", Jupiter> {
} Europa;
inline constexpr struct Ganymede : Origin<"Ganymede", Jupiter> {
} Ganymede;
inline constexpr struct Callisto : Origin<"Callisto", Jupiter> {
} Callisto;
inline constexpr struct Saturn : Origin<"Saturn", SolarSystemBarycenter> {
} Saturn;
inline constexpr struct Titan : Origin<"Titan", Saturn> {
} Titan;
inline constexpr struct Uranus : Origin<"Uranus", SolarSystemBarycenter> {
} Uranus;
inline constexpr struct Oberon : Origin<"Oberon", Uranus> {
} Oberon;
inline constexpr struct Titania : Origin<"Titania", Uranus> {
} Titania;
inline constexpr struct Neptune : Origin<"Neptune", SolarSystemBarycenter> {
} Neptune;
inline constexpr struct Triton : Origin<"Triton", Neptune> {
} Triton;

} // namespace origins

} // namespace astro
} // namespace astrea