#pragma once

#include <vector>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/ground/GroundArchitecture.hpp>
#include <access/platforms/ground/GroundStation.hpp>
#include <access/platforms/vehicles/Viewer.hpp>
#include <access/time/RiseSetArray.hpp>


namespace accesslib {

using TimeVector          = std::vector<astro::Time>;
using ViewerConstellation = astro::Constellation<Viewer>;

struct AccessInfo {
    astro::Time time;
    astro::Cartesian state1;
    astro::Cartesian state2;
    std::size_t id1;
    std::size_t id2;
    bool isOcculted;
    astro::RadiusVector ecefState;
};

AccessArray find_accesses(ViewerConstellation& constel, const astro::Time& resolution, const astro::AstrodynamicsSystem& sys);
AccessArray find_accesses(
    ViewerConstellation& constel,
    GroundArchitecture& grounds,
    const astro::Time& resolution,
    const astro::Date epoch,
    const astro::AstrodynamicsSystem& sys
);

TimeVector create_time_vector(const astro::StateHistory& states, const astro::Time& resolution);
void interpolate_states(std::vector<Viewer>& viewers, const TimeVector& times);
bool is_earth_occulting(const astro::Cartesian& state1, const astro::Cartesian& state2, const astro::AstrodynamicsSystem& sys);

RiseSetArray
    find_sat_to_sat_accesses(Viewer& viewer1, Viewer& viewer2, const TimeVector& times, const astro::AstrodynamicsSystem& sys, const bool& twoWay = false);
RiseSetArray find_sat_to_ground_accesses(
    Viewer& viewer,
    GroundStation& ground,
    const TimeVector& times,
    const astro::AstrodynamicsSystem& sys,
    const astro::Date epoch,
    const bool& twoWay = false
);

RiseSetArray
    find_sensor_to_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor1, const Sensor& sensor2, const bool& twoWay);
RiseSetArray
    find_sensor_to_ground_sensor_accesses(const std::vector<AccessInfo>& accessInfo, const Sensor& sensor, const Sensor& groundSensor, const bool& twoWay);

} // namespace accesslib