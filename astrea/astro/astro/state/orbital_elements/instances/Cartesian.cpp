#include <astro/state/orbital_elements/instances/Cartesian.hpp>

#include <iomanip>
#include <iostream>

// mp-units
#include <mp-units/math.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::non_si;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

Cartesian Cartesian::LEO(const AstrodynamicsSystem& system) { return Cartesian(Keplerian::LEO(), system); }
Cartesian Cartesian::LMEO(const AstrodynamicsSystem& system) { return Cartesian(Keplerian::LMEO(), system); }
Cartesian Cartesian::GPS(const AstrodynamicsSystem& system) { return Cartesian(Keplerian::GPS(), system); }
Cartesian Cartesian::HMEO(const AstrodynamicsSystem& system) { return Cartesian(Keplerian::HMEO(), system); }
Cartesian Cartesian::GEO(const AstrodynamicsSystem& system) { return Cartesian(Keplerian::GEO(), system); }

Cartesian::Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys)
{

    // Get mu
    const quantity mu = sys.get_center()->get_mu();

    // Extract elements
    const auto& a     = elements.get_semimajor();
    const auto& ecc   = elements.get_eccentricity();
    const auto& inc   = elements.get_inclination();
    const auto& raan  = elements.get_right_ascension();
    const auto& w     = elements.get_argument_of_perigee();
    const auto& theta = elements.get_true_anomaly();

    // Precalculate
    const quantity cosTheta = cos(theta);
    const quantity sinTheta = sin(theta);

    const quantity cosW = cos(w);
    const quantity sinW = sin(w);

    const quantity cosRaan = cos(raan);
    const quantity sinRaan = sin(raan);

    const quantity cosInc = cos(inc);
    const quantity sinInc = sin(inc);

    const quantity h = sqrt(mu * a * (1.0 - ecc * ecc));
    const quantity A = h * h / mu / (1.0 + ecc * cosTheta);
    const quantity B = mu / h;

    // Perifocal Coordinates
    const quantity xPeri = A * cosTheta;
    const quantity yPeri = A * sinTheta;

    const quantity vxPeri = -B * sinTheta;
    const quantity vyPeri = B * (ecc + cosTheta);

    // Preallocate Dcm values for speed
    const quantity DcmPeri2Eci11 = (cosW * cosRaan - sinW * cosInc * sinRaan);
    const quantity DcmPeri2Eci12 = (-sinW * cosRaan - cosW * cosInc * sinRaan);

    const quantity DcmPeri2Eci21 = (cosW * sinRaan + sinW * cosInc * cosRaan);
    const quantity DcmPeri2Eci22 = (-sinW * sinRaan + cosW * cosInc * cosRaan);

    const quantity DcmPeri2Eci31 = sinInc * sinW;
    const quantity DcmPeri2Eci32 = sinInc * cosW;

    // Inertial position and _velocity
    _r[0] = DcmPeri2Eci11 * xPeri + DcmPeri2Eci12 * yPeri;
    _r[1] = DcmPeri2Eci21 * xPeri + DcmPeri2Eci22 * yPeri;
    _r[2] = DcmPeri2Eci31 * xPeri + DcmPeri2Eci32 * yPeri;

    _v[0] = DcmPeri2Eci11 * vxPeri + DcmPeri2Eci12 * vyPeri;
    _v[1] = DcmPeri2Eci21 * vxPeri + DcmPeri2Eci22 * vyPeri;
    _v[2] = DcmPeri2Eci31 * vxPeri + DcmPeri2Eci32 * vyPeri;
}


Cartesian::Cartesian(const Equinoctial& elements, const AstrodynamicsSystem& sys)
{

    // Get mu
    const quantity mu = sys.get_center()->get_mu();

    // Extract
    const auto& semilatus     = elements.get_semilatus();
    const auto& f             = elements.get_f();
    const auto& g             = elements.get_g();
    const auto& h             = elements.get_h();
    const auto& k             = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Catch default/nonsense case
    if (semilatus == 0.0 * km) {
        _r[0] = 0.0 * km;
        _r[1] = 0.0 * km;
        _r[2] = 0.0 * km;
        _v[0] = 0.0 * km / s;
        _v[1] = 0.0 * km / s;
        _v[2] = 0.0 * km / s;
        return;
    }

    // Precalculate
    const auto cosL = cos(trueLongitude);
    const auto sinL = sin(trueLongitude);

    const auto alphaSq = h * h - k * k;
    const auto sSq     = 1.0 + h * h + k * k;
    const auto w       = 1.0 + f * cosL + g * sinL;
    const auto r       = semilatus / w;

    const auto rOverSSq = r / sSq;
    const auto twoHK    = 2.0 * h * k;

    const auto gamma = 1.0 / sSq * sqrt(mu / semilatus);

    // Radius
    _r[0] = rOverSSq * (cosL * (1.0 + alphaSq) + twoHK * sinL);
    _r[1] = rOverSSq * (sinL * (1.0 - alphaSq) + twoHK * cosL);
    _r[2] = 2.0 * rOverSSq * (h * sinL - k * cosL);

    // Velocity
    _v[0] = -gamma * (sinL * (1.0 + alphaSq) - twoHK * (cosL + f) + g * (1.0 + alphaSq));
    _v[1] = -gamma * (cosL * (-1.0 + alphaSq) + twoHK * (sinL + g) + f * (-1.0 + alphaSq));
    _v[2] = 2.0 * gamma * (h * cosL + k * sinL + f * h + g * k);
}

Cartesian::Cartesian(const OrbitalElements& elements, const AstrodynamicsSystem& sys)
{
    *this = elements.in_orbital_set<Cartesian>(sys);
}

// Copy constructor
Cartesian::Cartesian(const Cartesian& other) :
    _r(other._r),
    _v(other._v)
{
}

// Move constructor
Cartesian::Cartesian(Cartesian&& other) noexcept :
    _r(std::move(other._r)),
    _v(std::move(other._v))
{
}

// Move assignment operator
Cartesian& Cartesian::operator=(Cartesian&& other) noexcept
{
    if (this != &other) {
        _r = std::move(other._r);
        _v = std::move(other._v);
    }
    return *this;
}

// Copy assignment operator
Cartesian& Cartesian::operator=(const Cartesian& other) { return *this = Cartesian(other); }

// Comparitors operators
bool Cartesian::operator==(const Cartesian& other) const { return (_r == other._r && _v == other._v); }

bool Cartesian::operator!=(const Cartesian& other) const { return !(*this == other); }


// Mathmatical operators
Cartesian Cartesian::operator+(const Cartesian& other) const { return Cartesian(_r + other._r, _v + other._v); }
Cartesian& Cartesian::operator+=(const Cartesian& other)
{
    _r += other._r;
    _v += other._v;
    return *this;
}

Cartesian Cartesian::operator+(const RadiusVector<ECI>& r) const { return Cartesian(_r + r, _v); }
Cartesian& Cartesian::operator+=(const RadiusVector<ECI>& r)
{
    _r += r;
    return *this;
}

Cartesian Cartesian::operator+(const VelocityVector<ECI>& v) const { return Cartesian(_r, _v + v); }
Cartesian& Cartesian::operator+=(const VelocityVector<ECI>& v)
{
    _v += v;
    return *this;
}

Cartesian Cartesian::operator-(const Cartesian& other) const { return Cartesian(_r - other._r, _v - other._v); }
Cartesian& Cartesian::operator-=(const Cartesian& other)
{
    _r -= other._r;
    _v -= other._v;
    return *this;
}

Cartesian Cartesian::operator-(const RadiusVector<ECI>& r) const { return Cartesian(_r - r, _v); }
Cartesian& Cartesian::operator-=(const RadiusVector<ECI>& r)
{
    _r -= r;
    return *this;
}

Cartesian Cartesian::operator-(const VelocityVector<ECI>& v) const { return Cartesian(_r, _v - v); }
Cartesian& Cartesian::operator-=(const VelocityVector<ECI>& v)
{
    _v -= v;
    return *this;
}

Cartesian Cartesian::operator*(const Unitless& multiplier) const { return Cartesian(_r * multiplier, _v * multiplier); }
Cartesian& Cartesian::operator*=(const Unitless& multiplier)
{
    _r *= multiplier;
    _v *= multiplier;
    return *this;
}

CartesianPartial Cartesian::operator/(const Time& time) const { return CartesianPartial(_r / time, _v / time); }

Cartesian Cartesian::operator/(const Unitless& divisor) const { return Cartesian(_r / divisor, _v / divisor); }
Cartesian& Cartesian::operator/=(const Unitless& divisor)
{
    _r /= divisor;
    _v /= divisor;
    return *this;
}

Cartesian
    Cartesian::interpolate(const Time& thisTime, const Time& otherTime, const Cartesian& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    const Keplerian kepl      = Keplerian(*this, sys);
    const Keplerian otherKepl = Keplerian(other, sys);

    const Keplerian output = kepl.interpolate(thisTime, otherTime, otherKepl, sys, targetTime);

    return Cartesian(output, sys);
}

std::vector<Unitless> Cartesian::to_vector() const
{
    return { _r[0] / astrea::detail::distance_unit,
             _r[1] / astrea::detail::distance_unit,
             _r[2] / astrea::detail::distance_unit,
             _v[0] / (astrea::detail::distance_unit / astrea::detail::time_unit),
             _v[1] / (astrea::detail::distance_unit / astrea::detail::time_unit),
             _v[2] / (astrea::detail::distance_unit / astrea::detail::time_unit) };
}

Cartesian CartesianPartial::operator*(const Time& time) const { return Cartesian(_v * time, _a * time); }

std::ostream& operator<<(std::ostream& os, Cartesian const& elements)
{
    os << "[";
    os << elements.get_x() << ", ";
    os << elements.get_y() << ", ";
    os << elements.get_z() << ", ";
    os << elements.get_vx() << ", ";
    os << elements.get_vy() << ", ";
    os << elements.get_vz();
    os << "] (Cartesian)";
    return os;
}

std::ostream& operator<<(std::ostream& os, CartesianPartial const& elements)
{
    os << "[";
    os << elements._v[0] << ", ";
    os << elements._v[1] << ", ";
    os << elements._v[2] << ", ";
    os << elements._a[0] << ", ";
    os << elements._a[1] << ", ";
    os << elements._a[2];
    os << "] (CartesianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea