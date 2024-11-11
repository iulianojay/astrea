
#pragma once

#ifndef SWIG
    #include <unordered_map>
    #include <iostream>
    #include <functional>
#endif

#include "typedefs.hpp"
#include "ElementSet.hpp"

class AstrodynamicsSystem;

namespace conversions {

    //------------------------------------------- Frame Conversions --------------------------------------------//
    void bci_to_bcbf(const basis_array& rBCI, double julianDate, double rotRate, basis_array& rBCBF);
    void bcbf_to_bci(const basis_array& rBCBF, double julianDate, double rotRate, basis_array& rBCI);

    void bcbf_to_lla(const basis_array& rBCBF, const double& equitorialRadius, const double& polarRadius, basis_array& lla);
    void lla_to_bcbf(const basis_array& lla, const double& equitorialRadius, const double& polarRadius, basis_array& rBCBF);

    //---------------------------------------- Element Set Conversions -----------------------------------------//
    void coes_to_bci(double h, double ecc, double inc, double raan, double w, double theta, double mu, double* radius, double* velocity);
    void bci_to_coes(double* radius, double* velocity, double mu, double* coes);

    element_array coes_to_cartesian(const element_array& coes, const AstrodynamicsSystem& centralBody);
    element_array cartesian_to_coes(const element_array& cartesian, const AstrodynamicsSystem& centralBody);

    element_array coes_to_mees(const element_array& mees, const AstrodynamicsSystem& centralBody);
    element_array mees_to_coes(const element_array& coes, const AstrodynamicsSystem& centralBody);

    void _mees_to_coes(double p, double f, double g, double h, double k, double L, double* coes);

    //------------------------------------------- Time Conversions ---------------------------------------------//
    double epoch_to_julian_date(std::string epochString);
    double julian_date_to_sidereal_time(double julianDate, double rotRate);


    // For the love of god, don't touch this
    using set_conversion_function = std::function<element_array(const element_array&, const AstrodynamicsSystem&)>;
    using element_set_pair = std::pair<ElementSet, ElementSet>;

    const std::unordered_map<element_set_pair, set_conversion_function> elementSetConversions = {
        {element_set_pair(ElementSet::COE, ElementSet::CARTESIAN), coes_to_cartesian},
        {element_set_pair(ElementSet::CARTESIAN, ElementSet::COE), cartesian_to_coes},
        {element_set_pair(ElementSet::COE, ElementSet::MEE), coes_to_mees},
        {element_set_pair(ElementSet::MEE, ElementSet::COE), mees_to_coes}
    };

    element_array convert(const element_array& elements, const ElementSet& fromSet, const ElementSet& toSet, const AstrodynamicsSystem& system);
}
