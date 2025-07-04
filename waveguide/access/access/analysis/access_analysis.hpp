#pragma once

#include <vector>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/vehicles/Viewer.hpp>
#include <access/time/RiseSetArray.hpp>


namespace accesslib {

using TimeVector          = std::vector<astro::Time>;
using StateVector         = std::vector<astro::State>;
using ViewerConstellation = astro::Constellation<Viewer>;

void find_accesses(ViewerConstellation& constel, const astro::Time& resolution, const astro::AstrodynamicsSystem& sys);

TimeVector create_time_vector(const StateVector& states, const astro::Time& resolution);

void interpolate_states(std::vector<Viewer>& viewers, const TimeVector& times, const astro::AstrodynamicsSystem& sys);

RiseSetArray
    find_sat_to_sat_accesses(Viewer& viewer1, Viewer& viewer2, const TimeVector& times, const astro::AstrodynamicsSystem& sys, const bool& twoWay = false);
RiseSetArray find_sensor_to_sensor_accesses(
    const Viewer& viewer1,
    const Sensor& sensor1,
    const Viewer& viewer2,
    const Sensor& sensor2,
    const TimeVector& times,
    const astro::AstrodynamicsSystem& sys,
    const bool& twoWay = false
);

} // namespace accesslib