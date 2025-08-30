/**
 * @file Payload.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Payload class definition for astrea access platform
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <memory>

#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

static const astro::RadiusVector<astro::RIC> NADIR_RIC = { -1.0 * astrea::detail::distance_unit,
                                                           0.0 * astrea::detail::distance_unit,
                                                           0.0 * astrea::detail::distance_unit };
static const astro::RadiusVector<astro::RIC> CENTER    = { 0.0 * astrea::detail::distance_unit,
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
    PayloadParameters(const astro::RadiusVector<astro::RIC>& boresight = NADIR_RIC, const astro::RadiusVector<astro::RIC>& attachmentPoint = CENTER) :
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
     * @return astro::RadiusVector<astro::RIC> Boresight direction of the payload.
     */
    astro::RadiusVector<astro::RIC> get_boresight() const { return _boresight; }

    /**
     * @brief Get the attachment point of the payload.
     *
     * @return astro::RadiusVector<astro::RIC> Attachment point of the payload.
     */
    astro::RadiusVector<astro::RIC> get_attachment_point() const { return _attachmentPoint; }

    /**
     * @brief Set the boresight direction of the payload.
     *
     * @param boresight astro::RadiusVector<astro::RIC> Boresight direction of the payload.
     */
    void set_boresight(const astro::RadiusVector<astro::RIC>& boresight) { _boresight = boresight; }

    /**
     * @brief Set the attachment point of the payload.
     *
     * @param attachmentPoint astro::RadiusVector<astro::RIC> Attachment point of the payload.
     */
    void set_attachment_point(const astro::RadiusVector<astro::RIC>& attachmentPoint)
    {
        _attachmentPoint = attachmentPoint;
    }

  protected:
    astro::RadiusVector<astro::RIC> _boresight; //!< Boresight vector of the payload, indicating the direction it is pointing
    astro::RadiusVector<astro::RIC> _attachmentPoint; //!< Attachment point of the payload on the platform

    // TODO: Make a fixed-offset frame for attachment point
};

/**
 * @brief Payload class representing a payload on a platform
 *
 * This class inherits from AccessObject and provides functionality for payloads,
 * including field of view and access management.
 */
template <class Payload_T, class PayloadParameters_T>
class Payload { // TODO: add -> : public FrameReference

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
    Payload(Parent_T& parent, const PayloadParameters_T& parameters) :
        _parent(&parent),
        _parameters(parameters)
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
    PayloadParameters_T get_parameters() const { return _parameters; }

  protected:
    std::size_t _id;                           //!< Unique identifier for the payload
    const PayloadPlatform<Payload_T>* _parent; //!< Parent platform
    PayloadParameters_T _parameters;           //!< Payload parameters

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