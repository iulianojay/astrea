#include <astro/state/State.hpp>

namespace astro {

bool state_time_comparitor(State s, Time time) { return s.time < time; }

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.time << ", " << state.elements;
    return os;
}

} // namespace astro