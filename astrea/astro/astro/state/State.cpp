#include <astro/state/State.hpp>

namespace astrea {
namespace astro {

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.get_epoch() << ", " << state.get_elements();
    return os;
}

bool State::operator==(const State& other) const
{
    return _epoch == other._epoch && _elements == other._elements && _system == other._system;
}

} // namespace astro
} // namespace astrea