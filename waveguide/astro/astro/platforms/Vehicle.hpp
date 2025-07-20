#pragma once

#include <cassert>
#include <concepts>
#include <memory>
#include <type_traits>

#include <units/units.hpp>

#include <astro/state/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typeid_name_extract.hpp>

namespace waveguide {
namespace astro {

template <typename T>
concept HasUpdateState = requires(T vehicle, const State& state)
{
    { vehicle.update_state(state) };
};

template <typename T>
concept HasGetState = requires(T vehicle)
{
    {
        vehicle.get_state()
        } -> std::same_as<State&>;
};

template <typename T>
concept HasGetInitialState = requires(const T vehicle)
{
    {
        vehicle.get_initial_state()
        } -> std::same_as<const State&>;
};

template <typename T>
concept HasGetMass = requires(T vehicle)
{
    {
        vehicle.get_mass()
        } -> std::same_as<Mass>;
};

template <typename T>
concept HasGetRamArea = requires(T vehicle)
{
    {
        vehicle.get_ram_area()
        } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfDrag = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_drag()
        } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetLiftArea = requires(T vehicle)
{
    {
        vehicle.get_lift_area()
        } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfLift = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_lift()
        } -> std::same_as<Unitless>;
};

template <typename T>
concept HasGetSolarArea = requires(T vehicle)
{
    {
        vehicle.get_solar_area()
        } -> std::same_as<SurfaceArea>;
};

template <typename T>
concept HasGetCoefficientOfReflectivity = requires(T vehicle)
{
    {
        vehicle.get_coefficient_of_reflectivity()
        } -> std::same_as<Unitless>;
};

template <typename T>
concept HasClear = requires(T vehicle)
{
    { vehicle.clear() };
};

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

struct VehicleInnerBase {

    // Virtual destructor
    virtual ~VehicleInnerBase() {}

    // Required methods
    virtual void update_state(const State& state)  = 0;
    virtual State& get_state()                     = 0;
    virtual const State& get_initial_state() const = 0;
    virtual Mass get_mass() const                  = 0;

    // Optional methods
    virtual SurfaceArea get_ram_area() const   = 0;
    virtual SurfaceArea get_lift_area() const  = 0;
    virtual SurfaceArea get_solar_area() const = 0;

    virtual Unitless get_coefficient_of_drag() const         = 0;
    virtual Unitless get_coefficient_of_lift() const         = 0;
    virtual Unitless get_coefficient_of_reflectivity() const = 0;

    virtual void clear() = 0;

    // Implementation utilities
    virtual std::unique_ptr<VehicleInnerBase> clone() const = 0;
    virtual const void* get_ptr() const                     = 0;
    virtual void* get_ptr()                                 = 0;
};

template <typename T>
struct VehicleInner final : public VehicleInnerBase {

    // Default constructor
    VehicleInner() = default;

    // Delete other constructors
    VehicleInner(const VehicleInner&)            = delete;
    VehicleInner(VehicleInner&&)                 = delete;
    VehicleInner& operator=(const VehicleInner&) = delete;
    VehicleInner& operator=(VehicleInner&&)      = delete;

    // Constructors from T (copy and move variants).
    explicit VehicleInner(const T& x) :
        _value(x)
    {
    }
    explicit VehicleInner(T&& x) :
        _value(std::move(x))
    {
    }

    // Invoke required methods directly
    void update_state(const State& state) final { _value.update_state(state); }
    State& get_state() final { return _value.get_state(); }
    const State& get_initial_state() const final { return _value.get_initial_state(); }
    Mass get_mass() const final { return _value.get_mass(); }

    // Invoke implicit implementations for optional methods
    SurfaceArea get_ram_area() const final { return get_ram_area_impl(_value); }
    SurfaceArea get_lift_area() const final { return get_lift_area_impl(_value); }
    SurfaceArea get_solar_area() const final { return get_solar_area_impl(_value); }
    Unitless get_coefficient_of_drag() const final { return get_coefficient_of_drag_impl(_value); }
    Unitless get_coefficient_of_lift() const final { return get_coefficient_of_lift_impl(_value); }
    Unitless get_coefficient_of_reflectivity() const final { return get_coefficient_of_reflectivity_impl(_value); }
    void clear() final { clear_impl(_value); };

    // Use templates to switch between defined or default implementations
    template <typename U>
    requires(!HasGetRamArea<U>) static SurfaceArea get_ram_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }
    template <typename U>
    requires(HasGetRamArea<U>) static SurfaceArea get_ram_area_impl(const U& value) { return value.get_ram_area(); }

    template <typename U>
    requires(!HasGetLiftArea<U>) static SurfaceArea get_lift_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }
    template <typename U>
    requires(HasGetLiftArea<U>) static SurfaceArea get_lift_area_impl(const U& value) { return value.get_lift_area(); }

    template <typename U>
    requires(!HasGetSolarArea<U>) static SurfaceArea get_solar_area_impl(const U&)
    {
        return 0.0 * mp_units::pow<2>(waveguide::detail::minor_distance_unit);
    }
    template <typename U>
    requires(HasGetSolarArea<U>) static SurfaceArea get_solar_area_impl(const U& value)
    {
        return value.get_solar_area();
    }

    template <typename U>
    requires(!HasGetCoefficientOfDrag<U>) static Unitless get_coefficient_of_drag_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }
    template <typename U>
    requires(HasGetCoefficientOfDrag<U>) static Unitless get_coefficient_of_drag_impl(const U& value)
    {
        return value.get_coefficient_of_drag();
    }

    template <typename U>
    requires(!HasGetCoefficientOfLift<U>) static Unitless get_coefficient_of_lift_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }
    template <typename U>
    requires(HasGetCoefficientOfLift<U>) static Unitless get_coefficient_of_lift_impl(const U& value)
    {
        return value.get_coefficient_of_lift();
    }

    template <typename U>
    requires(!HasGetCoefficientOfReflectivity<U>) static Unitless get_coefficient_of_reflectivity_impl(const U&)
    {
        return 0.0 * mp_units::one;
    }
    template <typename U>
    requires(HasGetCoefficientOfReflectivity<U>) static Unitless get_coefficient_of_reflectivity_impl(const U& value)
    {
        return value.get_coefficient_of_reflectivity();
    }

    template <typename U>
    requires(!HasClear<U>) void clear_impl(U&) {}
    template <typename U>
    requires(HasClear<U>) void clear_impl(U& value) { value.clear(); }

    // The clone method, used in the copy constructor of Vehicle.
    std::unique_ptr<VehicleInnerBase> clone() const final { return std::make_unique<VehicleInner>(_value); }

    // Raw getters for the internal instance.
    const void* get_ptr() const final { return &_value; }
    void* get_ptr() final { return &_value; }

    // Vehicle object
    T _value;
};

} // namespace detail

class Vehicle;

template <typename T>
concept IsGenericallyConstructableVehicle = requires(T)
{
    requires IsUserDefinedVehicle<T>;
    std::negation<std::is_same<Vehicle, remove_cv_ref<T>>>::value;
};


class Vehicle {

  public:
    // Default constructor
    Vehicle();

  private:
    void generic_ctor_impl();

  public:
    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) explicit Vehicle(T&& x) :
        _ptr(std::make_unique<detail::VehicleInner<remove_cv_ref<T>>>(std::forward<T>(x)))
    {
        generic_ctor_impl();
    }

    // Copy constructor
    Vehicle(const Vehicle&);

    // Move constructor
    Vehicle(Vehicle&&) noexcept;

    // Move assignment operator
    Vehicle& operator=(Vehicle&&) noexcept;

    // Copy assignment operator
    Vehicle& operator=(const Vehicle&);

    /// Assignment from a user-defined Vehicle
    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) Vehicle& operator=(T&& x)
    {
        return (*this) = Vehicle(std::forward<T>(x));
    }

    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>) const T* extract() const noexcept
    {
        auto p = static_cast<const detail::VehicleInner<T>*>(ptr());
        return p == nullptr ? nullptr : &(p->_value);
    }

    // Update state
    void update_state(const State& state) { return _ptr->update_state(state); }

    // Get state
    State& get_state() { return _ptr->get_state(); }
    State get_state() const { return _ptr->get_state(); } // TODO: Extend to const context instead of copying

    // Get initial state
    const State& get_initial_state() const { return _ptr->get_state(); }

    // Get mass
    Mass get_mass() const { return _ptr->get_mass(); }

    // Ram area
    SurfaceArea get_ram_area() const { return _ptr->get_ram_area(); }

    // Lift area
    SurfaceArea get_lift_area() const { return _ptr->get_lift_area(); }

    // Solar area
    SurfaceArea get_solar_area() const { return _ptr->get_solar_area(); }

    // Coefficient of drag
    Unitless get_coefficient_of_drag() const { return _ptr->get_coefficient_of_drag(); }

    // Coefficient of lift
    Unitless get_coefficient_of_lift() const { return _ptr->get_coefficient_of_lift(); }

    // Coefficient of reflectivity
    Unitless get_coefficient_of_reflectivity() const { return _ptr->get_coefficient_of_reflectivity(); }

    void clear() { _ptr->clear(); }

    // Pointer to user-defined vehicle
    const void* get_ptr() const;
    void* get_ptr();

  private:
    // Pointer to the inner base vehicle
    std::unique_ptr<detail::VehicleInnerBase> _ptr;

    // Members
    State _state;
    Mass _mass;
    SurfaceArea _ramArea;
    SurfaceArea _liftArea;
    SurfaceArea _solarArea;
    Unitless _coefficientOfDrag;
    Unitless _coefficientOfLift;
    Unitless _coefficientOfReflectivity;

    // Ensure the pointer actually points to something
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
} // namespace waveguide