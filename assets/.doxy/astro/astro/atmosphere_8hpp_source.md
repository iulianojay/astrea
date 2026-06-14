

# File atmosphere.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**atmosphere.hpp**](atmosphere_8hpp.md)

[Go to the documentation of this file](atmosphere_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/state/angular_elements/Geodetic.hpp>
#include <astro/systems/celestial_bodies/Earth/Earth.hpp>
#include <astro/systems/celestial_bodies/Earth/atmosphere/HarrisPriester.hpp>
#include <astro/systems/celestial_bodies/Earth/atmosphere/JacciaRoberts.hpp>
#include <astro/systems/celestial_bodies/Mars/Mars.hpp>
#include <astro/systems/celestial_bodies/Saturn/Titan.hpp>
#include <astro/systems/celestial_bodies/Venus/Venus.hpp>
#include <astro/systems/property_getters.hpp>

namespace astrea {
namespace astro {

// ---------------------------------------------------------------------------
// Earth
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Earth>(const State& state)
{
    return planets::HarrisPriesterAtmosphere::find_atmospheric_density(state);
}

// ---------------------------------------------------------------------------
// Venus
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Venus>(const State& state)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::m;

    // Altitude Conditions(TABLE 7-4, Vallado)
    static const std::map<Altitude, Density> venutianAtmosphere = {
        // km, kg/m^3
        { 3.0 * km, 5.53e1 * kg / (pow<3>(m)) },    { 6.0 * km, 4.75e1 * kg / (pow<3>(m)) },
        { 9.0 * km, 4.02e1 * kg / (pow<3>(m)) },    { 12.0 * km, 3.44e1 * kg / (pow<3>(m)) },
        { 15.0 * km, 2.91e1 * kg / (pow<3>(m)) },   { 18.0 * km, 2.46e1 * kg / (pow<3>(m)) },
        { 21.0 * km, 2.06e1 * kg / (pow<3>(m)) },   { 24.0 * km, 1.70e1 * kg / (pow<3>(m)) },
        { 27.0 * km, 1.405e1 * kg / (pow<3>(m)) },  { 30.0 * km, 1.115e1 * kg / (pow<3>(m)) },
        { 33.0 * km, 9.0 * kg / (pow<3>(m)) },      { 36.0 * km, 7.15 * kg / (pow<3>(m)) },
        { 39.0 * km, 5.15 * kg / (pow<3>(m)) },     { 42.0 * km, 4.34 * kg / (pow<3>(m)) },
        { 45.0 * km, 3.30 * kg / (pow<3>(m)) },     { 48.0 * km, 2.39 * kg / (pow<3>(m)) },
        { 51.0 * km, 1.88 * kg / (pow<3>(m)) },     { 54.0 * km, 1.38 * kg / (pow<3>(m)) },
        { 57.0 * km, 9.6e-1 * kg / (pow<3>(m)) },   { 60.0 * km, 6.2e-1 * kg / (pow<3>(m)) },
        { 70.0 * km, 1.2e-1 * kg / (pow<3>(m)) },   { 80.0 * km, 1.8e-2 * kg / (pow<3>(m)) },
        { 90.0 * km, 2.3e-3 * kg / (pow<3>(m)) },   { 100.0 * km, 3.1e-4 * kg / (pow<3>(m)) },
        { 110.0 * km, 4.4e-5 * kg / (pow<3>(m)) },  { 120.0 * km, 7.2e-6 * kg / (pow<3>(m)) },
        { 130.0 * km, 1.4e-6 * kg / (pow<3>(m)) },  { 140.0 * km, 3.0e-7 * kg / (pow<3>(m)) },
        { 150.0 * km, 8.0e-8 * kg / (pow<3>(m)) },  { 160.0 * km, 2.6e-8 * kg / (pow<3>(m)) },
        { 170.0 * km, 9.5e-9 * kg / (pow<3>(m)) },  { 180.0 * km, 4.0e-9 * kg / (pow<3>(m)) },
        { 190.0 * km, 1.9e-9 * kg / (pow<3>(m)) },  { 200.0 * km, 9.4e-10 * kg / (pow<3>(m)) },
        { 210.0 * km, 4.9e-10 * kg / (pow<3>(m)) }, { 220.0 * km, 2.6e-10 * kg / (pow<3>(m)) },
        { 230.0 * km, 1.4e-10 * kg / (pow<3>(m)) }, { 240.0 * km, 7.5e-11 * kg / (pow<3>(m)) },
        { 250.0 * km, 5.5e-11 * kg / (pow<3>(m)) }, { 260.0 * km, 4.1e-11 * kg / (pow<3>(m)) },
        { 270.0 * km, 2.2e-11 * kg / (pow<3>(m)) }, { 280.0 * km, 1.2e-11 * kg / (pow<3>(m)) },
        { 290.0 * km, 6.5e-12 * kg / (pow<3>(m)) }, { 300.0 * km, 3.5e-12 * kg / (pow<3>(m)) }
    };

    const auto& position                       = state.get_position_in_frame<frames::venus::venus_fixed>();
    const auto [latitude, longitude, altitude] = convert_body_fixed_to_geodetic(position);

    const auto iter = venutianAtmosphere.upper_bound(altitude);
    return (iter != venutianAtmosphere.end()) ? iter->second : Density::zero();
}

// ---------------------------------------------------------------------------
// Mars
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<planets::Mars>(const State& state)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::kg;
    using mp_units::si::unit_symbols::km;
    using mp_units::si::unit_symbols::m;

    // Altitude Conditions(TABLE 7-4, Vallado)
    static const std::map<Altitude, Density> martianAtmosphere = {
        // km, kg/m^3
        { 2.0 * km, 1.19e-1 * kg / (pow<3>(m)) },  { 4.0 * km, 1.10e-1 * kg / (pow<3>(m)) },
        { 6.0 * km, 1.02e-1 * kg / (pow<3>(m)) },  { 8.0 * km, 9.39e-2 * kg / (pow<3>(m)) },
        { 10.0 * km, 8.64e-2 * kg / (pow<3>(m)) }, { 12.0 * km, 7.93e-2 * kg / (pow<3>(m)) },
        { 14.0 * km, 7.25e-2 * kg / (pow<3>(m)) }, { 16.0 * km, 6.61e-2 * kg / (pow<3>(m)) },
        { 18.0 * km, 6.00e-2 * kg / (pow<3>(m)) }, { 20.0 * km, 5.43e-2 * kg / (pow<3>(m)) },
        { 22.0 * km, 4.89e-2 * kg / (pow<3>(m)) }, { 24.0 * km, 3.91e-2 * kg / (pow<3>(m)) },
        { 26.0 * km, 3.32e-2 * kg / (pow<3>(m)) }, { 28.0 * km, 2.82e-2 * kg / (pow<3>(m)) },
        { 30.0 * km, 2.40e-2 * kg / (pow<3>(m)) }, { 32.0 * km, 2.04e-2 * kg / (pow<3>(m)) },
        { 34.0 * km, 1.73e-2 * kg / (pow<3>(m)) }, { 36.0 * km, 1.47e-2 * kg / (pow<3>(m)) },
        { 38.0 * km, 1.25e-2 * kg / (pow<3>(m)) }, { 40.0 * km, 1.06e-2 * kg / (pow<3>(m)) },
        { 45.0 * km, 7.03e-3 * kg / (pow<3>(m)) }, { 50.0 * km, 4.67e-3 * kg / (pow<3>(m)) },
        { 55.0 * km, 3.10e-3 * kg / (pow<3>(m)) }, { 60.0 * km, 2.06e-3 * kg / (pow<3>(m)) },
        { 65.0 * km, 1.36e-3 * kg / (pow<3>(m)) }, { 70.0 * km, 9.11e-4 * kg / (pow<3>(m)) },
        { 75.0 * km, 6.05e-4 * kg / (pow<3>(m)) }, { 80.0 * km, 4.02e-4 * kg / (pow<3>(m)) }
    };

    const auto& position                       = state.get_position_in_frame<frames::mars::mars_fixed>();
    const auto [latitude, longitude, altitude] = convert_body_fixed_to_geodetic(position);

    Unitless altitudeValue = altitude / astrea::detail::distance_unit;
    if (altitude <= 80.0 * km) {
        const auto iter = martianAtmosphere.upper_bound(altitude);
        return (iter != martianAtmosphere.end()) ? iter->second : Density::zero();
    }
    else if (altitude < 200.0 * km) {
        return exp(-2.55314e-10 * mp_units::pow<5>(altitudeValue) + 2.31927e-7 * mp_units::pow<4>(altitudeValue) -
                   8.33206e-5 * mp_units::pow<3>(altitudeValue) + 0.0151947 * mp_units::pow<2>(altitudeValue) -
                   1.52799 * altitudeValue + 48.69659) *
               kg / mp_units::pow<3>(km);
    }
    else if (altitude < 300.0 * km) {
        return exp(2.65472e-11 * mp_units::pow<5>(altitudeValue) - 2.45558e-8 * mp_units::pow<4>(altitudeValue) +
                   6.31410e-6 * mp_units::pow<3>(altitudeValue) + 4.73359e-4 * mp_units::pow<2>(altitudeValue) -
                   0.443712 * altitudeValue + 23.79408) *
               kg / mp_units::pow<3>(km);
    }
    else {
        return Density::zero();
    }
}

// ---------------------------------------------------------------------------
// Titan
// ---------------------------------------------------------------------------

template <>
inline Density find_atmospheric_density<moons::Titan>(const State& state)
{
    using namespace mp_units;
    using mp_units::si::unit_symbols::cm;
    using mp_units::si::unit_symbols::g;
    using mp_units::si::unit_symbols::km;

    using TitanDensity = quantity<g / pow<3>(cm)>;

    // Altitude Conditions(TABLE 7-4, Vallado)
    static const std::map<Altitude, TitanDensity> titanicAtmosphere = {
        // km, g/cm^3
        { 780.0 * km, 1.00e-12 * g / (pow<3>(cm)) },  { 790.0 * km, 8.45e-12 * g / (pow<3>(cm)) },
        { 800.0 * km, 7.16e-12 * g / (pow<3>(cm)) },  { 810.0 * km, 6.08e-12 * g / (pow<3>(cm)) },
        { 820.0 * km, 5.17e-12 * g / (pow<3>(cm)) },  { 830.0 * km, 4.41e-12 * g / (pow<3>(cm)) },
        { 840.0 * km, 3.77e-12 * g / (pow<3>(cm)) },  { 850.0 * km, 3.23e-12 * g / (pow<3>(cm)) },
        { 860.0 * km, 2.78e-12 * g / (pow<3>(cm)) },  { 870.0 * km, 2.39e-12 * g / (pow<3>(cm)) },
        { 880.0 * km, 2.06e-12 * g / (pow<3>(cm)) },  { 890.0 * km, 1.78e-12 * g / (pow<3>(cm)) },
        { 900.0 * km, 1.54e-12 * g / (pow<3>(cm)) },  { 910.0 * km, 1.34e-12 * g / (pow<3>(cm)) },
        { 920.0 * km, 1.16e-12 * g / (pow<3>(cm)) },  { 930.0 * km, 1.01e-12 * g / (pow<3>(cm)) },
        { 940.0 * km, 8.80e-13 * g / (pow<3>(cm)) },  { 950.0 * km, 7.67e-13 * g / (pow<3>(cm)) },
        { 960.0 * km, 6.69e-13 * g / (pow<3>(cm)) },  { 970.0 * km, 5.84e-13 * g / (pow<3>(cm)) },
        { 980.0 * km, 5.10e-13 * g / (pow<3>(cm)) },  { 990.0 * km, 4.46e-13 * g / (pow<3>(cm)) },
        { 1000.0 * km, 3.90e-13 * g / (pow<3>(cm)) }, { 1010.0 * km, 1.81e-13 * g / (pow<3>(cm)) },
        { 1020.0 * km, 2.99e-13 * g / (pow<3>(cm)) }, { 1030.0 * km, 2.62e-13 * g / (pow<3>(cm)) },
        { 1040.0 * km, 2.30e-13 * g / (pow<3>(cm)) }, { 1050.0 * km, 2.02e-13 * g / (pow<3>(cm)) },
        { 1060.0 * km, 1.78e-13 * g / (pow<3>(cm)) }, { 1070.0 * km, 1.56e-13 * g / (pow<3>(cm)) },
        { 1080.0 * km, 1.38e-13 * g / (pow<3>(cm)) }, { 1090.0 * km, 1.21e-13 * g / (pow<3>(cm)) },
        { 1100.0 * km, 1.07e-13 * g / (pow<3>(cm)) }, { 1110.0 * km, 9.43e-14 * g / (pow<3>(cm)) },
        { 1120.0 * km, 8.33e-14 * g / (pow<3>(cm)) }, { 1130.0 * km, 7.36e-14 * g / (pow<3>(cm)) },
        { 1140.0 * km, 6.51e-14 * g / (pow<3>(cm)) }, { 1150.0 * km, 5.76e-14 * g / (pow<3>(cm)) },
        { 1160.0 * km, 5.10e-14 * g / (pow<3>(cm)) }, { 1170.0 * km, 4.52e-14 * g / (pow<3>(cm)) },
        { 1180.0 * km, 4.01e-14 * g / (pow<3>(cm)) }, { 1190.0 * km, 3.56e-14 * g / (pow<3>(cm)) },
        { 1200.0 * km, 3.16e-14 * g / (pow<3>(cm)) }, { 1210.0 * km, 2.81e-14 * g / (pow<3>(cm)) },
        { 1220.0 * km, 2.50e-14 * g / (pow<3>(cm)) }, { 1230.0 * km, 2.22e-14 * g / (pow<3>(cm)) },
        { 1240.0 * km, 1.98e-14 * g / (pow<3>(cm)) }, { 1250.0 * km, 1.77e-14 * g / (pow<3>(cm)) },
        { 1260.0 * km, 1.58e-14 * g / (pow<3>(cm)) }, { 1270.0 * km, 1.41e-14 * g / (pow<3>(cm)) },
        { 1280.0 * km, 1.26e-14 * g / (pow<3>(cm)) }, { 1290.0 * km, 1.12e-14 * g / (pow<3>(cm)) },
        { 1300.0 * km, 1.00e-14 * g / (pow<3>(cm)) }
    };

    const auto& position                       = state.get_position_in_frame<frames::titan::titan_fixed>();
    const auto [latitude, longitude, altitude] = convert_body_fixed_to_geodetic(position);

    const auto iter = titanicAtmosphere.upper_bound(altitude);
    return (iter != titanicAtmosphere.end()) ? iter->second : 0.0 * g / (cm * cm * cm);
}

} // namespace astro
} // namespace astrea
```


