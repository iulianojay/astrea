#pragma once

#ifndef SWIG
    #include <vector>
#endif

#include "RiseSetArray.hpp"
#include "Constellation.hpp"
#include "Time.hpp"
#include "State.hpp"

void find_accesses(Constellation& constel, const Time& resolution, const AstrodynamicsSystem& sys);

std::vector<Time> create_time_vector(const std::vector<State>& states, const Time& resolution, const AstrodynamicsSystem& sys);
std::vector<std::vector<State>> interpolate_states(const std::vector<Spacecraft>& allSats, const std::vector<Time>& times, const AstrodynamicsSystem& sys);

RiseSetArray find_sat_to_sat_accesses(const size_t& iSat, const size_t& jSat, Spacecraft& sat1, Spacecraft& sat2,
    const std::vector<Time>& times, const std::vector<std::vector<State>>& states);
RiseSetArray find_sensor_to_sensor_accesses(const size_t& iSat, const size_t& jSat, const Sensor& sensor1, const Sensor& sensor2,
    const std::vector<Time>& times, const std::vector<std::vector<State>>& states);