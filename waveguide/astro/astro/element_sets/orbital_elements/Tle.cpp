#include <astro/element_sets/orbital_elements/Tle.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/element_sets/orbital_elements/Equinoctial.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
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

namespace astro {

Tle::Tle(const Keplerian& elements, const AstrodynamicsSystem& sys)
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
    _x = DcmPeri2Eci11 * xPeri + DcmPeri2Eci12 * yPeri;
    _y = DcmPeri2Eci21 * xPeri + DcmPeri2Eci22 * yPeri;
    _z = DcmPeri2Eci31 * xPeri + DcmPeri2Eci32 * yPeri;

    _vx = DcmPeri2Eci11 * vxPeri + DcmPeri2Eci12 * vyPeri;
    _vy = DcmPeri2Eci21 * vxPeri + DcmPeri2Eci22 * vyPeri;
    _vz = DcmPeri2Eci31 * vxPeri + DcmPeri2Eci32 * vyPeri;
}


Tle::Tle(const Equinoctial& elements, const AstrodynamicsSystem& sys)
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
    _x = rOverSSq * (cosL * (1.0 + alphaSq) + twoHK * sinL);
    _y = rOverSSq * (sinL * (1.0 - alphaSq) + twoHK * cosL);
    _z = 2.0 * rOverSSq * (h * sinL * -k * cosL);

    // Velocity
    _vx = -gamma * (sinL * (1.0 + alphaSq) - twoHK * (cosL + f) + g * (1.0 + alphaSq));
    _vy = -gamma * (cosL * (-1.0 + alphaSq) + twoHK * (sinL + g) + f * (-1.0 + alphaSq));
    _vz = 2.0 * gamma * (h * cosL + k * sinL + f * h + g * k);
}

// Copy constructor
Tle::Tle(const Tle& other) :
    _x(other._x),
    _y(other._y),
    _z(other._z),
    _vx(other._vx),
    _vy(other._vy),
    _vz(other._vz)
{
}

// Move constructor
Tle::Tle(Tle&& other) noexcept :
    _x(std::move(other._x)),
    _y(std::move(other._y)),
    _z(std::move(other._z)),
    _vx(std::move(other._vx)),
    _vy(std::move(other._vy)),
    _vz(std::move(other._vz))
{
}

// Move assignment operator
Tle& Tle::operator=(Tle&& other) noexcept
{
    if (this != &other) {
        _x  = std::move(other._x);
        _y  = std::move(other._y);
        _z  = std::move(other._z);
        _vx = std::move(other._vx);
        _vy = std::move(other._vy);
        _vz = std::move(other._vz);
    }
    return *this;
}

// Copy assignment operator
Tle& Tle::operator=(const Tle& other) { return *this = Tle(other); }

// Comparitors operators
bool Tle::operator==(const Tle& other) const
{
    return (_x == other._x && _y == other._y && _z == other._z && _vx == other._vx && _vy == other._vy && _vz == other._vz);
}

bool Tle::operator!=(const Tle& other) const { return !(*this == other); }


// Mathmatical operators
Tle Tle::operator+(const Tle& other) const
{
    return Tle(_x + other._x, _y + other._y, _z + other._z, _vx + other._vx, _vy + other._vy, _vz + other._vz);
}
Tle& Tle::operator+=(const Tle& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    _vx += other._vx;
    _vy += other._vy;
    _vz += other._vz;
    return *this;
}

Tle Tle::operator-(const Tle& other) const
{
    return Tle(_x - other._x, _y - other._y, _z - other._z, _vx - other._vx, _vy - other._vy, _vz - other._vz);
}
Tle& Tle::operator-=(const Tle& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    _vx -= other._vx;
    _vy -= other._vy;
    _vz -= other._vz;
    return *this;
}

Tle Tle::operator*(const Unitless& multiplier) const
{
    return Tle(_x * multiplier, _y * multiplier, _z * multiplier, _vx * multiplier, _vy * multiplier, _vz * multiplier);
}
Tle& Tle::operator*=(const Unitless& multiplier)
{
    _x *= multiplier;
    _y *= multiplier;
    _z *= multiplier;
    _vx *= multiplier;
    _vy *= multiplier;
    _vz *= multiplier;
    return *this;
}

TlePartial Tle::operator/(const Time& time) const
{
    return TlePartial(_x / time, _y / time, _z / time, _vx / time, _vy / time, _vz / time);
}

Tle Tle::operator/(const Unitless& divisor) const
{
    return Tle(_x / divisor, _y / divisor, _z / divisor, _vx / divisor, _vy / divisor, _vz / divisor);
}
Tle& Tle::operator/=(const Unitless& divisor)
{
    _x /= divisor;
    _y /= divisor;
    _z /= divisor;
    _vx /= divisor;
    _vy /= divisor;
    _vz /= divisor;
    return *this;
}

Tle Tle::interpolate(const Time& thisTime, const Time& otherTime, const Tle& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{

    const Distance interpx = math::interpolate<Time, Distance>({ thisTime, otherTime }, { _x, other.get_x() }, targetTime);
    const Distance interpy = math::interpolate<Time, Distance>({ thisTime, otherTime }, { _y, other.get_y() }, targetTime);
    const Distance interpz = math::interpolate<Time, Distance>({ thisTime, otherTime }, { _z, other.get_z() }, targetTime);
    const Velocity interpvx = math::interpolate<Time, Velocity>({ thisTime, otherTime }, { _vx, other.get_vx() }, targetTime);
    const Velocity interpvy = math::interpolate<Time, Velocity>({ thisTime, otherTime }, { _vy, other.get_vy() }, targetTime);
    const Velocity interpvz = math::interpolate<Time, Velocity>({ thisTime, otherTime }, { _vz, other.get_vz() }, targetTime);

    return Tle({ interpx, interpy, interpz }, { interpvx, interpvy, interpvz });
}

std::vector<Unitless> Tle::to_vector() const
{
    return { _x / detail::distance_unit,
             _y / detail::distance_unit,
             _z / detail::distance_unit,
             _vx / (detail::distance_unit / detail::time_unit),
             _vy / (detail::distance_unit / detail::time_unit),
             _vz / (detail::distance_unit / detail::time_unit) };
}

Tle TlePartial::operator*(const Time& time) const
{
    return Tle(_vx * time, _vy * time, _vz * time, _ax * time, _ay * time, _az * time);
}


std::ostream& operator<<(std::ostream& os, Tle const& elements)
{
    os << "[";
    os << elements.get_x() << ", ";
    os << elements.get_y() << ", ";
    os << elements.get_z() << ", ";
    os << elements.get_vx() << ", ";
    os << elements.get_vy() << ", ";
    os << elements.get_vz();
    os << "] (Tle)";
    return os;
}

} // namespace astro