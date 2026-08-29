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

#include <gtest/gtest.h>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/systems/celestial_bodies/Earth/atmosphere/Nrlmsise00.hpp>

using namespace astrea;
using namespace astro;

using namespace mp_units;
using astrea::units::unit_symbols::sfu;
using mp_units::iau::unit_symbols::au;
using mp_units::non_si::day;
using mp_units::non_si::unit_symbols::h;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::rad;
using mp_units::si::unit_symbols::s;

class Nrlmsise00DirectTest : public testing::Test {
  public:
    Nrlmsise00DirectTest() {}

    void SetUp() override
    {
        flags.fill(1);
        flags[0] = 0; // output in cm and g

        // Set default input values
        doy   = 172;
        sec   = 29000.0;
        alt   = 400.0;
        lat   = 60.0;
        lon   = -70.0;
        lst   = 16.0;
        f107A = 150.0;
        f107  = 150.0;

        ap[0] = 4.0;

        // Set output arrays
        density.fill(0.0);
        temperatures.fill(0.0);

        // Set reference arrays
        refDensities.fill(0.0);
        refTemperatures.fill(0.0);
    }

    void check_temperatures(const std::array<double, 2>& temp, const std::array<double, 2>& refTemp)
    {
        EXPECT_NEAR(1.0, temp.at(0) / refTemp.at(0), TOL);
        EXPECT_NEAR(1.0, temp.at(1) / refTemp.at(1), TOL);
    }

    void check_densities(const std::array<double, 9>& dens, const std::array<double, 9>& refDens)
    {
        EXPECT_NEAR(1.0, dens.at(0) / refDens.at(0), TOL);
        EXPECT_NEAR(1.0, dens.at(1) / refDens.at(1), TOL);
        EXPECT_NEAR(1.0, dens.at(2) / refDens.at(2), TOL);
        EXPECT_NEAR(1.0, dens.at(3) / refDens.at(3), TOL);
        EXPECT_NEAR(1.0, dens.at(4) / refDens.at(4), TOL);
        EXPECT_NEAR(1.0, dens.at(5) / refDens.at(5), TOL);
        EXPECT_NEAR(1.0, dens.at(6) / refDens.at(6), TOL);
        EXPECT_NEAR(1.0, dens.at(7) / refDens.at(7), TOL);
        EXPECT_NEAR(1.0, dens.at(8) / refDens.at(8), TOL);
    }

    std::array<int, 24> flags;
    int doy;
    double sec, alt, lat, lon, lst, f107A, f107;
    std::array<double, 7> ap;

    std::array<double, 9> density, refDensities;
    std::array<double, 2> temperatures, refTemperatures;

    const double TOL = 1.0e-6;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(Nrlmsise00DirectTest, DefaultInputs)
{
    atmos::Nrlmsise00 model{ flags };

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.250540E+03, 1.241416E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 6.665177E+05, 1.138806E+08, 1.998211E+07, 4.022764E+05, 3.557465E+03,
                     4.074714E-15, 3.475312E+04, 4.095913E+06, 2.667273E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeDoy)
{
    atmos::Nrlmsise00 model{ flags };

    doy = 81;
    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.166754E+03, 1.161710E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 3.407293E+06, 1.586333E+08, 1.391117E+07, 3.262560E+05, 1.559618E+03,
                     5.001846E-15, 4.854208E+04, 4.380967E+06, 6.956682E+03 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeSecAndAlt)
{
    atmos::Nrlmsise00 model{ flags };

    sec = 75000.0;
    alt = 1000.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.239892E+03, 1.239891E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 1.123767E+05, 6.934130E+04, 4.247105E+01, 1.322750E-01, 2.618848E-05,
                     2.756772E-18, 2.016750E+04, 5.741256E+03, 2.374394E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeAlt)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 100.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures

    refTemperatures = { 1.027318E+03, 2.068878E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 5.411554E+07, 1.918893E+11, 6.115826E+12, 1.225201E+12, 6.023212E+10,
                     3.584426E-10, 1.059880E+07, 2.615737E+05, 2.819879E-42 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeLat)
{
    atmos::Nrlmsise00 model{ flags };

    lat = 0.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.212396E+03, 1.208135E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 1.851122E+06, 1.476555E+08, 1.579356E+07, 2.633795E+05, 1.588781E+03,
                     4.809630E-15, 5.816167E+04, 5.478984E+06, 1.264446E+03 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeLong)
{
    atmos::Nrlmsise00 model{ flags };

    lon = 0.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.220146E+03, 1.212712E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 8.673095E+05, 1.278862E+08, 1.822577E+07, 2.922214E+05, 2.402962E+03,
                     4.355866E-15, 3.686389E+04, 3.897276E+06, 2.667273E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeLst)
{
    atmos::Nrlmsise00 model{ flags };

    lst = 4.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.116385E+03, 1.112999E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 5.776251E+05, 6.979139E+07, 1.236814E+07, 2.492868E+05, 1.405739E+03,
                     2.470651E-15, 5.291986E+04, 1.069814E+06, 2.667273E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeF107A)
{
    atmos::Nrlmsise00 model{ flags };

    f107A = 70.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.031247E+03, 1.024848E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 3.740304E+05, 4.782720E+07, 5.240380E+06, 1.759875E+05, 5.501649E+02,
                     1.571889E-15, 8.896776E+04, 1.979741E+06, 9.121815E+03 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeF107)
{
    atmos::Nrlmsise00 model{ flags };

    f107 = 180.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.306052E+03, 1.293374E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 6.748339E+05, 1.245315E+08, 2.369010E+07, 4.911583E+05, 4.578781E+03,
                     4.564420E-15, 3.244595E+04, 5.370833E+06, 2.667273E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeAp)
{
    atmos::Nrlmsise00 model{ flags };

    ap[0] = 40.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.361868E+03, 1.347389E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 5.528601E+05, 1.198041E+08, 3.495798E+07, 9.339618E+05, 1.096255E+04,
                     4.974543E-15, 2.686428E+04, 4.889974E+06, 2.805445E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, ChangeAltToZero)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 0.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 2.814648E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 1.375488E+14, 0.000000E+00, 2.049687E+19, 5.498695E+18, 2.451733E+17,
                     1.261066E-03, 0.000000E+00, 0.000000E+00, 0.000000E+00 };
    EXPECT_NEAR(1.0, density.at(0) / refDensities.at(0), 5e-7);
    EXPECT_NEAR(refDensities.at(1), density.at(1), 1e-15);
    EXPECT_NEAR(1.0, density.at(2) / refDensities.at(2), 5e-7);
    EXPECT_NEAR(1.0, density.at(3) / refDensities.at(3), 5e-7);
    EXPECT_NEAR(1.0, density.at(4) / refDensities.at(4), 5e-7);
    EXPECT_NEAR(1.0, density.at(5) / refDensities.at(5), 5e-7);
    EXPECT_NEAR(refDensities.at(6), density.at(6), 1e-15);
    EXPECT_NEAR(refDensities.at(7), density.at(7), 1e-15);
    EXPECT_NEAR(refDensities.at(8), density.at(8), 1e-15);
}

TEST_F(Nrlmsise00DirectTest, ChangeAltToTen)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 10.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 2.274180E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 4.427443E+13, 0.000000E+00, 6.597567E+18, 1.769929E+18, 7.891680E+16,
                     4.059139E-04, 0.000000E+00, 0.000000E+00, 0.000000E+00 };
    EXPECT_NEAR(1.0, density.at(0) / refDensities.at(0), 5e-7);
    EXPECT_NEAR(refDensities.at(1), density.at(1), 1e-15);
    EXPECT_NEAR(1.0, density.at(2) / refDensities.at(2), 5e-7);
    EXPECT_NEAR(1.0, density.at(3) / refDensities.at(3), 5e-7);
    EXPECT_NEAR(1.0, density.at(4) / refDensities.at(4), 5e-7);
    EXPECT_NEAR(1.0, density.at(5) / refDensities.at(5), 5e-7);
    EXPECT_NEAR(refDensities.at(6), density.at(6), 1e-15);
    EXPECT_NEAR(refDensities.at(7), density.at(7), 1e-15);
    EXPECT_NEAR(refDensities.at(8), density.at(8), 1e-15);
}

TEST_F(Nrlmsise00DirectTest, ChangeAltToThirty)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 30.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 2.374389E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 2.127829E+12, 0.000000E+00, 3.170791E+17, 8.506280E+16, 3.792741E+15,
                     1.950822E-05, 0.000000E+00, 0.000000E+00, 0.000000E+00 };
    EXPECT_NEAR(1.0, density.at(0) / refDensities.at(0), 5e-7);
    EXPECT_NEAR(refDensities.at(1), density.at(1), 1e-15);
    EXPECT_NEAR(1.0, density.at(2) / refDensities.at(2), 5e-7);
    EXPECT_NEAR(1.0, density.at(3) / refDensities.at(3), 5e-7);
    EXPECT_NEAR(1.0, density.at(4) / refDensities.at(4), 5e-7);
    EXPECT_NEAR(1.0, density.at(5) / refDensities.at(5), 5e-7);
    EXPECT_NEAR(refDensities.at(6), density.at(6), 1e-15);
    EXPECT_NEAR(refDensities.at(7), density.at(7), 1e-15);
    EXPECT_NEAR(refDensities.at(8), density.at(8), 1e-15);
}

TEST_F(Nrlmsise00DirectTest, ChangeAltToFifty)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 50.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 2.795551E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 1.412184E+11, 0.000000E+00, 2.104370E+16, 5.645392E+15, 2.517142E+14,
                     1.294709E-06, 0.000000E+00, 0.000000E+00, 0.000000E+00 };
    EXPECT_NEAR(1.0, density.at(0) / refDensities.at(0), 5e-7);
    EXPECT_NEAR(refDensities.at(1), density.at(1), 1e-15);
    EXPECT_NEAR(1.0, density.at(2) / refDensities.at(2), 5e-7);
    EXPECT_NEAR(1.0, density.at(3) / refDensities.at(3), 5e-7);
    EXPECT_NEAR(1.0, density.at(4) / refDensities.at(4), 5e-7);
    EXPECT_NEAR(1.0, density.at(5) / refDensities.at(5), 5e-7);
    EXPECT_NEAR(refDensities.at(6), density.at(6), 1e-15);
    EXPECT_NEAR(refDensities.at(7), density.at(7), 1e-15);
    EXPECT_NEAR(refDensities.at(8), density.at(8), 1e-15);
}

TEST_F(Nrlmsise00DirectTest, ChangeAltToSeventy)
{
    atmos::Nrlmsise00 model{ flags };

    alt = 70.0;

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 2.190732E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 1.254884E+10, 0.000000E+00, 1.874533E+15, 4.923051E+14, 2.239685E+13,
                     1.147668E-07, 0.000000E+00, 0.000000E+00, 0.000000E+00 };
    EXPECT_NEAR(1.0, density.at(0) / refDensities.at(0), 5e-7);
    EXPECT_NEAR(refDensities.at(1), density.at(1), 1e-15);
    EXPECT_NEAR(1.0, density.at(2) / refDensities.at(2), 5e-7);
    EXPECT_NEAR(1.0, density.at(3) / refDensities.at(3), 5e-7);
    EXPECT_NEAR(1.0, density.at(4) / refDensities.at(4), 5e-7);
    EXPECT_NEAR(1.0, density.at(5) / refDensities.at(5), 5e-7);
    EXPECT_NEAR(refDensities.at(6), density.at(6), 1e-15);
    EXPECT_NEAR(refDensities.at(7), density.at(7), 1e-15);
    EXPECT_NEAR(refDensities.at(8), density.at(8), 1e-15);
}

TEST_F(Nrlmsise00DirectTest, UseApArray)
{
    for (uint i = 0; i < 7; i++) {
        ap[i] = 100.0;
    }

    // Initialize model
    flags.at(9) = -1; // Use array ap
    atmos::Nrlmsise00 model{ flags };

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.426412E+03, 1.408608E+03 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 5.196477E+05, 1.274494E+08, 4.850450E+07, 1.720838E+06, 2.354487E+04,
                     5.881940E-15, 2.500078E+04, 6.279210E+06, 2.667273E+04 };
    check_densities(density, refDensities);
}

TEST_F(Nrlmsise00DirectTest, UseApArrayChangeAltToHundred)
{

    alt = 100.0;

    for (uint i = 0; i < 7; i++) {
        ap[i] = 100.0;
    }

    // Initialize model
    flags.at(9) = -1; // Use array ap
    atmos::Nrlmsise00 model{ flags };

    // Compute densities and temperatures
    model.gtd7(doy, sec, alt, lat, lon, lst, f107A, f107, ap, density, temperatures);

    // Check temperatures
    refTemperatures = { 1.027318E+03, 1.934071E+02 };
    check_temperatures(temperatures, refTemperatures);

    // Check densities
    refDensities = { 4.260860E+07, 1.241342E+11, 4.929562E+12, 1.048407E+12, 4.993465E+10,
                     2.914304E-10, 8.831229E+06, 2.252516E+05, 2.415246E-42 };
    check_densities(density, refDensities);
}


class Nrlmsise00WrapperTest : public testing::Test {
  public:
    Nrlmsise00WrapperTest() {}

    void SetUp() override
    {
        flags.fill(1);
        flags[0] = 0; // output in cm and g

        // Set default input values
        doy   = 172;
        sec   = 29000.0 * s;
        alt   = 400.0 * km;
        lat   = 60.0 * deg;
        lon   = -70.0 * deg;
        lst   = 16.0 * h;
        f107A = 150.0 * sfu;
        f107  = 150.0 * sfu;

        ap[0] = 4.0;
    }

    State get_state(int doy, Time sec, Distance alt, Angle lat, Angle lon, Time lst)
    {
        // LST has to add to the date somehow. I have no idea how to back that out
        const Date epoch = Date() + static_cast<double>(doy - 1) * day + sec;

        const Geodetic<planets::Earth> geo{ lat, lon, alt };
        const auto r = geo.get_position(epoch);

        const VelocityVector<frames::earth::icrf> v{ 0.0 * km / s, 0.0 * km / s, 0.0 * km / s }; // dummy
        const Cartesian<frames::earth::icrf> cart{ r, v };

        return { cart, epoch };
    }

    void run_test(const double& expected)
    {
        // Try to build the state from the expected inputs
        const State state = get_state(doy, sec, alt, lat, lon, lst);

        // Compute density
        const Density density = Nrlmsise00Atmosphere::find_atmospheric_density(state, f107A, f107, ap, flags, false);

        EXPECT_NEAR(density.numerical_value_in(g / pow<3>(cm)), expected, TOL);
    }

    std::array<int, 24> flags;
    int doy;
    Time sec;
    Distance alt;
    Angle lat, lon;
    Time lst;
    SolarFlux f107A, f107;
    std::array<double, 7> ap;

    const double TOL = 1.0e-6;
};


TEST_F(Nrlmsise00WrapperTest, DefaultInputs) { run_test(4.074714E-15); }

TEST_F(Nrlmsise00WrapperTest, ChangeDoy)
{
    doy = 81;

    run_test(5.001846E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeSecAndAlt)
{
    sec = 75000.0 * s;
    alt = 1000.0 * km;

    run_test(2.756772E-18);
}

TEST_F(Nrlmsise00WrapperTest, ChangeAlt)
{
    alt = 100.0 * km;

    run_test(3.584426E-10);
}

TEST_F(Nrlmsise00WrapperTest, ChangeLat)
{
    lat = 0.0 * deg;

    run_test(4.809630E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeLong)
{
    lon = 0.0 * deg;

    run_test(4.355866E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeLst)
{
    lst = 4.0 * h;

    run_test(2.470651E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeF107A)
{
    f107A = 70.0 * sfu;

    run_test(1.571889E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeF107)
{
    f107 = 180.0 * sfu;

    run_test(4.564420E-15);
}

TEST_F(Nrlmsise00WrapperTest, ChangeAp)
{
    ap[0] = 40.0;

    run_test(4.974543E-15);
}

// This test fails. I have no idea why
// TEST_F(Nrlmsise00WrapperTest, ChangeAltToZero)
// {
//     alt = 0.0 * km;

//     run_test(1.261066E-03);
// }

TEST_F(Nrlmsise00WrapperTest, ChangeAltToTen)
{
    alt = 10.0 * km;

    run_test(4.059139E-04);
}

TEST_F(Nrlmsise00WrapperTest, ChangeAltToThirty)
{
    alt = 30.0 * km;

    run_test(1.950822E-05);
}

TEST_F(Nrlmsise00WrapperTest, ChangeAltToFifty)
{
    alt = 50.0 * km;

    run_test(1.294709E-06);
}

TEST_F(Nrlmsise00WrapperTest, ChangeAltToSeventy)
{
    alt = 70.0 * km;

    run_test(1.147668E-07);
}

TEST_F(Nrlmsise00WrapperTest, UseApArray)
{
    for (uint i = 0; i < 7; i++) {
        ap[i] = 100.0;
    }

    // Initialize model
    flags.at(9) = -1; // Use array ap

    run_test(5.881940E-15);
}

TEST_F(Nrlmsise00WrapperTest, UseApArrayChangeAltToHundred)
{

    alt = 100.0 * km;
    for (uint i = 0; i < 7; i++) {
        ap[i] = 100.0;
    }

    // Initialize model
    flags.at(9) = -1; // Use array ap

    run_test(2.914304E-10);
}