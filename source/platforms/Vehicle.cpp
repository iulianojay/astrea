#include "Vehicle.hpp"

#include "NullVehicle.hpp"

// Default constructor
Vehicle::Vehicle() : Vehicle(NullVehicle{}) {}

// Copy constructor
Vehicle::Vehicle(const Vehicle& other) :
    _ptr(other._ptr->clone()),
    _state(other._state),
    _mass(other._mass),
    _ramArea(other._ramArea),
    _liftArea(other._liftArea),
    _solarArea(other._solarArea),
    _coefficientOfDrag(other._coefficientOfDrag),
    _coefficientOfLift(other._coefficientOfLift),
    _coefficientOfReflectivity(other._coefficientOfReflectivity)
{}

// Move constructor
Vehicle::Vehicle(Vehicle&& other) noexcept :
    _ptr(std::move(other._ptr)),
    _state(std::move(other._state)),
    _mass(std::move(other._mass)),
    _ramArea(std::move(other._ramArea)),
    _liftArea(std::move(other._liftArea)),
    _solarArea(std::move(other._solarArea)),
    _coefficientOfDrag(std::move(other._coefficientOfDrag)),
    _coefficientOfLift(std::move(other._coefficientOfLift)),
    _coefficientOfReflectivity(std::move(other._coefficientOfReflectivity))
{}

void Vehicle::generic_ctor_impl() {
    _state = std::move(ptr()->get_state());

    _mass = ptr()->get_mass();
    if (_mass < 0.0) {
        throw std::invalid_argument("Vehicle mass cannot be negative.");
    }

    _ramArea = ptr()->get_ram_area();
    if (_ramArea < 0.0) {
        throw std::invalid_argument("Vehicle ram area cannot be negative.");
    }

    _liftArea = ptr()->get_lift_area();
    if (_liftArea < 0.0) {
        throw std::invalid_argument("Vehicle lift area cannot be negative.");
    }

    _solarArea = ptr()->get_solar_area();
    if (_solarArea < 0.0) {
        throw std::invalid_argument("Vehicle solar area cannot be negative.");
    }

    _coefficientOfDrag = ptr()->get_coefficient_of_drag();
    if (_coefficientOfDrag < 0.0) {
        throw std::invalid_argument("Vehicle coefficient of drag cannot be negative.");
    }

    _coefficientOfLift = ptr()->get_coefficient_of_lift();
    if (_mass < 0.0) {
        throw std::invalid_argument("Vehicle coefficient of lift cannot be negative.");
    }

    _coefficientOfReflectivity = ptr()->get_coefficient_of_reflectivity();
    if (_mass < 0.0) {
        throw std::invalid_argument("Vehicle coefficient of lift cannot be negative.");
    }
}

// Move assignment operator
Vehicle& Vehicle::operator=(Vehicle&& other) noexcept {
    if (this != &other) {
        _ptr = std::move(other._ptr),
        _state = std::move(other._state);
        _mass = std::move(other._mass);
        _ramArea = std::move(other._ramArea);
        _liftArea = std::move(other._liftArea);
        _solarArea = std::move(other._solarArea);
        _coefficientOfDrag = std::move(other._coefficientOfDrag);
        _coefficientOfLift = std::move(other._coefficientOfLift);
        _coefficientOfReflectivity = std::move(other._coefficientOfReflectivity);
    }
    return *this;
}

// Copy assignment operator
Vehicle& Vehicle::operator=(const Vehicle& other) {
    return *this = Vehicle(other);
}

// Pointer to user-defined vehicle
const void* Vehicle::get_ptr() const {
    return ptr()->get_ptr();
}
void* Vehicle::get_ptr() {
    return ptr()->get_ptr();
}