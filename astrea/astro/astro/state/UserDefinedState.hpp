/**
 * @file UserDefinedState.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing the user-defined state of an astronomical object
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

#include <astro/types/concepts.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type is a user-defined vehicle.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsUserDefinedUserDefinedState = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires HasForceToDoubleVector<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

namespace detail {

/**
 * @brief Pure virtual base class for vehicle inner implementations.
 */
struct UserDefinedStateInnerBase {

    /**
     * @brief Destructor for UserDefinedStateInnerBase.
     */
    virtual ~UserDefinedStateInnerBase() {}

    virtual UserDefinedStateInnerBase operator+(const UserDefinedStateInnerBase& other) const = 0;
    virtual UserDefinedStateInnerBase operator-(const UserDefinedStateInnerBase& other) const = 0;
    virtual UserDefinedStateInnerBase& operator+=(const UserDefinedStateInnerBase& other)     = 0;
    virtual UserDefinedStateInnerBase& operator-=(const UserDefinedStateInnerBase& other)     = 0;
    virtual UserDefinedStateInnerBase operator*(const Unitless& scalar) const                 = 0;
    virtual UserDefinedStateInnerBase operator/(const Unitless& scalar) const                 = 0;
    virtual UserDefinedStateInnerBase& operator*=(const Unitless& scalar)                     = 0;
    virtual UserDefinedStateInnerBase& operator/=(const Unitless& scalar)                     = 0;
};

/**
 * @brief A template class for vehicle inner implementations.
 *
 * @tparam T The type of the vehicle implementation.
 */
template <typename T>
struct UserDefinedStateInner final : public UserDefinedStateInnerBase {

    /**
     * @brief Default constructor for UserDefinedStateInner.
     */
    UserDefinedStateInner() = default;

    /**
     * @brief Deleted copy assignment operator.
     */
    UserDefinedStateInner(const UserDefinedStateInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    UserDefinedStateInner(UserDefinedStateInner&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    UserDefinedStateInner& operator=(const UserDefinedStateInner&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    UserDefinedStateInner& operator=(UserDefinedStateInner&&) = delete;

    /**
     * @brief Constructs a UserDefinedStateInner with a given value.
     *
     * @param x The value to initialize the vehicle inner implementation.
     */
    explicit UserDefinedStateInner(const T& x) :
        _value(x)
    {
    }

    /**
     * @brief Constructs a UserDefinedStateInner with a given value.
     *
     * @param x The value to initialize the vehicle inner implementation.
     */
    explicit UserDefinedStateInner(T&& x) :
        _value(std::move(x))
    {
    }

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const final { return _value.get_mass(); }

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @return InertiaTensor<frames::dynamic::body> The inertia tensor of the vehicle.
     */
    InertiaTensor<frames::dynamic::body> get_inertia_tensor() const final { return get_inertia_tensor_impl(_value); }

    /**
     * @brief Gets the default inertia tensor of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the inertia tensor from.
     * @return InertiaTensor<frames::dynamic::body> The inertia tensor of the vehicle.
     */
    template <typename U>
        requires(!HasGetInertiaTensor<U>)
    static InertiaTensor<frames::dynamic::body> get_inertia_tensor_impl(const U&)
    {
        return InertiaTensor<frames::dynamic::body>();
    }

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the inertia tensor from.
     * @return InertiaTensor<frames::dynamic::body> The inertia tensor of the vehicle.
     */
    template <typename U>
        requires(HasGetInertiaTensor<U>)
    static InertiaTensor<frames::dynamic::body> get_inertia_tensor_impl(const U& value)
    {
        return value.get_inertia_tensor();
    }

    /**
     * @brief Gets the ram area of the vehicle or a default value.
     *
     * @return SurfaceArea The ram area of the vehicle.
     */
    SurfaceArea get_ram_area() const final { return get_ram_area_impl(_value); }

    /**
     * @brief Gets the default ram area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the ram area from.
     * @return SurfaceArea The ram area of the vehicle.
     */
    template <typename U>
        requires(!HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::distance_unit);
    }

    /**
     * @brief Gets the ram area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the ram area from.
     * @return SurfaceArea The ram area of the vehicle.
     */
    template <typename U>
        requires(HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U& value)
    {
        return value.get_ram_area();
    }

    /**
     * @brief Gets the lift area of the vehicle or a default value.
     *
     * @return SurfaceArea The lift area of the vehicle.
     */
    SurfaceArea get_lift_area() const final { return get_lift_area_impl(_value); }

    /**
     * @brief Gets the default lift area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the lift area from.
     * @return SurfaceArea The lift area of the vehicle.
     */
    template <typename U>
        requires(!HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::distance_unit);
    }

    /**
     * @brief Gets the lift area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the lift area from.
     * @return SurfaceArea The lift area of the vehicle.
     */
    template <typename U>
        requires(HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U& value)
    {
        return value.get_lift_area();
    }

    /**
     * @brief Gets the solar area of the vehicle or a default value.
     *
     * @return SurfaceArea The solar area of the vehicle.
     */
    SurfaceArea get_solar_area() const final { return get_solar_area_impl(_value); }

    /**
     * @brief Gets the default solar area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the solar area from.
     * @return SurfaceArea The solar area of the vehicle.
     */
    template <typename U>
        requires(!HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::distance_unit);
    }

    /**
     * @brief Gets the solar area of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the solar area from.
     * @return SurfaceArea The solar area of the vehicle.
     */
    template <typename U>
        requires(HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U& value)
    {
        return value.get_solar_area();
    }

    /**
     * @brief Gets the coefficient of drag of the vehicle or a default value.
     *
     * @return Unitless The coefficient of drag of the vehicle.
     */
    Unitless get_coefficient_of_drag() const final { return get_coefficient_of_drag_impl(_value); }

    /**
     * @brief Gets the default coefficient of drag of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of drag from.
     * @return Unitless The coefficient of drag of the vehicle.
     */
    template <typename U>
        requires(!HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U&)
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
        requires(HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U& value)
    {
        return value.get_coefficient_of_drag();
    }

    /**
     * @brief Gets the coefficient of lift of the vehicle or a default value.
     *
     * @return Unitless The coefficient of lift of the vehicle.
     */
    Unitless get_coefficient_of_lift() const final { return get_coefficient_of_lift_impl(_value); }

    /**
     * @brief Gets the default coefficient of lift of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of lift from.
     * @return Unitless The coefficient of lift of the vehicle.
     */
    template <typename U>
        requires(!HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U&)
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
        requires(HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U& value)
    {
        return value.get_coefficient_of_lift();
    }

    /**
     * @brief Gets the coefficient of reflectivity of the vehicle or a default value.
     *
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    Unitless get_coefficient_of_reflectivity() const final { return get_coefficient_of_reflectivity_impl(_value); }

    /**
     * @brief Gets the default coefficient of reflectivity of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the coefficient of reflectivity from.
     * @return Unitless The coefficient of reflectivity of the vehicle.
     */
    template <typename U>
        requires(!HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U&)
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
        requires(HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U& value)
    {
        return value.get_coefficient_of_reflectivity();
    }

    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const override final { return get_name_impl(_value); }

    /**
     * @brief Gets the default name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    template <typename U>
        requires(!HasGetName<U>)
    std::string get_name_impl(const U&) const
    {
        return "UserDefinedState";
    }

    /**
     * @brief Gets the name of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the name from.
     * @return std::string The name of the vehicle.
     */
    template <typename U>
        requires(HasGetName<U>)
    std::string get_name_impl(const U& value) const
    {
        return value.get_name();
    }

    /**
     * @brief Gets the control authority of the vehicle or a default value.
     *
     * @param state The state of the vehicle for which to get the control authority.
     * @return Perturbation The control authority of the vehicle.
     */
    Perturbation get_control_authority(const State& state) const final
    {
        return get_control_authority_impl(_value, state);
    }

    /**
     * @brief Gets the default thrust of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the control authority from.
     * @param state The state of the vehicle for which to get the control authority.
     * @return Perturbation The control authority of the vehicle.
     */
    template <typename U>
        requires(!HasGetControlAuthority<U>)
    Perturbation get_control_authority_impl(const U&, const State&) const
    {
        using mp_units::si::unit_symbols::m;
        using mp_units::si::unit_symbols::N;
        return { .force = { 0.0 * N, 0.0 * N, 0.0 * N }, .torque = { 0.0 * N * m, 0.0 * N * m, 0.0 * N * m } };
    }

    /**
     * @brief Gets the thrust and torque of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the thrust from.
     * @param state The state of the vehicle for which to get the thrust.
     * @return Perturbation The thrust and torque of the vehicle.
     */
    template <typename U>
        requires(HasGetControlAuthority<U>)
    Perturbation get_control_authority_impl(const U& value, const State& state) const
    {
        return value.get_control_authority(state);
    }

    /**
     * @brief Clones the vehicle inner implementation.
     *
     * @return std::unique_ptr<UserDefinedStateInnerBase> A unique pointer to the cloned vehicle inner implementation.
     */
    std::unique_ptr<UserDefinedStateInnerBase> clone() const final
    {
        return std::make_unique<UserDefinedStateInner>(_value);
    }

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

    /**
     * @brief Gets the type information of the internal vehicle instance.
     *
     * @return const std::type_info& The type information of the internal vehicle instance.
     */
    const std::type_info& type() const final { return typeid(T); }

    T _value; //!< The value of the vehicle inner implementation, which is the user-defined vehicle type.
};

} // namespace detail

class UserDefinedState; // Forward declaration of the UserDefinedState class

/**
 * @brief Concept to check if a type can be generically constructed as a UserDefinedState.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsGenericallyConstructableUserDefinedState = requires(T) {
    requires !std::is_same<UserDefinedState, remove_cv_ref<T>>::value;
    requires IsUserDefinedUserDefinedState<T>;
};


/**
 * @brief A class representing a vehicle in the astrea astro platform.
 * This class serves as a base for user-defined vehicles and provides a common interface.
 */
class UserDefinedState {

  public:
    /**
     * @brief Default constructor for UserDefinedState.
     */
    UserDefinedState();

  private:
    /**
     * @brief Generic implicit constructor for UserDefinedState.
     */
    void generic_ctor_impl();

  public:
    /**
     * @brief Constructs a UserDefinedState with a user-defined type.
     *
     * @tparam T The type of the user-defined vehicle.
     * @param x The user-defined vehicle instance to initialize the UserDefinedState.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    explicit UserDefinedState(T&& x) :
        _ptr(std::make_unique<detail::UserDefinedStateInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    /**
     * @brief Copy constructor for UserDefinedState.
     *
     * @param other The UserDefinedState instance to copy from.
     */
    UserDefinedState(const UserDefinedState&);

    /**
     * @brief Move constructor for UserDefinedState.
     *
     * @param other The UserDefinedState instance to move from.
     */
    UserDefinedState(UserDefinedState&&) noexcept;

    /**
     * @brief Copy assignment operator for UserDefinedState.
     *
     * @return UserDefinedState& A reference to the current UserDefinedState instance.
     */
    UserDefinedState& operator=(UserDefinedState&&) noexcept;

    /**
     * @brief Move assignment operator for UserDefinedState.
     *
     * @param other The UserDefinedState instance to move from.
     * @return UserDefinedState& A reference to the current UserDefinedState instance.
     */
    UserDefinedState& operator=(const UserDefinedState&);

    /**
     * @brief Generic assignment operator for UserDefinedState.
     *
     * @tparam T The type of the user-defined vehicle.
     * @param x The user-defined vehicle instance to assign to the UserDefinedState.
     * @return UserDefinedState& A reference to the current UserDefinedState instance.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    UserDefinedState& operator=(T&& x)
    {
        return (*this) = UserDefinedState(std::forward<T>(x));
    }

    /**
     * @brief Extracts the user-defined vehicle from the UserDefinedState instance.
     *
     * @tparam T The type of the user-defined vehicle to extract.
     * @return const T* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::UserDefinedStateInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Extracts the user-defined vehicle from the UserDefinedState instance.
     *
     * @tparam T The type of the user-defined vehicle to extract.
     * @return T* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr.
     */
    template <IsGenericallyConstructableUserDefinedState T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::UserDefinedStateInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const { return ptr()->get_mass(); }

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @return InertiaTensor<frames::dynamic::body> The inertia tensor of the vehicle.
     */
    InertiaTensor<frames::dynamic::body> get_inertia_tensor() const { return ptr()->get_inertia_tensor(); }

    /**
     * @brief Get the ram area of the vehicle.
     *
     * @return SurfaceArea The ram area of the vehicle.
     */
    SurfaceArea get_ram_area() const { return ptr()->get_ram_area(); }

    /**
     * @brief Get the lift area of the vehicle.
     *
     * @return SurfaceArea The lift area of the vehicle.
     */
    SurfaceArea get_lift_area() const { return ptr()->get_lift_area(); }

    /**
     * @brief Get the solar area of the vehicle.
     *
     * @return SurfaceArea The solar area of the vehicle.
     */
    SurfaceArea get_solar_area() const { return ptr()->get_solar_area(); }

    /**
     * @brief Gets the coefficient of drag.
     *
     * @return Unitless The coefficient of drag.
     */
    Unitless get_coefficient_of_drag() const { return ptr()->get_coefficient_of_drag(); }

    /**
     * @brief Gets the coefficient of lift.
     *
     * @return Unitless The coefficient of lift.
     */
    Unitless get_coefficient_of_lift() const { return ptr()->get_coefficient_of_lift(); }

    /**
     * @brief Gets the coefficient of reflectivity.
     *
     * @return Unitless The coefficient of reflectivity.
     */
    Unitless get_coefficient_of_reflectivity() const { return ptr()->get_coefficient_of_reflectivity(); }

    /**
     * @brief Gets the control authority of the vehicle.
     *
     * @param state The state of the vehicle for which to get the control authority.
     * @return Perturbation The control authority of the vehicle.
     */
    Perturbation get_control_authority(const State& state) const { return ptr()->get_control_authority(state); }


    /**
     * @brief Gets the name of the vehicle.
     *
     * @return std::string The name of the vehicle.
     */
    std::string get_name() const { return ptr()->get_name(); }

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
    std::unique_ptr<detail::UserDefinedStateInnerBase> _ptr; //!< Pointer to the internal vehicle implementation, which can be a user-defined type

    Mass _mass;                                          //!< Mass of the vehicle
    InertiaTensor<frames::dynamic::body> _inertiaTensor; //!< Inertia tensor of the vehicle
    SurfaceArea _ramArea;                                //!< Ram area of the vehicle
    SurfaceArea _liftArea;                               //!< Lift area of the vehicle
    SurfaceArea _solarArea;                              //!< Solar area of the vehicle
    Unitless _coefficientOfDrag;                         //!< Coefficient of drag of the vehicle
    Unitless _coefficientOfLift;                         //!< Coefficient of lift of the vehicle
    Unitless _coefficientOfReflectivity;                 //!< Coefficient of reflectivity of the vehicle

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return detail::UserDefinedStateInnerBase* A pointer to the internal vehicle instance.
     */
    detail::UserDefinedStateInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    /**
     * @brief Gets a pointer to the internal vehicle instance.
     *
     * @return detail::UserDefinedStateInnerBase* A pointer to the internal vehicle instance.
     */
    detail::UserDefinedStateInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace astrea