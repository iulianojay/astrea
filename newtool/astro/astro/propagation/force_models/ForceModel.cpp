#include "ForceModel.hpp"

#include <mp-units/systems/si.h>

using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;

template<typename T, typename ...Args>
const std::unique_ptr<Force>& ForceModel::add(Args&&... args) {
    std::string name = typeid(T).name();
    if (forces.count(name) == 0) {
        forces.emplace(name, std::make_unique<T>( std::forward<Args>(args)... ));
    }
    return forces.at(name);
}

AccelerationVector ForceModel::compute_forces(const JulianDate& julianDate, const Cartesian &state, const Vehicle &vehicle, const AstrodynamicsSystem &sys) const {
    AccelerationVector sum{0.0 * km/(s*s), 0.0 * km/(s*s), 0.0 * km/(s*s)};
    for (const auto& [name, force] : forces) {
        const auto result = force->compute_force(julianDate, state, vehicle, sys);
        for (size_t ii = 0; ii < 3; ++ii) {
            sum[ii] += result[ii];
        }
    }
    return sum;
}

const std::unique_ptr<Force>& ForceModel::at(const std::string& name) const {
    return forces.at(name);
}

template<typename T>
const std::unique_ptr<Force>& ForceModel::get() const {
    std::string name = typeid(T).name();
    return forces.at(name);
}
