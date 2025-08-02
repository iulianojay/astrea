/**
 * @file TwoBody.hpp
 * @author your name (you@domain.com)
 * @brief Header file for the Two Body equations of motion class.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/typedefs.hpp>

#include <astro/element_sets/ElementSet.hpp>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/types/typedefs.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Class implementing the Two Body equations of motion.
 */
class TwoBody : public EquationsOfMotion {

  public:
    /**
     * @brief Constructor for the Two Body equations of motion class.
     *
     * @param system The astrodynamics system containing the central body and its properties.
     */
    TwoBody(const AstrodynamicsSystem& system) :
        EquationsOfMotion(system),
        mu(system.get_center()->get_mu()){};

    /**
     * @brief Destructor for the Two Body equations of motion class.
     */
    ~TwoBody() = default;

    /**
     * @brief Computes the partial derivatives of the orbital elements using the Two Body method.
     *
     * @param state The current orbital elements of the vehicle.
     * @param vehicle The vehicle for which the equations of motion are being computed.
     * @return OrbitalElementPartials The computed partial derivatives of the orbital elements.
     */
    OrbitalElementPartials operator()(const OrbitalElements& state, const Vehicle& vehicle) const override;

    /**
     * @brief Returns the expected set of orbital elements for this equations of motion class.
     *
     * @return const ElementSet& The expected set of orbital elements.
     */
    const ElementSet& get_expected_set() const override { return expectedSet; };

  private:
    const ElementSet expectedSet = ElementSet::CARTESIAN; //<! Expected set of orbital elements for Two Body equations of motion.
    const GravParam mu;                                   //<! Gravitational parameter of the central body.
};

} // namespace astro
} // namespace waveguide