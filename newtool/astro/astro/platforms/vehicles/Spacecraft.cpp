#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <algorithm>

#include <astro/time/Time.hpp>
#include <astro/utilities/conversions.hpp>
#include <math/interpolation.hpp>

// Constructor/Destructor
Spacecraft::Spacecraft(OrbitalElements state0, Date epoch) :
    _epoch(epoch)
{
    update_state({ 0.0, state0 });
    generate_id_hash();
}
Spacecraft::~Spacecraft() {}


void Spacecraft::update_state(const State& state)
{
    _state = state; // TODO: Convert to element set?
    _states.emplace_back(state);
}

const State& Spacecraft::get_initial_state() const { return _states[0]; }
const State& Spacecraft::get_final_state() const { return _states[_states.size() - 1]; }

const State& Spacecraft::get_closest_state(const Time& time) const
{

    // Check if input time is out of bounds
    if (time <= _states[0].time) { return _states[0]; }
    else if (time >= _states[_states.size() - 1].time) {
        return _states[_states.size() - 1];
    }

    // Get index of lower bound closest to input time
    const auto id = std::distance(_states.begin(), std::lower_bound(_states.begin(), _states.end(), time, state_time_comparitor));

    // Compare time before and after index
    const Time lowerDiff = (_states[id].time - time);
    const Time upperDiff = (_states[id + 1].time - time);

    // Return closest
    if (lowerDiff < upperDiff) { return _states[id]; }
    else {
        return _states[id + 1];
    }
}

State Spacecraft::get_state_at(const Time& time) const
{

    // Check if input time is out of bounds
    if (time < _states[0].time || time > _states[_states.size() - 1].time) {
        throw std::runtime_error("Cannot extrapolate to state outside of existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    };

    // Get index of lower bound closest to input time
    const auto lower = std::lower_bound(_states.begin(), _states.end(), time, state_time_comparitor);
    const auto idx   = std::distance(_states.begin(), lower);

    // If exact, return
    if (_states[idx].time == time) { return _states[idx]; }

    // Separate time and elements
    std::vector<Time> times{ _states[idx - 1].time, _states[idx].time };
    std::vector<std::vector<double>> elements{ { _states[idx - 1].elements[0], _states[idx].elements[0] },
                                               { _states[idx - 1].elements[1], _states[idx].elements[1] },
                                               { _states[idx - 1].elements[2], _states[idx].elements[2] },
                                               { _states[idx - 1].elements[3], _states[idx].elements[3] },
                                               { _states[idx - 1].elements[4], _states[idx].elements[4] },
                                               { _states[idx - 1].elements[5], _states[idx].elements[5] } };

    // Interpolate one element at a time to reduce error
    OrbitalElements interpolatedElements = _states[0].elements; // copy so element set is the same
    for (size_t ii = 0; ii < 6; ++ii) {
        interpolatedElements[ii] = math::interpolate(times, elements[ii], time);
    }

    return State({ time, interpolatedElements });
}

// Spacecraft Property Getters
double Spacecraft::get_mass() const { return _mass; }
double Spacecraft::get_coefficient_of_drag() const { return _coefficientOfDrag; }
double Spacecraft::get_coefficient_of_lift() const { return _coefficientOfLift; }
double Spacecraft::get_coefficient_of_reflectivity() const { return _coefficientOfReflectivity; }
double Spacecraft::get_ram_area() const { return _ramArea; }
double Spacecraft::get_solar_area() const { return _sunArea; }
double Spacecraft::get_lift_area() const { return _liftArea; }


void Spacecraft::generate_id_hash()
{
    const auto elements0 = _states[0].elements;
    _id = std::hash<double>()(elements0[0]) ^ std::hash<double>()(elements0[1]) ^ std::hash<double>()(elements0[2]) ^
          std::hash<double>()(elements0[3]) ^ std::hash<double>()(elements0[4]) ^ std::hash<double>()(elements0[5]);
    _id ^= std::hash<double>()(_mass);
    _id ^= std::hash<double>()(_coefficientOfDrag);
    _id ^= std::hash<double>()(_coefficientOfLift);
    _id ^= std::hash<double>()(_coefficientOfReflectivity);
    _id ^= std::hash<double>()(_ramArea);
    _id ^= std::hash<double>()(_sunArea);
    _id ^= std::hash<double>()(_liftArea);
}