#pragma once

#ifndef SWIG
    #include <iostream>
    #include <array>
#endif

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <iomanip>
#include <iostream>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include "fwd/systems/AstrodynamicsSystem.fwd.hpp"
class Cartesian;

class Keplerian {

public:

    Keplerian() :
        semimajor{0.0 * mp_units::si::unit_symbols::km},
        eccentricity{0.0 * mp_units::one},
        inclination{0.0 * mp_units::si::unit_symbols::rad},
        rightAscension{0.0 * mp_units::si::unit_symbols::rad},
        argPerigee{0.0 * mp_units::si::unit_symbols::rad},
        trueAnomaly{0.0 * mp_units::si::unit_symbols::rad}
    {}
    Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys);
    ~Keplerian() = default;

    const auto& get_semimajor() const { return semimajor; }
    const auto& get_eccentricity() const { return eccentricity; }
    const auto& get_inclination() const { return inclination; }
    const auto& get_right_ascension() const { return rightAscension; }
    const auto& get_argument_of_perigee() const { return argPerigee; }
    const auto& get_true_anomaly() const { return trueAnomaly; }

private:

    mp_units::quantity<mp_units::si::unit_symbols::km>  semimajor;
    mp_units::quantity<mp_units::one>                   eccentricity;
    mp_units::quantity<mp_units::si::unit_symbols::rad> inclination;
    mp_units::quantity<mp_units::si::unit_symbols::rad> rightAscension;
    mp_units::quantity<mp_units::si::unit_symbols::rad> argPerigee;
    mp_units::quantity<mp_units::si::unit_symbols::rad> trueAnomaly;

};