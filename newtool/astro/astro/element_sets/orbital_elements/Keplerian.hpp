#pragma once

#ifndef SWIG
#include <array>
#include <iostream>
#endif

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <iomanip>
#include <iostream>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/Time.hpp>

class Keplerian {

    friend std::ostream& operator<<(std::ostream&, Keplerian const&);

    using Distance = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using Unitless = mp_units::quantity<mp_units::one>;
    using Angle    = mp_units::quantity<mp_units::si::unit_symbols::rad>;

  public:
    Keplerian() :
        _semimajor{ 0.0 * mp_units::si::unit_symbols::km },
        _eccentricity{ 0.0 * mp_units::one },
        _inclination{ 0.0 * mp_units::si::unit_symbols::rad },
        _rightAscension{ 0.0 * mp_units::si::unit_symbols::rad },
        _argPerigee{ 0.0 * mp_units::si::unit_symbols::rad },
        _trueAnomaly{ 0.0 * mp_units::si::unit_symbols::rad }
    {
    }
    Keplerian(const std::vector<double>& elements) :
        _semimajor{ elements[0] * mp_units::si::unit_symbols::km },
        _eccentricity{ elements[1] * mp_units::one },
        _inclination{ elements[2] * mp_units::si::unit_symbols::rad },
        _rightAscension{ elements[3] * mp_units::si::unit_symbols::rad },
        _argPerigee{ elements[4] * mp_units::si::unit_symbols::rad },
        _trueAnomaly{ elements[5] * mp_units::si::unit_symbols::rad }
    {
    }
    Keplerian(const Distance& semimajor, const Unitless& eccentricity, const Angle& inclination, const Angle& rightAscension, const Angle& argPerigee, const Angle& trueAnomaly) :
        _semimajor{ semimajor },
        _eccentricity{ eccentricity },
        _inclination{ inclination },
        _rightAscension{ rightAscension },
        _argPerigee{ argPerigee },
        _trueAnomaly{ trueAnomaly }
    {
    }
    Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys);
    Keplerian(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Keplerian(const Keplerian&);

    // Move constructor
    Keplerian(Keplerian&&) noexcept;

    // Move assignment operator
    Keplerian& operator=(Keplerian&&) noexcept;

    // Copy assignment operator
    Keplerian& operator=(const Keplerian&);

    // Destructor
    ~Keplerian() = default;

    // Comparitors operators
    bool operator==(const Keplerian& other) const;
    bool operator!=(const Keplerian& other) const;

    // Mathmatical operators
    Keplerian operator+(const Keplerian& other) const;
    Keplerian& operator+=(const Keplerian& other);

    Keplerian operator-(const Keplerian& other) const;
    Keplerian& operator-=(const Keplerian& other);

    Keplerian operator*(const double& multiplier) const;
    Keplerian& operator*=(const double& multiplier);

    Keplerian operator/(const double& divisor) const;
    Keplerian& operator/=(const double& divisor);

    // Element access
    const Distance& get_semimajor() const { return _semimajor; }
    const Unitless& get_eccentricity() const { return _eccentricity; }
    const Angle& get_inclination() const { return _inclination; }
    const Angle& get_right_ascension() const { return _rightAscension; }
    const Angle& get_argument_of_perigee() const { return _argPerigee; }
    const Angle& get_true_anomaly() const { return _trueAnomaly; }

    size_t size() const { return 6; }

    constexpr EnumType get_set_id() const { return _setId; }
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    std::vector<double> to_vector() const;
    void update_from_vector(const std::vector<double>& vec);

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::KEPLERIAN);

    Distance _semimajor;
    Unitless _eccentricity;
    Angle _inclination;
    Angle _rightAscension;
    Angle _argPerigee;
    Angle _trueAnomaly;
};