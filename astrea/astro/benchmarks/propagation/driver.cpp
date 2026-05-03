/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <benchmark/benchmark.h>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::km;

// EOM type indices
// 0 = TwoBody        (no forces)
// 1 = J2MeanVop      (no forces — closed-form secular J2)
// 2 = KeplerianVop   (OblatenessForce with degree/order from range)
// 3 = EquinoctialVop (OblatenessForce with degree/order from range)
// 4 = CowellsMethod  (OblatenessForce with degree/order from range)

static constexpr const char* kEomNames[] = { "TwoBody", "J2MeanVop", "KeplerianVop", "EquinoctialVop", "CowellsMethod" };

// Single benchmark — ranges:
//   range(0) : EOM type index (0–4)
//   range(1) : propagation time in minutes
//   range(2) : OblatenessForce degree/order (ignored for TwoBody and J2MeanVop)
static void BM_Propagation(benchmark::State& state)
{
    AstrodynamicsSystem sys{};
    const Date epoch{};
    const State state0{ Keplerian::LEO(), epoch, sys };
    Spacecraft sat{};
    Vehicle vehicle{ sat };

    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    const int eom_idx = static_cast<int>(state.range(0));
    const Time dt     = minutes(static_cast<double>(state.range(1)));
    const int gravity = static_cast<int>(state.range(2));

    ForceModel forces;
    if (eom_idx >= 2 && gravity > 0) forces.add<OblatenessForce>(sys, gravity, gravity);

    switch (eom_idx) {
        case 0: {
            TwoBody eom;
            integrator.set_equations_of_motion(eom);
            break;
        }
        case 1: {
            J2MeanVop eom;
            integrator.set_equations_of_motion(eom);
            break;
        }
        case 2: {
            KeplerianVop eom(forces, false);
            integrator.set_equations_of_motion(eom);
            break;
        }
        case 3: {
            EquinoctialVop eom(forces);
            integrator.set_equations_of_motion(eom);
            break;
        }
        case 4: {
            CowellsMethod eom(forces);
            integrator.set_equations_of_motion(eom);
            break;
        }
    }

    state.SetLabel(kEomNames[eom_idx]);

    for (auto _ : state) {
        auto result = integrator.propagate_no_storage(state0, dt, vehicle);
        benchmark::DoNotOptimize(result);
    }
}

// -----------------------------------------------------------------------
// Registration
//   Prop times : ~1 orbit (97 min), 1 day (1440 min), 1 week (10080 min)
//
//   No-force EOM (TwoBody, J2MeanVop): gravity arg unused, registered as 0
//   Force-based EOM: gravity sweeps 2, 20, 70
// -----------------------------------------------------------------------
BENCHMARK(BM_Propagation)
    ->ArgsProduct(
        {
            { 0, 1 },
            { 97, 1440, 10080 },
            { 0 },
        }
    )
    ->ArgNames({ "eom", "prop_time_min", "gravity" })
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BM_Propagation)
    ->ArgsProduct(
        {
            { 2, 3, 4 },
            { 97, 1440, 10080 },
            { 2, 20, 70 },
        }
    )
    ->ArgNames({ "eom", "prop_time_min", "gravity" })
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
