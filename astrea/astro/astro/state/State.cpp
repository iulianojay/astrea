#include <astro/state/State.hpp>

#include <iostream>

namespace astrea {
namespace astro {

State::State(const OrbitalElements& orbit, const Date& epoch, const AstrodynamicsSystem& sys) :
    _orbit(orbit),
    _epoch(epoch),
    _system(&sys)
{
}

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.get_epoch() << ", " << state.get_orbit();
    return os;
}

bool State::operator==(const State& other) const
{
    return _epoch == other._epoch && _orbit == other._orbit && _system == other._system;
}

} // namespace astro
} // namespace astrea