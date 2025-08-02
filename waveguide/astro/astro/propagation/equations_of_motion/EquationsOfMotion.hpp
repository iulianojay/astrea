/**
 * @file EquationsOfMotion.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the base class of equations of motion.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/Force.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/systems/AstrodynamicsSystem.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Base class for equations of motion in astrodynamics.
 */
class EquationsOfMotion {
  public:
    /**
     * @brief Constructor for the Equations of Motion class.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     */
    EquationsOfMotion(const AstrodynamicsSystem& system) :
        system(&system){};

    /**
     * @brief Destructor for the Equations of Motion class.
     */
    virtual ~EquationsOfMotion() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements.
     *
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    virtual OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const = 0;

    /**
     * @brief Checks if the current state of the vehicle is in a crash condition.
     *
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the crash condition is being checked.
     * @return true if the vehicle is in a crash condition, false otherwise.
     */
    virtual bool check_crash(const OrbitalElements& state, const Vehicle& vehicle) const
    {
        return false; // TODO: Implement these
    }

    /**
     * @brief Returns the expected set of orbital elements for this method.
     *
     * @return const ElementSet& The expected set of orbital elements.
     */
    virtual const ElementSet& get_expected_set() const = 0;

    /**
     * @brief Returns the astrodynamics system associated with this equations of motion.
     *
     * @return const AstrodynamicsSystem& The astrodynamics system.
     */
    const AstrodynamicsSystem& get_system() const { return *system; }

  protected:
    const AstrodynamicsSystem* system; ///< Pointer to the astrodynamics system containing the central body and its properties.
};

} // namespace astro
} // namespace waveguide
