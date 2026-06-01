/**
 * @file ImpulsiveBurn.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a null Event in the astrea astro platform.
 * @date 2025-08-02
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

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing an impulsive burn Event. It triggers when the true anomaly wraps around (i.e. at
 * perigee), and applies the total impulsive delta-v from all thrusters to the vehicle in the velocity direction.
 */
class ImpulsiveBurn {

    enum class BurnTrigger {
        TRUE_ANOMALY,
        MEAN_ANOMALY,
        ALTITUDE,
        SCHEDULED,
    };

  public:
    ImpulsiveBurn() :
        _nMaxTriggers(0),
        _trigger(BurnTrigger::TRUE_ANOMALY),
        _triggerAnomaly(0.0 * mp_units::angular::unit_symbols::rad),
        _triggerAltitude(0.0 * mp_units::si::unit_symbols::km),
        _triggerEpoch(Date()),
        _burnDirection(Direction<frames::dynamic::ric>(1.0, 0.0, 0.0))
    {
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event that triggers at a specific true anomaly.
     *
     * @param triggerAnomaly The true anomaly at which the burn should trigger.
     * @param burnDirection The direction of the burn in the ICRF frame.
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero.
     * @return ImpulsiveBurn An ImpulsiveBurn Event that triggers at the specified true anomaly.
     */
    static ImpulsiveBurn
        trigger_at_true_anomaly(const Angle& triggerAnomaly, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        return ImpulsiveBurn(nMaxTriggers, BurnTrigger::TRUE_ANOMALY, burnDirection, triggerAnomaly);
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event that triggers at a specific mean anomaly.
     *
     * @param triggerAnomaly The mean anomaly at which the burn should trigger.
     * @param burnDirection The direction of the burn in the ICRF frame.
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero.
     * @return ImpulsiveBurn An ImpulsiveBurn Event that triggers at the specified mean anomaly.
     */
    static ImpulsiveBurn
        trigger_at_mean_anomaly(const Angle& triggerAnomaly, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        return ImpulsiveBurn(nMaxTriggers, BurnTrigger::MEAN_ANOMALY, burnDirection, triggerAnomaly);
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event that triggers at a specific altitude.
     *
     * @param triggerAltitude The altitude at which the burn should trigger.
     * @param burnDirection The direction of the burn in the ICRF frame.
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero.
     * @return ImpulsiveBurn An ImpulsiveBurn Event that triggers at the specified altitude.
     */
    static ImpulsiveBurn
        trigger_at_altitude(const Distance& triggerAltitude, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        ImpulsiveBurn burn(nMaxTriggers, BurnTrigger::ALTITUDE, burnDirection, triggerAltitude);
        return burn;
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event that triggers at a specific epoch.
     *
     * @param triggerEpoch The epoch at which the burn should trigger.
     * @param burnDirection The direction of the burn in the ICRF frame.
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely. Default is zero.
     * @return ImpulsiveBurn An ImpulsiveBurn Event that triggers at the specified epoch.
     */
    static ImpulsiveBurn
        trigger_at_epoch(const Date& triggerEpoch, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        ImpulsiveBurn burn(nMaxTriggers, BurnTrigger::SCHEDULED, burnDirection, triggerEpoch);
        return burn;
    }

  private:
    /**
     * @brief Constructs an ImpulsiveBurn Event.
     *
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely.
     * @param trigger The condition that triggers the burn.
     * @param triggerAnomaly The mean anomaly at which the burn should trigger, if the trigger condition is based on mean anomaly.
     */
    ImpulsiveBurn(
        const unsigned nMaxTriggers,
        const BurnTrigger trigger,
        const Direction<frames::dynamic::ric> burnDirection,
        const Angle triggerAnomaly = 0.0 * astrea::detail::angle_unit
    ) :
        _nMaxTriggers(nMaxTriggers),
        _trigger(trigger),
        _triggerAnomaly(wrap_angle(triggerAnomaly)),
        _triggerAltitude(0.0 * mp_units::si::unit_symbols::km),
        _triggerEpoch(Date()),
        _burnDirection(burnDirection.direction())
    {
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event.
     *
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely.
     * @param trigger The condition that triggers the burn.
     * @param triggerAltitude The altitude at which the burn should trigger, if the trigger condition is based on altitude.
     */
    ImpulsiveBurn(const unsigned nMaxTriggers, const BurnTrigger trigger, const Direction<frames::dynamic::ric> burnDirection, const Distance triggerAltitude) :
        _nMaxTriggers(nMaxTriggers),
        _trigger(trigger),
        _triggerAnomaly(0.0 * mp_units::angular::unit_symbols::rad),
        _triggerAltitude(triggerAltitude),
        _triggerEpoch(Date()),
        _burnDirection(burnDirection.direction())
    {
    }

    /**
     * @brief Constructs an ImpulsiveBurn Event.
     *
     * @param nMaxTriggers The maximum number of times the Event can trigger before it is disabled. Zero means it can trigger infinitely.
     * @param trigger The condition that triggers the burn.
     * @param triggerEpoch The epoch at which the burn should trigger, if the trigger condition is based on a scheduled time.
     */
    ImpulsiveBurn(const unsigned nMaxTriggers, const BurnTrigger trigger, const Direction<frames::dynamic::ric> burnDirection, const Date triggerEpoch) :
        _nMaxTriggers(nMaxTriggers),
        _trigger(trigger),
        _triggerAnomaly(0.0 * mp_units::angular::unit_symbols::rad),
        _triggerAltitude(0.0 * mp_units::si::unit_symbols::km),
        _triggerEpoch(triggerEpoch),
        _burnDirection(burnDirection.direction())
    {
    }

  public:
    /**
     * @brief Gets the name of the Event.
     *
     * @return std::string The name of the Event.
     */
    std::string get_name() const;

    /**
     * @brief Measures the anomaly as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Triggers an impulsive burn.
     *
     * @param time The current time in the integration.
     * @param state The current state of the vehicle represented as orbital elements.
     * @param vehicle The Vehicle to trigger the action on.
     */
    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const;

    /**
     * @brief Checks if the Event is a terminal Event.
     *
     * @return true If the Event is a terminal Event.
     * @return false If the Event is not a terminal Event.
     */
    bool is_terminal() const;

  private:
    const unsigned _nMaxTriggers;
    const BurnTrigger _trigger;
    const Angle _triggerAnomaly;
    const Distance _triggerAltitude;
    const Date _triggerEpoch;
    const Direction<frames::dynamic::ric> _burnDirection;

    /**
     * @brief Measures the anomaly as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_anomaly_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Measures the altitude as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_altitude_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    /**
     * @brief Measures the epoch as a trigger.
     *
     * @param vehicle The Vehicle to check.
     * @return true If the Event is triggered by the Vehicle.
     * @return false If the Event is not triggered by the Vehicle.
     */
    Unitless measure_epoch_event(const Time& time, const State& state, const Vehicle& vehicle) const;
};

} // namespace astro
} // namespace astrea