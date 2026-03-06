

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

#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/FrameReference.hpp>
#include <astro/frames/frames.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/type_traits.hpp>

namespace astrea {
namespace astro {

template <typename T>
concept HasGetMass = requires(T vehicle) {
    { vehicle.get_mass() } -> std::same_as<Mass>;
};

template <typename T>
concept HasGetRamArea = requires(T vehicle) {
    { vehicle.get_ram_area() } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfDrag = requires(T vehicle) {
    { vehicle.get_coefficient_of_drag() } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetLiftArea = requires(T vehicle) {
    { vehicle.get_lift_area() } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfLift = requires(T vehicle) {
    { vehicle.get_coefficient_of_lift() } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetSolarArea = requires(T vehicle) {
    { vehicle.get_solar_area() } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfReflectivity = requires(T vehicle) {
    { vehicle.get_coefficient_of_reflectivity() } -> std::same_as<Unitless>;
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

struct VehicleInnerBase : public virtual FrameReference {

    virtual ~VehicleInnerBase() {}

    virtual Mass get_mass() const = 0;

    virtual SurfaceArea get_ram_area() const = 0;

    virtual SurfaceArea get_lift_area() const = 0;

    virtual SurfaceArea get_solar_area() const = 0;

    virtual Unitless get_coefficient_of_drag() const = 0;

    virtual Unitless get_coefficient_of_lift() const = 0;

    virtual Unitless get_coefficient_of_reflectivity() const = 0;

    virtual std::unique_ptr<VehicleInnerBase> clone() const = 0;

    virtual const void* get_ptr() const = 0;

    virtual void* get_ptr() = 0;
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

    Mass get_mass() const final { return _value.get_mass(); }

    SurfaceArea get_ram_area() const final { return get_ram_area_impl(_value); }

    SurfaceArea get_lift_area() const final { return get_lift_area_impl(_value); }

    SurfaceArea get_solar_area() const final { return get_solar_area_impl(_value); }

    Unitless get_coefficient_of_drag() const final { return get_coefficient_of_drag_impl(_value); }

    Unitless get_coefficient_of_lift() const final { return get_coefficient_of_lift_impl(_value); }

    Unitless get_coefficient_of_reflectivity() const final { return get_coefficient_of_reflectivity_impl(_value); }

    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const override final
    {
        return _value.get_inertial_position(date);
    }

    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const override final
    {
        return _value.get_inertial_velocity(date);
    }

    AccelerationVector<frames::earth::icrf> get_inertial_acceleration(const Date& date) const override final
    {
        return _value.get_inertial_acceleration(date);
    }

    std::string get_name() const override final { return _value.get_name(); }

    template <typename U>
        requires(!HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
    }

    template <typename U>
        requires(HasGetRamArea<U>)
    static SurfaceArea get_ram_area_impl(const U& value)
    {
        return value.get_ram_area();
    }


    template <typename U>
        requires(!HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
    }

    template <typename U>
        requires(HasGetLiftArea<U>)
    static SurfaceArea get_lift_area_impl(const U& value)
    {
        return value.get_lift_area();
    }

    template <typename U>
        requires(!HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(astrea::detail::minor_distance_unit);
    }

    template <typename U>
        requires(HasGetSolarArea<U>)
    static SurfaceArea get_solar_area_impl(const U& value)
    {
        return value.get_solar_area();
    }

    template <typename U>
        requires(!HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    template <typename U>
        requires(HasGetCoefficientOfDrag<U>)
    static Unitless get_coefficient_of_drag_impl(const U& value)
    {
        return value.get_coefficient_of_drag();
    }

    template <typename U>
        requires(!HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    template <typename U>
        requires(HasGetCoefficientOfLift<U>)
    static Unitless get_coefficient_of_lift_impl(const U& value)
    {
        return value.get_coefficient_of_lift();
    }

    template <typename U>
        requires(!HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }

    template <typename U>
        requires(HasGetCoefficientOfReflectivity<U>)
    static Unitless get_coefficient_of_reflectivity_impl(const U& value)
    {
        return value.get_coefficient_of_reflectivity();
    }

    std::unique_ptr<VehicleInnerBase> clone() const final { return std::make_unique<VehicleInner>(_value); }

    const void* get_ptr() const final { return &_value; }

    void* get_ptr() final { return &_value; }

    T _value; 
};

} // namespace detail

class Vehicle; // Forward declaration of the Vehicle class

template <typename T>
concept IsGenericallyConstructableVehicle = requires(T) {
    requires IsUserDefinedVehicle<T>;
    std::negation<std::is_same<Vehicle, remove_cv_ref<T>>>::value;
};


class Vehicle : public FrameReference {

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
        return p == nullptr ? nullptr : &(p->_value);
    }

    Mass get_mass() const { return _ptr->get_mass(); }

    SurfaceArea get_ram_area() const { return _ptr->get_ram_area(); }

    SurfaceArea get_lift_area() const { return _ptr->get_lift_area(); }

    SurfaceArea get_solar_area() const { return _ptr->get_solar_area(); }

    Unitless get_coefficient_of_drag() const { return _ptr->get_coefficient_of_drag(); }

    Unitless get_coefficient_of_lift() const { return _ptr->get_coefficient_of_lift(); }

    Unitless get_coefficient_of_reflectivity() const { return _ptr->get_coefficient_of_reflectivity(); }

    RadiusVector<frames::earth::icrf> get_inertial_position(const Date& date) const override
    {
        return ptr()->get_inertial_position(date);
    }

    VelocityVector<frames::earth::icrf> get_inertial_velocity(const Date& date) const override
    {
        return ptr()->get_inertial_velocity(date);
    }

    AccelerationVector<frames::earth::icrf> get_inertial_acceleration(const Date& date) const override
    {
        return ptr()->get_inertial_acceleration(date);
    }

    std::string get_name() const override { return ptr()->get_name(); }

    const void* get_ptr() const;

    void* get_ptr();

  private:
    std::unique_ptr<detail::VehicleInnerBase> _ptr; 

    Mass _mass;                          
    SurfaceArea _ramArea;                
    SurfaceArea _liftArea;               
    SurfaceArea _solarArea;              
    Unitless _coefficientOfDrag;         
    Unitless _coefficientOfLift;         
    Unitless _coefficientOfReflectivity; 

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


