#pragma once

#include <string> 

#include "astronomical_constants.h"

class Spacecraft
{
private:
    //---------------------------------------------------------------------------------------------------------//
    //---------------------------------------------- Variabless -----------------------------------------------//
    //---------------------------------------------------------------------------------------------------------//

    // Spacecraft properties
    double mass = 1000.0;
    double coefficientOfDrag = 2.2;
    double coefficientOfLift = 0.9;
    double coefficientOfReflectivity = 1.1;
    double areaRam[3] = { 0.01, 0.0, 0.0 };
    double areaSun[3] = { 0.01, 0.0, 0.0 };
    double areaLift[3] = { 0.01, 0.0, 0.0 };

    // Epoch variables
    std::string epoch = "2000-01-01 12:00:00";
    double epochJulianDate = J2000;

public:
    //---------------------------------------------------------------------------------------------------------//
    //------------------------------------------------ Methods ------------------------------------------------//
    //---------------------------------------------------------------------------------------------------------//

    // Constructor
    Spacecraft();
    
    // Destructor
    ~Spacecraft();

    //---------------------------------------Spacecraft property setters---------------------------------------//

    // Function: Set spacecraft mass
    // Inputs: mass (kg)
    void set_mass(double m);

    // Function: Set spacecraft coefficient of drag
    // Inputs: coefficient of drag (--)
    void set_coefficient_of_drag(double Cd);

    // Function: Set spacecraft coefficient of lift
    // Inputs: coefficient of lift (--)
    void set_coefficient_of_lift(double Cl);

    // Function: Set spacecraft coefficient of reflectivity
    // Inputs: coefficient of reflectivity (--)
    void coefficient_of_reflectivity(double Cr);

    // Function: Set spacecraft ram-facing area
    // Inputs: net ram-facing area (m^2)
    void set_ram_area(double aRam);

    // Function: Set spacecraft ram-facing areas
    // Inputs: array of areas (m^2)
    void set_ram_area(double* aRam);

    // Function: Set spacecraft sun-facing area
    // Inputs: net sun-facing area (m^2)
    void set_sun_area(double aSun);

    // Function: Set spacecraft sun-facing areas
    // Inputs: array of areas (m^2)
    void set_sun_area(double* aSun);

    // Function: Set spacecraft earth-facing area
    // Inputs: net earth-facing area (m^2)
    void set_lift_area(double aLift);

    // Function: Set spacecraft earth-facing areas
    // Inputs: array of areas (m^2)
    void set_lift_area(double* aLift);

    // Function: Set initial epoch of integration
    // Inputs: Initial epoch string in the format: "MON-DY-YEAR HH:MM:SS.SS"
    void set_epoch(std::string inputEpoch);

    //---------------------------------------Spacecraft property getters---------------------------------------//

    // Function: Get spacecraft mass
    // Outputs: mass (kg)
    double get_mass();

    // Function: Get spacecraft coefficient of drag
    // Outputs: coefficient of drag (--)
    double get_coefficient_of_drag();

    // Function: Get spacecraft coefficient of lift
    // Outputs: coefficient of lift (--)
    double get_coefficient_of_lift();

    // Function: Get spacecraft coefficient of reflectivity
    // Outputs: coefficient of reflectivity (--)
    double get_coefficient_of_reflectivity();

    // Function: Get spacecraft ram-facing area
    // Outputs: net ram-facing area / array of areas (m^2)
    double* get_ram_area();

    // Function: Get spacecraft sun-facing area
    // Outputs: net sun-facing area / array of areas (m^2)
    double* get_sun_area();

    // Function: Get spacecraft earth-facing area
    // Outputs: net earth-facing area / array of areas (m^2)
    double* get_lift_area();
};
