/**
 * @file SensorPlatform.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the SensorPlatform class, which represents a platform that can have sensors attached to it.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/frames/FrameReference.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/sensors/Sensor.hpp>


namespace waveguide {
namespace accesslib {

/**
 * @brief The SensorPlatform class represents a platform that can have sensors attached to it.
 * It provides methods to attach sensors and retrieve the list of attached sensors.
 */
class SensorPlatform {
  public:
    /**
     * @brief Default constructor for SensorPlatform
     */
    SensorPlatform() = default;

    /**
     * @brief Constructs a SensorPlatform with a list of sensors.
     *
     * @param sensors Vector of sensors to attach to the platform.
     */
    SensorPlatform(const std::vector<Sensor>& sensors) :
        _sensors(sensors){};

    /**
     * @brief Default destructor for SensorPlatform
     */
    virtual ~SensorPlatform() = default;

    /**
     * @brief Attaches a single sensor to the platform.
     *
     * @param sensor The sensor to attach.
     */
    void attach(const Sensor& sensor) { _sensors.emplace_back(sensor); }

    /**
     * @brief Attaches multiple sensors to the platform.
     *
     * @param sensors Vector of sensors to attach.
     */
    void attach(const std::vector<Sensor>& sensors)
    {
        _sensors.insert(std::end(_sensors), std::begin(sensors), std::end(sensors));
    }

    /**
     * @brief Retrieves the list of sensors attached to the platform.
     *
     * @return A vector of sensors attached to the platform.
     */
    std::vector<Sensor>& get_sensors() { return _sensors; }

    /**
     * @brief Retrieves the list of sensors attached to the platform (const version).
     *
     * @return A const vector of sensors attached to the platform.
     */
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

  protected:
    std::vector<Sensor> _sensors; // List of sensors attached to the platform
};


} // namespace accesslib
} // namespace waveguide