#pragma once

#include <array>
#include <iomanip>
#include <iostream>
#include <variant>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>
#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

#include <astro/astro.fwd.hpp>
#include <astro/element_sets/ElementSet.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

class Equinoctial {

    friend std::ostream& operator<<(std::ostream&, Equinoctial const&);

  public:
    Equinoctial() :
        _semilatus(0.0 * mp_units::si::unit_symbols::km),
        _f(0.0 * mp_units::one),
        _g(0.0 * mp_units::one),
        _h(0.0 * mp_units::one),
        _k(0.0 * mp_units::one),
        _trueLongitude(0.0 * mp_units::angular::unit_symbols::rad)
    {
    }
    Equinoctial(const Distance& semilatus, const Unitless& f, const Unitless& g, const Unitless& h, const Unitless& k, const Angle& trueLongitude) :
        _semilatus(semilatus),
        _f(f),
        _g(g),
        _h(h),
        _k(k),
        _trueLongitude(trueLongitude)
    {
    }
    Equinoctial(const Equinoctial& elements, const AstrodynamicsSystem& sys) :
        Equinoctial(elements)
    {
    }
    Equinoctial(const Keplerian& elements, const AstrodynamicsSystem& sys);

    // Copy constructor
    Equinoctial(const Equinoctial&);

    // Move constructor
    Equinoctial(Equinoctial&&) noexcept;

    // Move assignment operator
    Equinoctial& operator=(Equinoctial&&) noexcept;

    // Copy assignment operator
    Equinoctial& operator=(const Equinoctial&);

    ~Equinoctial() = default;

    // Comparitors operators
    bool operator==(const Equinoctial& other) const;
    bool operator!=(const Equinoctial& other) const;

    // Mathmatical operators
    Equinoctial operator+(const Equinoctial& other) const;
    Equinoctial& operator+=(const Equinoctial& other);

    Equinoctial operator-(const Equinoctial& other) const;
    Equinoctial& operator-=(const Equinoctial& other);

    Equinoctial operator*(const Unitless& multiplier) const;
    Equinoctial& operator*=(const Unitless& multiplier);

    Equinoctial operator/(const Unitless& divisor) const;
    Equinoctial& operator/=(const Unitless& divisor);

    // Element access
    const Distance& get_semilatus() const { return _semilatus; }
    const Unitless& get_f() const { return _f; }
    const Unitless& get_g() const { return _g; }
    const Unitless& get_h() const { return _h; }
    const Unitless& get_k() const { return _k; }
    const Angle& get_true_longitude() const { return _trueLongitude; }

    size_t size() const { return 6; }

    constexpr EnumType get_set_id() const { return _setId; }
    Equinoctial
        interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    std::vector<double> to_vector() const;

  private:
    constexpr static EnumType _setId = std::to_underlying(ElementSet::EQUINOCTIAL);

    Distance _semilatus;
    Unitless _f;
    Unitless _g;
    Unitless _h;
    Unitless _k;
    Angle _trueLongitude;
};

class EquinoctialPartial {

  public:
    EquinoctialPartial() = default;
    EquinoctialPartial(
        const Velocity& semilatusPartial,
        const UnitlessPerTime& fPartial,
        const UnitlessPerTime& gPartial,
        const UnitlessPerTime& hPartial,
        const UnitlessPerTime& kPartial,
        const AngularRate& trueLongitudePartial
    ) :
        _semilatusPartial(semilatusPartial),
        _fPartial(fPartial),
        _gPartial(gPartial),
        _hPartial(hPartial),
        _kPartial(kPartial),
        _trueLongitudePartial(trueLongitudePartial)
    {
    }
    Equinoctial operator*(const Time& time) const;

  private:
    Velocity _semilatusPartial;
    UnitlessPerTime _fPartial;
    UnitlessPerTime _gPartial;
    UnitlessPerTime _hPartial;
    UnitlessPerTime _kPartial;
    AngularRate _trueLongitudePartial;
};