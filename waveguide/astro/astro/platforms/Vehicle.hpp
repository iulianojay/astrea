/**
 * @file Vehicle.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a vehicle in the waveguide astro platform.
 * @version 0.1
 * @date 2025-08-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include <units/units.hpp>

#include <astro/element_sets/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frames.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/type_traits.hpp>

namespace waveguide {
namespace astro {

/**
 * @brief Concept to check if a type has a method to update the state.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasUpdateState = requires(T vehicle, const State& state)
{
    { vehicle.update_state(state) };
};

/**
 * @brief Concept to check if a type has a method to get the current state.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetState = requires(T vehicle)
{
    {
        vehicle.get_state()
        } -> std::same_as<State&>;
};

/**
 * @brief Concept to check if a type has a method to get the initial state.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetInitialState = requires(const T vehicle)
{
    {
        vehicle.get_initial_state()
        } -> std::same_as<const State&>;
};

/**
 * @brief Concept to check if a type has a method to get the mass.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetMass = requires(T vehicle)
{
    {
        vehicle.get_mass()
        } -> std::same_as<Mass>;
};

/**
 * @brief Concept to check if a type has a method to get the ram area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetRamArea = requires(T vehicle)
{
    {
        vehicle.get_ram_area()
        } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of drag.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfDrag = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_drag()
        } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to get the lift area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetLiftArea = requires(T vehicle)
{
    {
        vehicle.get_lift_area()
        } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of lift.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfLift = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_lift()
        } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to get the solar area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetSolarArea = requires(T vehicle)
{
    {
        vehicle.get_solar_area()
        } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of reflectivity.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfReflectivity = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_reflectivity()
        } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to clear its state.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasClear = requires(T vehicle)
{
    { vehicle.clear() };
};

/**
 * @brief Concept to check if a type is a user-defined vehicle.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsUserDefinedVehicle = requires(T)
{
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires HasUpdateState<T>;
    requires HasGetState<T>;
    requires HasGetInitialState<T>;
    requires HasGetMass<T>;
};

namespace detail {

/**
 * @brief Pure virtual base class for vehicle inner implementations.
 */
struct VehicleInnerBase : public virtual FrameReference {

    /**
     * @brief Destructor for VehicleInnerBase.
     */
    virtual ~VehicleInnerBase() {}

    /**
     * @brief Updates the state of the vehicle.
     *
     * @param state The new state to set for the vehicle.
     */
    virtual void update_state(const State& state) = 0;

    /**
     * @brief Gets the current state of the vehicle.
     *
     * @return State& A reference to the current state of the vehicle.
     */
    virtual State& get_state() = 0;

    /**
     * @brief Gets the initial state of the vehicle.
     *
     * @return const State& A reference to the initial state of the vehicle.
     */
    virtual const State& get_initial_state() const = 0;

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    virtual Mass get_mass() const = 0;

    /**
     * @brief Gets the ram area of the vehicle.
     *
     * @return SurfaceArea The ram area of the vehicle.
     */
    virtual SurfaceArea get_ram_area() const = 0;

    /**
     * @brief Gets the lift area of the vehicle.
     *
     * @return SurfaceArea The lift area of the vehicle.
     */
    virtual SurfaceArea get_lift_area() const = 0;

    /**
     * @brief Gets the solar area of the vehicle.
     *
     * @return SurfaceArea The solar area of the vehicle.
     */
    virtual SurfaceArea get_solar_area() const = 0;

    /**
     * @brief Gets the coefficient of drag of the vehicle.
     *
     * @return Unitless The coefficient of drag of the vehicle.
     */
    virtual Unitless get_coefficient_of_drag() const = 0;

    /**
     * @brief Gets the coefficient of lift of the vehicle.
     *
     * @return Unitless The coefficient of lift of the vehicle.
     */
    virtual Unitless get_coefficient_of_lift() const = 0;

    /**
     * @brief Gets the coefficient of reflectivity of the vehicle.
     *
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    virtual Unitless get_coefficient_of_reflectivity() const = 0;

    /**
     * @brief Clears the state of the vehicle.
     */
    virtual void clear() = 0;

    /**
     * @brief Clones the vehicle inner implementation.
     *
     * @return std::unique_ptr<VehicleInnerBase> A unique pointer to the cloned vehicle inner implementation.
     */
    virtual std::unique_ptr<VehicleInnerBase> clone() const = 0;

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return const void* A pointer to the internal vehicle instance.
     */
    virtual const void* get_ptr() const = 0;

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return void* A pointer to the internal vehicle instance.
     */
    virtual void* get_ptr() = 0;
};

/**
 * @brief A template class for vehicle inner implementations.
 *
 * @tparam T The type of the vehicle implementation.
 */
template <typename T>
struct VehicleInner final : public VehicleInnerBase {

    /**
     * @brief Default constructor for VehicleInner.
     */
    VehicleInner() = default;

    /**
     * @brief Deleted copy assignment operator.
     */
    VehicleInner(const VehicleInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    VehicleInner(VehicleInner&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    VehicleInner& operator=(const VehicleInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    VehicleInner& operator=(VehicleInner&&) = delete;

    /**
     * @brief Constructs a VehicleInner with a given value.
     *
     * @param x The value to initialize the vehicle inner implementation.
     */
    explicit VehicleInner(const T& x) :
        _value(x)
    {
    }

    /**
     * @brief Constructs a VehicleInner with a given value.
     *
     * @param x The value to initialize the vehicle inner implementation.
     */
    explicit VehicleInner(T&& x) :
        _value(std::move(x))
    {
    }

    /**
     * @brief Updates the state of the vehicle.
     *
     * @param state The new state to set for the vehicle.
     */
    void update_state(const State& state) final { _value.update_state(state); }

    /**
     * @brief Gets the current state of the vehicle.
     *
     * @return State& A reference to the current state of the vehicle.
     */
    State& get_state() final { return _value.get_state(); }

    /**
     * @brief Gets the initial state of the vehicle.
     *
     * @return const State& A reference to the initial state of the vehicle.
     */
    const State& get_initial_state() const final { return _value.get_initial_state(); }

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const final { return _value.get_mass(); }

    /**
     * @brief Gets the ram area of the vehicle or a default value.
     *
     * @return SurfaceArea The ram area of the vehicle.
     */
    SurfaceArea get_ram_area() const final { return get_ram_area_impl(_value); }

    /**
     * @brief Gets the lift area of the vehicle or a default value.
     *
     * @return SurfaceArea The lift area of the vehicle.
     */
    SurfaceArea get_lift_area() const final { return get_lift_area_impl(_value); }

    /**
     * @brief Gets the solar area of the vehicle or a default value.
     *
     * @return SurfaceArea The solar area of the vehicle.
     */
    SurfaceArea get_solar_area() const final { return get_solar_area_impl(_value); }

    /**
     * @brief Gets the coefficient of drag of the vehicle or a default value.
     *
     * @return Unitless The coefficient of drag of the vehicle.
     */
    Unitless get_coefficient_of_drag() const final { return get_coefficient_of_drag_impl(_value); }

    /**
     * @brief Gets the coefficient of lift of the vehicle or a default value.
     *
     * @return Unitless The coefficient of lift of the vehicle.
     */
    Unitless get_coefficient_of_lift() const final { return get_coefficient_of_lift_impl(_value); }

    /**
     * @brief Gets the coefficient of reflectivity of the vehicle or a default value.
     *
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    Unitless get_coefficient_of_reflectivity() const final { return get_coefficient_of_reflectivity_impl(_value); }

    /**
     * @brief Clears the state of the vehicle.
     */
    void clear() final { clear_impl(_value); };

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return RadiusVector<EarthCenteredInertial>
     */
    RadiusVector<EarthCenteredInertial> get_inertial_position(const Date& date) const override final
    {
        return _value.get_inertial_position(date);
    }

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return VelocityVector<EarthCenteredInertial>
     */
    VelocityVector<EarthCenteredInertial> get_inertial_velocity(const Date& date) const override final
    {
        return _value.get_inertial_velocity(date);
    }

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return AccelerationVector<EarthCenteredInertial>
     */
    AccelerationVector<EarthCenteredInertial> get_inertial_acceleration(const Date& date) const override final
    {
        return _value.get_inertial_acceleration(date);
    }

    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const override final { return _value.get_name(); }

    /**
     * @brief Gets the default ram area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the ram area from.
     * @return SurfaceArea The ram area of the vehicle.
     */
    template <typename U>
    requires(!HasGetRamArea<U>) static SurfaceArea get_ram_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }

    /**
     * @brief Gets the ram area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the ram area from.
     * @return SurfaceArea The ram area of the vehicle.
     */
    template <typename U>
    requires(HasGetRamArea<U>) static SurfaceArea get_ram_area_impl(const U& value) { return value.get_ram_area(); }


    /**
     * @brief Gets the default lift area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the lift area from.
     * @return SurfaceArea The lift area of the vehicle.
     */
    template <typename U>
    requires(!HasGetLiftArea<U>) static SurfaceArea get_lift_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }

    /**
     * @brief Gets the lift area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the lift area from.
     * @return SurfaceArea The lift area of the vehicle.
     */
    template <typename U>
    requires(HasGetLiftArea<U>) static SurfaceArea get_lift_area_impl(const U& value) { return value.get_lift_area(); }

    /**
     * @brief Gets the default solar area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the solar area from.
     * @return SurfaceArea The solar area of the vehicle.
     */
    template <typename U>
    requires(!HasGetSolarArea<U>) static SurfaceArea get_solar_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }

    /**
     * @brief Gets the solar area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the solar area from.
     * @return SurfaceArea The solar area of the vehicle.
     */
    template <typename U>
    requires(HasGetSolarArea<U>) static SurfaceArea get_solar_area_impl(const U& value)
    {
        return value.get_solar_area();
    }

    /**
     * @brief Gets the default coefficient of drag of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of drag from.
     * @return Unitless The coefficient of drag of the vehicle.
     */
    template <typename U>
    requires(!HasGetCoefficientOfDrag<U>) static Unitless get_coefficient_of_drag_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    /**
     * @brief Gets the coefficient of drag of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of drag from.
     * @return Unitless The coefficient of drag of the vehicle.
     */
    template <typename U>
    requires(HasGetCoefficientOfDrag<U>) static Unitless get_coefficient_of_drag_impl(const U& value)
    {
        return value.get_coefficient_of_drag();
    }

    /**
     * @brief Gets the default coefficient of lift of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of lift from.
     * @return Unitless The coefficient of lift of the vehicle.
     */
    template <typename U>
    requires(!HasGetCoefficientOfLift<U>) static Unitless get_coefficient_of_lift_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    /**
     * @brief Gets the coefficient of lift of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of lift from.
     * @return Unitless The coefficient of lift of the vehicle.
     */
    template <typename U>
    requires(HasGetCoefficientOfLift<U>) static Unitless get_coefficient_of_lift_impl(const U& value)
    {
        return value.get_coefficient_of_lift();
    }

    /**
     * @brief Gets the default coefficient of reflectivity of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of reflectivity from.
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    template <typename U>
    requires(!HasGetCoefficientOfReflectivity<U>) static Unitless get_coefficient_of_reflectivity_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    /**
     * @brief Gets the coefficient of reflectivity of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of reflectivity from.
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    template <typename U>
    requires(HasGetCoefficientOfReflectivity<U>) static Unitless get_coefficient_of_reflectivity_impl(const U& value)
    {
        return value.get_coefficient_of_reflectivity();
    }

    /**
     * @brief Does nothing on clear
     *
     * @param value The vehicle instance to clear.
     */
    template <typename U>
    requires(!HasClear<U>) void clear_impl(U&) {}

    /**
     * @brief Clears the state of the vehicle.
     *
     * @param value The vehicle instance to clear.
     */
    template <typename U>
    requires(HasClear<U>) void clear_impl(U& value) { value.clear(); }

    /**
     * @brief Clones the vehicle inner implementation.
     *
     * @return std::unique_ptr<VehicleInnerBase> A unique pointer to the cloned vehicle inner implementation.
     */
    std::unique_ptr<VehicleInnerBase> clone() const final { return std::make_unique<VehicleInner>(_value); }

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return const void* A pointer to the internal vehicle instance.
     */
    const void* get_ptr() const final { return &_value; }

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return void* A pointer to the internal vehicle instance.
     */
    void* get_ptr() final { return &_value; }

    T _value; //!< The value of the vehicle inner implementation, which is the user-defined vehicle type.
};

} // namespace detail

class Vehicle; // Forward declaration of the Vehicle class

/**
 * @brief Concept to check if a type can be generically constructed as a Vehicle.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsGenericallyConstructableVehicle = requires(T)
{
    requires IsUserDefinedVehicle<T>;
    std::negation<std::is_same<Vehicle, remove_cv_ref<T>>>::value;
};


/**
 * @brief A class representing a vehicle in the waveguide astro platform.
 * This class serves as a base for user-defined vehicles and provides a common interface.
 */
class Vehicle : public FrameReference {

  public:
    /**
     * @brief Default constructor for Vehicle.
     */
    Vehicle();

  private:
    /**
     * @brief Generic implicit constructor for Vehicle.
     */
    void generic_ctor_impl();

  public:
    /**
     * @brief Constructs a Vehicle with a user-defined type.
     *
     * @tparam T The type of the user-defined vehicle.
     * @param x The user-defined vehicle instance to initialize the Vehicle.
     */
    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) explicit Vehicle(T&& x) :
        _ptr(std::make_unique<detail::VehicleInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    /**
     * @brief Copy constructor for Vehicle.
     *
     * @param other The Vehicle instance to copy from.
     */
    Vehicle(const Vehicle&);

    /**
     * @brief Move constructor for Vehicle.
     *
     * @param other The Vehicle instance to move from.
     */
    Vehicle(Vehicle&&) noexcept;

    /**
     * @brief Copy assignment operator for Vehicle.
     *
     * @return Vehicle& A reference to the current Vehicle instance.
     */
    Vehicle& operator=(Vehicle&&) noexcept;

    /**
     * @brief Move assignment operator for Vehicle.
     *
     * @param other The Vehicle instance to move from.
     * @return Vehicle& A reference to the current Vehicle instance.
     */
    Vehicle& operator=(const Vehicle&);

    /**
     * @brief Generic assignment operator for Vehicle.
     *
     * @tparam T The type of the user-defined vehicle.
     * @param x The user-defined vehicle instance to assign to the Vehicle.
     * @return Vehicle& A reference to the current Vehicle instance.
     */
    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) Vehicle& operator=(T&& x)
    {
        return (*this) = Vehicle(std::forward<T>(x));
    }

    /**
     * @brief Extracts the user-defined vehicle from the Vehicle instance.
     *
     * @tparam T The type of the user-defined vehicle to extract.
     * @return const T* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr.
     */
    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) const T* extract() const noexcept
    {
        auto p = static_cast<const detail::VehicleInner<T>*>(ptr());
        return p == nullptr ? nullptr : &(p->_value);
    }

    /**
     * @brief Updates the state of the vehicle.
     *
     * @param state The new state to set for the vehicle.
     */
    void update_state(const State& state) { return _ptr->update_state(state); }

    /**
     * @brief Gets the current state of the vehicle.
     *
     * @return State& A reference to the current state of the vehicle.
     */
    State& get_state() { return _ptr->get_state(); }

    /**
     * @brief Gets the state of the vehicle.
     *
     * @return State A copy to the state of the vehicle.
     */
    State get_state() const { return _ptr->get_state(); } // TODO: Extend to const context instead of copying

    /**
     * @brief Gets the initial state of the vehicle.
     *
     * @return const State& A reference to the initial state of the vehicle.
     */
    const State& get_initial_state() const { return _ptr->get_state(); }

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const { return _ptr->get_mass(); }

    /**
     * @brief Get the ram area of the vehicle.
     *
     * @return SurfaceArea The ram area of the vehicle.
     */
    SurfaceArea get_ram_area() const { return _ptr->get_ram_area(); }

    /**
     * @brief Get the lift area of the vehicle.
     *
     * @return SurfaceArea The lift area of the vehicle.
     */
    SurfaceArea get_lift_area() const { return _ptr->get_lift_area(); }

    /**
     * @brief Get the solar area of the vehicle.
     *
     * @return SurfaceArea The solar area of the vehicle.
     */
    SurfaceArea get_solar_area() const { return _ptr->get_solar_area(); }

    /**
     * @brief Gets the coefficient of drag.
     *
     * @return Unitless The coefficient of drag.
     */
    Unitless get_coefficient_of_drag() const { return _ptr->get_coefficient_of_drag(); }

    /**
     * @brief Gets the coefficient of lift.
     *
     * @return Unitless The coefficient of lift.
     */
    Unitless get_coefficient_of_lift() const { return _ptr->get_coefficient_of_lift(); }

    /**
     * @brief Gets the coefficient of reflectivity.
     *
     * @return Unitless The coefficient of reflectivity.
     */
    Unitless get_coefficient_of_reflectivity() const { return _ptr->get_coefficient_of_reflectivity(); }

    /**
     * @brief Clears the state of the vehicle.
     */
    void clear() { _ptr->clear(); }

    /**
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return RadiusVector<EarthCenteredInertial>
     */
    RadiusVector<EarthCenteredInertial> get_inertial_position(const Date& date) const override
    {
        return ptr()->get_inertial_position(date);
    }

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return VelocityVector<EarthCenteredInertial>
     */
    VelocityVector<EarthCenteredInertial> get_inertial_velocity(const Date& date) const override
    {
        return ptr()->get_inertial_velocity(date);
    }

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return AccelerationVector<EarthCenteredInertial>
     */
    AccelerationVector<EarthCenteredInertial> get_inertial_acceleration(const Date& date) const override
    {
        return ptr()->get_inertial_acceleration(date);
    }

    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const override { return ptr()->get_name(); }

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return const void* A pointer to the internal vehicle instance.
     */
    const void* get_ptr() const;

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return void* A pointer to the internal vehicle instance.
     */
    void* get_ptr();

  private:
    std::unique_ptr<detail::VehicleInnerBase> _ptr; //!< Pointer to the internal vehicle implementation, which can be a user-defined type

    State _state;                        //!< Current state of the vehicle
    Mass _mass;                          //!< Mass of the vehicle
    SurfaceArea _ramArea;                //!< Ram area of the vehicle
    SurfaceArea _liftArea;               //!< Lift area of the vehicle
    SurfaceArea _solarArea;              //!< Solar area of the vehicle
    Unitless _coefficientOfDrag;         //!< Coefficient of drag of the vehicle
    Unitless _coefficientOfLift;         //!< Coefficient of lift of the vehicle
    Unitless _coefficientOfReflectivity; //!< Coefficient of reflectivity of the vehicle

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return detail::VehicleInnerBase* A pointer to the internal vehicle instance.
     */
    detail::VehicleInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return detail::VehicleInnerBase* A pointer to the internal vehicle instance.
     */
    detail::VehicleInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace waveguide