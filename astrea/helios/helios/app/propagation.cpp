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

#include <helios/app/propagation.hpp>

#include <units/units.hpp>

using namespace astrea;
using namespace astro;
using namespace helios;

using namespace mp_units;
using mp_units::si::unit_symbols::deg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::min;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace helios {

inline constexpr struct AppFrame
    : FixedOffsetFrame<frames::primary, Angle(90.0 * deg), Angle::zero(), Angle::zero(), RotationSequence::XYZ> {
} AppFrame;

PropagationResult propagate_many_objects(const std::vector<GeneralPerturbations>& gpObjects, const PropagationSettings& settings)
{
    std::cout << "[helios] Propagation settings:\n";
    std::cout << "  Propagation time: " << settings.propTime.in(min) << " min\n";
    std::cout << "  Output step:      " << settings.step.in(min) << " min\n";
    std::cout << "  Force model:\n";
    std::cout << "\t - Oblateness "
              << (settings.ten    ? "10x10" :
                  settings.fourty ? "40x40" :
                  settings.eighty ? "80x80" :
                                    "OFF")
              << "\n";
    std::cout << "\t - Solar Radiation Pressure " << (settings.srp ? "ON" : "OFF") << "\n";
    std::cout << "\t - N-Body (Moon, Sun) " << (settings.nBody ? "ON" : "OFF") << "\n";
    std::cout << "\t - Atmospheric Drag " << (settings.drag ? "ON" : "OFF") << "\n";

    const Time propTime = settings.propTime;
    const Time stepTime = settings.step;

    const std::size_t nExpectedFrames =
        static_cast<std::size_t>(propTime.numerical_value_in(s) / stepTime.numerical_value_in(s)) + 1;

    const std::size_t objectCount = gpObjects.size();
    PropagationResult result;
    result.nFrames = nExpectedFrames;
    result.frames.assign(nExpectedFrames, AnimationFrame{ std::vector<Point3>(objectCount, { 0.0, 0.0, 0.0 }) });

    const auto start = std::chrono::steady_clock::now();

    double maxRadius = 0.0;

#pragma omp parallel reduction(max : maxRadius)
    {
        Integrator integrator;
        integrator.set_abs_tol(1.0e-10);
        integrator.set_rel_tol(1.0e-10);

        if (settings.ten || settings.fourty || settings.eighty || settings.srp || settings.nBody || settings.drag) {
            ForceModel forceModel;
            if (settings.eighty) { forceModel.add<OblatenessForce, planets::Earth, 80, 80>(); }
            else if (settings.fourty) {
                forceModel.add<OblatenessForce, planets::Earth, 40, 40>();
            }
            else if (settings.ten) {
                forceModel.add<OblatenessForce, planets::Earth, 10, 10>();
            }
            if (settings.srp) { forceModel.add<SolarRadiationPressure>(); }
            if (settings.nBody) { forceModel.add<NBodyForce, moons::Moon, star::Sun>(); }
            if (settings.drag) { forceModel.add<AtmosphericForce, planets::Earth>(); }
            EquinoctialVop equinoctialVop{ forceModel };
            integrator.set_equations_of_motion(equinoctialVop);
        }
        else {
            J2MeanVop j2mean;
            integrator.set_equations_of_motion(j2mean);
        }
        integrator.switch_fixed_timestep(true, stepTime);

#pragma omp for schedule(dynamic, 64)
        for (std::size_t ii = 0; ii < objectCount; ++ii) {
            try {
                Spacecraft sc(gpObjects[ii]);
                Vehicle vehicle{ sc };
                const State state0         = sc.get_initial_state();
                const StateHistory history = integrator.propagate(state0, propTime, vehicle);

                std::size_t frameIdx = 0;
                for (const auto& state : history) {
                    if (frameIdx >= nExpectedFrames) break;
                    // TODO: Do this rotation here for speed
                    const auto rApp = state.get_position();
                    // const auto rApp             = state.get_position_in_frame<AppFrame>();
                    const double R = rApp.norm().numerical_value_in(km);
                    const double x = rApp.get_x().numerical_value_in(km);
                    const double y = rApp.get_y().numerical_value_in(km);
                    const double z = rApp.get_z().numerical_value_in(km);

                    result.frames[frameIdx][ii] = { x, y, z };
                    maxRadius                   = std::max(maxRadius, R);
                    ++frameIdx;
                }
                for (; frameIdx > 0 && frameIdx < nExpectedFrames; ++frameIdx) {
                    result.frames[frameIdx][ii] = result.frames[frameIdx - 1][ii];
                }
            }
            catch (...) {
                // Leave this object at (0,0,0) if it fails to propagate
                const auto& gp = gpObjects[ii];
                const auto name =
                    gp.OBJECT_NAME.value_or(gp.NORAD_CAT_ID ? std::string("NORAD Object ") + std::to_string(gp.NORAD_CAT_ID) : "Unknown");
                std::cerr << "[helios] Error propagating " << name << ". Leaving at (0,0,0).\n";
            }
        }
    }

    const auto end   = std::chrono::steady_clock::now();
    result.elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

    // Cap max radius at geostationary distance for better visualization scaling
    static const double GEO_RADIUS_KM = 42164.0;
    result.maxRadiusKm                = std::min(maxRadius, GEO_RADIUS_KM);

    return result;
}

} // namespace helios
} // namespace astrea