#pragma once

#include <vector>

#include <astro/platforms/space/Constellation.hpp>
#include <astro/state/State.hpp>
#include <astro/types/typedefs.hpp>

#include <access/platforms/vehicles/Viewer.hpp>
#include <access/time/RiseSetArray.hpp>


namespace accesslib {

void find_accesses(astro::Constellation<Viewer>& constel, const astro::Time& resolution, const astro::AstrodynamicsSystem& sys);

std::vector<astro::Time>
    create_time_vector(const std::vector<astro::State>& states, const astro::Time& resolution, const astro::AstrodynamicsSystem& sys);
std::vector<std::vector<astro::State>>
    interpolate_states(const std::vector<Viewer>& allSats, const std::vector<astro::Time>& times, const astro::AstrodynamicsSystem& sys);

RiseSetArray find_sat_to_sat_accesses(
    const std::size_t& iSat,
    const std::size_t& jSat,
    Viewer& sat1,
    Viewer& sat2,
    const std::vector<astro::Time>& times,
    const std::vector<std::vector<astro::State>>& states,
    const astro::AstrodynamicsSystem& sys
);
RiseSetArray find_sensor_to_sensor_accesses(
    const std::size_t& iSat,
    const std::size_t& jSat,
    const Sensor& sensor1,
    const Sensor& sensor2,
    const std::vector<astro::Time>& times,
    const std::vector<std::vector<astro::State>>& states,
    const astro::AstrodynamicsSystem& sys
);

} // namespace accesslib