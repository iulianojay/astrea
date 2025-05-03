#pragma once

#include <string>
#include <unordered_map>

// mp-units
#include <mp-units/compat_macros.h>
#include <mp-units/ext/format.h>

#include <mp-units/format.h>
#include <mp-units/ostream.h>
#include <mp-units/systems/si.h>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/constants/astronomical_constants.h>
#include <astro/element_sets/OrbitalElements.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/time/Time.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/units/units.hpp>

namespace astro {

class Spacecraft {

  public:
    // Constructor
    Spacecraft() = default;
    Spacecraft(OrbitalElements state0, Date epoch = J2000);

    // Destructor
    virtual ~Spacecraft() = default;

    void update_state(const State& state);
    State& get_state() { return _state; };
    Date get_epoch() const { return _epoch; }
    Mass get_mass() const;

    const State& get_initial_state() const;
    const State& get_final_state() const;
    const State& get_closest_state(const Time& time) const;
    State get_state_at(const Time& time, const AstrodynamicsSystem& sys) const;
    std::vector<State>& get_states() { return _states; }
    const std::vector<State>& get_states() const { return _states; }
    size_t n_states() const { return _states.size(); }

    Unitless get_coefficient_of_drag() const;
    Unitless get_coefficient_of_lift() const;
    Unitless get_coefficient_of_reflectivity() const;

    SurfaceArea get_ram_area() const;
    SurfaceArea get_solar_area() const;
    SurfaceArea get_lift_area() const;

    size_t get_id() const { return _id; }

  protected:
    size_t _id;
    std::string _name;

    // Spacecraft properties
    Mass _mass                          = 1000.0 * mp_units::si::unit_symbols::kg;
    Unitless _coefficientOfDrag         = 2.2 * mp_units::one;
    Unitless _coefficientOfLift         = 0.9 * mp_units::one;
    Unitless _coefficientOfReflectivity = 1.1 * mp_units::one;
    SurfaceArea _ramArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    SurfaceArea _sunArea                = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);
    SurfaceArea _liftArea               = 1.0 * mp_units::pow<2>(mp_units::si::unit_symbols::m);

    // Orbital elements
    State _state;
    std::vector<State> _states;

    // Epoch variables
    Date _epoch;

    void generate_id_hash();
};

} // namespace astro