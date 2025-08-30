/**
 * @file GroundStation.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the GroundStation class.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <mp-units/systems/isq_angle.h>

#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/systems/CelestialBody.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/utilities/conversions.hpp>

#include <trace/platforms/ground/GroundPoint.hpp>
#include <trace/platforms/sensors/Sensor.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Ground station class for managing ground-based access.
 * This class inherits from GroundPoint, AccessObject, and SensorPlatform.
 * It represents a ground station with a specific latitude, longitude, altitude,
 * and a collection of sensors. It also provides methods to manage access and
 * sensor functionalities.
 */
class GroundStation : public GroundPoint, public astro::PayloadPlatform<Sensor> {
  public:
    /**
     * @brief Constructs a GroundStation object with specified latitude, longitude, altitude, sensors, and name.
     *
     * @param latitude The latitude of the ground station.
     * @param longitude The longitude of the ground station.
     * @param altitude The altitude of the ground station.
     * @param sensors The sensors associated with the ground station.
     * @param name The name of the ground station.
     */
    GroundStation(
        const astro::CelestialBody* parent,
        const Angle& latitude,
        const Angle& longitude,
        const Distance& altitude                     = 0.0 * mp_units::si::unit_symbols::km,
        const std::string name                       = "Unnammed",
        const std::vector<SensorParameters>& sensors = {}
    ) :
        GroundPoint(parent, latitude, longitude, altitude),
        astro::PayloadPlatform<Sensor>(),
        _name(name)
    {
        for (const auto& sensor : sensors) {
            attach_payload(sensor);
        }
        generate_id_hash();
    };

    /**
     * @brief Default destructor for the GroundStation class.
     */
    ~GroundStation() = default;

    /**
     * @brief Get the ID of the payload.
     *
     * @return std::size_t ID of the payload.
     */
    std::size_t get_id() const { return _id; }

    /**
     * @brief Get the name of the ground station.
     *
     * @return std::string The name of the ground station.
     */
    std::string get_name() const { return _name; }

    /**
     * @brief Get the inertial position of the ground station in the ECI frame.
     *
     * @param date The date for which to compute the position.
     * @return RadiusVector<ECI> The inertial position of the ground station.
     */
    astro::RadiusVector<astro::ECI> get_inertial_position(const astro::Date& date) const
    {
        return _lla.get_position(date, _parent);
    }

    /**
     * @brief Get the inertial velocity of the ground station in the ECI frame.
     *
     * @param date The date for which to compute the velocity.
     * @return VelocityVector<ECI> The inertial velocity of the ground station.
     */
    astro::VelocityVector<astro::ECI> get_inertial_velocity(const astro::Date& date) const
    {
        using namespace astro;
        using mp_units::isq_angle::cotes_angle;
        using mp_units::si::unit_symbols::km;

        const RadiusVector<ECEF> rEcef = _lla.get_position(_parent);

        const RadiusVector<ECEF> rEcefPlanar = { rEcef.get_x(), rEcef.get_y(), 0.0 * km };
        const Distance rEcefPlanarNorm       = rEcefPlanar.norm();
        const Velocity vEcefMag              = rEcefPlanarNorm * _parent->get_rotation_rate() / cotes_angle;
        const RadiusVector<ECEF> z           = { 0.0 * km, 0.0 * km, 1.0 * km };
        const VelocityVector<ECEF> vEcef =
            (z.cross(rEcefPlanar).unit()) * vEcefMag; // z cross (x,y,0) give perpendicular direction vector
        return vEcef.in_frame<ECI>(date);
    }

  private:
    std::string _name; //!< Name of the ground station.
};

} // namespace trace
} // namespace astrea