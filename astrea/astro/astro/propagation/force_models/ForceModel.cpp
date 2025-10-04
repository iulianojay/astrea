#include <astro/propagation/force_models/ForceModel.hpp>

#include <mp-units/systems/si.h>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::s;

AccelerationVector<frames::earth::icrf>
    ForceModel::compute_forces(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{
    AccelerationVector<frames::earth::icrf> sum{ 0.0 * km / (s * s), 0.0 * km / (s * s), 0.0 * km / (s * s) };
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
} // namespace astrea