#include <astro/state/StateHistory.hpp>

#include <mp-units/math.h>

using namespace mp_units;

namespace waveguide {
namespace astro {


State& StateHistory::operator[](const Date& date) { return _states[date]; }
const State& StateHistory::at(const Date& date) const { return _states.at(date); }

void StateHistory::insert(const Date& date, const State& state) { _states[date] = state; }
std::size_t StateHistory::size() const { return _states.size(); }
void StateHistory::clear() { _states.clear(); }

const State& StateHistory::get_closest_state(const Date& date) const
{
    // If exact, return
    if (_states.contains(date)) { return _states.at(date); }

    // Check if input date is out of bounds
    auto iter = _states.lower_bound(date);
    if (iter == _states.begin()) {
        throw std::runtime_error("Cannot extrapolate to state before existing propagation bounds. Try "
                                 "repropagating to include all desired dates.");
    }
    else if (iter == _states.end()) {
        throw std::runtime_error("Cannot extrapolate to state after existing propagation bounds. Try "
                                 "repropagating to include all desired dates.");
    }

    // Compare date before and after index
    const Time upperDiff = abs((iter)->first - date);
    const Time lowerDiff = abs(std::prev(iter)->first - date);

    // Return closest
    if (lowerDiff < upperDiff) { return std::prev(iter)->second; }
    else {
        return (iter)->second;
    }
}

State StateHistory::get_state_at(const Date& date) const
{
    // If exact, return
    if (_states.contains(date)) { return _states.at(date); }

    // Check if input date is out of bounds
    auto iter = _states.lower_bound(date);
    if (iter == _states.begin()) {
        throw std::runtime_error("Cannot extrapolate to state before existing propagation bounds. Try repropagating to "
                                 "include all desired dates.");
    }
    else if (iter == _states.end()) {
        throw std::runtime_error("Cannot extrapolate to state after existing propagation bounds. Try repropagating to "
                                 "include all desired dates.");
    }

    // Interpolate
    const Date& postDate                = iter->first;
    const OrbitalElements& postElements = (iter->second).get_elements();

    const Date& preDate                = std::prev(iter)->first;
    const State& preState              = std::prev(iter)->second;
    const OrbitalElements& preElements = preState.get_elements();

    const auto& system = preState.get_system();

    // Normalize to initial date for simplicity
    const Time time0 = 0.0 * mp_units::si::unit_symbols::s;
    const Time timef = postDate - preDate;
    const Time time  = date - preDate;

    OrbitalElements interpolatedElements = preElements.interpolate(time0, timef, postElements, system, time);
    return State({ interpolatedElements, date, system });

    // // Insert if we want this to store
    // _states[date] = interpolatedState;

    // return _states.at(date);
}

} // namespace astro
} // namespace waveguide