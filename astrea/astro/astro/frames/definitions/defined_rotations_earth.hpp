/**
 * @file defined_rotations_earth.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Earth-specific DCM explicit specialisations.
 *
 * This file is intentionally separate from defined_rotations.hpp so that the
 * generic templates in defined_rotations.hpp can be included mid-way through
 * the include graph (e.g. via dynamic_frames.hpp) without pulling in
 * frames::earth::*, which are only complete once body_centered_inertial_frames.hpp
 * and body_fixed_frames.hpp have both finished.
 *
 * frames.hpp includes this file AFTER its two frame-instance headers, so by
 * the time these specialisations are compiled all earth frame types are complete.
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 */
#pragma once

#include <type_traits>

#include <mp-units/systems/si/math.h>

#include <math/trig.hpp>
#include <units/units.hpp>

#include <astro/frames/definitions/body_centered_inertial_frames.hpp>
#include <astro/frames/definitions/body_fixed_frames.hpp>
#include <astro/frames/definitions/defined_rotations.hpp>
#include <astro/systems/celestial_bodies.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

namespace axes {
inline constexpr struct cep : Axis<"Earth Celestial Pole", axes::icrf> {
} cep;
} // namespace axes

namespace frames {
namespace earth {

inline constexpr struct cep : Frame<"Earth Celestial Pole", planets::Earth, axes::cep> {
} cep;

} // namespace earth
} // namespace frames

struct NutationModel {
    std::array<int8_t, 5> k;
    Time period;
    mp_units::quantity<mp_units::si::arcminute> a0;
    mp_units::quantity<mp_units::si::arcsecond> a1;
    mp_units::quantity<mp_units::si::arcminute> b0;
    mp_units::quantity<mp_units::si::arcsecond> b1;
};

static constexpr std::size_t NUTATION_COEFFICIENTS_SIZE = 106;

inline constexpr NutationModel get_nutation_coefficient(std::size_t idx)
{

    using namespace mp_units;
    using mp_units::non_si::day;
    using mp_units::si::unit_symbols::arcmin;
    using mp_units::si::unit_symbols::arcsec;

    static constexpr std::array<NutationModel, NUTATION_COEFFICIENTS_SIZE> NUTATION_COEFFICIENTS = {
        NutationModel({ { 0, 0, 0, 0, 1 } }, -6798.4 * day, 1996.0e-4 * arcmin, -174.2 * arcsec, 92025.0e-4 * arcmin, 8.9 * arcsec),
        NutationModel({ { 0, 0, 2, -2, 2 } }, 182.6 * day, 3187.0e-4 * arcmin, -1.6 * arcsec, 5736.0e-4 * arcmin, -3.1 * arcsec),
        NutationModel({ { 0, 0, 2, 0, 2 } }, 13.7 * day, 2274.0e-4 * arcmin, -0.2 * arcsec, 977.0e-4 * arcmin, -0.5 * arcsec),
        NutationModel({ { 0, 0, 0, 0, 2 } }, -3399.2 * day, 2062.0e-4 * arcmin, 0.2 * arcsec, -895.0e-4 * arcmin, 0.5 * arcsec),
        NutationModel({ { 0, -1, 0, 0, 0 } }, -365.3 * day, 1426.0e-4 * arcmin, 3.4 * arcsec, 54.0e-4 * arcmin, -0.1 * arcsec),
        NutationModel({ { 1, 0, 0, 0, 0 } }, 27.6 * day, 712.0e-4 * arcmin, 0.1 * arcsec, -7.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 2, -2, 2 } }, 121.7 * day, -517.0e-4 * arcmin, 1.2 * arcsec, 224.0e-4 * arcmin, -0.6 * arcsec),
        NutationModel({ { 0, 0, 2, 0, 1 } }, 13.6 * day, -386.0e-4 * arcmin, -0.4 * arcsec, 200.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, 0, 2 } }, 9.1 * day, -301.0e-4 * arcmin, 0.0 * arcsec, 129.0e-4 * arcmin, -0.1 * arcsec),
        NutationModel({ { 0, -1, 2, -2, 2 } }, 365.2 * day, 217.0e-4 * arcmin, -0.5 * arcsec, -95.0e-4 * arcmin, 0.3 * arcsec),
        NutationModel({ { -1, 0, 0, 2, 0 } }, 31.8 * day, 158.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, -2, 1 } }, 177.8 * day, 129.0e-4 * arcmin, 0.1 * arcsec, -70.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, 0, 2 } }, 27.1 * day, 123.0e-4 * arcmin, 0.0 * arcsec, -53.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, 0, 1 } }, 27.7 * day, 63.0e-4 * arcmin, 0.1 * arcsec, -33.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 0, 2, 0 } }, 14.8 * day, 63.0e-4 * arcmin, 0.0 * arcsec, -2.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, 2, 2 } }, 9.6 * day, -59.0e-4 * arcmin, 0.0 * arcsec, 26.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 0, 0, 1 } }, -27.4 * day, -58.0e-4 * arcmin, -0.1 * arcsec, 32.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, 0, 1 } }, 9.1 * day, -51.0e-4 * arcmin, 0.0 * arcsec, 27.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 0, 2, 0 } }, -205.9 * day, -48.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 2, 0, 1 } }, 1305.5 * day, 46.0e-4 * arcmin, 0.0 * arcsec, -24.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, 2, 2 } }, 7.1 * day, -38.0e-4 * arcmin, 0.0 * arcsec, 16.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 2, 0, 2 } }, 6.9 * day, -31.0e-4 * arcmin, 0.0 * arcsec, 13.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 0, 0, 0 } }, 13.8 * day, 29.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, -2, 2 } }, 23.9 * day, 29.0e-4 * arcmin, 0.0 * arcsec, -12.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, 0, 0 } }, 13.6 * day, 26.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, -2, 0 } }, 173.3 * day, -22.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, 0, 1 } }, 27.0 * day, 21.0e-4 * arcmin, 0.0 * arcsec, -10.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 2, 0, 0, 0 } }, 182.6 * day, 17.0e-4 * arcmin, -0.1 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 2, 2, -2, 2 } }, 91.3 * day, -16.0e-4 * arcmin, 0.1 * arcsec, 7.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 0, 2, 1 } }, 32.0 * day, 16.0e-4 * arcmin, 0.0 * arcsec, -8.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 0, 0, 1 } }, 386.0 * day, -15.0e-4 * arcmin, 0.0 * arcsec, 9.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, -2, 1 } }, -31.7 * day, -13.0e-4 * arcmin, 0.0 * arcsec, 7.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -1, 0, 0, 1 } }, -346.6 * day, -12.0e-4 * arcmin, 0.0 * arcsec, 6.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, -2, 0, 0 } }, -1095.2 * day, 11.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, 2, 1 } }, 9.5 * day, -10.0e-4 * arcmin, 0.0 * arcsec, 5.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, 2, 2 } }, 5.6 * day, -8.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -1, 2, 0, 2 } }, 14.2 * day, -7.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, 2, 1 } }, 7.1 * day, -7.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 1, 0, -2, 0 } }, -34.8 * day, -7.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 2, 0, 2 } }, 13.2 * day, 7.0e-4 * arcmin, 0.0 * arcsec, -3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 0, 2, 1 } }, -199.8 * day, -6.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 0, 2, 1 } }, 14.8 * day, -6.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 2, -2, 2 } }, 12.8 * day, 6.0e-4 * arcmin, 0.0 * arcsec, -3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, 2, 0 } }, 9.6 * day, 6.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, -2, 1 } }, 23.9 * day, 6.0e-4 * arcmin, 0.0 * arcsec, -3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 0, -2, 1 } }, -14.7 * day, -5.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -1, 2, -2, 1 } }, 346.6 * day, -5.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 2, 0, 1 } }, 6.9 * day, -5.0e-4 * arcmin, 0.0 * arcsec, 3.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, -1, 0, 0, 0 } }, 29.8 * day, 5.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, -1, 0 } }, 411.8 * day, -4.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 0, 1, 0 } }, 29.5 * day, -4.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 0, -2, 0 } }, -15.4 * day, -4.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, -2, 0, 0 } }, -26.9 * day, 4.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 0, -2, 1 } }, 212.3 * day, 4.0e-4 * arcmin, 0.0 * arcsec, -2.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 2, -2, 1 } }, 119.6 * day, 4.0e-4 * arcmin, 0.0 * arcsec, -2.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 1, 0, 0, 0 } }, 25.6 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, -1, 0, -1, 0 } }, -3232.9 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, -1, 2, 2, 2 } }, 9.8 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -1, 2, 2, 2 } }, 7.2 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, -1, 2, 0, 2 } }, 9.4 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 3, 0, 2, 0, 2 } }, 5.5 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 2, 0, 2 } }, 1615.7 * day, -3.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, 0, 0 } }, 9.1 * day, 3.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, 4, 2 } }, 5.8 * day, -2.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, 0, 2 } }, 27.8 * day, -2.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 2, -2, 1 } }, -32.6 * day, -2.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -2, 2, -2, 1 } }, 6786.3 * day, -2.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 0, 0, 1 } }, -13.7 * day, -2.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 0, 0, 1 } }, 13.8 * day, 2.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 3, 0, 0, 0, 0 } }, 9.2 * day, 2.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 1, 2, 0, 2 } }, 8.9 * day, 2.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, 1, 2 } }, 9.3 * day, 2.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, 2, 1 } }, 9.6 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, 2, 1 } }, 5.6 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 1, 0, -2, 1 } }, -34.7 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 0, 2, 0 } }, 14.2 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 2, -2, 0 } }, 117.5 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, -2, 2, 0 } }, -329.8 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, -2, 2, 0 } }, 23.8 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, -2, -2, 0 } }, -9.5 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 2, -2, 0 } }, 32.8 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 0, 0, -4, 0 } }, -10.1 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 0, -4, 0 } }, -15.9 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, 4, 2 } }, 4.8 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 2, -1, 2 } }, 25.4 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 2, 4, 2 } }, 7.3 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 2, 2, 2 } }, 4.7 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, -1, 2, 0, 1 } }, 14.2 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, -2, 0, 1 } }, -13.6 * day, -1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, 4, -2, 2 } }, 12.7 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 0, 0, 2 } }, 409.2 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, 1, 2, -2, 2 } }, 22.5 * day, 1.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 3, 0, 2, -2, 2 } }, 8.7 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -2, 0, 2, 2, 2 } }, 14.6 * day, 1.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 0, 0, 2 } }, -27.3 * day, 1.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 0, -2, 2, 1 } }, -169.0 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 2, 0, 1 } }, 13.1 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 4, 0, 2 } }, 9.1 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 1, 0, -2, 0 } }, 131.7 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 0, 2, 0 } }, 7.1 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, 2, -2, 1 } }, 12.8 * day, 1.0e-4 * arcmin, 0.0 * arcsec, -1.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 2, 0, -2, 0, 1 } }, -943.2 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 1, -1, 0, -2, 0 } }, -29.3 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, 0, 0, 1, 1 } }, -388.3 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { -1, -1, 0, 2, 1 } }, 35.0 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec),
        NutationModel({ { 0, 1, 0, 1, 0 } }, 27.3 * day, 1.0e-4 * arcmin, 0.0 * arcsec, 0.0e-4 * arcmin, 0.0 * arcsec)
    };

    return NUTATION_COEFFICIENTS[idx];
}

inline constexpr struct revolution final : mp_units::named_unit<"rev", mp_units::mag<360> * mp_units::si::unit_symbols::deg> {
} revolution;
inline constexpr auto rev = revolution;

inline constexpr std::array<mp_units::quantity<mp_units::si::unit_symbols::arcsec>, 5> get_anomaly_terms(const Unitless& T)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::arcmin;
    using mp_units::si::unit_symbols::arcsec;
    using mp_units::si::unit_symbols::deg;

    // Lunar mean anomaly
    const quantity<arcsec> l = 485866.733 * arcsec + (1325 * rev + 715922.633 * arcsec) * T +
                               31.8792 * arcsec * pow<2>(T) + 0.064 * arcsec * pow<3>(T);

    // Solar mean anomaly
    const quantity<arcsec> lp = 1287099.804 * arcsec + (99 * rev + 129596581.0481 * arcsec) * T -
                                0.577 * arcsec * pow<2>(T) - 0.00012 * arcsec * pow<3>(T);

    // Lunar mean argument of latitude
    const quantity<arcsec> F = 335778.877 * arcsec + (1342 * rev + 295263.137 * arcsec) * T -
                               13.257 * arcsec * pow<2>(T) + 0.011 * arcsec * pow<3>(T);

    // Mean elongation of the Moon from the Sun
    const quantity<arcsec> D = 1072261.307 * arcsec + (1235 * rev + 1105601.328 * arcsec) * T -
                               6.891 * arcsec * pow<2>(T) + 0.019 * arcsec * pow<3>(T);

    // Mean longitude of the ascending node of the Moon
    const quantity<arcsec> Om =
        450160.280 * arcsec - (5 * rev + 482890.539 * arcsec) * T + 7.455 * arcsec * pow<2>(T) + 0.008 * arcsec * pow<3>(T);

    return { l, lp, F, D, Om };
}

inline constexpr std::array<mp_units::quantity<mp_units::si::unit_symbols::arcsec>, 2> get_nutation_angles(const Unitless& T)
{
    using namespace mp_units;
    using math::cos;
    using math::sin;
    using mp_units::si::unit_symbols::arcsec;

    quantity<arcsec> dpsi = 0.0 * arcsec;
    quantity<arcsec> deps = 0.0 * arcsec;

    const auto anomalyTerms = get_anomaly_terms(T);
    for (std::size_t ii = 0; ii < NUTATION_COEFFICIENTS_SIZE; ++ii) {
        const auto& coeff = get_nutation_coefficient(ii);
        const auto arg    = coeff.k[0] * anomalyTerms[0] + coeff.k[1] * anomalyTerms[1] + coeff.k[2] * anomalyTerms[2] +
                         coeff.k[3] * anomalyTerms[3] + coeff.k[4] * anomalyTerms[4];

        dpsi += (coeff.a0 + coeff.a1 * T) * sin(arg);
        deps += (coeff.b0 + coeff.b1 * T) * cos(arg);
    }

    return { dpsi, deps };
}

/**
 * @brief DCM from frames::earth::icrf to frames::earth::cep.
 *
 * @param date The date at which to compute the DCM.
 * @return DirectionCosineMatrix<frames::earth::icrf, frames::earth::cep> The DCM from frames::earth::icrf to frames::earth::cep at the given date.
 *
 * @note https://gssc.esa.int/navipedia/index.php?title=ICRF_to_CEP
 */
template <>
inline constexpr DirectionCosineMatrix<frames::earth::icrf, frames::earth::cep>
    get_dcm<frames::earth::icrf, frames::earth::cep>(const Date& date)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::arcmin;
    using mp_units::si::unit_symbols::arcsec;
    using mp_units::si::unit_symbols::deg;

    // These equations really should give the constants in terms of angular rates, accels, etc., but
    // it's easier to write them as unit-unaware polynomials and since everyone does that, we're just mimicking it here
    const Unitless T = (date - J2000).numerical_value_in(JulianCentury) * one;

    const quantity<arcsec> z = 2306.2181 * arcsec * T + 1.09468 * arcsec * pow<2>(T) + 0.018203 * arcsec * pow<3>(T);
    const quantity<arcsec> theta = 2004.3109 * arcsec * T - 0.42665 * arcsec * pow<2>(T) - 0.041833 * arcsec * pow<3>(T);
    const quantity<arcsec> zeta = 2306.2181 * arcsec * T + 0.30188 * arcsec * pow<2>(T) + 0.017998 * arcsec * pow<3>(T);
    const auto P                = DCM<frames::earth::cep, frames::earth::cep>::ZYZ(-z, theta, -zeta);

    const quantity<arcsec> eps = (23 * deg + 26 * arcmin + 21.448 * arcsec) - 46.8150 * arcsec * T -
                                 0.00059 * arcsec * pow<2>(T) + 0.001813 * arcsec * pow<3>(T);
    const auto [dpsi, deps] = get_nutation_angles(T);
    const auto N            = DCM<frames::earth::icrf, frames::earth::cep>::XZX(-(eps + deps), -dpsi, eps);

    return N * P;
}

template <>
inline constexpr DirectionCosineMatrix<frames::earth::cep, frames::earth::itrf>
    get_dcm<frames::earth::cep, frames::earth::itrf>(const Date& date)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::arcmin;
    using mp_units::si::unit_symbols::arcsec;
    using mp_units::si::unit_symbols::deg;

    // These equations really should give the constants in terms of angular rates, accels, etc., but
    // it's easier to write them as unit-unaware polynomials and since everyone does that, we're just mimicking it here
    // const Unitless T = (date - J2000).numerical_value_in(JulianCentury) * one;

    const Angle gst = julian_date_to_sidereal_time(date.jd());
    const auto Rs   = DCM<frames::earth::cep, frames::earth::itrf>::Z(gst);

    const Angle xp = 0.0 * arcsec;
    const Angle yp = 0.0 * arcsec;

    const auto R1 = DCM<frames::earth::itrf, frames::earth::itrf>::Y(-xp);
    const auto R2 = DCM<frames::earth::itrf, frames::earth::itrf>::X(-yp);
    const auto Rm = R1 * R2;

    return Rs * Rm;
}

/**
 * @brief DCM from any Earth-centred ICRF frame (including the canonical frames::earth::icrf)
 * to any Earth-centred body-fixed frame.
 *
 * The explicit template<> specialisation was replaced with this constrained template so that
 * HasDcm<earth::icrf, earth::earth_fixed> (and similar requires-expressions) can find this
 * overload.  GCC 15 does not locate explicit template<> specialisations when checking
 * concept requires-expressions with constrained-auto NTTP arguments.
 */
template <IsFrame auto in_frame, IsFrame auto out_frame>
    requires(
        equivalent(in_frame.origin, out_frame.origin) && equivalent(in_frame.origin, planets::Earth) &&
        equivalent(in_frame.axis, axes::icrf) && IsBodyFixedFrame<decltype(out_frame)>
    )
inline constexpr DirectionCosineMatrix<in_frame, out_frame> get_dcm(const Date& date)
{
    const auto dcmIcrfToCep = get_dcm<frames::earth::icrf, frames::earth::cep>(date);
    const auto dcmCepToItrf = get_dcm<frames::earth::cep, frames::earth::itrf>(date);
    return DCM<in_frame, out_frame>{ dcmIcrfToCep * dcmCepToItrf };
}

} // namespace astro
} // namespace astrea
