/**
 * @file NRLMSISE00.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the NRLMSISE00 class.
 * @date 2026-05-01
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <mp-units/systems/si.h>
#include <nrlmsise00/Nrlmsise00.hpp>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/systems/system_utilities.hpp>


namespace astrea {
namespace astro {


Time calculate_local_solar_time(const State& state)
{
    using mp_units::non_si::unit_symbols::h;
    using mp_units::si::atan2;
    using mp_units::si::unit_symbols::rad;

    const Date& date     = state.get_epoch();
    const auto& position = state.get_position();

    const auto sunDirection =
        frames::rotate_vector_into_frame<frames::primary>(get_relative_position<star::Sun, planets::Earth>(date).direction(), date);

    const Angle lst =
        std::numbers::pi * rad + atan2(
                                     sunDirection.get_x() * position.get_y() - sunDirection.get_y() * position.get_x(),
                                     sunDirection.get_x() * position.get_x() + sunDirection.get_y() * position.get_y()
                                 );
    return lst * 12.0 / std::numbers::pi * h / rad;
}

inline constexpr std::array<int, 24> get_default_flags()
{
    // Ostensibly, 0 is off, and 1 is on. It's not super well documented
    return std::array<int, 24>{
        0, // output in meters and kilograms instead of centimeters and grams -> NOTE: Don't touch this, the output units are hard coded
        1, // F10.7 effect on mean
        1, // time independent
        1, // symmetrical annual
        1, // symmetrical semiannual
        1, // asymmetrical annual
        1, // asymmetrical semiannual
        1, // diurnal
        1, // semidiurnal
        1, // daily ap [when this is set to -1 (!) the pointer ap_a in struct nrlmsise_input must point to a struct ap_array]
        1, // all UT/long effects
        1, // longitudinal
        1, // UT and mixed UT/long
        1, // mixed AP/UT/LONG
        1, // terdiurnal
        1, // departures from diffusive equilibrium
        1, // all TINF var
        1, // all TLB var
        1, // all TN1 var
        1, // all S var
        1, // all TN2 var
        1, // all NLB var
        1, // all TN3 var
        1  // turbo scale height var
    };
}

class Nrlmsise00Atmosphere {
  public:
    /**
     * @brief Deleted constructor — use static factory or find_atmospheric_density directly.
     */
    Nrlmsise00Atmosphere() = delete;

    /**
     * @brief Find the atmospheric density at a given state and solar/geomagnetic conditions.
     * @param state The current state of the satellite.
     * @param f107a The 81-day average of the F10.7 solar flux.
     * @param f107 The daily F10.7 solar flux.
     * @param ap The array of geomagnetic indices.
     * @return The atmospheric density.

     * \parblock
     * @note The magnetic index array contains:
     * Array containing the following magnetic values:
     * - 0: daily AP
     * - 1: 3 hr AP index for current time
     * - 2: 3 hr AP index for 3 hrs before current time
     * - 3: 3 hr AP index for 6 hrs before current time
     * - 4: 3 hr AP index for 9 hrs before current time
     * - 5: Average of eight 3 hr AP indicies from 12 to 33 hrs prior to current time
     * - 6: Average of eight 3 hr AP indicies from 36 to 57 hrs prior to current time
     * \endparblock
     * \parblock
     * @note f107 and f107A values used to generate the model correspond
     *       to the 10.7 cm radio flux at the actual distance of the Earth
     *       from the Sun rather than the radio flux at 1 AU.
     * \endparblock
     * \parblock
     * @note f107, f107A, and ap effects are neither large nor well
     *       established below 80 km and these parameters should be set to
     *       150., 150., and 4. respectively.
     */
    static inline Density find_atmospheric_density(
        const State& state,
        const SolarFlux& f107a,
        const SolarFlux& f107,
        std::array<double, 7>& ap,
        const std::array<int, 24>& flags = get_default_flags()
    )
    {
        using namespace mp_units;
        using astrea::units::unit_symbols::sfu;
        using mp_units::non_si::unit_symbols::h;
        using mp_units::si::unit_symbols::cm;
        using mp_units::si::unit_symbols::deg;
        using mp_units::si::unit_symbols::g;
        using mp_units::si::unit_symbols::km;
        using mp_units::si::unit_symbols::s;

        // Build the model every single time, cause we really needed a pimpl idiom for an open-source model
        atmos::Nrlmsise00 model(flags);

        // compute day number in current year and the seconds within the day
        const Date& date = state.get_epoch();
        const int doy    = date.day_of_year();
        const Time sec   = date.seconds_in_local_day();

        // compute geodetic position
        const auto& rEcef          = state.get_position_in_frame<frames::earth::earth_fixed>();
        const auto [lat, lon, alt] = convert_body_fixed_to_geodetic(rEcef);

        if (alt < 80.0 * km) { return Density::zero(); }

        // compute local solar time
        const Time lst = calculate_local_solar_time(state);

        // Unsafe downcasts to double
        const double sec_s     = sec.numerical_value_in(s);
        const double alt_km    = alt.numerical_value_in(km);
        const double lat_deg   = lat.numerical_value_in(deg);
        const double lon_deg   = lon.numerical_value_in(deg);
        const double lst_h     = lst.numerical_value_in(h);
        const double f107a_sfu = f107a.numerical_value_in(sfu);
        const double f107_sfu  = f107.numerical_value_in(sfu);

        // Call the model
        std::array<double, 9> density      = { 0.0 };
        std::array<double, 2> temperatures = { 0.0 };
        model.gtd7(doy, sec_s, alt_km, lat_deg, lon_deg, lst_h, f107a_sfu, f107_sfu, ap, density, temperatures);

        // Extract the total mass density (d[5])
        return density[5] * g / pow<3>(cm);
    }
};

} // namespace astro
} // namespace astrea
