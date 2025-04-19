#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <algorithm>

#include <astro/time/Time.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::non_si;
using namespace mp_units::si::unit_symbols;


// Constructor/Destructor
Spacecraft::Spacecraft(OrbitalElements state0, Date epoch) :
    _epoch(epoch)
{
    update_state(State(0.0 * day, state0));
    generate_id_hash();
}


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

State Spacecraft::get_state_at(const Time& time, const AstrodynamicsSystem& sys) const
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

    // Interpolate
    const State& preState              = _states[idx - 1];
    const Time& preTime                = preState.time;
    const OrbitalElements& preElements = preState.elements;

    const State& postState              = _states[idx];
    const Time& postTime                = postState.time;
    const OrbitalElements& postElements = postState.elements;

    OrbitalElements interpolatedElements =
        std::visit([&](const auto& x) { return x.interpolate(preTime, postTime, postElements, sys, time); }, preElements);

    return State({ time, interpolatedElements });
}

// Spacecraft Property Getters
Mass Spacecraft::get_mass() const { return _mass; }
Unitless Spacecraft::get_coefficient_of_drag() const { return _coefficientOfDrag; }
Unitless Spacecraft::get_coefficient_of_lift() const { return _coefficientOfLift; }
Unitless Spacecraft::get_coefficient_of_reflectivity() const { return _coefficientOfReflectivity; }
SurfaceArea Spacecraft::get_ram_area() const { return _ramArea; }
SurfaceArea Spacecraft::get_solar_area() const { return _sunArea; }
SurfaceArea Spacecraft::get_lift_area() const { return _liftArea; }


void Spacecraft::generate_id_hash()
{
    // const auto elements0 = _states[0].elements.to_vector();
    // _id  = std::hash<double>()(elements0[0]) ^ std::hash<double>()(elements0[1]) ^ std::hash<double>()(elements0[2]) ^
    //        std::hash<double>()(elements0[3]) ^ std::hash<double>()(elements0[4]) ^ std::hash<double>()(elements0[5]); // TODO: Fix this
    _id ^= std::hash<double>()(_mass.numerical_value_ref_in(_mass.unit));
    _id ^= std::hash<double>()(_coefficientOfDrag.numerical_value_ref_in(_coefficientOfDrag.unit));
    _id ^= std::hash<double>()(_coefficientOfLift.numerical_value_ref_in(_coefficientOfLift.unit));
    _id ^= std::hash<double>()(_coefficientOfReflectivity.numerical_value_ref_in(_coefficientOfReflectivity.unit));
    _id ^= std::hash<double>()(_ramArea.numerical_value_ref_in(_ramArea.unit));
    _id ^= std::hash<double>()(_sunArea.numerical_value_ref_in(_sunArea.unit));
    _id ^= std::hash<double>()(_liftArea.numerical_value_ref_in(_liftArea.unit));
}