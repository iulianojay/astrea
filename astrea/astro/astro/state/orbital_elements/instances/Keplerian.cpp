#include <astro/state/orbital_elements/instances/Keplerian.hpp>

#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/si/math.h>

#include <astro/state/orbital_elements/instances/Cartesian.hpp>
#include <astro/state/orbital_elements/instances/Equinoctial.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>
#include <math/interpolation.hpp>


using namespace mp_units;
using namespace mp_units::angular;
using angular::unit_symbols::deg;
using angular::unit_symbols::rad;
using si::unit_symbols::km;
using si::unit_symbols::s;

namespace astrea {
namespace astro {

Keplerian Keplerian::LEO() { return Keplerian(7000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::LMEO() { return Keplerian(10000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::GPS() { return Keplerian(22000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::HMEO() { return Keplerian(30000.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }
Keplerian Keplerian::GEO() { return Keplerian(42164.0 * km, 0.0 * one, 0.0 * rad, 0.0 * rad, 0.0 * rad, 0.0 * rad); }

Keplerian::Keplerian(const Cartesian& elements, const AstrodynamicsSystem& sys)
{

    /*
        Force rounding errors to assume zero values for angles. Assume complex
        results are the result of rounding errors. Flip values near their antipode
        to zero for simplicity. Assume NaN results are from singularities and force
        values to be 0.

        No idea how much of this is just wrong.
    */
    static const quantity<one> tol        = 1.0e-10 * one;
    static const quantity<rad> angularTol = 1.0e-10 * rad;
    static const quantity piRad           = 1.0 * (mag<pi> * rad);
    static const quantity twoPiRad        = 2.0 * (mag<pi> * rad);

    // Get mu
    const quantity mu = sys.get_center()->get_mu();

    // Get r and v
    const auto& x  = elements.get_x();
    const auto& y  = elements.get_y();
    const auto& z  = elements.get_z();
    const auto& vx = elements.get_vx();
    const auto& vy = elements.get_vy();
    const auto& vz = elements.get_vz();

    const quantity R = sqrt(x * x + y * y + z * z);
    const quantity V = sqrt(vx * vx + vy * vy + vz * vz);

    // Catch default/nonsense case
    if (R == 0.0 * km) {
        _semimajor      = 0.0 * km;
        _eccentricity   = 0.0 * one;
        _inclination    = 0.0 * rad;
        _rightAscension = 0.0 * rad;
        _argPerigee     = 0.0 * rad;
        _trueAnomaly    = 0.0 * rad;
        return;
    }

    // Specific Relative Angular Momentum
    const quantity hx = y * vz - z * vy; // h = cross(r, v)
    const quantity hy = z * vx - x * vz;
    const quantity hz = x * vy - y * vx;

    const quantity normH = sqrt(hx * hx + hy * hy + hz * hz);

    // Setup
    const quantity Nx = -hy; // N = cross([0 0 1], h)
    const quantity Ny = hx;

    const quantity normN = sqrt(Nx * Nx + Ny * Ny);

    // Semimajor Axis
    _semimajor = 1.0 / (2.0 / R - V * V / mu);

    // Eccentricity
    const quantity dotRV                = x * vx + y * vy + z * vz;
    const quantity oneOverMu            = (1.0 / mu);
    const quantity vSquaredMinuMuTimesR = (V * V - mu / R);

    const quantity eccX = oneOverMu * (vSquaredMinuMuTimesR * x - dotRV * vx);
    const quantity eccY = oneOverMu * (vSquaredMinuMuTimesR * y - dotRV * vy);
    const quantity eccZ = oneOverMu * (vSquaredMinuMuTimesR * z - dotRV * vz);

    _eccentricity = sqrt(eccX * eccX + eccY * eccY + eccZ * eccZ);

    /*
        If the orbit has an _inclination of exactly 0, w is ill-defined, the
        _eccentricity vector is ill-defined, and true anomaly is ill defined. Force
        _eccentricity very close to 0 be exactly 0 to avoid issues where w and
        anomaly flail around wildly as ecc fluctuates.
    */
    if (_eccentricity < tol) { _eccentricity = 0.0 * one; }

    // Inclination (rad)
    _inclination = acos(hz / normH);
    if (abs(_inclination - piRad) < angularTol) { _inclination = 0.0 * rad; }

    // Right Ascension of Ascending Node (rad)
    if (_inclination == 0.0 * rad) { // No nodal line
        _rightAscension = 0.0 * rad;
    }
    else {
        if (Ny > 0.0 * (km * km / s)) { _rightAscension = acos(Nx / normN); }
        else {
            _rightAscension = twoPiRad - acos(Nx / normN);
        }

        if (abs(_rightAscension - twoPiRad) < angularTol) { _rightAscension = 0.0 * rad; }
    }

    // True Anomaly (rad)
    if (_eccentricity == 0.0 * one) {    // No argument of perigee, use nodal line
        if (_inclination == 0.0 * rad) { // No nodal line, use true longitude
            if (vx <= 0.0 * km / s) { _trueAnomaly = acos(x / R); }
            else {
                _trueAnomaly = 2 * piRad - acos(x / R);
            }
        }
        else { // Use argument of latitude
            const quantity nDotR = Nx * x + Ny * y;
            if (z >= 0.0 * km) { _trueAnomaly = acos(nDotR / (normN * R)); }
            else {
                _trueAnomaly = 2 * piRad - acos(nDotR / (normN * R));
            }
        }
    }
    else {
        const quantity eccDotR = eccX * x + eccY * y + eccZ * z;
        if (dotRV >= 0.0 * (km * km / s)) { _trueAnomaly = acos(eccDotR / (_eccentricity * R)); }
        else {
            _trueAnomaly = twoPiRad - acos(eccDotR / (_eccentricity * R));
        }
    }

    // Argument of Parigee (rad)
    if (_eccentricity == 0.0 * one) { // Ill-defined. Assume zero
        _argPerigee = 0.0 * rad;
    }
    else if (_inclination == 0.0 * rad) { // No nodal line, use ecc vec
        if (hz > 0.0 * (km * km / s)) { _argPerigee = atan2(eccY, eccX); }
        else {
            _argPerigee = 2 * piRad - atan2(eccY, eccX);
        }
    }
    else {
        const quantity eccDotN = eccX * Nx + eccY * Ny;
        if (eccZ < 0.0 * one) { _argPerigee = twoPiRad - acos(eccDotN / (_eccentricity * normN)); }
        else {
            _argPerigee = acos(eccDotN / (_eccentricity * normN));
        }
    }

    // Catch garbage
    if (normN == 0.0 * (km * km / s) || abs(_argPerigee - twoPiRad) < angularTol) {
        _trueAnomaly += _argPerigee;
        _argPerigee = 0.0 * rad;
    }

    if (abs(_trueAnomaly - twoPiRad) < angularTol) { _trueAnomaly = 0.0 * rad; }

    sanitize_angles();
}

Keplerian::Keplerian(const Equinoctial& elements, const AstrodynamicsSystem& sys)
{

    const auto& semilatus     = elements.get_semilatus();
    const auto& f             = elements.get_f();
    const auto& g             = elements.get_g();
    const auto& h             = elements.get_h();
    const auto& k             = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Semimajor
    const auto eccSq = f * f + g * g;
    _semimajor       = semilatus / (1 - eccSq);

    // Eccentricity
    _eccentricity = sqrt(eccSq);

    // Inclination
    const auto hSqPlusKSq = h * h + k * k;
    _inclination          = atan2(2.0 * sqrt(hSqPlusKSq), 1 - hSqPlusKSq);

    // Arg perigee
    _argPerigee = atan2(g * h - f * k, f * h + g * k);

    // Right ascension
    _rightAscension = atan2(k, h);

    // Anomaly
    _trueAnomaly = trueLongitude - (_rightAscension + _argPerigee);

    sanitize_angles();
}

// Copy constructor
Keplerian::Keplerian(const Keplerian& other) :
    _semimajor(other._semimajor),
    _eccentricity(other._eccentricity),
    _inclination(other._inclination),
    _rightAscension(other._rightAscension),
    _argPerigee(other._argPerigee),
    _trueAnomaly(other._trueAnomaly)
{
}

// Move constructor
Keplerian::Keplerian(Keplerian&& other) noexcept :
    _semimajor(std::move(other._semimajor)),
    _eccentricity(std::move(other._eccentricity)),
    _inclination(std::move(other._inclination)),
    _rightAscension(std::move(other._rightAscension)),
    _argPerigee(std::move(other._argPerigee)),
    _trueAnomaly(std::move(other._trueAnomaly))
{
}

// Move assignment operator
Keplerian& Keplerian::operator=(Keplerian&& other) noexcept
{
    if (this != &other) {
        _semimajor      = std::move(other._semimajor);
        _eccentricity   = std::move(other._eccentricity);
        _inclination    = std::move(other._inclination);
        _rightAscension = std::move(other._rightAscension);
        _argPerigee     = std::move(other._argPerigee);
        _trueAnomaly    = std::move(other._trueAnomaly);
    }
    return *this;
}

// Copy assignment operator
Keplerian& Keplerian::operator=(const Keplerian& other) { return *this = Keplerian(other); }

// Comparitors operators
bool Keplerian::operator==(const Keplerian& other) const
{
    return (
        _semimajor == other._semimajor && _eccentricity == other._eccentricity && _inclination == other._inclination &&
        _rightAscension == other._rightAscension && _argPerigee == other._argPerigee && _trueAnomaly == other._trueAnomaly
    );
}

bool Keplerian::operator!=(const Keplerian& other) const { return !(*this == other); }


// Mathmatical operators
Keplerian Keplerian::operator+(const Keplerian& other) const
{
    return Keplerian(
        _semimajor + other._semimajor,
        _eccentricity + other._eccentricity,
        _inclination + other._inclination,
        _rightAscension + other._rightAscension,
        _argPerigee + other._argPerigee,
        _trueAnomaly + other._trueAnomaly
    );
}
Keplerian& Keplerian::operator+=(const Keplerian& other)
{
    _semimajor += other._semimajor;
    _eccentricity += other._eccentricity;
    _inclination += other._inclination;
    _rightAscension += other._rightAscension;
    _argPerigee += other._argPerigee;
    _trueAnomaly += other._trueAnomaly;
    return *this;
}

Keplerian Keplerian::operator-(const Keplerian& other) const
{
    return Keplerian(
        _semimajor - other._semimajor,
        _eccentricity - other._eccentricity,
        _inclination - other._inclination,
        _rightAscension - other._rightAscension,
        _argPerigee - other._argPerigee,
        _trueAnomaly - other._trueAnomaly
    );
}
Keplerian& Keplerian::operator-=(const Keplerian& other)
{
    _semimajor -= other._semimajor;
    _eccentricity -= other._eccentricity;
    _inclination -= other._inclination;
    _rightAscension -= other._rightAscension;
    _argPerigee -= other._argPerigee;
    _trueAnomaly -= other._trueAnomaly;
    return *this;
}

Keplerian Keplerian::operator*(const Unitless& multiplier) const
{
    return Keplerian(
        _semimajor * multiplier, _eccentricity * multiplier, _inclination * multiplier, _rightAscension * multiplier, _argPerigee * multiplier, _trueAnomaly * multiplier
    );
}
Keplerian& Keplerian::operator*=(const Unitless& multiplier)
{
    _semimajor *= multiplier;
    _eccentricity *= multiplier;
    _inclination *= multiplier;
    _rightAscension *= multiplier;
    _argPerigee *= multiplier;
    _trueAnomaly *= multiplier;
    return *this;
}

KeplerianPartial Keplerian::operator/(const Time& time) const
{
    return KeplerianPartial(_semimajor / time, _eccentricity / time, _inclination / time, _rightAscension / time, _argPerigee / time, _trueAnomaly / time);
}

Keplerian Keplerian::operator/(const Unitless& divisor) const
{
    return Keplerian(_semimajor / divisor, _eccentricity / divisor, _inclination / divisor, _rightAscension / divisor, _argPerigee / divisor, _trueAnomaly / divisor);
}
Keplerian& Keplerian::operator/=(const Unitless& divisor)
{
    _semimajor /= divisor;
    _eccentricity /= divisor;
    _inclination /= divisor;
    _rightAscension /= divisor;
    _argPerigee /= divisor;
    _trueAnomaly /= divisor;
    return *this;
}

Keplerian
    Keplerian::interpolate(const Time& thisTime, const Time& otherTime, const Keplerian& other, const AstrodynamicsSystem& sys, const Time& targetTime) const
{
    const std::vector<Time> times = { thisTime, otherTime };
    const Distance interpSemimajor = math::interpolate<Time, Distance>(times, { _semimajor, other.get_semimajor() }, targetTime);
    const Unitless interpEcc = math::interpolate<Time, Unitless>(times, { _eccentricity, other.get_eccentricity() }, targetTime);
    const Angle interpInc    = interpolate_angle(times, { _inclination, other.get_inclination() }, targetTime);
    const Angle interpRaan   = interpolate_angle(times, { _rightAscension, other.get_right_ascension() }, targetTime);
    const Angle interpArgPer = interpolate_angle(times, { _argPerigee, other.get_argument_of_perigee() }, targetTime);
    const Angle interpTheta  = interpolate_angle(times, { _trueAnomaly, other.get_true_anomaly() }, targetTime);

    return Keplerian(interpSemimajor, interpEcc, interpInc, interpRaan, interpArgPer, interpTheta);
}

Angle Keplerian::interpolate_angle(const std::vector<Time>& times, const std::vector<Angle>& angles, const Time& targetTime) const
{
    // These is an assumption on the size of the diff. If the time step is too big, this will cause errors
    // TODO: Catch large interpolation steps
    if (abs(angles[0] - angles[1]) > 300.0 * deg) {
        if (angles[0] > angles[1]) {
            return math::interpolate<Time, Angle>(times, { angles[0], angles[1] + 360.0 * deg }, targetTime);
        }
        return math::interpolate<Time, Angle>(times, { angles[0] + 360.0 * deg, angles[1] }, targetTime);
    }
    return math::interpolate<Time, Angle>(times, { angles[0], angles[1] }, targetTime);
}

std::vector<Unitless> Keplerian::to_vector() const
{
    return { _semimajor / astrea::detail::distance_unit, _eccentricity,
             _inclination / astrea::detail::angle_unit,  _rightAscension / astrea::detail::angle_unit,
             _argPerigee / astrea::detail::angle_unit,   _trueAnomaly / astrea::detail::angle_unit };
}

void Keplerian::sanitize_angles()
{
    _inclination    = sanitize_angle(_inclination);
    _rightAscension = sanitize_angle(_rightAscension);
    _argPerigee     = sanitize_angle(_argPerigee);
    _trueAnomaly    = sanitize_angle(_trueAnomaly);
}


Keplerian KeplerianPartial::operator*(const Time& time) const
{
    return Keplerian(
        _semimajorPartial * time,
        _eccentricityPartial * time,
        _inclinationPartial * time,
        _rightAscensionPartial * time,
        _argPerigeePartial * time,
        _trueAnomalyPartial * time
    );
}

std::ostream& operator<<(std::ostream& os, Keplerian const& elements)
{
    os << "[";
    os << elements.get_semimajor() << ", ";
    os << elements.get_eccentricity() << ", ";
    os << elements.get_inclination() << ", ";
    os << elements.get_right_ascension() << ", ";
    os << elements.get_argument_of_perigee() << ", ";
    os << elements.get_true_anomaly();
    os << "] (Keplerian)";
    return os;
}

std::ostream& operator<<(std::ostream& os, KeplerianPartial const& elements)
{
    os << "[";
    os << elements._semimajorPartial << ", ";
    os << elements._eccentricityPartial << ", ";
    os << elements._inclinationPartial << ", ";
    os << elements._rightAscensionPartial << ", ";
    os << elements._argPerigeePartial << ", ";
    os << elements._trueAnomalyPartial;
    os << "] (KeplerianPartial)";
    return os;
}

} // namespace astro
} // namespace astrea