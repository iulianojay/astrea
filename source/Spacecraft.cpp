
#include "Spacecraft.hpp"
#include "conversions.hpp"

// Constructor/Destructor
Spacecraft::Spacecraft() { }
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
    // Update spacecraft
    epoch = inputEpoch;
    epochJulianDate = conversions::epoch_to_julian_date(inputEpoch);
}

//----------------------------------------------------------------------------------------------------------//
//------------------------------------------------ Getters -------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//

// Spacecraft Property Getters
double  Spacecraft::get_mass()                        { return mass; }
double  Spacecraft::get_coefficient_of_drag()         { return coefficientOfDrag; }
double  Spacecraft::get_coefficient_of_lift()         { return coefficientOfLift; }
double  Spacecraft::get_coefficient_of_reflectivity() { return coefficientOfReflectivity; }
double* Spacecraft::get_ram_area()                    { return areaRam; }
double* Spacecraft::get_sun_area()                    { return areaSun; }
double* Spacecraft::get_lift_area()                   { return areaLift; }
