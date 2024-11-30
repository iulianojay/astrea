#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include "astronomical_constants.h"
#include "typedefs.hpp"

#include "Sensor.hpp"
#include "OrbitalElements.hpp"
#include "State.hpp"
#include "Date.hpp"

#include "Plane.fwd.hpp"
#include "Shell.fwd.hpp"
#include "Constellation.fwd.hpp"

class Spacecraft {

public:

    // Constructor
    Spacecraft() = default;
    Spacecraft(OrbitalElements state0, std::string epoch);

    // Destructor
    ~Spacecraft();

    // Function: Set spacecraft coefficient of reflectivity
    // Inputs: coefficient of reflectivity (--)
    void coefficient_of_reflectivity(double Cr);

    // Function: Set initial epoch of integration
    // Inputs: Initial epoch string in the format: "MON-DY-YEAR HH:MM:SS.SS"
    void set_epoch(std::string inputEpoch);

    void update_state(const State& state);

    const State& get_initial_state() const;
    const State& get_final_state() const;
    const State& get_closest_state(const Time& time) const;
    State get_state_at(const Time& time) const;
    std::vector<State>& get_states() { return _states; }
    const std::vector<State>& get_states() const { return _states; }

    size_t n_states() const { return _states.size(); }

    const Date& get_epoch() const { return _epoch; }

    // Function: Get spacecraft mass
    // Outputs: mass (kg)
    double get_mass() const;

    // Function: Get spacecraft coefficient of drag
    // Outputs: coefficient of drag (--)
    double get_coefficient_of_drag() const;

    // Function: Get spacecraft coefficient of lift
    // Outputs: coefficient of lift (--)
    double get_coefficient_of_lift() const;

    // Function: Get spacecraft coefficient of reflectivity
    // Outputs: coefficient of reflectivity (--)
    double get_coefficient_of_reflectivity() const;

    // Function: Get spacecraft ram-facing area
    // Outputs: net ram-facing area / array of areas (m^2)
    double get_ram_area() const;

    // Function: Get spacecraft sun-facing area
    // Outputs: net sun-facing area / array of areas (m^2)
    double get_solar_area() const;

    // Function: Get spacecraft earth-facing area
    // Outputs: net earth-facing area / array of areas (m^2)
    double get_lift_area() const;

    void attach(Sensor& sensor) { _sensors.emplace_back(sensor); }
    void attach(std::vector<Sensor>& _sensors) { _sensors.insert(std::end(_sensors), std::begin(_sensors), std::end(_sensors)); }

    std::vector<Sensor>& get_sensors() { return _sensors; }
    const std::vector<Sensor>& get_sensors() const { return _sensors; }

    size_t get_id() const { return _id; }

    void add_access(const size_t& receiverId, const RiseSetArray& access) {
        _accesses[_id, receiverId] = access;
    }

private:

    size_t _id;
    std::string _name;

    // Spacecraft properties
    double _mass = 1000.0;
    double _coefficientOfDrag = 2.2;
    double _coefficientOfLift = 0.9;
    double _coefficientOfReflectivity = 1.1;
    double _ramArea = 1.0;
    double _sunArea = 1.0;
    double _liftArea = 1.0;

    // Orbital elements
    State _state;
    std::vector<State> _states;

    // Epoch variables
    Date _epoch;

    // Access data
    AccessArray _accesses;
    std::vector<Sensor> _sensors;

    void generate_id_hash();
};


#ifdef SWIG

%template(SpacecraftVector) std::vector<Spacecraft>;
%template(SpacecraftVectorVector) std::vector<std::vector<Spacecraft>>;

#endif