#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include <astro/platforms/space/Constellation.hpp>
#include <astro/time/Time.hpp>
#include <astro/State.hpp>

#include <access/time/RiseSetArray.hpp>
#include <access/platforms/vehicles/Viewer.hpp>

void find_accesses(Constellation& constel, const Time& resolution, const AstrodynamicsSystem& sys);

std::vector<Time> create_time_vector(const std::vector<State>& states, const Time& resolution, const AstrodynamicsSystem& sys);
std::vector<std::vector<State>> interpolate_states(const std::vector<Viewer>& allSats, const std::vector<Time>& times, const AstrodynamicsSystem& sys);

RiseSetArray find_sat_to_sat_accesses(const size_t& iSat, const size_t& jSat, Viewer& sat1, Viewer& sat2,
    const std::vector<Time>& times, const std::vector<std::vector<State>>& states);
RiseSetArray find_sensor_to_sensor_accesses(const size_t& iSat, const size_t& jSat, const Sensor& sensor1, const Sensor& sensor2,
    const std::vector<Time>& times, const std::vector<std::vector<State>>& states);