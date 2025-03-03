#include "Cartesian.hpp"

#include <mp-units/math.h>
#include <mp-units/systems/si/math.h>
#include <mp-units/systems/angular/math.h>

#include "AstrodynamicsSystem.hpp"
#include "Keplerian.hpp"
#include "Equinoctial.hpp"
#include "Time.hpp"
#include "OrbitalElements.hpp"
#include "interpolation.hpp"


using namespace mp_units;
using namespace mp_units::si;
using namespace mp_units::si::unit_symbols;


Cartesian::Cartesian(const Keplerian& elements, const AstrodynamicsSystem& sys) {

    // Constants
    static const quantity piRad = 1.0 * (mag<pi>*rad);
    static const quantity twoPiRad = 2.0 * (mag<pi>*rad);

    // Get mu
    const quantity mu = sys.get_center()->get_mu();

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

    const quantity h = sqrt(mu*a*(1.0 - ecc*ecc));
    const quantity A = h*h/mu/(1.0 + ecc*cosTheta);
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


Cartesian::Cartesian(const Equinoctial& elements, const AstrodynamicsSystem& sys) {

    // Get mu
    const quantity mu = sys.get_center()->get_mu();

    // Extract
    const auto& semilatus = elements.get_semilatus();
    const auto& f = elements.get_f();
    const auto& g = elements.get_g();
    const auto& h = elements.get_h();
    const auto& k = elements.get_k();
    const auto& trueLongitude = elements.get_true_longitude();

    // Precalculate
    const auto cosL = cos(trueLongitude);
    const auto sinL = sin(trueLongitude);

    const auto alphaSq = h*h - k*k;
    const auto sSq = 1.0 + h*h + k*k;
    const auto w = 1.0 + f*cosL + g*sinL;
    const auto r = semilatus/w;

    const auto rOverSSq = r/sSq;
    const auto twoHK = 2.0*h*k;

    const auto gamma = 1.0/sSq*sqrt(mu/semilatus);

    // Radius
    _radius[0] = rOverSSq*(cosL*(1.0 + alphaSq) + twoHK*sinL);
    _radius[1] = rOverSSq*(sinL*(1.0 - alphaSq) + twoHK*cosL);
    _radius[2] = 2.0*rOverSSq*(h*sinL* - k*cosL);

    // Velocity
    _velocity[0] = -gamma*(sinL*(1.0 + alphaSq) - twoHK*(cosL + f) + g*(1.0 + alphSq));
    _velocity[1] = -gamma*(cosL*(-1.0 + alphaSq) + twoHK*(sinL + g) + f*(-1.0 + alphSq));
    _velocity[2] = 2.0*gamma*(h*cosL + k*sinL + f*h + g*k);
    
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


OrbitalElements Cartesian::interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const {

    Cartesian elements = other.to_cartesian(sys);

    const quantity interpx  = ::interpolate({thisTime, otherTime}, {_x,  elements.get_x()},  targetTime);
    const quantity interpy  = ::interpolate({thisTime, otherTime}, {_y,  elements.get_y()},  targetTime);
    const quantity interpz  = ::interpolate({thisTime, otherTime}, {_z,  elements.get_z()},  targetTime);
    const quantity interpvx = ::interpolate({thisTime, otherTime}, {_vx, elements.get_vx()}, targetTime);
    const quantity interpvy = ::interpolate({thisTime, otherTime}, {_vy, elements.get_vy()}, targetTime);
    const quantity interpvz = ::interpolate({thisTime, otherTime}, {_vz, elements.get_vz()}, targetTime);

    Cartesian iterpCart({interpx, interpy, interpz}, {interpvx, interpvy, interpvz});

    return OrbitalElements(iterpCart);
}

std::vector<double> Cartesian::to_vector() const {
    return {
        value_cast<double>(_radius[0]),
        value_cast<double>(_radius[1]),
        value_cast<double>(_radius[2]),
        value_cast<double>(_velocity[0]),
        value_cast<double>(_velocity[1]),
        value_cast<double>(_velocity[2])
    };
}

void Cartesian::update_from_vector(const std::vector<double>& vec) {
    _radius = {
        vec[0] * km,
        vec[1] * km,
        vec[2] * km
    }
    _velocity = {
        vec[0] * km / s,
        vec[1] * km / s,
        vec[2] * km / s
    }
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