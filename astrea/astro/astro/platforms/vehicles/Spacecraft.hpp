/**
 * @file Spacecraft.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a spacecraft in the astrea astro platform.
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <string>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/platforms/Vehicle.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/state/StateHistory.hpp>

namespace astrea {
namespace astro {

/**
 * @brief A class representing a spacecraft in the astrea astro platform.
 * This class encapsulates the properties of a spacecraft, including its
 * mass, dynamic coefficients, and surface areas.
 */
class Spacecraft : public ThrusterPlatform {

  public:
    /**
     * @brief Default constructor for Spacecraft.
     */
    Spacecraft() { generate_id(); };

    /**
     * @brief Constructs a Spacecraft with a GeneralPerturbations object and an AstrodynamicsSystem.
     *
     * @param gp The GeneralPerturbations object containing initial parameters.
     * @param sys The AstrodynamicsSystem to which this spacecraft belongs.
     */
    Spacecraft(const GeneralPerturbations& gp, const AstrodynamicsSystem& sys);

    /**
     * @brief Virtual destructor for Spacecraft.
     */
    virtual ~Spacecraft() = default;

    /**
     * @brief Equality operator to compare two Spacecraft objects.
     *
     * @param other The other Spacecraft to compare with.
     * @return true if the Spacecraft objects are equal, false otherwise.
     */
    bool operator==(const Spacecraft& other) const;

    /**
     * @brief Gets the inertial position of the spacecraft at a specific date.
     *
     * @param date The date at which to retrieve the position.
     * @return RadiusVector<frames::earth::icrf> The inertial position of the spacecraft.
     */
    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const override;

    /**
     * @brief Gets the inertial velocity of the spacecraft at a specific date.
     *
     * @param date The date at which to retrieve the velocity.
     * @return VelocityVector<frames::earth::icrf> The inertial velocity of the spacecraft.
     */
    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const override;

    /**
     * @brief Stores the state history of the spacecraft.
     *
     * @param history The StateHistory object to store.
     */
    void set_state_history(const StateHistory& history);

    /**
     * @brief Stores a single state in the spacecraft's state history.
     *
     * @param state The State object to store.
     */
    void store_state(const State& state);

    /**
     * @brief Gets the initial state of the spacecraft.
     *
     * @return State& A reference to the initial state of the spacecraft.
     */
    State& get_initial_state() { return _stateHistory.begin()->second; }

    /**
     * @brief Gets the initial state of the spacecraft.
     *
     * @return const State& A reference to the initial state of the spacecraft.
     */
    const State& get_initial_state() const { return _stateHistory.begin()->second; }

    /**
     * @brief Gets the state history of the spacecraft.
     *
     * @return StateHistory& A reference to the state history of the spacecraft.
     */
    StateHistory& get_state_history();

    /**
     * @brief Gets the state history of the spacecraft.
     *
     * @return const StateHistory& A reference to the state history of the spacecraft.
     */
    const StateHistory& get_state_history() const;

    /**
     * @brief Gets the mass of the spacecraft.
     *
     * @return Mass The mass of the spacecraft.
     */
    Mass get_mass() const;

    /**
     * @brief Gets the inertia tensor of the spacecraft.
     *
     * @return InertiaTensor<> The inertia tensor of the spacecraft.
     */
    InertiaTensor<> get_inertia_tensor() const;

    /**
     * @brief Gets the coefficients of drag, lift, and reflectivity.
     *
     * @return Unitless The coefficient of drag.
     */
    Unitless get_coefficient_of_drag() const;

    /**
     * @brief Gets the coefficient of lift.
     *
     * @return Unitless The coefficient of lift.
     */
    Unitless get_coefficient_of_lift() const;

    /**
     * @brief Gets the coefficient of reflectivity.
     *
     * @return Unitless The coefficient of reflectivity.
     */
    Unitless get_coefficient_of_reflectivity() const;

    /**
     * @brief Gets the surface areas for ram, solar, and lift.
     *
     * @return SurfaceArea The ram area of the spacecraft.
     */
    SurfaceArea get_ram_area() const;

    /**
     * @brief Gets the solar area of the spacecraft.
     *
     * @return SurfaceArea The solar area of the spacecraft.
     */
    SurfaceArea get_solar_area() const;

    /**
     * @brief Gets the lift area of the spacecraft.
     *
     * @return SurfaceArea The lift area of the spacecraft.
     */
    SurfaceArea get_lift_area() const;

    /**
     * @brief Gets the thrust of the spacecraft.
     *
     * @param state The state of the spacecraft for which to get the thrust.
     * @return ForceVector<frames::earth::icrf> The thrust of the spacecraft.
     */
    Perturbation get_control_authority(const State& state) const;

    /**
     * @brief Gets the unique identifier of the spacecraft.
     *
     * @return std::size_t The unique identifier of the spacecraft.
     */
    std::size_t get_id() const { return _id; }

    /**
     * @brief Gets the name of the spacecraft.
     *
     * @return std::string The name of the spacecraft.
     */
    std::string get_name() const { return _name; }

    /**
     * @brief Sets the mass of the spacecraft.
     *
     * @param mass The new mass to set for the spacecraft.
     */
    void set_mass(const Mass& mass);

    /**
     * @brief Sets the inertia tensor of the spacecraft.
     *
     * @param inertiaTensor The new inertia tensor to set for the spacecraft.
     */
    void set_inertia_tensor(const InertiaTensor<>& inertiaTensor);

    /**
     * @brief Sets the coefficients of drag.
     *
     * @param cd The coefficient of drag to set.
     */
    void set_coefficient_of_drag(const Unitless& cd);

    /**
     * @brief Sets the coefficient of lift.
     *
     * @param cl The coefficient of lift to set.
     */
    void set_coefficient_of_lift(const Unitless& cl);

    /**
     * @brief Sets the coefficient of reflectivity.
     *
     * @param cr The coefficient of reflectivity to set.
     */
    void set_coefficient_of_reflectivity(const Unitless& cr);

    /**
     * @brief Sets the surface area for ram.
     *
     * @param ramArea The ram area to set.
     */
    void set_ram_area(const SurfaceArea& ramArea);

    /**
     * @brief Sets the solar area of the spacecraft.
     *
     * @param solarArea The solar area to set.
     */
    void set_solar_area(const SurfaceArea& solarArea);

    /**
     * @brief Sets the lift area of the spacecraft.
     *
     * @param liftArea The lift area to set.
     */
    void set_lift_area(const SurfaceArea& liftArea);

    /**
     * @brief Sets the name of the spacecraft.
     *
     * @param name The name to set for the spacecraft.
     */
    void set_name(const std::string& name);

    // I hate this
    using PayloadPlatform<Thruster>::attach_payload;
    using PayloadPlatform<Thruster>::get_payloads;

    static constexpr Mass DEFAULT_MASS = 1000.0 * astrea::detail::mass_unit;     // Default mass of the spacecraft
    static constexpr InertiaTensor<> DEFAULT_INERTIA_TENSOR = InertiaTensor<>{}; // Default inertia tensor of the spacecraft
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_DRAG = 2.2 * astrea::detail::unitless; // Default coefficient of drag
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_LIFT = 0.9 * astrea::detail::unitless; // Default coefficient of lift
    static constexpr Unitless DEFAULT_COEFFICIENT_OF_REFLECTIVITY =
        1.1 * astrea::detail::unitless; // Default coefficient of reflectivity
    static constexpr SurfaceArea DEFAULT_RAM_AREA = 1.0 * mp_units::pow<2>(astrea::detail::distance_unit); // Default ram area
    static constexpr SurfaceArea DEFAULT_SOLAR_AREA = 1.0 * mp_units::pow<2>(astrea::detail::distance_unit); // Default solar area
    static constexpr SurfaceArea DEFAULT_LIFT_AREA = 1.0 * mp_units::pow<2>(astrea::detail::distance_unit); // Default lift area

  protected:
    std::size_t _id;   // Unique identifier for the spacecraft, generated from its properties
    std::string _name; // Name of the spacecraft, can be set by the user

    // Spacecraft properties
    Mass _mass                          = DEFAULT_MASS;                        //!< Mass of the spacecraft
    InertiaTensor<> _inertiaTensor      = DEFAULT_INERTIA_TENSOR;              //!< Inertia tensor of the spacecraft
    Unitless _coefficientOfDrag         = DEFAULT_COEFFICIENT_OF_DRAG;         //!< Coefficient of drag
    Unitless _coefficientOfLift         = DEFAULT_COEFFICIENT_OF_LIFT;         //!< Coefficient of lift
    Unitless _coefficientOfReflectivity = DEFAULT_COEFFICIENT_OF_REFLECTIVITY; //!< Coefficient of reflectivity
    SurfaceArea _ramArea                = DEFAULT_RAM_AREA;                    //!< Ram area of the spacecraft
    SurfaceArea _sunArea                = DEFAULT_SOLAR_AREA;                  //!< Solar area of the spacecraft
    SurfaceArea _liftArea               = DEFAULT_LIFT_AREA;                   //!< Lift area of the spacecraft

    // State history
    StateHistory _stateHistory; // History of states for the spacecraft

    /**
     * @brief Generates a unique identifier for the spacecraft based on its properties.
     * This method is called in the constructor to ensure that each spacecraft has a unique ID.
     */
    void generate_id();
};

static_assert(IsUserDefinedVehicle<Spacecraft>, "Spacecraft must satisfy the IsVehicle concept");

} // namespace astro
} // namespace astrea