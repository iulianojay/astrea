#include <astro/state/State.hpp>

bool state_time_comparitor(State s, Time time) { return s.time < time; }

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << state.time << ", ";
    std::visit([&](const auto& x) { os << x; }, state.elements);
    return os;
}