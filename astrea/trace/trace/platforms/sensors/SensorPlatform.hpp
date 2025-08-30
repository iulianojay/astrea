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

#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/types/typedefs.hpp>

#include <trace/platforms/sensors/Sensor.hpp>


namespace astrea {
namespace trace {

using SensorPlatform = astro::PayloadPlatform<Sensor, SensorParameters>;

// /**
//  * @brief The SensorPlatform class represents a platform that can have sensors attached to it.
//  * It provides methods to attach sensors and retrieve the list of attached sensors.
//  */
// class SensorPlatform : virtual public astro::FrameReference, virtual public AccessObject {
//   public:
//     /**
//      * @brief Default constructor for SensorPlatform
//      */
//     SensorPlatform() = default;

//     /**
//      * @brief Default destructor for SensorPlatform
//      */
//     virtual ~SensorPlatform() = default;

//     /**
//      * @brief Copy constructor for SensorPlatform
//      *
//      * @param other The other SensorPlatform to copy from.
//      */
//     SensorPlatform(const SensorPlatform& other)
//     {
//         _sensors = other._sensors;
//         reset_sensor_parentage();
//     }

//     /**
//      * @brief Move constructor for SensorPlatform
//      *
//      * @param other The other SensorPlatform to move from.
//      */
//     SensorPlatform(SensorPlatform&& other) noexcept
//     {
//         _sensors = std::move(other._sensors);
//         reset_sensor_parentage();
//     }

//     /**
//      * @brief Copy assignment operator for SensorPlatform
//      *
//      * @param other The other SensorPlatform to copy from.
//      * @return SensorPlatform& Reference to this SensorPlatform.
//      */
//     SensorPlatform& operator=(const SensorPlatform& other)
//     {
//         if (this != &other) {
//             _sensors = other._sensors;
//             reset_sensor_parentage();
//         }
//         return *this;
//     }

//     /**
//      * @brief Move assignment operator for SensorPlatform
//      *
//      * @param other The other SensorPlatform to move from.
//      * @return SensorPlatform& Reference to this SensorPlatform.
//      */
//     SensorPlatform& operator=(SensorPlatform&& other) noexcept
//     {
//         if (this != &other) {
//             _sensors = std::move(other._sensors);
//             reset_sensor_parentage();
//         }
//         return *this;
//     }

//     /**
//      * @brief Attaches a single sensor to the platform.
//      *
//      * @param parameters The sensor parameters to attach.
//      */
//     void attach(const SensorParameters& parameters) { _sensors.emplace_back(Sensor(*this, parameters)); }

//     /**
//      * @brief Attaches multiple sensors to the platform.
//      *
//      * @param parameterPack Vector of sensor parameters to attach.
//      */
//     void attach(const std::vector<SensorParameters>& parameterPack)
//     {
//         for (const auto& parameters : parameterPack) {
//             _sensors.emplace_back(Sensor(*this, parameters));
//         }
//     }

//     /**
//      * @brief Retrieves the list of sensors attached to the platform.
//      *
//      * @return A vector of sensors attached to the platform.
//      */
//     std::vector<Sensor>& get_sensors() { return _sensors; }

//     /**
//      * @brief Retrieves the list of sensors attached to the platform (const version).
//      *
//      * @return A const vector of sensors attached to the platform.
//      */
//     const std::vector<Sensor>& get_sensors() const { return _sensors; }

//   protected:
//     std::vector<Sensor> _sensors; // List of sensors attached to the platform

//     /**
//      * @brief Resets the parentage of all sensors attached to the platform to this.
//      */
//     void reset_sensor_parentage()
//     {
//         for (auto& sensor : _sensors) {
//             sensor.set_parent(*this);
//         }
//     }
// };


} // namespace trace
} // namespace astrea