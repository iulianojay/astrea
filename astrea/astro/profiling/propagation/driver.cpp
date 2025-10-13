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

#include <benchmark/benchmark.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/propagation/equations_of_motion/CowellsMethod.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/numerical/Integrator.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Interval.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

class BenchmarkPropagation : public benchmark::Fixture {
  public:
    void SetUp(::benchmark::State& bmState) { interval = { days(0), days(1) }; }

    void TearDown(::benchmark::State& bmState) {}

    void propagate(::benchmark::State& bmState, const State& state0, const Interval& interval, const EquationsOfMotion& eom)
    {
        Spacecraft sat(state0);
        Vehicle vehicle{ sat };
        for (auto _ : bmState) {
            integrator.propagate(epoch, interval, eom, vehicle, true);
        }
    }

    AstrodynamicsSystem sys;
    ForceModel forces;
    Integrator integrator;
    Interval interval;
    Date epoch;
};

BENCHMARK_F(BenchmarkPropagation, CowellsMethodNoForcesLEO)(benchmark::State& bmState)
{
    CowellsMethod eom(sys, forces);
    State state0{ { Keplerian::LEO() }, epoch, sys };
    propagate(bmState, state0, interval, eom);
}

BENCHMARK_F(BenchmarkPropagation, CowellsMethodNoForcesLMEO)(benchmark::State& bmState)
{
    CowellsMethod eom(sys, forces);
    State state0{ { Keplerian::LMEO() }, epoch, sys };
    propagate(bmState, state0, interval, eom);
}

BENCHMARK_F(BenchmarkPropagation, CowellsMethodNoForcesGPS)(benchmark::State& bmState)
{
    CowellsMethod eom(sys, forces);
    State state0{ { Keplerian::GPS() }, epoch, sys };
    propagate(bmState, state0, interval, eom);
}

BENCHMARK_F(BenchmarkPropagation, CowellsMethodNoForcesHMEO)(benchmark::State& bmState)
{
    CowellsMethod eom(sys, forces);
    State state0{ { Keplerian::HMEO() }, epoch, sys };
    propagate(bmState, state0, interval, eom);
}

BENCHMARK_F(BenchmarkPropagation, CowellsMethodNoForcesGEO)(benchmark::State& bmState)
{
    CowellsMethod eom(sys, forces);
    State state0{ { Keplerian::GEO() }, epoch, sys };
    propagate(bmState, state0, interval, eom);
}