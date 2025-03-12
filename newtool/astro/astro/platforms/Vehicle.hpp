#pragma once

#include <cassert>
#include <memory>
#include <type_traits>
#include <concepts>

#include <astro/State.hpp>
#include <astro/time/Date.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typeid_name_extract.hpp>


template <typename T>
concept has_update_state = requires(T vehicle, const State& state) {
    { vehicle.update_state(state) };
};

template <typename T>
concept has_get_state = requires(T vehicle) {
    { vehicle.get_state() } -> std::same_as<State&>;
};

template <typename T>
concept has_get_epoch = requires(T vehicle) {
    { vehicle.get_epoch() } -> std::same_as<Date>;
};

template <typename T>
concept has_get_mass = requires(T vehicle) {
    { vehicle.get_mass() } -> std::same_as<double>;
};

template <typename T>
concept has_get_ram_area = requires(T vehicle) {
    { vehicle.get_ram_area() } -> std::same_as<double>;
};

template <typename T>
concept has_get_coefficient_of_drag = requires(T vehicle) {
    { vehicle.get_coefficient_of_drag() } -> std::same_as<double>;
};

template <typename T>
concept has_get_lift_area = requires(T vehicle) {
    { vehicle.get_lift_area() } -> std::same_as<double>;
};

template <typename T>
concept has_get_coefficient_of_lift = requires(T vehicle) {
    { vehicle.get_coefficient_of_lift() } -> std::same_as<double>;
};

template <typename T>
concept has_get_solar_area = requires(T vehicle) {
    { vehicle.get_solar_area() } -> std::same_as<double>;
};

template <typename T>
concept has_get_coefficient_of_reflectivity = requires(T vehicle) {
    { vehicle.get_coefficient_of_reflectivity() } -> std::same_as<double>;
};

template <typename T>
concept IsUserDefinedVehicle = requires(T) {
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires has_update_state<T>;
    requires has_get_state<T>;
    requires has_get_epoch<T>;
    requires has_get_mass<T>;
};

namespace detail {

struct VehicleInnerBase {
    // Virtual destructor
    virtual ~VehicleInnerBase() {}

    // Required methods
    virtual void update_state(const State& state) = 0;
    virtual State& get_state() = 0;
    virtual Date get_epoch() const = 0;
    virtual double get_mass() const = 0;

    // Optional methods
    virtual double get_ram_area() const = 0;
    virtual double get_lift_area() const = 0;
    virtual double get_solar_area() const = 0;

    virtual double get_coefficient_of_drag() const = 0;
    virtual double get_coefficient_of_lift() const = 0;
    virtual double get_coefficient_of_reflectivity() const = 0;

    // Implementation utilities
    virtual std::unique_ptr<VehicleInnerBase> clone() const = 0;
    virtual const void *get_ptr() const = 0;
    virtual void *get_ptr() = 0;
};

template <typename T>
struct VehicleInner final : public VehicleInnerBase {

    // Default constructor
    VehicleInner() = default;

    // Delete other constructors
    VehicleInner(const VehicleInner&) = delete;
    VehicleInner(VehicleInner&&) = delete;
    VehicleInner& operator=(const VehicleInner&) = delete;
    VehicleInner& operator=(VehicleInner&&) = delete;

    // Constructors from T (copy and move variants).
    explicit VehicleInner(const T &x) : _value(x) {}
    explicit VehicleInner(T &&x) : _value(std::move(x)) {}

    // Invoke required methods directly
    void update_state(const State& state) final {
        _value.update_state(state);
    }
    State& get_state() final {
        return _value.get_state();
    }
    Date get_epoch() const final {
        return _value.get_epoch();
    }
    double get_mass() const final {
        return _value.get_mass();
    }

    // Invoke implicit implementations for optional methods
    double get_ram_area() const final {
        return get_ram_area_impl(_value);
    }
    double get_lift_area() const final {
        return get_lift_area_impl(_value);
    }
    double get_solar_area() const final {
        return get_solar_area_impl(_value);
    }
    double get_coefficient_of_drag() const final {
        return get_coefficient_of_drag_impl(_value);
    }
    double get_coefficient_of_lift() const final {
        return get_coefficient_of_lift_impl(_value);
    }
    double get_coefficient_of_reflectivity() const final {
        return get_coefficient_of_reflectivity_impl(_value);
    }

    // Use templates to switch between defined or default implementations
    template <typename U>
    requires(!has_get_ram_area<U>)
    static double get_ram_area_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_ram_area<U>)
    static double get_ram_area_impl(const U& value) {
        return value.get_ram_area();
    }

    template <typename U>
    requires(!has_get_lift_area<U>)
    static double get_lift_area_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_lift_area<U>)
    static double get_lift_area_impl(const U& value) {
        return value.get_lift_area();
    }

    template <typename U>
    requires(!has_get_solar_area<U>)
    static double get_solar_area_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_solar_area<U>)
    static double get_solar_area_impl(const U& value) {
        return value.get_solar_area();
    }

    template <typename U>
    requires(!has_get_coefficient_of_drag<U>)
    static double get_coefficient_of_drag_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_coefficient_of_drag<U>)
    static double get_coefficient_of_drag_impl(const U& value) {
        return value.get_coefficient_of_drag();
    }

    template <typename U>
    requires(!has_get_coefficient_of_lift<U>)
    static double get_coefficient_of_lift_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_coefficient_of_lift<U>)
    static double get_coefficient_of_lift_impl(const U& value) {
        return value.get_coefficient_of_lift();
    }

    template <typename U>
    requires(!has_get_coefficient_of_reflectivity<U>)
    static double get_coefficient_of_reflectivity_impl(const U&) {
        return 0.0;
    }
    template <typename U>
    requires(has_get_coefficient_of_reflectivity<U>)
    static double get_coefficient_of_reflectivity_impl(const U& value) {
        return value.get_coefficient_of_reflectivity();
    }

    // The clone method, used in the copy constructor of Vehicle.
    std::unique_ptr<VehicleInnerBase> clone() const final {
        return std::make_unique<VehicleInner>(_value);
    }

    // Raw getters for the internal instance.
    const void* get_ptr() const final {
        return &_value;
    }
    void* get_ptr() final {
        return &_value;
    }

    // Vehicle object
    T _value;
};

} // namespace detail

class Vehicle;

template <typename T>
concept IsGenericallyConstructableVehicle = requires(T) {
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
    requires(IsGenericallyConstructableVehicle<T>)
    explicit Vehicle(T &&x)
        : _ptr( std::make_unique< detail::VehicleInner<remove_cv_ref<T>> >(std::forward<T>(x)) )
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
    requires(IsGenericallyConstructableVehicle<T>)
    Vehicle& operator=(T&& x) {
        return (*this) = Vehicle(std::forward<T>(x));
    }

    template <typename T>
    requires(IsGenericallyConstructableVehicle<T>)
    const T *extract() const noexcept {
        auto p = static_cast<const detail::VehicleInner<T> *>(ptr());
        return p == nullptr ? nullptr : &(p->_value);
    }

    // Update state
    void update_state(const State& state) {
        return _ptr->update_state(state);
    }

    // Get state
    State& get_state() {
        return _ptr->get_state();
    }

    // Get state
    Date get_epoch() const {
        return _ptr->get_epoch();
    }

    // Get mass
    double get_mass() const {
        return _ptr->get_mass();
    }

    // Ram area
    double get_ram_area() const {
        return _ptr->get_ram_area();
    }

    // Lift area
    double get_lift_area() const {
        return _ptr->get_lift_area();
    }

    // Solar area
    double get_solar_area() const {
        return _ptr->get_solar_area();
    }

    // Coefficient of drag
    double get_coefficient_of_drag() const {
        return _ptr->get_coefficient_of_drag();
    }

    // Coefficient of lift
    double get_coefficient_of_lift() const {
        return _ptr->get_coefficient_of_lift();
    }

    // Coefficient of reflectivity
    double get_coefficient_of_reflectivity() const {
        return _ptr->get_coefficient_of_reflectivity();
    }

    // Pointer to user-defined vehicle
    const void* get_ptr() const;
    void* get_ptr();

private:

    // Pointer to the inner base vehicle
    std::unique_ptr<detail::VehicleInnerBase> _ptr;

    // Members
    State _state;
    Date _epoch;
    double _mass;
    double _ramArea;
    double _liftArea;
    double _solarArea;
    double _coefficientOfDrag;
    double _coefficientOfLift;
    double _coefficientOfReflectivity;

    // Ensure the pointer actually points to something
    detail::VehicleInnerBase const *ptr() const {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
    detail::VehicleInnerBase *ptr() {
        assert(_ptr.get() != nullptr);
        return _ptr.get();
    }
};