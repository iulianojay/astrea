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

#include <astro/propagation/force_models/ForceModel.hpp>

#include <mp-units/systems/si.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

Perturbation ForceModel::compute_perturbations(const State& state, const Vehicle& vehicle) const
{
    Perturbation sum{ .force  = { 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s) },
                      .torque = { 0.0 * N * m, 0.0 * N * m, 0.0 * N * m } };
    for (const auto& [name, force] : forces) {
        const auto result = force->compute_perturbation(state, vehicle);
        for (std::size_t ii = 0; ii < 3; ++ii) {
            sum.force[ii] += result.force[ii];
            sum.torque[ii] += result.torque[ii];
        }
    }
    return sum;
}

const std::unique_ptr<PerturbingForce>& ForceModel::at(const std::string& name) const { return forces.at(name); }


} // namespace astro
} // namespace astrea