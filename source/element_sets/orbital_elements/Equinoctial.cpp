#include "Equinoctial.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "AstrodynamicsSystem.hpp"
#include "Keplerian.hpp"
#include "interpolation.hpp"
#include "Time.hpp"
#include "OrbitalElements.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


Equinoctial::Equinoctial(const Keplerian& elements, const AstrodynamicsSystem& sys) {

    // Get r and v
    const auto& a = elements.get_semimajor();
    const auto& ecc = elements.get_eccentricity();
    const auto& inc = elements.get_inclination();
    const auto& raan = elements.get_right_ascension();
    const auto& argPer = elements.get_argument_of_perigee();
    const auto& theta = elements.get_true_anomaly();

    // Semilatus rectum
    _semilatus = a*(1 - ecc*ecc);

    // Non-dimensionalized parameters
    _f = ecc*cos(argPer + raan);
    _g = ecc*sin(argPer + raan);
    _h = tan(inc/2.0)*cos(raan);
    _k = tan(inc/2.0)*sin(raan);

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
{}

// Move constructor
Equinoctial::Equinoctial(Equinoctial&& other) noexcept :
    _semilatus(std::move(other._semilatus)),
    _f(std::move(other._f)),
    _g(std::move(other._g)),
    _h(std::move(other._h)),
    _k(std::move(other._k)),
    _trueLongitude(std::move(other._trueLongitude))
{}

// Move assignment operator
Equinoctial& Equinoctial::operator=(Equinoctial&& other) noexcept {
    if (this != &other) {
        _semilatus = std::move(other._semilatus);
        _f = std::move(other._f);
        _g = std::move(other._g);
        _h = std::move(other._h);
        _k = std::move(other._k);
        _trueLongitude = std::move(other._trueLongitude);
    }
    return *this;
}

// Copy assignment operator
Equinoctial& Equinoctial::operator=(const Equinoctial& other) {
    return *this = Equinoctial(other);
}


OrbitalElements Equinoctial::interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const {
    Equinoctial elements = other.to_keplerian(sys);

    const quantity<km>  interpSemimajor = ::interpolate({thisTime, otherTime}, {_semilatus,      elements.get_semilatus()},           targetTime);
    const quantity<one> interpEcc       = ::interpolate({thisTime, otherTime}, {_f,   elements.get_f()},        targetTime);
    const quantity<rad> interpInc       = ::interpolate({thisTime, otherTime}, {_g,    elements.get_g()},         targetTime);
    const quantity<rad> interpRaan      = ::interpolate({thisTime, otherTime}, {_h, elements.get_h()},     targetTime);
    const quantity<rad> interpArgPer    = ::interpolate({thisTime, otherTime}, {_k,     elements.get_k()}, targetTime);
    const quantity<rad> interpTheta     = ::interpolate({thisTime, otherTime}, {_trueLongitude,    elements.get_true_longitude()},        targetTime);

    Equinoctial iterpKepl(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);

    return OrbitalElements(iterpKepl);
}

std::vector<double> Equinoctial::to_vector() const {
    return {
        value_cast<double>(_semilatus),
        value_cast<double>(_f),
        value_cast<double>(_g),
        value_cast<double>(_h),
        value_cast<double>(_k),
        value_cast<double>(_trueLongitude)
    };
}

void Keplerian::update_from_vector(const std::vector<double>& vec) {
    _semilatus = vec[0] * km;
    _f = vec[1] * one;
    _g = vec[2] * one;
    _h = vec[3] * one;
    _k = vec[4] * one;
    _trueLongitude = vec[5] * rad;
}

std::ostream &operator<<(std::ostream& os, Equinoctial const& elements) {
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