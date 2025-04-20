
#pragma once

#include <cmath>
#include <functional>
#include <iostream>
#include <unordered_map>

#include <math/utils.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/JulianDateClock.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

class AstrodynamicsSystem;

namespace conversions {

//------------------------------------------- Frame Conversions --------------------------------------------//
void bci_to_bcbf(const RadiusVector& rBCI, JulianDate julianDate, AngularRate rotRate, RadiusVector& rBCBF);
void bcbf_to_bci(const RadiusVector& rBCBF, JulianDate julianDate, AngularRate rotRate, RadiusVector& rBCI);

void bcbf_to_lla(const RadiusVector& rBCBF, const Distance& equitorialRadius, const Distance& polarRadius, Angle& lat, Angle& lon, Distance& alt);
void lla_to_bcbf(const Angle& lat, const Angle& lon, const Distance& alt, const Distance& equitorialRadius, const Distance& polarRadius, RadiusVector& rBCBF);

//------------------------------------------- Time Conversions ---------------------------------------------//
double epoch_to_julian_date(std::string epochString);
Angle julian_date_to_siderial_time(JulianDate julianDate, AngularRate rotRate);

} // namespace conversions
