#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class Keplerian {

    friend std::ostream& operator<<(std::ostream&, Keplerian const&);

  public:
    Keplerian(Unitless scale = 0.0 * detail::unitless) :
        _semimajor(scale * detail::distance_unit),
        _eccentricity(scale * detail::unitless),
        _inclination(scale * detail::angle_unit),
        _rightAscension(scale * detail::angle_unit),
        _argPerigee(scale * detail::angle_unit),
        _trueAnomaly(scale * detail::angle_unit)
    {
    }
    Keplerian(const Distance& semimajor, const Unitless& eccentricity, const Angle& inclination, const Angle& rightAscension, const Angle& argPerigee, const Angle& trueAnomaly) :
        _semimajor(semimajor),
        _eccentricity(eccentricity),
        _inclination(inclination),
        _rightAscension(rightAscension),
        _argPerigee(argPerigee),
        _trueAnomaly(trueAnomaly)
    {
    }
    Keplerian(const Keplerian& elements, const AstrodynamicsSystem& sys) :
        Keplerian(elements)
    {
    }
    Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys);
    Keplerian(const Equinoctial& elements, const AstrodynamicsSystem& sys);

    // Defaults
    static Keplerian LEO();
    static Keplerian LMEO();
    static Keplerian GPS();
    static Keplerian HMEO();
    static Keplerian GEO();

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

    Keplerian operator*(const Unitless& multiplier) const;
    Keplerian& operator*=(const Unitless& multiplier);

    KeplerianPartial operator/(const Time& time) const;
    Keplerian operator/(const Unitless& divisor) const;
    Keplerian& operator/=(const Unitless& divisor);

    // Element access
    const Distance& get_semimajor() const { return _semimajor; }
    const Unitless& get_eccentricity() const { return _eccentricity; }
    const Angle& get_inclination() const { return _inclination; }
    const Angle& get_right_ascension() const { return _rightAscension; }
    const Angle& get_argument_of_perigee() const { return _argPerigee; }
    const Angle& get_true_anomaly() const { return _trueAnomaly; }

    std::size_t size() const { return 6; }

    constexpr EnumType get_set_id() const { return _setId; }
    Keplerian interpolate(const Time& thisTime, const Time& otherTime, const Keplerian& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    std::vector<Unitless> to_vector() const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::KEPLERIAN);

    Distance _semimajor;
    Unitless _eccentricity;
    Angle _inclination;
    Angle _rightAscension;
    Angle _argPerigee;
    Angle _trueAnomaly;

    void sanitize_angles();
};

class KeplerianPartial {

  public:
    KeplerianPartial() = default;
    KeplerianPartial(
        const Velocity& semimajorPartial,
        const UnitlessPerTime& eccentricityPartial,
        const AngularRate& inclinationPartial,
        const AngularRate& rightAscensionPartial,
        const AngularRate& argPerigeePartial,
        const AngularRate& trueAnomalyPartial
    ) :
        _semimajorPartial(semimajorPartial),
        _eccentricityPartial(eccentricityPartial),
        _inclinationPartial(inclinationPartial),
        _rightAscensionPartial(rightAscensionPartial),
        _argPerigeePartial(argPerigeePartial),
        _trueAnomalyPartial(trueAnomalyPartial)
    {
    }
    Keplerian operator*(const Time& time) const;

  private:
    Velocity _semimajorPartial;
    UnitlessPerTime _eccentricityPartial;
    AngularRate _inclinationPartial;
    AngularRate _rightAscensionPartial;
    AngularRate _argPerigeePartial;
    AngularRate _trueAnomalyPartial;
};

} // namespace astro