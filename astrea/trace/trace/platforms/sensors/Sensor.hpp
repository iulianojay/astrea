/**
 * @file Sensor.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Sensor class definition for astrea access platform
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/Payload.hpp>
#include <astro/types/typedefs.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/platforms/sensors/fov/FieldOfView.hpp>
#include <trace/risesets/AccessArray.hpp>
#include <trace/trace.fwd.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Class for storing and managing sensor parameters.
 */
class SensorParameters : public astro::PayloadParameters {
  public:
    /**
     * @brief Constructor for SensorParameters
     *
     * @param fov Field of View for the sensor.
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    SensorParameters(
        const FieldOfView* fov                                                               = nullptr,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& boresight       = astro::NADIR_RIC,
        const astro::CartesianVector<Distance, astro::frames::dynamic::ric>& attachmentPoint = astro::CENTER
    ) :
        astro::PayloadParameters(boresight, attachmentPoint),
        _fov(fov)
    {
    }

    /**
     * @brief Default destructor for SensorParameters
     */
    virtual ~SensorParameters() = default;

    /**
     * @brief Get the field of view of the sensor.
     *
     * @return FieldOfView* Pointer to the field of view object.
     */
    const FieldOfView* get_fov() const { return _fov; }

    /**
     * @brief Set the field of view of the sensor.
     *
     * @param fov FieldOfView* Pointer to the field of view object.
     */
    void set_fov(FieldOfView* fov) { _fov = fov; }

  protected:
    const FieldOfView* _fov; //!< Field of view of the sensor, defining its coverage area
};

/**
 * @brief Sensor class representing a sensor on a platform
 *
 * This class inherits from AccessObject and provides functionality for sensors,
 * including field of view and access management.
 */
class Sensor : public AccessObject, public astro::Payload<Sensor, SensorParameters> {

    friend Payload<Sensor, SensorParameters>;

  public:
    /**
     * @brief Constructs a Sensor from a FieldOfView object.
     *
     * @param parent The parent platform to which the sensor is attached.
     * @param fov Field of view object defining the sensor's coverage area.
     * @param boresight The boresight vector of the sensor.
     * @param attachmentPoint The point on the platform where the sensor is attached.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<astro::FrameReference, Parent_T>)
    Sensor(const Parent_T& parent, const SensorParameters& parameters) :
        AccessObject(),
        Payload<Sensor, SensorParameters>(parent, parameters)
    {
    }

    /**
     * @brief Default destructor for Sensor
     */
    virtual ~Sensor() = default;

    /**
     * @brief Get the ID of the sensor.
     *
     * @return std::size_t ID of the sensor.
     */
    std::size_t get_id() const { return _id; }

    /**
     * @brief Check if the sensor can see a target given the boresight vector.
     *
     * @param sensor2target Vector from the sensor to the target.
     * @param date The date for which the visibility is checked.
     * @return true If the target is within the sensor's field of view.
     * @return false If the target is outside the sensor's field of view.
     */
    bool contains(const astro::RadiusVector<astro::frames::earth::icrf>& sensor2target, const astro::Date& date) const;

  private:
    /**
     * @brief Generate a hash for the sensor ID.
     */
    std::size_t generate_id_hash() const
    {
        return 0; // TODO: Fix
    }
};

/**
 * @brief Type definition for sensor platforms.
 */
using SensorPlatform = astro::PayloadPlatform<Sensor>;

} // namespace trace
} // namespace astrea