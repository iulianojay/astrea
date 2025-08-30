/**
 * @file PayloadPlatform.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief This file defines the PayloadPlatform class, which represents a platform that can have payloads attached to it.
 * @version 0.1
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>

#include <astro/state/frames/FrameReference.hpp>
#include <astro/types/typedefs.hpp>


namespace astrea {
namespace astro {

/**
 * @brief The PayloadPlatform class represents a platform that can have payloads attached to it.
 * It provides methods to attach payloads and retrieve the list of attached payloads.
 */
template <class Payload_T>
class PayloadPlatform : virtual public FrameReference {

    using PayloadParameters_T = decltype(std::declval<Payload_T>().get_parameters());

  protected:
    /**
     * @brief Default constructor for PayloadPlatform
     */
    PayloadPlatform() = default;

    /**
     * @brief Default destructor for PayloadPlatform
     */
    virtual ~PayloadPlatform() = default;

    /**
     * @brief Copy constructor for PayloadPlatform
     *
     * @param other The other PayloadPlatform to copy from.
     */
    PayloadPlatform(const PayloadPlatform& other)
    {
        _payloads = other._payloads;
        reset_payload_parentage();
    }

    /**
     * @brief Move constructor for PayloadPlatform
     *
     * @param other The other PayloadPlatform to move from.
     */
    PayloadPlatform(PayloadPlatform&& other) noexcept
    {
        _payloads = std::move(other._payloads);
        reset_payload_parentage();
    }

    /**
     * @brief Copy assignment operator for PayloadPlatform
     *
     * @param other The other PayloadPlatform to copy from.
     * @return PayloadPlatform& Reference to this PayloadPlatform.
     */
    PayloadPlatform& operator=(const PayloadPlatform& other)
    {
        if (this != &other) {
            _payloads = other._payloads;
            reset_payload_parentage();
        }
        return *this;
    }

    /**
     * @brief Move assignment operator for PayloadPlatform
     *
     * @param other The other PayloadPlatform to move from.
     * @return PayloadPlatform& Reference to this PayloadPlatform.
     */
    PayloadPlatform& operator=(PayloadPlatform&& other) noexcept
    {
        if (this != &other) {
            _payloads = std::move(other._payloads);
            reset_payload_parentage();
        }
        return *this;
    }

  public:
    /**
     * @brief Get the ID of the payload.
     *
     * @return std::size_t ID of the payload.
     */
    virtual std::size_t get_id() const = 0;

    /**
     * @brief Attaches a single payload to the platform.
     *
     * @param parameters The payload parameters to attach.
     */
    void attach_payload(const PayloadParameters_T& parameters) { _payloads.emplace_back(Payload_T(*this, parameters)); }

    /**
     * @brief Attaches multiple payloads to the platform.
     *
     * @param parameterPack Vector of payload parameters to attach.
     */
    void attach_payloads(const std::vector<PayloadParameters_T>& parameterPack)
    {
        for (const auto& parameters : parameterPack) {
            attach_payload(parameters);
        }
    }

    /**
     * @brief Retrieves the list of payloads attached to the platform.
     *
     * @return A vector of payloads attached to the platform.
     */
    std::vector<Payload_T>& get_payloads() { return _payloads; }

    /**
     * @brief Retrieves the list of payloads attached to the platform (const version).
     *
     * @return A const vector of payloads attached to the platform.
     */
    const std::vector<Payload_T>& get_payloads() const { return _payloads; }

  protected:
    std::vector<Payload_T> _payloads; // List of payloads attached to the platform

    /**
     * @brief Resets the parentage of all payloads attached to the platform to this.
     */
    void reset_payload_parentage()
    {
        for (auto& payload : _payloads) {
            payload.set_parent(*this);
        }
    }
};


} // namespace astro
} // namespace astrea