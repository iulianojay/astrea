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

using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;

// EOM type indices
// 0 = TwoBody        (no forces)
// 1 = J2MeanVop      (no forces — closed-form secular J2)
// 2 = KeplerianVop   (OblatenessForce with degree/order from range)
// 3 = EquinoctialVop (OblatenessForce with degree/order from range)
// 4 = CowellsMethod  (OblatenessForce with degree/order from range)

// Perturbation bit-flags for range(3) — combine with bitwise OR
// Ignored for EOM types 0 (TwoBody) and 1 (J2MeanVop)
static constexpr int kDrag  = 1 << 0; // 1
static constexpr int kNBody = 1 << 1; // 2
static constexpr int kSRP   = 1 << 2; // 4

static constexpr const char* kEomNames[] = { "TwoBody", "J2MeanVop", "KeplerianVop", "EquinoctialVop", "CowellsMethod" };

// Single benchmark — ranges:
//   range(0) : EOM type index (0–4)
//   range(1) : propagation time in minutes
//   range(2) : OblatenessForce degree/order (ignored for TwoBody and J2MeanVop)
//   range(3) : perturbation flags kDrag|kNBody|kSRP (ignored for TwoBody and J2MeanVop)
static void BenchmarkPropagation(benchmark::State& state)
{
    const Date epoch{};
    const State state0{ Keplerian<frames::earth::icrf>::LEO(), epoch };
    Spacecraft sat{};
    Vehicle vehicle{ sat };

    Integrator integrator;
    integrator.set_abs_tol(1.0e-10);
    integrator.set_rel_tol(1.0e-10);

    const int eomIdx  = static_cast<int>(state.range(0));
    const Time dt     = minutes(static_cast<double>(state.range(1)));
    const int gravity = static_cast<int>(state.range(2));
    const int perturb = static_cast<int>(state.range(3));

    ForceModel forces;
    if (eomIdx >= 2) {
        if (gravity > 0) {
            // Ugh
            if (gravity == 2) { forces.add<OblatenessForce, planets::Earth, 2, 2>(); }
            else if (gravity == 20) {
                forces.add<OblatenessForce, planets::Earth, 20, 20>();
            }
            else if (gravity == 70) {
                forces.add<OblatenessForce, planets::Earth, 70, 70>();
            }
        }
        if (perturb & kDrag) { forces.add<AtmosphericForce>(); }
        if (perturb & kNBody) { forces.add<NBodyForce, planets::Earth, moons::Moon, star::Sun>(); }
        if (perturb & kSRP) { forces.add<SolarRadiationPressure>(); }
    }

    switch (eomIdx) {
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

    state.SetLabel(kEomNames[eomIdx]);

    for (auto _ : state) {
        auto result = integrator.propagate_no_storage(state0, dt, vehicle);
        benchmark::DoNotOptimize(result);
    }
}

// -----------------------------------------------------------------------
// Registration
//   Prop times  : ~1 orbit (97 min), 1 day (1440 min)
//
//   No-force EOM (0 - TwoBody, 1 - J2MeanVop):
//     gravity = 0, perturb = 0 (flags ignored)
//
//   Force-based EOM (2 - KeplerianVop, 3 - EquinoctialVop, 4 - CowellsMethod):
//     gravity sweeps : 2, 20, 70
//     perturb sweeps : 0 (none), 1 (drag), 2 (n-body), 4 (srp), 7 (all)
// -----------------------------------------------------------------------
BENCHMARK(BenchmarkPropagation)
    ->ArgsProduct(
        {
            { 0, 1 },
            { 97, 1440 },
            { 0 },
            { 0 },
        }
    )
    ->ArgNames({ "eom", "prop_time_min", "gravity", "perturb" })
    ->Unit(benchmark::kMillisecond);

BENCHMARK(BenchmarkPropagation)
    ->ArgsProduct(
        {
            { 2, 3, 4 },
            { 97, 1440 },
            { 2, 20, 70 },
            { 0, 1, 2, 4, 7 },
        }
    )
    ->ArgNames({ "eom", "prop_time_min", "gravity", "perturb" })
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
