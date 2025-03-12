#pragma once

#ifndef SWIG
    #include <string>
    #include <unordered_map>
#endif

#include <access/platforms/Sensor.hpp>

#include <astro/constants/astronomical_constants.h>
#include <astro/types/typedefs.hpp>

#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/State.hpp>
#include <astro/time/Time.hpp>
#include <astro/time/Date.hpp>

#include <astro/astro.fwd.hpp>

class Spacecraft {

public:

    // Constructor
    Spacecraft() = default;
    Spacecraft(OrbitalElements state0, Date epoch = J2000);

    // Destructor
    ~Spacecraft();

    void update_state(const State& state);
    State& get_state() { return _state; };
    Date get_epoch() const { return _epoch; }
    double get_mass() const;

    const State& get_initial_state() const;
    const State& get_final_state() const;
    const State& get_closest_state(const Time& time) const;
    State get_state_at(const Time& time) const;
    std::vector<State>& get_states() { return _states; }
    const std::vector<State>& get_states() const { return _states; }
    size_t n_states() const { return _states.size(); }

    double get_coefficient_of_drag() const;
    double get_coefficient_of_lift() const;
    double get_coefficient_of_reflectivity() const;

    double get_ram_area() const;
    double get_solar_area() const;
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