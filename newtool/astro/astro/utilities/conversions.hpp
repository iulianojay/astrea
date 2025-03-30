
#pragma once

#ifndef SWIG
#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>
#endif

#include <math/utils.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/types/typedefs.hpp>

class AstrodynamicsSystem;

static const double RAD_TO_DEG = 180.0 / M_PI;
static const double DEG_TO_RAD = M_PI / 180.0;

static const double DAY_TO_SEC = 86400.0;
static const double SEC_TO_DAY = 1.0 / 86400.0;

static const double YEAR_TO_DAY = 365.25;
static const double DAY_TO_YEAR = 1.0 / 365.25;

static const double YEAR_TO_SEC = 31556926.0;
static const double SEC_TO_YEAR = 1.0 / 31556926.0;

static const double KM_TO_M = 1000.0;
static const double M_TO_KM = 0.001;

static const double KM_TO_AU = 1.0 / 1.49597871e8;
static const double AU_TO_KM = 1.49597871e8;

namespace conversions {

//------------------------------------------- Frame Conversions --------------------------------------------//
void bci_to_bcbf(const BasisArray& rBCI, double julianDate, double rotRate, BasisArray& rBCBF);
void bcbf_to_bci(const BasisArray& rBCBF, double julianDate, double rotRate, BasisArray& rBCI);

void bcbf_to_lla(const BasisArray& rBCBF, const double& equitorialRadius, const double& polarRadius, BasisArray& lla);
void lla_to_bcbf(const BasisArray& lla, const double& equitorialRadius, const double& polarRadius, BasisArray& rBCBF);

//---------------------------------------- Element Set Conversions -----------------------------------------//
std::vector<double> keplerian_to_bci(double h, double ecc, double inc, double raan, double w, double theta, double mu);
std::vector<double> bci_to_keplerian(const std::vector<double>& radius, const std::vector<double>& velocity, double mu);

ElementArray keplerian_to_cartesian(const ElementArray& coes, const AstrodynamicsSystem& centralBody);
ElementArray cartesian_to_keplerian(const ElementArray& cartesian, const AstrodynamicsSystem& centralBody);

ElementArray keplerian_to_equinoctial(const ElementArray& mees, const AstrodynamicsSystem& centralBody);
ElementArray equinoctial_to_keplerian(const ElementArray& coes, const AstrodynamicsSystem& centralBody);

void _equinoctial_to_keplerian(double p, double f, double g, double h, double k, double L, double* coes);

//------------------------------------------- Time Conversions ---------------------------------------------//
double epoch_to_julian_date(std::string epochString);
double julian_date_to_siderial_time(double julianDate, double rotRate);

// For the love of god, don't touch this
using set_conversion_function = std::function<ElementArray(const ElementArray&, const AstrodynamicsSystem&)>;
using element_set_pair        = std::pair<ElementSet, ElementSet>;

const std::unordered_map<element_set_pair, set_conversion_function> elementSetConversions = {
    { element_set_pair(ElementSet::KEPLERIAN, ElementSet::CARTESIAN), keplerian_to_cartesian },
    { element_set_pair(ElementSet::CARTESIAN, ElementSet::KEPLERIAN), cartesian_to_keplerian },
    { element_set_pair(ElementSet::KEPLERIAN, ElementSet::EQUINOCTIAL), keplerian_to_equinoctial },
    { element_set_pair(ElementSet::EQUINOCTIAL, ElementSet::KEPLERIAN), equinoctial_to_keplerian }
};

ElementArray convert(const ElementArray& elements, const ElementSet& fromSet, const ElementSet& toSet, const AstrodynamicsSystem& system);
} // namespace conversions
