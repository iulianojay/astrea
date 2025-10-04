/**
 * @file AtmosphericForce.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the AtmosphericForce class, which computes the atmospheric force on a vehicle.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <map>
#include <tuple>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/Force.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class to compute the atmospheric force on a vehicle.
 *
 * This class computes the atmospheric force on a vehicle based on its state and the celestial body's atmosphere.
 */
class AtmosphericForce : public Force {

  public:
    /**
     * @brief Default constructor for AtmosphericForce.
     */
    AtmosphericForce() = default;

    /**
     * @brief Default destructor for AtmosphericForce.
     */
    ~AtmosphericForce() = default;

    /**
     * @brief Computes the atmospheric force on a vehicle.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param vehicle Vehicle object representing the spacecraft
     * @param sys Astrodynamics system containing celestial body data
     * @return AccelerationVector<frames::earth::icrf> The computed acceleration vector due to atmospheric force.
     */
    CartesianVector<Acceleration, frames::earth::icrf>
        compute_force(const Date& date, const Cartesian& state, const Vehicle& vehicle, const AstrodynamicsSystem& sys) const override;

  private:
    /**
     * @brief Finds the atmospheric density at a given altitude.
     *
     * @param date Date of the computation
     * @param state Cartesian state vector of the vehicle
     * @param center Celestial body around which the vehicle is orbiting
     * @return Density The atmospheric density at the given altitude.
     */
    const Density find_atmospheric_density(const Date& date, const Cartesian& state, const std::unique_ptr<CelestialBody>& center) const;
};

} // namespace astro
} // namespace astrea