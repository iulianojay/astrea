/**
 * @file Viewer.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Viewer class for managing access and sensors on a spacecraft.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <string>


#include <astro/astro.fwd.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>

#include <trace/platforms/AccessObject.hpp>
#include <trace/platforms/sensors/Sensor.hpp>
#include <trace/platforms/sensors/SensorPlatform.hpp>

namespace astrea {
namespace trace {

/**
 * @brief Viewer class for managing access and sensors on a spacecraft.
 * This class inherits from Spacecraft, AccessObject, and SensorPlatform.
 * It provides functionality to manage sensors and access rights for the spacecraft.
 */
class Viewer : public astro::Spacecraft, public SensorPlatform {

  public:
    /**
     * @brief Default constructor for Viewer.
     */
    Viewer() = default;

    /**
     * @brief Constructor for Viewer with GeneralPerturbations and AstrodynamicsSystem.
     * @param gp The GeneralPerturbations object containing spacecraft data.
     * @param system The AstrodynamicsSystem object for astrodynamics calculations.
     */
    Viewer(const astro::GeneralPerturbations& gp, const astro::AstrodynamicsSystem& system) :
        Spacecraft(gp, system),
        AccessObject()
    {
    }

    /**
     * @brief Constructor for Viewer with initial state.
     * @param state0 The initial state of the spacecraft.
     */
    Viewer(const astro::State& state0) :
        Spacecraft(state0),
        AccessObject()
    {
    }

    /**
     * @brief Default destructor for Viewer.
     */
    ~Viewer() = default;

    /**
     * @brief Get the viewer ID.
     *
     * @return std::size_t The ID of the viewer.
     */
    std::size_t get_id() const { return Spacecraft::get_id(); }

    /**
     * @brief Get the name of the viewer.
     *
     * @return std::string The name of the viewer.
     */
    std::string get_name() const { return Spacecraft::get_name(); }

    /**
     * @brief Get the inertial position of the viewer.
     *
     * @param date The date for which to get the position.
     * @return astro::RadiusVector<astro::ECI> The inertial position of the viewer.
     */
    astro::RadiusVector<astro::ECI> get_inertial_position(const astro::Date& date) const
    {
        return Spacecraft::get_inertial_position(date);
    }

    /**
     * @brief Get the inertial velocity of the viewer.
     *
     * @param date The date for which to get the velocity.
     * @return astro::RadiusVector<astro::ECI> The inertial velocity of the viewer.
     */
    astro::VelocityVector<astro::ECI> get_inertial_velocity(const astro::Date& date) const
    {
        return Spacecraft::get_inertial_velocity(date);
    }
};

} // namespace trace
} // namespace astrea