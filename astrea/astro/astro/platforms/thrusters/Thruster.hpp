/**
 * @file Thruster.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Thruster class definition for astrea access platform
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/dynamic_frames.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/Payload.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class for storing and managing thruster parameters.
 */
class ThrusterParameters : public PayloadParameters {
  public:
    /**
     * @brief Constructor for ThrusterParameters
     *
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    ThrusterParameters(
        const Force& thrust,
        const CartesianVector<Distance, frames::dynamic::ric>& boresight       = NADIR_RIC,
        const CartesianVector<Distance, frames::dynamic::ric>& attachmentPoint = CENTER
    ) :
        PayloadParameters(boresight, attachmentPoint),
        _thrust(thrust)
    {
    }

    /**
     * @brief Default destructor for ThrusterParameters
     */
    virtual ~ThrusterParameters() = default;

    /**
     * @brief Get the thrust magnitude.
     *
     * @return Force magnitude.
     */
    Force get_thrust() const { return _thrust; }

    /**
     * @brief Set the thrust magnitude.
     *
     * @param thrust Force magnitude to set.
     */
    bool is_on() const { return _isOn; }

    /**
     * @brief Switch the thruster on.
     */
    void switch_on() { _isOn = true; }

    /**
     * @brief Switch the thruster off.
     */
    void switch_off() { _isOn = false; }

  protected:
    Force _thrust;      //!< Force magnitude
    bool _isOn = false; //!< Thruster state (on/off)
};

/**
 * @brief Thruster class representing a thruster on a platform
 *
 * This class inherits from AccessObject and provides functionality for thrusters,
 * including field of view and access management.
 */
class Thruster : public Payload<Thruster, ThrusterParameters> {

    friend Payload<Thruster, ThrusterParameters>;

  public:
    /**
     * @brief Constructor for Thruster
     *
     * @param parent Parent frame reference.
     * @param parameters Thruster parameters.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<FrameReference, Parent_T>)
    Thruster(const Parent_T& parent, const ThrusterParameters& parameters) :
        Payload<Thruster, ThrusterParameters>(parent, parameters)
    {
    }

    /**
     * @brief Default destructor for Thruster
     */
    virtual ~Thruster() = default;

    /**
     * @brief Get the ID of the sensor.
     *
     * @return std::size_t ID of the sensor.
     */
    std::size_t get_id() const;

    /**
     * @brief Get the impulsive delta-v provided by the thruster.
     *
     * @return Velocity The impulsive delta-v.
     */
    Velocity get_impulsive_delta_v() const;

    /**
     * @brief Get the thrust of the thruster for a given state.
     *
     * @param state The state of the vehicle for which to get the thrust.
     * @return Force The thrust of the thruster.
     */
    Force get_thrust() const;

    /**
     * @brief Switch the thruster on.
     */
    void switch_on();

    /**
     * @brief Switch the thruster off.
     */
    void switch_off();

    /**
     * @brief Check if the thruster is on.
     *
     * @return true if the thruster is on, false otherwise.
     */
    bool is_on() const;
};

/**
 * @brief Thruster platform type definition.
 */
using ThrusterPlatform = PayloadPlatform<Thruster>;

} // namespace astro
} // namespace astrea