/**
 * @file Payload.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Payload class definition for astrea access platform
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025-2026 Jay Iuliano
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

#include <memory>

#include <utilities/IdProvider.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

static const astro::RadiusVector<astro::frames::dynamic::ric> NADIR_RIC  = { -1.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };
static const astro::RadiusVector<astro::frames::dynamic::ric> RADIAL_RIC = { 1.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };
static const astro::RadiusVector<astro::frames::dynamic::ric> CENTER     = { 0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit,
                                                                             0.0 * astrea::detail::distance_unit };

/**
 * @brief Class for storing and managing payload parameters.
 */
class PayloadParameters {
  protected:
    /**
     * @brief Constructor for PayloadParameters
     *
     * @param boresight Boresight direction in RIC coordinates (default is Nadir).
     * @param attachmentPoint Attachment point in RIC coordinates (default is Center).
     */
    PayloadParameters(
        const astro::RadiusVector<astro::frames::dynamic::ric>& boresight       = NADIR_RIC,
        const astro::RadiusVector<astro::frames::dynamic::ric>& attachmentPoint = CENTER
    ) :
        _boresight(boresight),
        _attachmentPoint(attachmentPoint)
    {
    }

    /**
     * @brief Default destructor for PayloadParameters
     */
    virtual ~PayloadParameters() = default;

  public:
    /**
     * @brief Get the boresight direction of the payload.
     *
     * @return astro::RadiusVector<astro::frames::dynamic::ric>Boresight direction of the payload.
     */
    const astro::RadiusVector<astro::frames::dynamic::ric>& get_boresight() const { return _boresight; }

    /**
     * @brief Get the attachment point of the payload.
     *
     * @return astro::RadiusVector<astro::frames::dynamic::ric>Attachment point of the payload.
     */
    const astro::RadiusVector<astro::frames::dynamic::ric>& get_attachment_point() const { return _attachmentPoint; }

    /**
     * @brief Set the boresight direction of the payload.
     *
     * @param boresight astro::RadiusVector<astro::frames::dynamic::ric>Boresight direction of the payload.
     */
    void set_boresight(const astro::RadiusVector<astro::frames::dynamic::ric>& boresight) { _boresight = boresight; }

    /**
     * @brief Set the attachment point of the payload.
     *
     * @param attachmentPoint astro::RadiusVector<astro::frames::dynamic::ric>Attachment point of the payload.
     */
    void set_attachment_point(const astro::RadiusVector<astro::frames::dynamic::ric>& attachmentPoint)
    {
        _attachmentPoint = attachmentPoint;
    }

  protected:
    astro::RadiusVector<astro::frames::dynamic::ric> _boresight; //!< Boresight vector of the payload, indicating the direction it is pointing
    astro::RadiusVector<astro::frames::dynamic::ric> _attachmentPoint; //!< Attachment point of the payload on the platform

    // TODO: Make a fixed-offset frame for attachment point
};

/**
 * @brief Payload class representing a payload on a platform
 *
 * This class inherits from AccessObject and provides functionality for payloads,
 * including field of view and access management.
 */
template <class Payload_T, class PayloadParameters_T>
class Payload {

    friend PayloadPlatform<Payload_T>;

  protected:
    /**
     * @brief Constructs a Payload from a FieldOfView object.
     *
     * @param parent The parent platform to which the payload is attached.
     * @param parameters The parameters for the payload.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<PayloadPlatform<Payload_T>, Parent_T>)
    Payload(const Parent_T& parent, const PayloadParameters_T& parameters) :
        _parent(&parent),
        _parameters(parameters),
        _id(utilities::IdProvider::get_next_id<"Payload">())
    {
    }

    /**
     * @brief Default destructor for Payload
     */
    virtual ~Payload() = default;

  public:
    /**
     * @brief Get the ID of the payload.
     *
     * @return std::size_t ID of the payload.
     */
    virtual std::size_t get_id() const = 0;

    /**
     * @brief Get the parent platform of the payload.
     *
     * @return const PayloadPlatform<Payload_T, PayloadParameters_T>* Pointer to the parent platform.
     */
    const PayloadPlatform<Payload_T>* const get_parent() const { return _parent; }

    /**
     * @brief Get the payload parameters of the payload.
     *
     * @return PayloadParameters_T Payload parameters of the payload.
     */
    const PayloadParameters_T& get_parameters() const { return _parameters; }

    /**
     * @brief Get the payload parameters of the payload.
     *
     * @return PayloadParameters_T Payload parameters of the payload.
     */
    PayloadParameters_T& get_parameters() { return _parameters; }

    /**
     * @brief Get the name of the payload.
     *
     * @return std::string Name of the payload.
     */
    std::string get_name() const { return "Payload"; }

    /**
     * @brief Get the position of the payload in the primary frame.
     *
     * @param date The date for which to get the position.
     * @return CartesianVector<Distance, frames::primary> Position of the payload in the primary frame.
     */
    CartesianVector<Distance, frames::primary> get_position(const Date& date) const
    {
        // Assumes the payload is fixed
        static const auto parentToPayload = get_parameters().get_attachment_point();

        // Get current RIC
        const auto parentPosition = get_parent()->get_position(date);
        const auto parentVelocity = get_parent()->get_velocity(date);
        const auto ricFrame       = frames::dynamic::ric.instantaneous(parentPosition, parentVelocity);

        // Rotate to inertial
        const auto parentToPayloadInInertial = ricFrame.rotate_out_of_this_frame(parentToPayload, date);

        return parentPosition + parentToPayloadInInertial;
    }

    /**
     * @brief Get the velocity of the payload in the primary frame. Assumes all payloads are fixed to their platform.
     *
     * @param date The date for which to get the velocity.
     * @return CartesianVector<Velocity, frames::primary> Velocity of the payload in the primary frame.
     */
    CartesianVector<Velocity, frames::primary> get_velocity(const Date& date) const
    {
        // Assumes the payload is fixed
        return get_parent()->get_velocity(date);
    }

  protected:
    const PayloadPlatform<Payload_T>* _parent; //!< Parent platform
    PayloadParameters_T _parameters;           //!< Payload parameters
    std::size_t _id;                           //!< Unique identifier for the payload

    /**
     * @brief Set the parent platform of the payload.
     *
     * @tparam T Type of the parent platform.
     * @param parent The parent platform to set.
     */
    template <typename Parent_T>
        requires(std::is_base_of_v<PayloadPlatform<Payload_T>, Parent_T>)
    void set_parent(const Parent_T& parent)
    {
        _parent = &parent;
    }
};

} // namespace astro
} // namespace astrea