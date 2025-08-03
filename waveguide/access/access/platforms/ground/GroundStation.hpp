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

#include <astro/types/typedefs.hpp>

#include <access/platforms/ground/GroundPoint.hpp>
#include <access/platforms/sensors/SensorPlatform.hpp>


namespace waveguide {
namespace accesslib {

/**
 * @brief Ground station class for managing ground-based access.
 * This class inherits from GroundPoint, AccessObject, and SensorPlatform.
 * It represents a ground station with a specific latitude, longitude, altitude,
 * and a collection of sensors. It also provides methods to manage access and
 * sensor functionalities.
 */
class GroundStation : public GroundPoint, public AccessObject, public SensorPlatform {
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
        const Angle& latitude,
        const Angle& longitude,
        const Distance& altitude           = 0.0 * mp_units::si::unit_symbols::km,
        const std::vector<Sensor>& sensors = {},
        const std::string name             = "Unnammed"
    ) :
        GroundPoint(latitude, longitude, altitude),
        AccessObject(),
        SensorPlatform(sensors),
        _name(name)
    {
        generate_id_hash();
    };

    /**
     * @brief Default destructor for the GroundStation class.
     */
    ~GroundStation() = default;

    /**
     * @brief Get the unique identifier for the ground station.
     *
     * @return std::size_t The unique identifier for the ground station.
     */
    std::size_t get_id() const { return _id; }

    /**
     * @brief Get the name of the ground station.
     *
     * @return std::string The name of the ground station.
     */
    std::string get_name() const { return _name; }

  private:
    std::size_t _id;   //<! Unique identifier for the ground station, generated from its properties.
    std::string _name; //<! Name of the ground station.

    /**
     * @brief Generates a unique identifier for the ground station based on its properties.
     * This method is called in the constructor to ensure that each ground station has a unique ID.
     */
    void generate_id_hash();
};

} // namespace accesslib
} // namespace waveguide