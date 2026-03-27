/**
 * @file Vehicle.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief A class representing a vehicle in the astrea astro platform.
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

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include <units/units.hpp>

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frames.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Concept to check if a type has a method to get the mass.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetMass = requires(const T vehicle) {
    { vehicle.get_mass() } -> std::same_as<Mass>;
};

/**
 * @brief Concept to check if a type has a method to get the inertia tensor.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetInertiaTensor = requires(const T vehicle) {
    { vehicle.get_inertia_tensor() } -> std::same_as<InertiaTensor<>>;
};

/**
 * @brief Concept to check if a type has a method to get the ram area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetRamArea = requires(const T vehicle) {
    { vehicle.get_ram_area() } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of drag.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfDrag = requires(const T vehicle) {
    { vehicle.get_coefficient_of_drag() } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to get the lift area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetLiftArea = requires(const T vehicle) {
    { vehicle.get_lift_area() } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of lift.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfLift = requires(const T vehicle) {
    { vehicle.get_coefficient_of_lift() } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to get the solar area.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetSolarArea = requires(const T vehicle) {
    { vehicle.get_solar_area() } -> std::same_as<SurfaceArea>;
};

/**
 * @brief Concept to check if a type has a method to get the coefficient of reflectivity.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetCoefficientOfReflectivity = requires(const T vehicle) {
    { vehicle.get_coefficient_of_reflectivity() } -> std::same_as<Unitless>;
};

/**
 * @brief Concept to check if a type has a method to get the inertial position.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept HasGetControlAuthority = requires(const T& vehicle, const State& state) {
    { vehicle.get_control_authority(state) } -> std::same_as<Perturbation>;
};

/**
 * @brief Concept to check if a type is a user-defined vehicle.
 *
 * @tparam T The type to check.
 */
template <typename T>
concept IsUserDefinedVehicle = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
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
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    virtual Mass get_mass() const = 0;

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @return InertiaTensor<> The inertia tensor of the vehicle.
     */
    virtual InertiaTensor<> get_inertia_tensor() const { return InertiaTensor<>(); }

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
     * @brief Gets the control authority of the vehicle.
     *
     * @param state The state of the vehicle for which to get the control authority.
     * @return Perturbation The control force and torque of the vehicle.
     */
    virtual Perturbation get_control_authority(const State& state) const = 0;

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

    /**
     * @brief Gets the type information of the internal vehicle instance.
     *
     * @return const std::type_info& The type information of the internal vehicle instance.
     */
    virtual const std::type_info& type() const = 0;
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
     * @brief Gets the mass of the vehicle.
     *
     * @return Mass The mass of the vehicle.
     */
    Mass get_mass() const final { return _value.get_mass(); }

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @return InertiaTensor<> The inertia tensor of the vehicle.
     */
    InertiaTensor<> get_inertia_tensor() const final { return get_inertia_tensor_impl(_value); }

    /**
     * @brief Gets the default inertia tensor of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the inertia tensor from.
     * @return InertiaTensor<> The inertia tensor of the vehicle.
     */
    template <typename U>
        requires(!HasGetInertiaTensor<U>)
    static InertiaTensor<> get_inertia_tensor_impl(const U&)
    {
        return InertiaTensor<>();
    }

    /**
     * @brief Gets the inertia tensor of the vehicle.
     *
     * @tparam U The type of the vehicle implementation.
     * @param value The vehicle instance to get the inertia tensor from.
     * @return InertiaTensor<> The inertia tensor of the vehicle.
     */
    template <typename U>
        requires(HasGetInertiaTensor<U>)
    static InertiaTensor<> get_inertia_tensor_impl(const U& value)
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
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
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
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
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
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
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
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return RadiusVector<frames::earth::icrf>
     */
    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const override final
    {
        return _value.get_inertial_position(date);
    }

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return VelocityVector<frames::earth::icrf>
     */
    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const override final
    {
        return _value.get_inertial_velocity(date);
    }

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return AccelerationVector<frames::earth::icrf>
     */
    AccelerationVector<frames::earth::icrf> get_inertial_acceleration(const Date& date) const override final
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

    /**
     * @brief Gets the type information of the internal vehicle instance.
     *
     * @return const std::type_info& The type information of the internal vehicle instance.
     */
    const std::type_info& type() const final { return typeid(T); }

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
concept IsGenericallyConstructableVehicle = requires(T) {
    requires IsUserDefinedVehicle<T>;
    std::negation<std::is_same<Vehicle, remove_cv_ref<T>>>::value;
};


/**
 * @brief A class representing a vehicle in the astrea astro platform.
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
    template <IsGenericallyConstructableVehicle T>
    explicit Vehicle(T&& x) :
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
    template <IsGenericallyConstructableVehicle T>
    Vehicle& operator=(T&& x)
    {
        return (*this) = Vehicle(std::forward<T>(x));
    }

    /**
     * @brief Extracts the user-defined vehicle from the Vehicle instance.
     *
     * @tparam T The type of the user-defined vehicle to extract.
     * @return const T* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr.
     */
    template <IsGenericallyConstructableVehicle T>
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::VehicleInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    /**
     * @brief Extracts the user-defined vehicle from the Vehicle instance.
     *
     * @tparam T The type of the user-defined vehicle to extract.
     * @return T* A pointer to the user-defined vehicle if it matches the type, otherwise nullptr.
     */
    template <IsGenericallyConstructableVehicle T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::VehicleInner<T>*>(ptr());
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
     * @return InertiaTensor<> The inertia tensor of the vehicle.
     */
    InertiaTensor<> get_inertia_tensor() const { return ptr()->get_inertia_tensor(); }

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
     * @brief Get the position of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the position.
     * @return RadiusVector<frames::earth::icrf>
     */
    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const override
    {
        return ptr()->get_inertial_position(date);
    }

    /**
     * @brief Get the velocity of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the velocity.
     * @return VelocityVector<frames::earth::icrf>
     */
    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const override
    {
        return ptr()->get_inertial_velocity(date);
    }

    /**
     * @brief Get the acceleration of the frame in Earth-Centered Inertial coordinates.
     *
     * @param date The date for which to get the acceleration.
     * @return AccelerationVector<frames::earth::icrf>
     */
    AccelerationVector<frames::earth::icrf> get_inertial_acceleration(const Date& date) const override
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

    Mass _mass;                          //!< Mass of the vehicle
    InertiaTensor<> _inertiaTensor;      //!< Inertia tensor of the vehicle
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
} // namespace astrea