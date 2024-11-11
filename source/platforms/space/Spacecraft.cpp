#include "Spacecraft.hpp"

#include <algorithm>

#include "conversions.hpp"
#include "interpolation.hpp"
#include "Time.hpp"

// Constructor/Destructor
Spacecraft::Spacecraft(OrbitalElements state0, std::string epoch) : epoch(J2000) {
    states.push_back({0.0, state0});
    set_epoch(epoch);

    generate_id_hash();
}
Spacecraft::~Spacecraft() { }

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ Setters -------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Spacecraft Properties
void Spacecraft::set_mass(double m) {
    mass = m;
}
void Spacecraft::set_coefficient_of_drag(double Cd) {
    coefficientOfDrag = Cd;
}
void Spacecraft::set_coefficient_of_lift(double Cl) {
    coefficientOfLift = Cl;
}
void Spacecraft::coefficient_of_reflectivity(double Cr) {
    coefficientOfReflectivity = Cr;
}

void Spacecraft::set_ram_area(double aRam) { //TODO: Watch unit conversion issues in EOM
    areaRam[0] = aRam;
}
void Spacecraft::set_ram_area(double* aRam) {
    for (int ii = 0; ii < 3; ++ii) {
        areaRam[ii] = aRam[ii];
    }
}

void Spacecraft::set_sun_area(double aSun) {
    areaSun[0] = aSun;
}
void Spacecraft::set_sun_area(double* aSun) {
    for (int ii = 0; ii < 3; ++ii) {
        areaSun[ii] = aSun[ii];
    }
}

void Spacecraft::set_lift_area(double aLift) {
    areaLift[0] = aLift;
}
void Spacecraft::set_lift_area(double* aLift) {
    for (int ii = 0; ii < 3; ++ii) {
        areaLift[ii] = aLift[ii];
    }
}

void Spacecraft::set_epoch(std::string inputEpoch) {
    epoch = Date(inputEpoch);
}


void Spacecraft::set_states(std::vector<State> statesIn) {
    states = statesIn;
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ Getters -------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

const State& Spacecraft::get_initial_state() const { return states[0]; }
const State& Spacecraft::get_final_state() const { return states[states.size()-1]; }

const State& Spacecraft::get_closest_state(const Time& time) const {

    // Check if input time is out of bounds
    if (time <= states[0].time) {
        return states[0];
    }
    else if (time >= states[states.size()-1].time) {
        return states[states.size()-1];
    }

    // Get index of lower bound closest to input time
    const auto id = std::distance(states.begin(), std::lower_bound(states.begin(), states.end(), time, state_time_comparitor));

    // Compare time before and after index
    const Time lowerDiff = (states[id].time - time);
    const Time upperDiff = (states[id+1].time - time);

    // Return closest
    if (lowerDiff < upperDiff) {
        return states[id];
    }
    else {
        return states[id+1];
    }
}

const State Spacecraft::get_state_at(const Time& time) const {

    // Check if input time is out of bounds
    if (time < states[0].time || time > states[states.size()-1].time) {
        throw std::runtime_error("Cannot extrapolate to state outside of existing propagation bounds. Try repropagating to include all desired times.");
    };

    // Get index of lower bound closest to input time
    const auto lower = std::lower_bound(states.begin(), states.end(), time, state_time_comparitor);
    const auto idx = std::distance(states.begin(), lower);

    // If exact, return
    if (states[idx].time == time) {
        return states[idx];
    }

    // Separate time and elements
    std::vector<Time> times{ states[idx-1].time, states[idx].time };
    std::vector<std::vector<double>> elements{
        { states[idx-1].elements[0], states[idx].elements[0] },
        { states[idx-1].elements[1], states[idx].elements[1] },
        { states[idx-1].elements[2], states[idx].elements[2] },
        { states[idx-1].elements[3], states[idx].elements[3] },
        { states[idx-1].elements[4], states[idx].elements[4] },
        { states[idx-1].elements[5], states[idx].elements[5] }
    };

    // Interpolate one element at a time to reduce error
    OrbitalElements interpolatedElements = states[0].elements; // copy so element set is the same
    for (size_t ii = 0; ii < 6; ++ii) {
        interpolatedElements[ii] = interpolate(times, elements[ii], time);
    }

    return State({time, interpolatedElements});
}

// Spacecraft Property Getters
const double& Spacecraft::get_mass()                        const { return mass; }
const double& Spacecraft::get_coefficient_of_drag()         const { return coefficientOfDrag; }
const double& Spacecraft::get_coefficient_of_lift()         const { return coefficientOfLift; }
const double& Spacecraft::get_coefficient_of_reflectivity() const { return coefficientOfReflectivity; }
const basis_array& Spacecraft::get_ram_area()               const { return areaRam; }
const basis_array& Spacecraft::get_sun_area()               const { return areaSun; }
const basis_array& Spacecraft::get_lift_area()              const { return areaLift; }


void Spacecraft::generate_id_hash() {
    const auto elements0 = states[0].elements;
    id  = std::hash<double>()(elements0[0]) ^ std::hash<double>()(elements0[1]) ^ std::hash<double>()(elements0[2]) ^
          std::hash<double>()(elements0[3]) ^ std::hash<double>()(elements0[4]) ^ std::hash<double>()(elements0[5]);
    id ^= std::hash<double>()(mass);
    id ^= std::hash<double>()(coefficientOfDrag);
    id ^= std::hash<double>()(coefficientOfLift);
    id ^= std::hash<double>()(coefficientOfReflectivity);
    id ^= std::hash<double>()(areaRam[0]) ^ std::hash<double>()(areaRam[1]) ^ std::hash<double>()(areaRam[2]);
    id ^= std::hash<double>()(areaSun[0]) ^ std::hash<double>()(areaSun[1]) ^ std::hash<double>()(areaSun[2]);
    id ^= std::hash<double>()(areaLift[0]) ^ std::hash<double>()(areaLift[1]) ^ std::hash<double>()(areaLift[2]);
}