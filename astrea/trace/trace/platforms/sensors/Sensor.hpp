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

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frames.hpp>
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
class SensorParameters {
  public:
    /**
     * @brief Constructor for SensorParameters
     *
     * @param fov Field of View for the sensor.
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    SensorParameters(
        const FieldOfView* fov,
        const astro::RadiusVector<astro::RIC>& boresight       = { -1.0 * astrea::detail::distance_unit, // Nadir
                                                                   0.0 * astrea::detail::distance_unit,
                                                                   0.0 * astrea::detail::distance_unit },
        const astro::RadiusVector<astro::RIC>& attachmentPoint = { 0.0 * astrea::detail::distance_unit, // Center
                                                                   0.0 * astrea::detail::distance_unit,
                                                                   0.0 * astrea::detail::distance_unit }
    ) :
        _fov(fov),
        _boresight(boresight),
        _attachmentPoint(attachmentPoint)
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
     * @brief Get the boresight direction of the sensor.
     *
     * @return astro::RadiusVector<astro::RIC> Boresight direction of the sensor.
     */
    astro::RadiusVector<astro::RIC> get_boresight() const { return _boresight; }

    /**
     * @brief Get the attachment point of the sensor.
     *
     * @return astro::RadiusVector<astro::RIC> Attachment point of the sensor.
     */
    astro::RadiusVector<astro::RIC> get_attachment_point() const { return _attachmentPoint; }

    /**
     * @brief Set the field of view of the sensor.
     *
     * @param fov FieldOfView* Pointer to the field of view object.
     */
    void set_fov(FieldOfView* fov) { _fov = fov; }

    /**
     * @brief Set the boresight direction of the sensor.
     *
     * @param boresight astro::RadiusVector<astro::RIC> Boresight direction of the sensor.
     */
    void set_boresight(const astro::RadiusVector<astro::RIC>& boresight) { _boresight = boresight; }

    /**
     * @brief Set the attachment point of the sensor.
     *
     * @param attachmentPoint astro::RadiusVector<astro::RIC> Attachment point of the sensor.
     */
    void set_attachment_point(const astro::RadiusVector<astro::RIC>& attachmentPoint)
    {
        _attachmentPoint = attachmentPoint;
    }

  protected:
    const FieldOfView* _fov;                    //!< Field of view of the sensor, defining its coverage area
    astro::RadiusVector<astro::RIC> _boresight; //!< Boresight vector of the sensor, indicating the direction it is pointing
    astro::RadiusVector<astro::RIC> _attachmentPoint; //!< Attachment point of the sensor on the platform
};

/**
 * @brief Sensor class representing a sensor on a platform
 *
 * This class inherits from AccessObject and provides functionality for sensors,
 * including field of view and access management.
 */
class Sensor : public AccessObject {

    friend class SensorPlatform;

  public:
    /**
     * @brief Constructs a Sensor from a FieldOfView object.
     *
     * @param parent The parent platform to which the sensor is attached.
     * @param fov Field of view object defining the sensor's coverage area.
     * @param boresight The boresight vector of the sensor.
     * @param attachmentPoint The point on the platform where the sensor is attached.
     */
    template <typename T>
    Sensor(const T& parent, const SensorParameters& parameters) :
        AccessObject(),
        _parent(&parent),
        _parameters(parameters)
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
     * @brief Get the parent platform of the sensor.
     *
     * @return const SensorPlatform* Pointer to the parent platform.
     */
    const SensorPlatform* get_parent() const { return _parent; }

    /**
     * @brief Get the sensor parameters of the sensor.
     *
     * @return SensorParameters Sensor parameters of the sensor.
     */
    SensorParameters get_sensor_parameters() const { return _parameters; }

    /**
     * @brief Check if the sensor can see a target given the boresight vector.
     *
     * @param sensor2target Vector from the sensor to the target.
     * @param date The date for which the visibility is checked.
     * @return true If the target is within the sensor's field of view.
     * @return false If the target is outside the sensor's field of view.
     */
    bool contains(const astro::RadiusVector<astro::ECI>& sensor2target, const astro::Date& date) const;

  private:
    std::size_t _id;               //!< Unique identifier for the sensor
    const SensorPlatform* _parent; //!< Parent platform
    SensorParameters _parameters;  //!< Sensor parameters

    // TODO: Make a fixed-offset frame for attachment point

    /**
     * @brief Generate a hash for the sensor ID.
     */
    void generate_id_hash();

    /**
     * @brief Set the parent platform of the sensor.
     *
     * @tparam T Type of the parent platform.
     * @param parent The parent platform to set.
     */
    template <typename T>
    void set_parent(const T& parent)
    {
        _parent = &parent;
    }
};

} // namespace trace
} // namespace astrea