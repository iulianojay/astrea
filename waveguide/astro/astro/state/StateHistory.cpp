#include <astro/state/StateHistory.hpp>

#include <mp-units/math.h>

using namespace mp_units;

namespace waveguide {
namespace astro {


State& StateHistory::operator[](const Time& time) { return _states[time]; }
const State& StateHistory::at(const Time& time) const { return _states.at(time); }

void StateHistory::insert(const Time& time, const State& state) { _states[time] = state; }
std::size_t StateHistory::size() const { return _states.size(); }
void StateHistory::clear() { _states.clear(); }

const State& StateHistory::get_closest_state(const Time& time) const
{
    // If exact, return
    if (_states.contains(time)) { return _states.at(time); }

    // Check if input time is out of bounds
    auto iter = _states.lower_bound(time);
    if (iter == _states.begin()) {
        throw std::runtime_error("Cannot extrapolate to state before existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }
    else if (iter == _states.end()) {
        throw std::runtime_error("Cannot extrapolate to state after existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }

    // Compare time before and after index
    const Time upperDiff = abs((iter)->first - time);
    const Time lowerDiff = abs(std::prev(iter)->first - time);

    // Return closest
    if (lowerDiff < upperDiff) { return std::prev(iter)->second; }
    else {
        return (iter)->second;
    }
}

const State& StateHistory::get_state_at(const Time& time)
{
    // If exact, return
    if (_states.contains(time)) { return _states.at(time); }

    // Check if input time is out of bounds
    auto iter = _states.lower_bound(time);
    if (iter == _states.begin()) {
        throw std::runtime_error("Cannot extrapolate to state before existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }
    else if (iter == _states.end()) {
        throw std::runtime_error("Cannot extrapolate to state after existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }

    // Interpolate
    const Time& postTime                = iter->first;
    const State& postState              = iter->second;
    const OrbitalElements& postElements = postState.get_elements();

    const Time& preTime                = std::prev(iter)->first;
    const State& preState              = std::prev(iter)->second;
    const OrbitalElements& preElements = preState.get_elements();

    OrbitalElements interpolatedElements = preElements.interpolate(preTime, postTime, postElements, preState.get_system(), time);
    State interpolatedState({ interpolatedElements, preState.get_epoch() + (time - preTime), preState.get_system() });

    // Insert
    _states[time] = interpolatedState;

    return _states.at(time);
}

} // namespace astro
} // namespace waveguide