

# File ImpulsiveBurn.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**event\_detection**](dir_283e5a6c8e70b5075f630fb83b6454d7.md) **>** [**events**](dir_ffe0d0558a41319d577ebe8d35f3c9da.md) **>** [**ImpulsiveBurn.hpp**](ImpulsiveBurn_8hpp.md)

[Go to the documentation of this file](ImpulsiveBurn_8hpp.md)


```C++

#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions.hpp>
#include <astro/frames/definitions/dynamic_frames.hpp>
#include <astro/utilities/conversions.hpp>

namespace astrea {
namespace astro {

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

    static ImpulsiveBurn
        trigger_at_true_anomaly(const Angle& triggerAnomaly, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        return ImpulsiveBurn(nMaxTriggers, BurnTrigger::TRUE_ANOMALY, burnDirection, triggerAnomaly);
    }

    static ImpulsiveBurn
        trigger_at_mean_anomaly(const Angle& triggerAnomaly, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        return ImpulsiveBurn(nMaxTriggers, BurnTrigger::MEAN_ANOMALY, burnDirection, triggerAnomaly);
    }

    static ImpulsiveBurn
        trigger_at_altitude(const Distance& triggerAltitude, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        ImpulsiveBurn burn(nMaxTriggers, BurnTrigger::ALTITUDE, burnDirection, triggerAltitude);
        return burn;
    }

    static ImpulsiveBurn
        trigger_at_epoch(const Date& triggerEpoch, const Direction<frames::dynamic::ric> burnDirection, const unsigned nMaxTriggers = 0)
    {
        ImpulsiveBurn burn(nMaxTriggers, BurnTrigger::SCHEDULED, burnDirection, triggerEpoch);
        return burn;
    }

  private:
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

    ImpulsiveBurn(const unsigned nMaxTriggers, const BurnTrigger trigger, const Direction<frames::dynamic::ric> burnDirection, const Distance triggerAltitude) :
        _nMaxTriggers(nMaxTriggers),
        _trigger(trigger),
        _triggerAnomaly(0.0 * mp_units::angular::unit_symbols::rad),
        _triggerAltitude(triggerAltitude),
        _triggerEpoch(Date()),
        _burnDirection(burnDirection.direction())
    {
    }

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
    std::string get_name() const;

    Unitless measure_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    void trigger_action(const Time& time, State& state, Vehicle& vehicle) const;

    bool is_terminal() const;

  private:
    const unsigned _nMaxTriggers;
    const BurnTrigger _trigger;
    const Angle _triggerAnomaly;
    const Distance _triggerAltitude;
    const Date _triggerEpoch;
    const Direction<frames::dynamic::ric> _burnDirection;

    Unitless measure_anomaly_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    Unitless measure_altitude_event(const Time& time, const State& state, const Vehicle& vehicle) const;

    Unitless measure_epoch_event(const Time& time, const State& state, const Vehicle& vehicle) const;
};

} // namespace astro
} // namespace astrea
```


