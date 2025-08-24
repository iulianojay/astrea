/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the SolarRadiationPressure class, which computes the solar radiation pressure force on a spacecraft.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>
#include <astro/types/typedefs.hpp>
#include <units/units.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the solar radiation pressure force on a spacecraft.
 *
 */
class SolarRadiationPressure : public Force {
  public:
    /**
     * @brief Default constructor for SolarRadiationPressure.
     */
    SolarRadiationPressure() = default;

    /**
     * @brief Default destructor for SolarRadiationPressure.
     */
    ~SolarRadiationPressure() = default;

    /**
     * @brief Computes the solar radiation pressure force on a spacecraft.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<ECI> The computed acceleration vector due to solar radiation pressure.
     */
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
};

} // namespace astro
} // namespace astrea