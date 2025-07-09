#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <algorithm>

#include <astro/types/typedefs.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astro {

// Constructor/Destructor
Spacecraft::Spacecraft(OrbitalElements state0, Date epoch) :
    _epoch(epoch)
{
    update_state(State(0.0 * s, state0));
    generate_id_hash();
}

Spacecraft::Spacecraft(const snapshot::SpaceTrackGP& gp)
{
    // TODO: Add catch/warning for missing values
    _id    = gp.NORAD_CAT_ID;
    _name  = gp.OBJECT_NAME.has_value() ? gp.OBJECT_NAME.value() : "UNNAMED";
    _epoch = gp.EPOCH.has_value() ? Date(gp.EPOCH.value(), "%Y-%m-%dT%H:%M:%S") : J2000;
    if (!gp.SEMIMAJOR_AXIS.has_value() || !gp.ECCENTRICITY.has_value() || !gp.INCLINATION.has_value() ||
        !gp.RA_OF_ASC_NODE.has_value() || !gp.ARG_OF_PERICENTER.has_value() || !gp.MEAN_ANOMALY.has_value()) {
        std::cerr << "Missing GP info. Sad." << std::endl;
    }
    Keplerian coes(
        gp.SEMIMAJOR_AXIS.value() * km,
        gp.ECCENTRICITY.value() * one,
        gp.INCLINATION.value() * deg,
        gp.RA_OF_ASC_NODE.value() * deg,
        gp.ARG_OF_PERICENTER.value() * deg,
        gp.MEAN_ANOMALY.value() * deg
    );

    update_state(State(0.0 * s, coes));

    // All of these are just default values - TODO: Look into different or better values for approximating these
    // effects, or find how to approximate these
    // _mass
    // _coefficientOfLift
    // _sunArea
    // _liftArea
}

void Spacecraft::update_state(const State& state)
{
    _state = state;
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

const State& Spacecraft::get_state_at(const Time& time, const AstrodynamicsSystem& sys)
{

    // Check if input time is out of bounds
    if (time < _states.front().time) {
        throw std::runtime_error("Cannot extrapolate to state before existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }
    else if (time > _states.back().time) {
        throw std::runtime_error("Cannot extrapolate to state after existing propagation bounds. Try "
                                 "repropagating to include all desired times.");
    }

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

    OrbitalElements interpolatedElements = preElements.interpolate(preTime, postTime, postElements, sys, time);
    State interpolatedState({ time, interpolatedElements });

    // Insert
    _states.insert(_states.begin() + idx, interpolatedState);

    return _states[idx];
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
    const auto elements0 = _states[0].elements.to_vector();
    _id = std::hash<Unitless>()(elements0[0]) ^ std::hash<Unitless>()(elements0[1]) ^ std::hash<Unitless>()(elements0[2]) ^
          std::hash<Unitless>()(elements0[3]) ^ std::hash<Unitless>()(elements0[4]) ^ std::hash<Unitless>()(elements0[5]);
    _id ^= std::hash<double>()(_mass.numerical_value_ref_in(_mass.unit));
    _id ^= std::hash<double>()(_coefficientOfDrag.numerical_value_ref_in(_coefficientOfDrag.unit));
    _id ^= std::hash<double>()(_coefficientOfLift.numerical_value_ref_in(_coefficientOfLift.unit));
    _id ^= std::hash<double>()(_coefficientOfReflectivity.numerical_value_ref_in(_coefficientOfReflectivity.unit));
    _id ^= std::hash<double>()(_ramArea.numerical_value_ref_in(_ramArea.unit));
    _id ^= std::hash<double>()(_sunArea.numerical_value_ref_in(_sunArea.unit));
    _id ^= std::hash<double>()(_liftArea.numerical_value_ref_in(_liftArea.unit));
}

} // namespace astro