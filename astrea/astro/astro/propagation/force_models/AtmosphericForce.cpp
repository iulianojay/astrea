#include <astro/propagation/force_models/AtmosphericForce.hpp>

// mp-units
#include <mp-units/math.h>
#include <mp-units/systems/angular.h>
#include <mp-units/systems/angular/math.h>
#include <mp-units/systems/isq_angle.h>
#include <mp-units/systems/si.h>
#include <mp-units/systems/si/math.h>

#include <astro/platforms/Vehicle.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/angular_elements/angular_elements.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/state/orbital_elements/instances/Keplerian.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/time/Date.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::cm;
using mp_units::si::unit_symbols::g;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;


AccelerationVector<ECI>
    AtmosphericForce::compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const
{

    static const CelestialBodyUniquePtr& center = sys.get_central_body();

    // Extract
    const Distance& x = state.get_x();
    const Distance& y = state.get_y();
    const Distance& z = state.get_z();
    const Distance& R = sqrt(x * x + y * y + z * z);

    const Velocity& vx = state.get_vx();
    const Velocity& vy = state.get_vy();
    const Velocity& vz = state.get_vz();

    // Central body properties
    static const AngularRate& bodyRotationRate = center->get_rotation_rate();

    // Find velocity relative to atmosphere
    const Velocity relVx = vx - (y * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle));
    const Velocity relVy = vy + (x * bodyRotationRate.in(rad / s) / (isq_angle::cotes_angle));
    const Velocity relVz = vz;

    // Exponential Drag Model
    const Density atmosphericDensity = find_atmospheric_density(date, state, center);

    // Accel due to drag
    const Velocity relativeVelocityMagnitude = sqrt(relVx * relVx + relVy * relVy + relVz * relVz);
    const Unitless coefficientOfDrag         = vehicle.get_coefficient_of_drag();
    const SurfaceArea areaRam                = vehicle.get_ram_area();
    const Mass mass                          = vehicle.get_mass();
    const quantity dragMagnitude = -0.5 * coefficientOfDrag * (areaRam) / mass * atmosphericDensity * relativeVelocityMagnitude;

    const AccelerationVector<ECI> accelDrag{ dragMagnitude * relVx, dragMagnitude * relVy, dragMagnitude * relVz };

    // Velocity in the radial direction
    const Velocity radialVelcityMagnitude = (vx * x + vy * y + vz * z) / R;

    // accel due to lift
    const Unitless coefficientOfLift = vehicle.get_coefficient_of_lift();
    const SurfaceArea areaLift       = vehicle.get_lift_area();
    const quantity tempA =
        0.5 * coefficientOfLift * areaLift / mass * atmosphericDensity * radialVelcityMagnitude * radialVelcityMagnitude / R;

    const AccelerationVector<ECI> accelLift{ tempA * x, tempA * y, tempA * z };

    return { accelDrag[0] + accelLift[0], accelDrag[1] + accelLift[1], accelDrag[2] + accelLift[2] };
}


const Density AtmosphericForce::find_atmospheric_density(const Date& date, const Cartesian& state, const CelestialBodyUniquePtr& center) const
{
    // Central body properties
    static const Distance equitorialR = center->get_equitorial_radius();
    static const Distance polarR      = center->get_polar_radius();

    // Find altitude
    const RadiusVector<ECEF> rEcef = state.get_position().in_frame<ECEF>(date);
    const auto [latitude, longitude, altitude] =
        convert_earth_fixed_to_geodetic(rEcef, center->get_equitorial_radius(), center->get_polar_radius());

    return center->find_atmospheric_density(date, altitude);
}


} // namespace astro
} // namespace astrea