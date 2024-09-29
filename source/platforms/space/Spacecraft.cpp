#include <algorithm>

#include "Spacecraft.hpp"
#include "conversions.hpp"

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

const State& Spacecraft::get_initial_state() { return states[0]; }
const State& Spacecraft::get_final_state() { return states[states.size()-1]; }

const State& Spacecraft::get_state(Time time) {
    // Get index of lower bound closest to input time
    auto id = std::distance(states.begin(), std::lower_bound(states.begin(), states.end(), time, state_time_comparitor));
    
    // Compare time before and after index
    Time lowerDiff = (states[id].time - time);
    Time upperDiff = (states[id+1].time - time);

    // Return closest
    if (lowerDiff < upperDiff) {
        return states[id];
    }
    else {
        return states[id+1];
    }
}

// Spacecraft Property Getters
double  Spacecraft::get_mass()                        { return mass; }
double  Spacecraft::get_coefficient_of_drag()         { return coefficientOfDrag; }
double  Spacecraft::get_coefficient_of_lift()         { return coefficientOfLift; }
double  Spacecraft::get_coefficient_of_reflectivity() { return coefficientOfReflectivity; }
double* Spacecraft::get_ram_area()                    { return areaRam; }
double* Spacecraft::get_sun_area()                    { return areaSun; }
double* Spacecraft::get_lift_area()                   { return areaLift; }


void Spacecraft::generate_id_hash() { // TODO: Link this into the orbital elements somehow
    id = std::hash<int>()(mass);
    id ^= std::hash<int>()(coefficientOfDrag);
    id ^= std::hash<int>()(coefficientOfLift);
    id ^= std::hash<int>()(coefficientOfReflectivity);
    id ^= std::hash<int>()(areaRam[0]) ^ std::hash<int>()(areaRam[1]) ^ std::hash<int>()(areaRam[2]);
    id ^= std::hash<int>()(areaSun[0]) ^ std::hash<int>()(areaSun[1]) ^ std::hash<int>()(areaSun[2]);
    id ^= std::hash<int>()(areaLift[0]) ^ std::hash<int>()(areaLift[1]) ^ std::hash<int>()(areaLift[2]);
}