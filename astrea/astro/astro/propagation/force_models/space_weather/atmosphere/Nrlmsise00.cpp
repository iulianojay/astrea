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

#include <astro/propagation/force_models/space_weather/atmosphere/Nrlmsise00.hpp>

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/systems/system_utilities.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using astrea::units::unit_symbols::sfu;
using mp_units::non_si::unit_symbols::h;
using mp_units::si::atan2;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

Time calculate_local_solar_time(const State& state)
{

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

std::array<int, 24> Nrlmsise00Atmosphere::get_default_flags()
{
    // Ostensibly, 0 is off, and 1 is on. One of them can be negative one sometimes? It's not super well documented
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

Density Nrlmsise00Atmosphere::find_atmospheric_density(
    const State& state,
    const SolarFlux& f107a,
    const SolarFlux& f107,
    const std::array<Unitless, 8>& ap,
    const std::array<int, 24>& flags,
    const bool ignoreLowAltitudes
)
{
    atmos::Nrlmsise00 model(flags);

    // compute day number in current year and the seconds within the day
    const Date& date = state.get_epoch();
    const int doy    = date.day_of_year();
    const Time sec   = date.seconds_in_local_day();

    // compute geodetic position
    const auto& rEcef          = state.get_position_in_frame<frames::earth::earth_fixed>();
    const auto [lat, lon, alt] = convert_body_fixed_to_geodetic(rEcef);

    if (ignoreLowAltitudes && alt < 80.0 * km) { return Density::zero(); }

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

    // NOTE: For some reason, the NRLMSISE-00 model expects the ap array to be a double array of size 7, not 8. The last element is ignored.
    std::array<double, 7> ap_u = { ap[0].numerical_value_in(one), ap[1].numerical_value_in(one),
                                   ap[2].numerical_value_in(one), ap[3].numerical_value_in(one),
                                   ap[4].numerical_value_in(one), ap[5].numerical_value_in(one),
                                   ap[6].numerical_value_in(one) };

    // Call the model
    std::array<double, 9> density      = { 0.0 };
    std::array<double, 2> temperatures = { 0.0 };
    model.gtd7(doy, sec_s, alt_km, lat_deg, lon_deg, lst_h, f107a_sfu, f107_sfu, ap_u, density, temperatures);

    // Extract the total mass density (d[5])
    if (flags[0] == 0) {
        // Output in cm and g
        return density[5] * g / pow<3>(cm);
    }
    else {
        // Output in m and kg
        return density[5] * kg / pow<3>(m);
    }
}

} // namespace astro
} // namespace astrea
