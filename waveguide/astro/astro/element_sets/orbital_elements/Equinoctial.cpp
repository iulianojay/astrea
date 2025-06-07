#include <astro/element_sets/orbital_elements/Equinoctial.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <math/interpolation.hpp>

#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>


using namespace mp_units;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astro {

Equinoctial Equinoctial::LEO() { return Equinoctial(Keplerian::LEO(), AstrodynamicsSystem()); }
Equinoctial Equinoctial::LMEO() { return Equinoctial(Keplerian::LMEO(), AstrodynamicsSystem()); }
Equinoctial Equinoctial::GPS() { return Equinoctial(Keplerian::GPS(), AstrodynamicsSystem()); }
Equinoctial Equinoctial::HMEO() { return Equinoctial(Keplerian::HMEO(), AstrodynamicsSystem()); }
Equinoctial Equinoctial::GEO() { return Equinoctial(Keplerian::GEO(), AstrodynamicsSystem()); }

Equinoctial::Equinoctial(const Keplerian& elements, const AstrodynamicsSystem& sys)
{

    // Get r and v
    const auto& a      = elements.get_semimajor();
    const auto& ecc    = elements.get_eccentricity();
    const auto& inc    = elements.get_inclination();
    const auto& raan   = elements.get_right_ascension();
    const auto& argPer = elements.get_argument_of_perigee();
    const auto& theta  = elements.get_true_anomaly();

    // Semilatus rectum
    _semilatus = a * (1 - ecc * ecc);

    // Non-dimensionalized parameters
    _f = ecc * cos(argPer + raan);
    _g = ecc * sin(argPer + raan);
    _h = tan(inc / 2.0) * cos(raan);
    _k = tan(inc / 2.0) * sin(raan);

    // True longitude
    _trueLongitude = conversions::sanitize_angle(raan + argPer + theta);
}

Equinoctial::Equinoctial(const Cartesian& elements, const AstrodynamicsSystem& sys) :
    Equinoctial(Keplerian(elements, sys), sys)
{
}

// Copy constructor
Equinoctial::Equinoctial(const Equinoctial& other) :
    _semilatus(other._semilatus),
    _f(other._f),
    _g(other._g),
    _h(other._h),
    _k(other._k),
    _trueLongitude(other._trueLongitude)
{
}

// Move constructor
Equinoctial::Equinoctial(Equinoctial&& other) noexcept :
    _semilatus(std::move(other._semilatus)),
    _f(std::move(other._f)),
    _g(std::move(other._g)),
    _h(std::move(other._h)),
    _k(std::move(other._k)),
    _trueLongitude(std::move(other._trueLongitude))
{
}

// Move assignment operator
Equinoctial& Equinoctial::operator=(Equinoctial&& other) noexcept
{
    if (this != &other) {
        _semilatus     = std::move(other._semilatus);
        _f             = std::move(other._f);
        _g             = std::move(other._g);
        _h             = std::move(other._h);
        _k             = std::move(other._k);
        _trueLongitude = std::move(other._trueLongitude);
    }
    return *this;
}

// Copy assignment operator
Equinoctial& Equinoctial::operator=(const Equinoctial& other) { return *this = Equinoctial(other); }

// Comparitors operators
bool Equinoctial::operator==(const Equinoctial& other) const
{
    return (
        _semilatus == other._semilatus && _f == other._f && _g == other._g && _h == other._h && _k == other._k &&
        _trueLongitude == other._trueLongitude
    );
}

bool Equinoctial::operator!=(const Equinoctial& other) const { return !(*this == other); }


// Mathmatical operators
Equinoctial Equinoctial::operator+(const Equinoctial& other) const
{
    return Equinoctial(
        _semilatus + other._semilatus,
        _f + other._f,
        _g + other._g,
        _h + other._h,
        _k + other._k,
        _trueLongitude + other._trueLongitude
    );
}
Equinoctial& Equinoctial::operator+=(const Equinoctial& other)
{
    _semilatus += other._semilatus;
    _f += other._f;
    _g += other._g;
    _h += other._h;
    _k += other._k;
    _trueLongitude += other._trueLongitude;
    return *this;
}

Equinoctial Equinoctial::operator-(const Equinoctial& other) const
{
    return Equinoctial(
        _semilatus - other._semilatus,
        _f - other._f,
        _g - other._g,
        _h - other._h,
        _k - other._k,
        _trueLongitude - other._trueLongitude
    );
}
Equinoctial& Equinoctial::operator-=(const Equinoctial& other)
{
    _semilatus -= other._semilatus;
    _f -= other._f;
    _g -= other._g;
    _h -= other._h;
    _k -= other._k;
    _trueLongitude -= other._trueLongitude;
    return *this;
}

Equinoctial Equinoctial::operator*(const Unitless& multiplier) const
{
    return Equinoctial(_semilatus * multiplier, _f * multiplier, _g * multiplier, _h * multiplier, _k * multiplier, _trueLongitude * multiplier);
}
Equinoctial& Equinoctial::operator*=(const Unitless& multiplier)
{
    _semilatus *= multiplier;
    _f *= multiplier;
    _g *= multiplier;
    _h *= multiplier;
    _k *= multiplier;
    _trueLongitude *= multiplier;
    return *this;
}

EquinoctialPartial Equinoctial::operator/(const Time& time) const
{
    return EquinoctialPartial(_semilatus / time, _f / time, _g / time, _h / time, _k / time, _trueLongitude / time);
}

Equinoctial Equinoctial::operator/(const Unitless& divisor) const
{
    return Equinoctial(_semilatus / divisor, _f / divisor, _g / divisor, _h / divisor, _k / divisor, _trueLongitude / divisor);
}

Equinoctial& Equinoctial::operator/=(const Unitless& divisor)
{
    _semilatus /= divisor;
    _f /= divisor;
    _g /= divisor;
    _h /= divisor;
    _k /= divisor;
    _trueLongitude /= divisor;
    return *this;
}


Equinoctial
    Equinoctial::interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    const Distance interpSemimajor =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _semilatus, other.get_semilatus() }, targetTime);
    const Unitless interpEcc = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _f, other.get_f() }, targetTime);
    const Unitless interpInc = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _g, other.get_g() }, targetTime);
    const Unitless interpRaan = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _h, other.get_h() }, targetTime);
    const Unitless interpArgPer = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _k, other.get_k() }, targetTime);
    const Angle interpTheta =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _trueLongitude, other.get_true_longitude() }, targetTime);

    return Equinoctial(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

std::vector<Unitless> Equinoctial::to_vector() const
{
    return { _semilatus / detail::distance_unit, _f, _g, _h, _k, _trueLongitude / detail::angle_unit };
}


Equinoctial EquinoctialPartial::operator*(const Time& time) const
{
    return Equinoctial(_semilatusPartial * time, _fPartial * time, _gPartial * time, _hPartial * time, _kPartial * time, _trueLongitudePartial * time);
}

std::ostream& operator<<(std::ostream& os, Equinoctial const& elements)
{
    os << "[";
    os << elements.get_semilatus() << ", ";
    os << elements.get_f() << ", ";
    os << elements.get_g() << ", ";
    os << elements.get_h() << ", ";
    os << elements.get_k() << ", ";
    os << elements.get_true_longitude();
    os << "] (Equinoctial)";
    return os;
}

} // namespace astro