#include <astro/element_sets/orbital_elements/Equinoctial.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Time.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


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
    _trueLongitude = raan + argPer + theta;
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


OrbitalElements
    Equinoctial::interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    Equinoctial elements = other.to_equinoctial(sys);

    const Distance interpSemimajor =
        math::interpolate<Time, Distance>({ thisTime, otherTime }, { _semilatus, elements.get_semilatus() }, targetTime);
    const Unitless interpEcc = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _f, elements.get_f() }, targetTime);
    const Unitless interpInc = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _g, elements.get_g() }, targetTime);
    const Unitless interpRaan = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _h, elements.get_h() }, targetTime);
    const Unitless interpArgPer = math::interpolate<Time, Unitless>({ thisTime, otherTime }, { _k, elements.get_k() }, targetTime);
    const Angle interpTheta =
        math::interpolate<Time, Angle>({ thisTime, otherTime }, { _trueLongitude, elements.get_true_longitude() }, targetTime);

    Equinoctial iterpKepl(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);

    return OrbitalElements(iterpKepl);
}

std::vector<double> Equinoctial::to_vector() const
{
    return { _semilatus.numerical_value_ref_in(_semilatus.unit),
             _f.numerical_value_ref_in(_f.unit),
             _g.numerical_value_ref_in(_g.unit),
             _h.numerical_value_ref_in(_h.unit),
             _k.numerical_value_ref_in(_k.unit),
             _trueLongitude.numerical_value_ref_in(_trueLongitude.unit) };
}

void Equinoctial::update_from_vector(const std::vector<double>& vec)
{
    _semilatus     = vec[0] * km;
    _f             = vec[1] * one;
    _g             = vec[2] * one;
    _h             = vec[3] * one;
    _k             = vec[4] * one;
    _trueLongitude = vec[5] * rad;
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