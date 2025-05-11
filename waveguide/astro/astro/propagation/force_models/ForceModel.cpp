#include <astro/propagation/force_models/ForceModel.hpp>

#include <mp-units/systems/si.h>

using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;

namespace astro {

AccelerationVector
    ForceModel::compute_forces(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    AccelerationVector sum{ 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s) };
    for (const auto& [name, force] : forces) {
        const auto result = force->compute_force(date, state, vehicle, sys);
        for (std::size_t ii = 0; ii < 3; ++ii) {
            sum[ii] += result[ii];
        }
    }
    return sum;
}

const std::unique_ptr<Force>& ForceModel::at(const std::string& name) const { return forces.at(name); }


} // namespace astro