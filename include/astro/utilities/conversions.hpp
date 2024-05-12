
#pragma once

#include <map>
#include <iostream>

#include "typedefs.hpp"
#include "ElementSet.hpp"

class AstrodynamicsSystem;

namespace conversions {

    //------------------------------------------- Frame Conversions --------------------------------------------//
    void bci_to_bcbf(double* rBCI, double julianDate, double rotRate, double* rBCBF);
    void bcbf_to_bci(double* rBCBF, double julianDate, double rotRate, double* rBCI);
    
    void bcbf_to_lla(double* rBCBF, double equitorialRadius, double polarRadius, double* lla);
    void lla_to_bcbf(double* lla, double equitorialRadius, double polarRadius, double* rBCBF);

    //---------------------------------------- Element Set Conversions -----------------------------------------//
    void coes_to_bci(double h, double ecc, double inc, double w, double raan, double theta, double mu, double* radius, double* velocity);
    void bci_to_coes(double* radius, double* velocity, double mu, double* coes);

    element_array coes_to_cartesian(element_array coes, AstrodynamicsSystem* centralBody);
    element_array cartesian_to_coes(element_array cartesian, AstrodynamicsSystem* centralBody);

    void mees_to_coes(double p, double f, double g, double h, double k, double L, double* coes);

    //------------------------------------------- Time Conversions ---------------------------------------------//
    double epoch_to_julian_date(std::string epochString);
    double julian_date_to_sidereal_time(double julianDate, double rotRate);


    // For the love of god, don't touch this
    using set_conversion_function = std::function<element_array(element_array, AstrodynamicsSystem*)>;
    using element_set_pair = std::pair<ElementSet, ElementSet>;

    static const std::map<element_set_pair, set_conversion_function> elementSetConversions = {
        {element_set_pair(ElementSet::COE, ElementSet::CARTESIAN), coes_to_cartesian},
        {element_set_pair(ElementSet::CARTESIAN, ElementSet::COE), cartesian_to_coes}
    };

    element_array convert(element_array elements, ElementSet fromSet, ElementSet toSet, AstrodynamicsSystem* system);
}
