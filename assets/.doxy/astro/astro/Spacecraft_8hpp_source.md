

# File Spacecraft.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**vehicles**](dir_6209fec1d31cfd277683fcd634983a45.md) **>** [**Spacecraft.hpp**](Spacecraft_8hpp.md)

[Go to the documentation of this file](Spacecraft_8hpp.md)


```C++

#pragma once

#include <string>

#include <units/units.hpp>
#include <utilities/IdProvider.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/definitions/dynamic_frames/tags.hpp>
#include <astro/frames/definitions/primary_frame.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

class Spacecraft : public ThrusterPlatform {

  public:
    Spacecraft() { _id = utilities::IdProvider::get_next_id<"Platform">(); };

    Spacecraft(const GeneralPerturbations& gp);

    virtual ~Spacecraft() = default;

    bool operator==(const Spacecraft& other) const;

    RadiusVector<frames::primary> get_position(const Date& date) const;

    VelocityVector<frames::primary> get_velocity(const Date& date) const;

    void set_state_history(const StateHistory& history);

    void store_state(const State& state);

    State& get_initial_state() { return _stateHistory.first(); }

    const State& get_initial_state() const { return _stateHistory.first(); }

    StateHistory& get_state_history();

    const StateHistory& get_state_history() const;

    Mass get_mass(const State& state) const;

    InertiaTensor<frames::dynamic::body> get_inertia_tensor(const State& state) const;

    Unitless get_coefficient_of_drag(const State& state) const;

    Unitless get_coefficient_of_lift(const State& state) const;

    Unitless get_coefficient_of_reflectivity(const State& state) const;

    SurfaceArea get_ram_area(const State& state) const;

    SurfaceArea get_solar_area(const State& state) const;

    SurfaceArea get_lift_area(const State& state) const;

    Perturbation get_control_authority(const State& state) const;

    std::size_t get_id() const { return _id; }

    std::string get_name() const { return _name; }

    void set_mass(const Mass& mass);

    void set_inertia_tensor(const InertiaTensor<frames::dynamic::body>& inertiaTensor);

    void set_coefficient_of_drag(const Unitless& cd);

    void set_coefficient_of_lift(const Unitless& cl);

    void set_coefficient_of_reflectivity(const Unitless& cr);

    void set_ram_area(const SurfaceArea& ramArea);

    void set_solar_area(const SurfaceArea& solarArea);

    void set_lift_area(const SurfaceArea& liftArea);

    void set_name(const std::string& name);

    // I hate this
    using PayloadPlatform<Thruster>::attach_payload;
    using PayloadPlatform<Thruster>::get_payloads;

    static constexpr Mass DEFAULT_MASS = 1000.0 * mp_units::si::unit_symbols::kg; // Default mass of the spacecraft
    static constexpr InertiaTensor<frames::dynamic::body> DEFAULT_INERTIA_TENSOR =
        InertiaTensor<frames::dynamic::body>{}; // Default inertia tensor of the spacecraft
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_DRAG = 2.2 * mp_units::one;         // Default coefficient of drag
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_LIFT = 0.9 * mp_units::one;         // Default coefficient of lift
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_REFLECTIVITY = 1.1 * mp_units::one; // Default coefficient of reflectivity
    static constexpr SurfaceArea DEFAULT_RAM_AREA = 1.0 * mp_units::si::unit_symbols::m * mp_units::si::unit_symbols::m; // Default ram area
    static constexpr SurfaceArea DEFAULT_SOLAR_AREA = 1.0 * mp_units::si::unit_symbols::m * mp_units::si::unit_symbols::m; // Default solar area
    static constexpr SurfaceArea DEFAULT_LIFT_AREA = 1.0 * mp_units::si::unit_symbols::m * mp_units::si::unit_symbols::m; // Default lift area

  protected:
    std::size_t _id;   // Unique identifier for the spacecraft, generated from its properties
    std::string _name; // Name of the spacecraft, can be set by the user

    // Spacecraft properties
    Mass _mass                                          = DEFAULT_MASS;           
    InertiaTensor<frames::dynamic::body> _inertiaTensor = DEFAULT_INERTIA_TENSOR; 
    Unitless _coefficientOfDrag                         = DEFAULT_COEFFICIENT_OF_DRAG; 
    Unitless _coefficientOfLift                         = DEFAULT_COEFFICIENT_OF_LIFT; 
    Unitless _coefficientOfReflectivity = DEFAULT_COEFFICIENT_OF_REFLECTIVITY;         
    SurfaceArea _ramArea                = DEFAULT_RAM_AREA;                            
    SurfaceArea _sunArea                = DEFAULT_SOLAR_AREA;                          
    SurfaceArea _liftArea               = DEFAULT_LIFT_AREA;                           

    // State history
    StateHistory _stateHistory; // History of states for the spacecraft
};

static_assert(IsUserDefinedVehicle<Spacecraft>, "Spacecraft must satisfy the IsVehicle concept");

} // namespace astro
} // namespace astrea
```


