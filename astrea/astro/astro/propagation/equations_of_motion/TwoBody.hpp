/**
 * @file TwoBody.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the Two Body equations of motion class.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

namespace astrea {
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
    TwoBody(const AstrodynamicsSystem& system);

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
     * @return std::size_t The expected set id of orbital elements.
     */
    constexpr std::size_t get_expected_set_id() const override { return OrbitalElements::get_set_id<Cartesian>(); };

  private:
    GravParam mu; //!< Gravitational parameter of the central body.
};

} // namespace astro
} // namespace astrea