/*
    This file is part of the Iuliano Orbital Propagation Suite

    The Orbital Propagation Suite is a high precision orbital propagation toolset
    Copyright(C) 2018, Jay Iuliano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.

    iuliano.jay@gmail.com
*/

#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#include "math_constants.h"
#include "astronomical_constants.h"
#include "math_c.hpp"


namespace convert {
    extern "C" {
    //------------------------------------------- Frame Conversions --------------------------------------------//
    void bci_to_bcbf(double* rBCI, double julianDate, double rotRate, double* rBCBF);
    void bcbf_to_bci(double* rBCBF, double julianDate, double rotRate, double* rBCI);
    
    void bcbf_to_lla(double* rBCBF, double equitorialRadius, double polarRadius, double* lla);
    void lla_to_bcbf(double* lla, double equitorialRadius, double polarRadius, double* rBCBF);

    //---------------------------------------- Element Set Conversions -----------------------------------------//
    void coes_to_bci(double h, double ecc, double inc, double w, double raan, double theta, double mu, double* radius, double* velocity);
    void bci_to_coes(double* radius, double* velocity, double mu, double* coes);

    void mees_to_coes(double p, double f, double g, double h, double k, double L, double* coes);

    //------------------------------------------- Time Conversions ---------------------------------------------//
    double epoch_to_julian_date(std::string epochString);
    double julian_date_to_sidereal_time(double julianDate, double rotRate);
    }
}
