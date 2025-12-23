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

#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/TwoBody.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

#include <tests/nasa_6dof_checkcases/helpers/AtmosphericCheckcase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/CheckcaseDatabase.hpp>
#include <tests/nasa_6dof_checkcases/helpers/OrbitalCheckcase.hpp>

using namespace astrea;
using namespace astro;
using namespace astro::tests;

using namespace sqlite_orm;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::W;


class Orbital6DofTest : public testing::Test {
  public:
    Orbital6DofTest() :
        mu(sys.get_mu()),
        epoch("2007/324:00:00:00", "%Y/%j:%H:%M:%S"),
        circular(
            RadiusVector<frames::earth::icrf>(-4292.65341 * km, 955.16847 * km, 5139.35657 * km),
            VelocityVector<frames::earth::icrf>(0.109649663 * km / s, -7.527726490 * km / s, 1.484521489 * km / s)
        ),
        elliptic(
            RadiusVector<frames::earth::icrf>(-4315.96774 * km, 960.35620 * km, 5167.26953 * km),
            VelocityVector<frames::earth::icrf>(0.129091037 * km / s, -7.491513855 * km / s, 1.452515654 * km / s)
        ),
        propInterval(0.0 * s, 28800.0 * s)
    {
    }

    void SetUp() override { integrator.set_timestep(60.0 * s); }

    const Unitless REL_TOL = 1.0e-6;
    const Unitless ABS_TOL = 1.0e-2;

    AstrodynamicsSystem sys;
    GravParam mu;
    Date epoch;
    Cartesian circular;
    Cartesian elliptic;
    Interval propInterval;
    Integrator integrator;
};


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST_F(Orbital6DofTest, Checkcase2Propagation)
{
    // Circular initial conditions
    Spacecraft sat({ Cartesian(circular, mu), epoch, sys });
    Vehicle vehicle{ sat };

    // Setup Propagator
    TwoBody eom(sys);
    ForceModel forces;
    const auto stateHistory = integrator.propagate(epoch, propInterval, eom, vehicle, true);

    // Grab history from database
    auto ccdb = get_checkcase_database();
    ccdb.sync_schema();

    auto checkcases = ccdb.get_all<OrbitalCheckcase>(where(like(&OrbitalCheckcase::name, "Orbit_02%%")));

    for (const auto& checkcase : checkcases) {

    }
}
