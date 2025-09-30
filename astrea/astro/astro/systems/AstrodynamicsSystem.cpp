#include <astro/systems/AstrodynamicsSystem.hpp>

#include <astro/frames/frames.hpp>
#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

CartesianVector<InterplanetaryDistance, frames::solar_system_barycenter::icrf>
    AstrodynamicsSystem::get_relative_position(const Date& date, const CelestialBodyId id1, const CelestialBodyId id2) const
{
    const auto pos1 = get(id1)->get_position_at(date);
    const auto pos2 = get(id2)->get_position_at(date);
    return pos1 - pos2;
}

} // namespace astro
} // namespace astrea