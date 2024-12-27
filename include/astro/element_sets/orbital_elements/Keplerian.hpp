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

    friend std::ostream& operator<<(std::ostream&, Keplerian const&);

public:

    Keplerian() :
        _semimajor{0.0 * mp_units::si::unit_symbols::km},
        _eccentricity{0.0 * mp_units::one},
        _inclination{0.0 * mp_units::si::unit_symbols::rad},
        _rightAscension{0.0 * mp_units::si::unit_symbols::rad},
        _argPerigee{0.0 * mp_units::si::unit_symbols::rad},
        _trueAnomaly{0.0 * mp_units::si::unit_symbols::rad}
    {}
    Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Keplerian(const Keplerian&);

    // Move constructor
    Keplerian(Keplerian&&) noexcept;

    // Move assignment operator
    Keplerian& operator=(Keplerian&&) noexcept;

    // Copy assignment operator
    Keplerian& operator=(const Keplerian&);

    ~Keplerian() = default;

    const auto& get_semimajor() const { return _semimajor; }
    const auto& get_eccentricity() const { return _eccentricity; }
    const auto& get_inclination() const { return _inclination; }
    const auto& get_right_ascension() const { return _rightAscension; }
    const auto& get_argument_of_perigee() const { return _argPerigee; }
    const auto& get_true_anomaly() const { return _trueAnomaly; }

private:

    mp_units::quantity<mp_units::si::unit_symbols::km>  _semimajor;
    mp_units::quantity<mp_units::one>                   _eccentricity;
    mp_units::quantity<mp_units::si::unit_symbols::rad> _inclination;
    mp_units::quantity<mp_units::si::unit_symbols::rad> _rightAscension;
    mp_units::quantity<mp_units::si::unit_symbols::rad> _argPerigee;
    mp_units::quantity<mp_units::si::unit_symbols::rad> _trueAnomaly;

};