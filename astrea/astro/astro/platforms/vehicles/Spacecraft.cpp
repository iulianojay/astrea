#include <astro/platforms/vehicles/Spacecraft.hpp>

#include <algorithm>
#include <iostream>
#include <string>

#include <mp-units/systems/si.h>

#include <math/interpolation.hpp>
#include <units/units.hpp>

#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/state/CartesianVector.hpp>
#include <astro/state/State.hpp>
#include <astro/state/StateHistory.hpp>
#include <astro/state/frames/FrameReference.hpp>
#include <astro/state/frames/frames.hpp>
#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/typedefs.hpp>


using namespace mp_units;
using mp_units::angular::unit_symbols::deg;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

namespace astrea {
namespace astro {

Spacecraft::Spacecraft(const State& state0) :
    _state(state0),
    _state0(state0)
{
    generate_id_hash();
}

Spacecraft::Spacecraft(const GeneralPerturbations& gp, const AstrodynamicsSystem& sys)
{
    // TODO: Add catch/warning for missing values
    _id   = gp.NORAD_CAT_ID;
    _name = gp.OBJECT_NAME.has_value() ? gp.OBJECT_NAME.value() : "UNNAMED";
    if (!gp.SEMIMAJOR_AXIS.has_value() || !gp.ECCENTRICITY.has_value() || !gp.INCLINATION.has_value() ||
        !gp.RA_OF_ASC_NODE.has_value() || !gp.ARG_OF_PERICENTER.has_value() || !gp.MEAN_ANOMALY.has_value()) {
        std::cerr << "Missing GP info. Sad." << std::endl;
    }
    Keplerian coes(
        gp.SEMIMAJOR_AXIS.value() * km,
        gp.ECCENTRICITY.value() * one,
        gp.INCLINATION.value() * deg,
        gp.RA_OF_ASC_NODE.value() * deg,
        gp.ARG_OF_PERICENTER.value() * deg,
        gp.MEAN_ANOMALY.value() * deg
    );
    Date epoch = gp.EPOCH.has_value() ? Date(gp.EPOCH.value(), "%Y-%m-%dT%H:%M:%S") : J2000;

    _state0 = State(coes, epoch, sys);
    update_state(_state0);

    // All of these are just default values - TODO: Look into different or better values for approximating these
    // effects, or find how to approximate these
    // _mass
    // _coefficientOfLift
    // _sunArea
    // _liftArea
}

bool Spacecraft::operator==(const Spacecraft& other) const
{
    return (_id == other._id) && (_name == other._name) && (_mass == other._mass) &&
           (_coefficientOfDrag == other._coefficientOfDrag) && (_coefficientOfLift == other._coefficientOfLift) &&
           (_coefficientOfReflectivity == other._coefficientOfReflectivity) && (_ramArea == other._ramArea) &&
           (_sunArea == other._sunArea) && (_liftArea == other._liftArea) && (_state == other._state) &&
           (_state0 == other._state0);
}

State& Spacecraft::get_state() { return _state; };
const State& Spacecraft::get_initial_state() const { return _state0; }
void Spacecraft::update_state(const State& state) { _state = state; }
void Spacecraft::store_state_history(const StateHistory& history) { _stateHistory = history; }
StateHistory& Spacecraft::get_state_history() { return _stateHistory; }
const StateHistory& Spacecraft::get_state_history() const { return _stateHistory; }

// Spacecraft Property Getters
Mass Spacecraft::get_mass() const { return _mass; }
Unitless Spacecraft::get_coefficient_of_drag() const { return _coefficientOfDrag; }
Unitless Spacecraft::get_coefficient_of_lift() const { return _coefficientOfLift; }
Unitless Spacecraft::get_coefficient_of_reflectivity() const { return _coefficientOfReflectivity; }
SurfaceArea Spacecraft::get_ram_area() const { return _ramArea; }
SurfaceArea Spacecraft::get_solar_area() const { return _sunArea; }
SurfaceArea Spacecraft::get_lift_area() const { return _liftArea; }

// Setters
void Spacecraft::set_mass(const Mass& mass) { _mass = mass; }

void Spacecraft::set_coefficient_of_drag(const Unitless& cd) { _coefficientOfDrag = cd; }
void Spacecraft::set_coefficient_of_lift(const Unitless& cl) { _coefficientOfLift = cl; }
void Spacecraft::set_coefficient_of_reflectivity(const Unitless& cr) { _coefficientOfReflectivity = cr; }

void Spacecraft::set_ram_area(const SurfaceArea& ramArea) { _ramArea = ramArea; }
void Spacecraft::set_solar_area(const SurfaceArea& solarArea) { _sunArea = solarArea; }
void Spacecraft::set_lift_area(const SurfaceArea& liftArea) { _liftArea = liftArea; }

void Spacecraft::set_name(const std::string& name) { _name = name; }

RadiusVector<EarthCenteredInertial> Spacecraft::get_inertial_position(const Date& date) const
{
    const Cartesian elements = get_cartesian_state(date);
    return elements.get_position();
}

VelocityVector<EarthCenteredInertial> Spacecraft::get_inertial_velocity(const Date& date) const
{
    const Cartesian elements = get_cartesian_state(date);
    return elements.get_velocity();
}

Cartesian Spacecraft::get_cartesian_state(const Date& date) const
{
    if (_stateHistory.size() == 0) { throw std::runtime_error("State history is empty"); }
    const State state        = _stateHistory.get_state_at(date);
    const Cartesian elements = state.in_element_set<Cartesian>();
    return elements;
}

void Spacecraft::generate_id_hash()
{
    const auto elements0 = _state0.get_elements().to_vector();
    _id = std::hash<Unitless>()(elements0[0]) ^ std::hash<Unitless>()(elements0[1]) ^ std::hash<Unitless>()(elements0[2]) ^
          std::hash<Unitless>()(elements0[3]) ^ std::hash<Unitless>()(elements0[4]) ^ std::hash<Unitless>()(elements0[5]);
    _id ^= std::hash<double>()(_mass.numerical_value_ref_in(_mass.unit));
    _id ^= std::hash<double>()(_coefficientOfDrag.numerical_value_ref_in(_coefficientOfDrag.unit));
    _id ^= std::hash<double>()(_coefficientOfLift.numerical_value_ref_in(_coefficientOfLift.unit));
    _id ^= std::hash<double>()(_coefficientOfReflectivity.numerical_value_ref_in(_coefficientOfReflectivity.unit));
    _id ^= std::hash<double>()(_ramArea.numerical_value_ref_in(_ramArea.unit));
    _id ^= std::hash<double>()(_sunArea.numerical_value_ref_in(_sunArea.unit));
    _id ^= std::hash<double>()(_liftArea.numerical_value_ref_in(_liftArea.unit));
}

} // namespace astro
} // namespace astrea