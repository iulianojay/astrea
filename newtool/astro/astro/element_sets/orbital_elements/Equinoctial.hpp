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
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>

class Equinoctial {

    friend std::ostream& operator<<(std::ostream&, Equinoctial const&);

    using Distance = mp_units::quantity<mp_units::si::unit_symbols::km>;
    using Unitless = mp_units::quantity<mp_units::one>;
    using Angle    = mp_units::quantity<mp_units::si::unit_symbols::rad>;

  public:
    Equinoctial() :
        _semilatus{ 0.0 * mp_units::si::unit_symbols::km },
        _f{ 0.0 * mp_units::one },
        _g{ 0.0 * mp_units::one },
        _h{ 0.0 * mp_units::one },
        _k{ 0.0 * mp_units::one },
        _trueLongitude{ 0.0 * mp_units::si::unit_symbols::rad }
    {
    }
    Equinoctial(const Distance& semilatus, const Unitless& f, const Unitless& g, const Unitless& h, const Unitless& k, const Angle& trueLongitude) :
        _semilatus{ semilatus },
        _f{ f },
        _g{ g },
        _h{ h },
        _k{ k },
        _trueLongitude{ trueLongitude }
    {
    }
    Equinoctial(const OrbitalElements& elements, const AstrodynamicsSystem& sys);
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

    Equinoctial operator*(const double& multiplier) const;
    Equinoctial& operator*=(const double& multiplier);

    Equinoctial operator/(const double& divisor) const;
    Equinoctial& operator/=(const double& divisor);

    // Element access
    const Distance& get_semilatus() const { return _semilatus; }
    const Unitless& get_f() const { return _f; }
    const Unitless& get_g() const { return _g; }
    const Unitless& get_h() const { return _h; }
    const Unitless& get_k() const { return _k; }
    const Angle& get_true_longitude() const { return _trueLongitude; }

    size_t size() const { return 6; }

    constexpr EnumType get_set_id() const { return _setId; }
    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    std::vector<double> to_vector() const;
    void update_from_vector(const std::vector<double>& vec);

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
    using DistancePerTime = mp_units::quantity<mp_units::si::unit_symbols::km / mp_units::non_si::day>;
    using UnitlessPerTime = mp_units::quantity<mp_units::one / mp_units::non_si::day>;
    using AnglePerTime    = mp_units::quantity<mp_units::si::unit_symbols::rad / mp_units::non_si::day>;

  public:
    Equinoctial operator*(const Time& time);

  private:
    DistancePerTime _semilatusPerTime;
    UnitlessPerTime _fPerTime;
    UnitlessPerTime _gPerTime;
    UnitlessPerTime _hPerTime;
    UnitlessPerTime _kPerTime;
    AnglePerTime _trueLongitudePerTime;
};