#include <access/access.hpp>

#include <access/platforms/Sensor.hpp>

void find_accesses(Constellation<Viewer>& constel, const Time& resolution, const AstrodynamicsSystem& sys)
{

    // Get all sats
    auto allSats       = constel.get_all_spacecraft();
    const size_t nSats = allSats.size();

    // Create time array
    std::vector<Time> times =
        create_time_vector(allSats[0].get_states(), resolution, sys); // TODO: Check all state histories for common time frame

    // Get and store interpolated states in cartesian to reduce overhead
    std::vector<std::vector<State>> interpStates = interpolate_states(allSats, times, sys);

    // For each sat
    for (size_t iSat = 0; iSat < nSats; ++iSat) {
        Viewer& sat1     = allSats[iSat];
        const size_t id1 = sat1.get_id();

        // For every other sat
        for (size_t jSat = iSat + 1; jSat < nSats; ++jSat) {
            Viewer& sat2     = allSats[jSat];
            const size_t id2 = sat2.get_id();

            // Satellite-level access for sat1 -> sat2
            RiseSetArray satAccess = find_sat_to_sat_accesses(iSat, jSat, sat1, sat2, times, interpStates);

            // Store
            if (satAccess.size() > 0) {
                sat1.add_access(id2, satAccess);
                sat2.add_access(id1, satAccess);
            }
        }
    }
}

std::vector<Time> create_time_vector(const std::vector<State>& states, const Time& resolution, const AstrodynamicsSystem& sys)
{
    // Setup
    const size_t nSates   = states.size();
    const Time& startTime = states[0].time;
    const Time& endTime   = states[nSates - 1].time;

    // Reserve
    const size_t nTimes = std::ceil((endTime - startTime) / resolution) + 1;
    std::vector<Time> times;
    times.resize(nTimes);

    // Fill
    for (size_t ii = 0; ii < nTimes; ++ii) {
        if (ii < nTimes - 1) { times[ii] = startTime + ii * resolution; }
        else {
            times[ii] = endTime;
        }
    }

    return times;
}

std::vector<std::vector<State>>
    interpolate_states(const std::vector<Viewer>& allSats, const std::vector<Time>& times, const AstrodynamicsSystem& sys)
{

    const size_t nTimes = times.size();
    const size_t nSats  = allSats.size();

    std::vector<std::vector<State>> interpStates;
    interpStates.resize(nTimes);

    for (size_t iTime = 0; iTime < nTimes; ++iTime) {

        const Time& time = times[iTime];
        interpStates[iTime].resize(nSats);

        for (size_t iSat = 0; iSat < nSats; ++iSat) {

            const Viewer& sat = allSats[iSat];
            const State state = sat.get_state_at(time);

            const auto elements = conversions::convert(state.elements, state.elements.get_set(), ElementSet::CARTESIAN, sys);
            interpStates[iTime][iSat] = State{ time, elements };
        }
    }

    return interpStates;
}

RiseSetArray find_sat_to_sat_accesses(
    const size_t& iSat,
    const size_t& jSat,
    Viewer& sat1,
    Viewer& sat2,
    const std::vector<Time>& times,
    const std::vector<std::vector<State>>& states
)
{

    // Total sat to sat access
    RiseSetArray satAccess;

    // First determine access sensor by sensor
    for (auto& sensor1 : sat1.get_sensors()) {
        const size_t id1 = sensor1.get_id();

        for (auto& sensor2 : sat2.get_sensors()) {
            const size_t id2 = sensor1.get_id();

            RiseSetArray access = find_sensor_to_sensor_accesses(iSat, jSat, sensor1, sensor2, times, states);

            // Store
            satAccess = (satAccess | access);
            if (access.size() > 0) { // TODO: Check 2-way access
                sensor1.add_access(id2, access);
                sensor2.add_access(id1, access);
            }
        }
    }

    return satAccess;
}


RiseSetArray find_sensor_to_sensor_accesses(
    const size_t& iSat,
    const size_t& jSat,
    const Sensor& sensor1,
    const Sensor& sensor2,
    const std::vector<Time>& times,
    const std::vector<std::vector<State>>& states
)
{

    RiseSetArray access;
    Time rise;
    bool hasAccess;
    for (size_t iTime = 0; iTime < states.size(); ++iTime) {

        // Get states
        const State& state1 = states[iTime][iSat];
        const State& state2 = states[iTime][jSat];

        const BasisArray& state1to2 = { state2.elements[0] - state1.elements[0],
                                        state2.elements[1] - state1.elements[1],
                                        state2.elements[2] - state1.elements[2] };

        // Manage bookends
        if (iTime == 0) {
            hasAccess = sensor1.contains(state1to2);
            if (hasAccess) { rise = times[0]; }
            continue;
        }
        else if (iTime == states.size() - 1) {
            if ((hasAccess && sensor1.contains(state1to2))) { access.append(rise, times[iTime]); }

            // NOTE: this ignores cases where the last time is a rise time -> access analyzed for [0, T)
        }

        // Check for rise/set times
        if (hasAccess && !sensor1.contains(state1to2)) {
            hasAccess = false;

            access.append(rise, times[iTime]);
        }
        else if (!hasAccess && sensor1.contains(state1to2)) {
            hasAccess = true;
            rise      = times[iTime];
        }
    }

    return access;
}