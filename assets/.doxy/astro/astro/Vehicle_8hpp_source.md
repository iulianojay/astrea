

# File Vehicle.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**platforms**](dir_2552b27872b33d254ad75ac21654b66a.md) **>** [**Vehicle.hpp**](Vehicle_8hpp.md)

[Go to the documentation of this file](Vehicle_8hpp.md)


```C++

#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include <units/units.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/platforms/InertiaTensor.hpp>
#include <astro/propagation/force_models/Perturbation.hpp>
#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/concepts.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <typename T>
concept HasGetMass = requires(const T vehicle, const State& state) {
    { vehicle.get_mass(state) } -> std::same_as<Mass>;
};

template <typename T>
concept HasGetInertiaTensor = requires(const T vehicle, const State& state) {
    { vehicle.get_inertia_tensor(state) } -> std::same_as<InertiaTensor<frames::dynamic::body>>;
};

template <typename T>
concept HasGetRamArea = requires(const T vehicle, const State& state) {
    { vehicle.get_ram_area(state) } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfDrag = requires(const T vehicle, const State& state) {
    { vehicle.get_coefficient_of_drag(state) } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetLiftArea = requires(const T vehicle, const State& state) {
    { vehicle.get_lift_area(state) } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfLift = requires(const T vehicle, const State& state) {
    { vehicle.get_coefficient_of_lift(state) } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetSolarArea = requires(const T vehicle, const State& state) {
    { vehicle.get_solar_area(state) } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfReflectivity = requires(const T vehicle, const State& state) {
    { vehicle.get_coefficient_of_reflectivity(state) } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetControlAuthority = requires(const T& vehicle, const State& state) {
    { vehicle.get_control_authority(state) } -> std::same_as<Perturbation>;
};

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

struct VehicleInnerBase {

    virtual ~VehicleInnerBase() {}

    virtual Mass get_mass(const State& state) const = 0;

    virtual InertiaTensor<frames::dynamic::body> get_inertia_tensor(const State& state) const
    {
        return InertiaTensor<frames::dynamic::body>();
    }

    virtual SurfaceArea get_ram_area(const State& state) const = 0;

    virtual SurfaceArea get_lift_area(const State& state) const = 0;

    virtual SurfaceArea get_solar_area(const State& state) const = 0;

    virtual Unitless get_coefficient_of_drag(const State& state) const = 0;

    virtual Unitless get_coefficient_of_lift(const State& state) const = 0;

    virtual Unitless get_coefficient_of_reflectivity(const State& state) const = 0;

    virtual Perturbation get_control_authority(const State& state) const = 0;

    virtual std::unique_ptr<VehicleInnerBase> clone() const = 0;

    virtual const void* get_ptr() const = 0;

    virtual void* get_ptr() = 0;

    virtual const std::type_info& type() const = 0;

    virtual std::string get_name() const = 0;
};

template <typename T>
struct VehicleInner final : public VehicleInnerBase {

    VehicleInner() = default;

    VehicleInner(const VehicleInner&) = delete;

    VehicleInner(VehicleInner&&) = delete;

    VehicleInner& operator=(const VehicleInner&) = delete;

    VehicleInner& operator=(VehicleInner&&) = delete;

    explicit VehicleInner(const T& x) :
        _value(x)
    {
    }

    explicit VehicleInner(T&& x) :
        _value(std::move(x))
    {
    }

    Mass get_mass(const State& state) const final { return _value.get_mass(state); }

    InertiaTensor<frames::dynamic::body> get_inertia_tensor(const State& state) const final
    {
        return get_inertia_tensor_impl(_value, state);
    }

    template <typename U>
        requires(!HasGetInertiaTensor<U>)
    static InertiaTensor<frames::dynamic::body> get_inertia_tensor_impl(const U&, const State&)
    {
        return InertiaTensor<frames::dynamic::body>();
    }

    template <typename U>
        requires(HasGetInertiaTensor<U>)
    static InertiaTensor<frames::dynamic::body> get_inertia_tensor_impl(const U& value, const State& state)
    {
        return value.get_inertia_tensor(state);
    }

    SurfaceArea get_ram_area(const State& state) const final { return get_ram_area_impl(_value, state); }

    template <typename U>
        requires(!HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U&, const State&)
    {
        return SurfaceArea::zero();
    }

    template <typename U>
        requires(HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U& value, const State& state)
    {
        return value.get_ram_area(state);
    }

    SurfaceArea get_lift_area(const State& state) const final { return get_lift_area_impl(_value, state); }

    template <typename U>
        requires(!HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U&, const State&)
    {
        return SurfaceArea::zero();
    }

    template <typename U>
        requires(HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U& value, const State& state)
    {
        return value.get_lift_area(state);
    }

    SurfaceArea get_solar_area(const State& state) const final { return get_solar_area_impl(_value, state); }

    template <typename U>
        requires(!HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U&, const State&)
    {
        return SurfaceArea::zero();
    }

    template <typename U>
        requires(HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U& value, const State& state)
    {
        return value.get_solar_area(state);
    }

    Unitless get_coefficient_of_drag(const State& state) const final
    {
        return get_coefficient_of_drag_impl(_value, state);
    }

    template <typename U>
        requires(!HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U&, const State&)
    {
        return Unitless::zero();
    }

    template <typename U>
        requires(HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U& value, const State& state)
    {
        return value.get_coefficient_of_drag(state);
    }

    Unitless get_coefficient_of_lift(const State& state) const final
    {
        return get_coefficient_of_lift_impl(_value, state);
    }

    template <typename U>
        requires(!HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U&, const State&)
    {
        return Unitless::zero();
    }

    template <typename U>
        requires(HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U& value, const State& state)
    {
        return value.get_coefficient_of_lift(state);
    }

    Unitless get_coefficient_of_reflectivity(const State& state) const final
    {
        return get_coefficient_of_reflectivity_impl(_value, state);
    }

    template <typename U>
        requires(!HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U&, const State&)
    {
        return Unitless::zero();
    }

    template <typename U>
        requires(HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U& value, const State& state)
    {
        return value.get_coefficient_of_reflectivity(state);
    }

    std::string get_name() const override final { return get_name_impl(_value); }

    template <typename U>
        requires(!HasGetName<U>)
    std::string get_name_impl(const U&) const
    {
        return "Vehicle";
    }

    template <typename U>
        requires(HasGetName<U>)
    std::string get_name_impl(const U& value) const
    {
        return value.get_name();
    }

    Perturbation get_control_authority(const State& state) const final
    {
        return get_control_authority_impl(_value, state);
    }

    template <typename U>
        requires(!HasGetControlAuthority<U>)
    Perturbation get_control_authority_impl(const U&, const State&) const
    {
        using mp_units::si::unit_symbols::m;
        using mp_units::si::unit_symbols::N;
        return { .force = { 0.0 * N, 0.0 * N, 0.0 * N }, .torque = { 0.0 * N * m, 0.0 * N * m, 0.0 * N * m } };
    }

    template <typename U>
        requires(HasGetControlAuthority<U>)
    Perturbation get_control_authority_impl(const U& value, const State& state) const
    {
        return value.get_control_authority(state);
    }

    std::unique_ptr<VehicleInnerBase> clone() const final { return std::make_unique<VehicleInner>(_value); }

    const void* get_ptr() const final { return &_value; }

    void* get_ptr() final { return &_value; }

    const std::type_info& type() const final { return typeid(T); }

    T _value; 
};

} // namespace detail

class Vehicle; // Forward declaration of the Vehicle class

template <typename T>
concept IsGenericallyConstructableVehicle = requires(T) {
    requires !std::is_same<Vehicle, remove_cv_ref<T>>::value;
    requires IsUserDefinedVehicle<T>;
};


class Vehicle {

  public:
    Vehicle();

  private:
    void generic_ctor_impl();

  public:
    template <IsGenericallyConstructableVehicle T>
    explicit Vehicle(T&& x) :
        _ptr(std::make_unique<detail::VehicleInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    Vehicle(const Vehicle&);

    Vehicle(Vehicle&&) noexcept;

    Vehicle& operator=(Vehicle&&) noexcept;

    Vehicle& operator=(const Vehicle&);

    template <IsGenericallyConstructableVehicle T>
    Vehicle& operator=(T&& x)
    {
        return (*this) = Vehicle(std::forward<T>(x));
    }

    template <IsGenericallyConstructableVehicle T>
    const T* extract() const noexcept
    {
        auto p = static_cast<const detail::VehicleInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    template <IsGenericallyConstructableVehicle T>
    T* extract_mutable_reference() noexcept
    {
        auto p = static_cast<detail::VehicleInner<T>*>(ptr());
        return ptr()->type() == typeid(T) ? &(p->_value) : nullptr;
    }

    Mass get_mass(const State& state) const { return ptr()->get_mass(state); }

    InertiaTensor<frames::dynamic::body> get_inertia_tensor(const State& state) const
    {
        return ptr()->get_inertia_tensor(state);
    }

    SurfaceArea get_ram_area(const State& state) const { return ptr()->get_ram_area(state); }

    SurfaceArea get_lift_area(const State& state) const { return ptr()->get_lift_area(state); }

    SurfaceArea get_solar_area(const State& state) const { return ptr()->get_solar_area(state); }

    Unitless get_coefficient_of_drag(const State& state) const { return ptr()->get_coefficient_of_drag(state); }

    Unitless get_coefficient_of_lift(const State& state) const { return ptr()->get_coefficient_of_lift(state); }

    Unitless get_coefficient_of_reflectivity(const State& state) const
    {
        return ptr()->get_coefficient_of_reflectivity(state);
    }

    Perturbation get_control_authority(const State& state) const { return ptr()->get_control_authority(state); }


    std::string get_name() const { return ptr()->get_name(); }

    const void* get_ptr() const;

    void* get_ptr();

  private:
    std::unique_ptr<detail::VehicleInnerBase> _ptr; 

    detail::VehicleInnerBase const* ptr() const
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }

    detail::VehicleInnerBase* ptr()
    {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};

} // namespace astro
} // namespace astrea
```


