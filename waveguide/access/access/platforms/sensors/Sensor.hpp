/**
 * @file Sensor.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Sensor class definition for waveguide access platform
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/AccessObject.hpp>
#include <access/platforms/sensors/fov/FieldOfView.hpp>
#include <access/risesets/AccessArray.hpp>

namespace waveguide {
namespace accesslib {

/**
 * @brief Sensor class representing a sensor on a platform
 *
 * This class inherits from AccessObject and provides functionality for sensors,
 * including field of view and access management.
 */
class Sensor : public AccessObject {

  public:
    /**
     * @brief Default constructor for Sensor
     */
    Sensor() = default;

    /**
     * @brief Constructs a Sensor from a FieldOfView object.
     *
     * @tparam FieldOfView_T Type of the field of view, must inherit from FieldOfView
     * @param fov Field of view object defining the sensor's coverage area.
     */
    template <typename FieldOfView_T>
    Sensor(const FieldOfView_T& fov) :
        AccessObject(),
        _fov(std::make_shared<FieldOfView_T>(fov))
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
     * @brief Check if the sensor can see a target.
     *
     * @param sensor2target Vector from the sensor to the target.
     * @return true If the target is within the sensor's field of view.
     * @return false If the target is outside the sensor's field of view.
     */
    virtual const bool contains(const astro::RadiusVector<astro::ECI>& sensor2target) const
    {
        return _fov->contains(_boresight, sensor2target);
    }

    /**
     * @brief Check if the sensor can see a target given the boresight vector.
     *
     * @param boresight Boresight vector of the sensor.
     * @param sensor2target Vector from the sensor to the target.
     * @return true If the target is within the sensor's field of view.
     * @return false If the target is outside the sensor's field of view.
     */
    virtual const bool contains(const astro::RadiusVector<astro::ECI>& boresight, const astro::RadiusVector<astro::ECI>& sensor2target) const
    {
        return _fov->contains(boresight, sensor2target);
    }

  private:
    std::size_t _id;                                  // Unique identifier for the sensor
    int _parentId;                                    // ID of the parent platform
    astro::RadiusVector<astro::ECI> _attachmentPoint; // Attachment point of the sensor on the platform
    astro::RadiusVector<astro::ECI> _boresight; // Boresight vector of the sensor, indicating the direction it is pointing
    std::shared_ptr<FieldOfView> _fov;          // Field of view of the sensor, defining its coverage area

    void generate_id_hash();
};

} // namespace accesslib
} // namespace waveguide