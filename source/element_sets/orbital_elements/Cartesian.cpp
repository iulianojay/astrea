#include "Cartesian.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "AstrodynamicsSystem.hpp"
#include "Keplerian.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


Cartesian::Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys) {

    // Constants
    static const quantity piRad = 1.0 * (mag<pi>*rad);
    static const quantity twoPiRad = 2.0 * (mag<pi>*rad);

    // Get mu
    const quantity mu = sys.get_center()->get_mu() * km*km*km/(s*s);

    // Extract elements
    const auto& a = elements.get_semimajor();
    const auto& ecc = elements.get_eccentricity();
    const auto& inc = elements.get_inclination();
    const auto& raan = elements.get_right_ascension();
    const auto& w = elements.get_argument_of_perigee();
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

    const quantity h = sqrt(mu*a*(1 - ecc*ecc));
    const quantity A = h*h/mu/(1 + ecc*cosTheta);
    const quantity B = mu/h;

    // Perifocal Coordinates
    const quantity xPeri = A*cosTheta;
    const quantity yPeri = A*sinTheta;

    const quantity vxPeri = -B*sinTheta;
    const quantity vyPeri = B*(ecc + cosTheta);

    // Preallocate Dcm values for speed
    const quantity DcmPeri2Eci11 = (cosW*cosRaan - sinW*cosInc*sinRaan);
    const quantity DcmPeri2Eci12 = (-sinW*cosRaan - cosW*cosInc*sinRaan);

    const quantity DcmPeri2Eci21 = (cosW*sinRaan + sinW*cosInc*cosRaan);
    const quantity DcmPeri2Eci22 = (-sinW*sinRaan + cosW*cosInc*cosRaan);

    const quantity DcmPeri2Eci31 = sinInc*sinW;
    const quantity DcmPeri2Eci32 = sinInc*cosW;

    // Inertial position and _velocity
    _radius[0] = DcmPeri2Eci11*xPeri + DcmPeri2Eci12*yPeri;
    _radius[1] = DcmPeri2Eci21*xPeri + DcmPeri2Eci22*yPeri;
    _radius[2] = DcmPeri2Eci31*xPeri + DcmPeri2Eci32*yPeri;

    _velocity[0] = DcmPeri2Eci11*vxPeri + DcmPeri2Eci12*vyPeri;
    _velocity[1] = DcmPeri2Eci21*vxPeri + DcmPeri2Eci22*vyPeri;
    _velocity[2] = DcmPeri2Eci31*vxPeri + DcmPeri2Eci32*vyPeri;
}


// Copy constructor
Cartesian::Cartesian(const Cartesian& other) :
    _radius(other._radius),
    _velocity(other._velocity)
{}

// Move constructor
Cartesian::Cartesian(Cartesian&& other) noexcept :
    _radius(std::move(other._radius)),
    _velocity(std::move(other._velocity))
{}

// Move assignment operator
Cartesian& Cartesian::operator=(Cartesian&& other) noexcept {
    if (this != &other) {
        _radius = std::move(other._radius);
        _velocity = std::move(other._velocity);
    }
    return *this;
}

// Copy assignment operator
Cartesian& Cartesian::operator=(const Cartesian& other) {
    return *this = Cartesian(other);
}


std::ostream &operator<<(std::ostream& os, Cartesian const& elements) {
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