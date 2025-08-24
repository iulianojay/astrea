/**
 * @file OblatenessForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the NBodyForce class, which computes the gravitational force due to multiple celestial bodies.
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
 * @brief Class to compute the gravitational force due to multiple celestial bodies.
 *
 */
class NBodyForce : public Force {
  public:
    /**
     * @brief Default constructor for NBodyForce.
     */
    NBodyForce() = default;

    /**
     * @brief Default destructor for NBodyForce.
     */
    ~NBodyForce() = default;

    /**
     * @brief Computes the gravitational force due to multiple celestial bodies.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<ECI> The computed acceleration vector due to multiple bodies.
     */
    AccelerationVector<ECI>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
};

} // namespace astro
} // namespace astrea