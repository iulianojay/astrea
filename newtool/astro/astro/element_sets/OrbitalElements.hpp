#pragma once

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <variant>

// Astro
#include <astro/astro.fwd.hpp>
#include <astro/element_sets/orbital_elements/Cartesian.hpp>
#include <astro/element_sets/orbital_elements/Equinoctial.hpp>
#include <astro/element_sets/orbital_elements/Keplerian.hpp>
#include <astro/types/detail.hpp>
#include <astro/types/type_traits.hpp>
#include <astro/types/typedefs.hpp>
#include <astro/types/typeid_name_extract.hpp>
#include <astro/units/units.hpp>

namespace astro {

// class OrbitalElements;

template <typename T>
concept HasGetSetId = requires(const T elements)
{
    {
        elements.get_set_id()
        } -> std::same_as<EnumType>;
};

template <typename T, typename U>
concept IsConstructableTo = requires(T elements, const AstrodynamicsSystem& sys)
{
    { U(elements, sys) };
};

template <typename T>
concept HasDirectCartesianConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_cartesian(sys)
        } -> std::same_as<Cartesian>;
};

template <typename T>
concept HasDirectKeplerianConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_keplerian(sys)
        } -> std::same_as<Keplerian>;
};

template <typename T>
concept HasDirectEquinoctialConversion = requires(const T elements, const AstrodynamicsSystem& sys)
{
    {
        elements.to_equinoctial(sys)
        } -> std::same_as<Equinoctial>;
};

template <typename T>
concept HasIterpolate =
    requires(const T elements, const Time& thisTime, const Time& otherTime, const T& other, const AstrodynamicsSystem& sys, const Time& targetTime)
{
    {
        elements.interpolate(thisTime, otherTime, other, sys, targetTime)
        } -> std::same_as<T>;
};

template <typename T>
concept HasToVector = requires(const T elements)
{
    {
        elements.to_vector()
        } -> std::same_as<std::vector<Unitless>>;
};

template <typename T>
concept HasSize = requires(const T elements)
{
    {
        elements.size()
        } -> std::same_as<size_t>;
};

template <typename T>
concept HasMathOperators = requires(const T elements, const T other, const Unitless scalar)
{
    {
        elements + other
        } -> std::same_as<T>;
    {
        elements - other
        } -> std::same_as<T>;
    {
        elements* scalar
        } -> std::same_as<T>;
    {
        elements / scalar
        } -> std::same_as<T>;
};

template <typename T>
concept HasInPlaceMathOperators = requires(T elements, const T other, const Unitless scalar)
{
    { elements += other };
    { elements -= other };
    { elements *= scalar };
    { elements /= scalar };
};

template <typename T>
concept IsOrbitalElements = requires(T)
{
    std::is_same<T, remove_cv_ref<T>>::value;
    std::is_default_constructible<T>::value;
    std::is_copy_constructible<T>::value;
    std::is_move_constructible<T>::value;
    std::is_destructible<T>::value;
    requires std::is_same<T, Cartesian>::value || IsConstructableTo<T, Cartesian> || HasDirectCartesianConversion<T>;
    requires HasGetSetId<T>;
    requires HasToVector<T>;
    requires HasSize<T>;
    requires HasMathOperators<T>;
    requires HasInPlaceMathOperators<T>;
};

class OrbitalElementPartials;

class OrbitalElements {

    using ElementVariant = std::variant<Cartesian, Keplerian, Equinoctial>;

    friend std::ostream& operator<<(std::ostream& os, const OrbitalElements& state);

  public:
    OrbitalElements() :
        _elements(Cartesian())
    {
    }
    OrbitalElements(Cartesian elements) :
        _elements(elements)
    {
    }
    OrbitalElements(Keplerian elements) :
        _elements(elements)
    {
    }
    OrbitalElements(Equinoctial elements) :
        _elements(elements)
    {
    }

    template <IsOrbitalElements T>
    void convert(const AstrodynamicsSystem& sys)
    {
        _elements = in<T>(sys);
    }
    template <IsOrbitalElements T>
    OrbitalElements convert(const AstrodynamicsSystem& sys) const
    {
        return in<T>(sys);
    }

    template <IsOrbitalElements T>
    T in(const AstrodynamicsSystem& sys) const
    {
        return std::visit([&](const auto& x) -> T { return T(x, sys); }, _elements);
    }

    OrbitalElements operator+(const OrbitalElements& other) const;
    OrbitalElements& operator+=(const OrbitalElements& other);

    OrbitalElements operator-(const OrbitalElements& other) const;
    OrbitalElements& operator-=(const OrbitalElements& other);

    OrbitalElements operator*(const Unitless& multiplier) const;
    OrbitalElements& operator*=(const Unitless& multiplier);

    OrbitalElementPartials operator/(const Time& divisor) const;
    std::vector<Unitless> to_vector() const;
    OrbitalElements operator/(const Unitless& divisor) const;
    OrbitalElements& operator/=(const Unitless& divisor);

    OrbitalElements
        interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

    const ElementVariant& extract() const;
    ElementVariant& extract();

    constexpr size_t index() const;

  private:
    ElementVariant _elements;

    void same_underlying_type(const OrbitalElements& other) const;
    void throw_mismatched_types() const;
};

class OrbitalElementPartials {

    using PartialVariant = std::variant<CartesianPartial, KeplerianPartial, EquinoctialPartial>;

  public:
    OrbitalElementPartials() :
        _elements(CartesianPartial())
    {
    }
    OrbitalElementPartials(CartesianPartial elements) :
        _elements(elements)
    {
    }
    OrbitalElementPartials(KeplerianPartial elements) :
        _elements(elements)
    {
    }
    OrbitalElementPartials(EquinoctialPartial elements) :
        _elements(elements)
    {
    }

    OrbitalElements operator*(const Time& time) const;

    const PartialVariant& extract() const;
    PartialVariant& extract();

    constexpr size_t index() const;

  private:
    PartialVariant _elements;

    void same_underlying_type(const OrbitalElementPartials& other) const;
    void throw_mismatched_types() const;
};


bool nearly_equal(const OrbitalElements& first, const OrbitalElements& second, bool ignoreFastVariable = false, Unitless relTol = 1.0e-5 * mp_units::one);

// namespace detail {

// struct OrbitalElementsInnerBase {

//     friend std::ostream& operator<<(std::ostream& os, const OrbitalElementsInnerBase& elements)
//     {
//         elements.print(os);
//         return os;
//     }

//     // Virtual destructor
//     virtual ~OrbitalElementsInnerBase() {}

//     // Required methods
//     virtual Cartesian to_cartesian(const AstrodynamicsSystem& sys) const     = 0;
//     virtual Keplerian to_keplerian(const AstrodynamicsSystem& sys) const     = 0;
//     virtual Equinoctial to_equinoctial(const AstrodynamicsSystem& sys) const = 0;
//     virtual EnumType get_set_id() const                                      = 0;
//     virtual std::vector<double> to_vector() const                            = 0;
//     virtual void update_from_vector(const std::vector<double>& vec)          = 0;
//     virtual size_t size() const                                              = 0;

//     // Optional methods
//     virtual OrbitalElements
//         interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const = 0;

//     // Implementation utilities
//     virtual std::unique_ptr<OrbitalElementsInnerBase> clone() const = 0;
//     virtual const void* get_ptr() const                             = 0;
//     virtual void* get_ptr()                                         = 0;

//     // Operators
//     virtual OrbitalElementsInnerBase operator+(const OrbitalElementsInnerBase& other) const = 0;
//     virtual OrbitalElementsInnerBase operator-(const OrbitalElementsInnerBase& other) const = 0;
//     virtual OrbitalElementsInnerBase operator*(const double& scalar) const                  = 0;
//     virtual OrbitalElementsInnerBase operator/(const double& scalar) const                  = 0;

//     virtual void operator+=(const OrbitalElementsInnerBase& other) = 0;
//     virtual void operator-=(const OrbitalElementsInnerBase& other) = 0;
//     virtual void operator*=(const double& scalar)                  = 0;
//     virtual void operator/=(const double& scalar)                  = 0;

//   private:
//     virtual void print(std::ostream&) const = 0;
// };

// template <typename T>
// struct OrbitalElementsInner final : public OrbitalElementsInnerBase {

//     // Default constructor
//     OrbitalElementsInner() = default;

//     // Delete other constructors
//     OrbitalElementsInner(const OrbitalElementsInner&)            = delete;
//     OrbitalElementsInner(OrbitalElementsInner&&)                 = delete;
//     OrbitalElementsInner& operator=(const OrbitalElementsInner&) = delete;
//     OrbitalElementsInner& operator=(OrbitalElementsInner&&)      = delete;

//     // Constructors from T (copy and move variants).
//     explicit OrbitalElementsInner(const T& x) :
//         _value(x)
//     {
//     }
//     explicit OrbitalElementsInner(T&& x) :
//         _value(std::move(x))
//     {
//     }

//     // Size
//     size_t size() const final { return _value.size(); };

//     // Get set
//     EnumType get_set_id() const final { return _value.get_set_id(); }

//     // Vector conversions
//     std::vector<double> to_vector() const final { return _value.to_vector(); }
//     void update_from_vector(const std::vector<double>& vec) final { _value.update_from_vector(vec); }

//     // Interpolate
//     OrbitalElements
//         interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const final;

//     // Cartesian conversion
//     Cartesian to_cartesian(const AstrodynamicsSystem& system) const { return to_cartesian_impl(_value, system); }

//     template <typename U>
//     requires(std::is_same<U, Cartesian>::value) Cartesian to_cartesian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Cartesian(value); }
//     template <typename U>
//     requires(IsConstructableTo<U, Cartesian>) Cartesian to_cartesian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Cartesian(value, system); }
//     template <typename U>
//     requires(!IsConstructableTo<U, Cartesian> && HasDirectCartesianConversion<U>) Cartesian
//         to_cartesian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return value.to_cartesian(system); }

//     // Keplerian conversion
//     Keplerian to_keplerian(const AstrodynamicsSystem& system) const { return to_keplerian_impl(_value, system); }

//     template <typename U>
//     requires(std::is_same<U, Keplerian>::value) Keplerian to_keplerian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Keplerian(value); }
//     template <typename U>
//     requires(IsConstructableTo<U, Keplerian>) Keplerian to_keplerian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Keplerian(value, system); }
//     template <typename U>
//     requires(!IsConstructableTo<U, Keplerian> && HasDirectKeplerianConversion<U>) Keplerian
//         to_keplerian_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return value.to_keplerian(system); }

//     // Equinoctial conversion
//     Equinoctial to_equinoctial(const AstrodynamicsSystem& system) const { return to_equinoctial_impl(_value, system); }

//     template <typename U>
//     requires(std::is_same<U, Equinoctial>::value) Equinoctial to_equinoctial_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Equinoctial(value); }
//     template <typename U>
//     requires(IsConstructableTo<U, Equinoctial>) Equinoctial to_equinoctial_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return Equinoctial(value, system); }
//     template <typename U>
//     requires(!IsConstructableTo<U, Equinoctial> && HasDirectEquinoctialConversion<U>) Equinoctial
//         to_equinoctial_impl(const U& value, const AstrodynamicsSystem& system)
//     const { return value.to_equinoctial(system); }
//     template <typename U>
//     requires(!IsConstructableTo<U, Equinoctial> && !HasDirectEquinoctialConversion<U>) Equinoctial
//         to_equinoctial_impl(const U& value, const AstrodynamicsSystem& system)
//     const { throw std::logic_error("No conversion from this set to equinoctial elements has been defined."); }

//     // The clone method, used in the copy constructor of OrbitalElements.
//     std::unique_ptr<OrbitalElementsInnerBase> clone() const final
//     {
//         return std::make_unique<OrbitalElementsInner>(_value);
//     }

//     // Raw getters for the internal instance.
//     const void* get_ptr() const final { return &_value; }
//     void* get_ptr() final { return &_value; }

//     // Operators
//     OrbitalElementsInner operator+(const OrbitalElementsInnerBase& other) const override
//     {
//         auto otherPtr = check_valid(other);
//         OrbitalElementsInner ret(*this);
//         ret += otherPtr->_value;
//         return ret;
//     }
//     OrbitalElementsInner operator-(const OrbitalElementsInnerBase& other) const override
//     {
//         auto otherPtr = check_valid(other);
//         OrbitalElementsInner ret(*this);
//         ret -= otherPtr->_value;
//         return ret;
//     }
//     OrbitalElementsInner operator*(const double& scalar) const override
//     {
//         OrbitalElementsInner ret(*this);
//         ret *= scalar;
//         return ret;
//     }
//     OrbitalElementsInner operator/(const double& scalar) const override
//     {
//         OrbitalElementsInner ret(*this);
//         ret /= scalar;
//         return ret;
//     }

//     void operator+=(const OrbitalElementsInnerBase& other) override
//     {
//         auto otherPtr = check_valid(other);
//         _value += otherPtr->_value;
//     }
//     void operator-=(const OrbitalElementsInnerBase& other) override
//     {
//         auto otherPtr = check_valid(other);
//         _value -= otherPtr->_value;
//     }
//     void operator*(const double& scalar) override { _value *= scalar; }
//     void operator/(const double& scalar) override { _value /= scalar; }

//     // OrbitalElements object
//     T _value;

//   private:
//     void print(std::ostream& os) const final { os << _value; }
//     auto check_valid(const OrbitalElementsInnerBase& other)
//     {
//         auto otherPtr = dynamic_cast<const OrbitalElementsInner*>(&other);
//         if (!otherPtr) { throw std::invalid_argument("argument must be of type OrbitalElementsInner"); }
//         return otherPtr;
//     }
// };

// } // namespace detail

// template <typename T>
// concept IsGenericallyConstructableOrbitalElements = requires(T)
// {
//     requires IsUserDefinedOrbitalElements<remove_cv_ref<T>>;
//     std::negation<std::is_same<OrbitalElements, remove_cv_ref<T>>>::value;
// };


// class OrbitalElements {

//     friend std::ostream& operator<<(std::ostream& os, OrbitalElements const& elements);

//   public:
//     // Default constructor
//     OrbitalElements();

//   private:
//     void generic_ctor_impl();

//   public:
//     template <typename T>
//     requires(IsGenericallyConstructableOrbitalElements<T>) explicit OrbitalElements(T&& x) :
//         _ptr(std::make_unique<detail::OrbitalElementsInner<remove_cv_ref<T>>>(std::forward<T>(x)))
//     {
//         generic_ctor_impl();
//     }

//     // Copy constructor
//     OrbitalElements(const OrbitalElements&);

//     // Move constructor
//     OrbitalElements(OrbitalElements&&) noexcept;

//     // Move assignment operator
//     OrbitalElements& operator=(OrbitalElements&&) noexcept;

//     // Copy assignment operator
//     OrbitalElements& operator=(const OrbitalElements&);

//     /// Assignment from a user-defined OrbitalElements
//     template <typename T>
//     requires(IsGenericallyConstructableOrbitalElements<T>) OrbitalElements& operator=(T&& x);

//     template <typename T>
//     requires(IsGenericallyConstructableOrbitalElements<T>) const T* extract() const noexcept;

//     // Utilities
//     template <typename T>
//     requires(IsGenericallyConstructableOrbitalElements<T>&& HasVectorConstructor<T>) void convert(const AstrodynamicsSystem& system);

//     template <typename T>
//     requires(IsGenericallyConstructableOrbitalElements<T>&& HasVectorConstructor<T>) OrbitalElements
//         convert(const AstrodynamicsSystem& system)
//     const;

//     void convert(const ElementSet& newSet, const AstrodynamicsSystem& system);
//     OrbitalElements convert(const ElementSet& newSet, const AstrodynamicsSystem& system) const;

//     Cartesian to_cartesian(const AstrodynamicsSystem& system) const;
//     Keplerian to_keplerian(const AstrodynamicsSystem& system) const;
//     Equinoctial to_equinoctial(const AstrodynamicsSystem& system) const;

//     size_t size() const { return ptr()->size(); }

//     EnumType get_set_id() const;
//     const bool same_set(const OrbitalElements& other) const;

//     OrbitalElements
//         interpolate(const Time& thisTime, const Time& otherTime, const OrbitalElements& other, const AstrodynamicsSystem& sys, const Time& targetTime) const;

//     std::vector<double> to_vector() const;
//     void update_from_vector(const std::vector<double>& vec);

//     bool nearly_equal(const OrbitalElements& other, const double& tol = 1.0e-6);

//     // Pointer to user-defined elements
//     const void* get_ptr() const;
//     void* get_ptr();

//     // Operators
//     OrbitalElements operator+(const OrbitalElements& other) const
//     {
//         check_same_set(other);
//         return (*ptr()) + (*other.ptr());
//     }
//     OrbitalElements operator-(const OrbitalElements& other) const
//     {
//         check_same_set(other);
//         return *ptr() - *other.ptr();
//     }
//     OrbitalElements operator*(const double& scalar) const { return ptr() * scalar; }
//     OrbitalElements operator/(const double& scalar) const { return ptr() / scalar; }

//     void operator+=(const OrbitalElements& other)
//     {
//         check_same_set(other);
//         *ptr() += *other.ptr();
//     }
//     void operator-=(const OrbitalElements& other)
//     {
//         check_same_set(other);
//         *ptr() -= *other.ptr();
//     }
//     void operator*=(const double& scalar) { ptr() *= scalar; }
//     void operator/=(const double& scalar) { ptr() /= scalar; }

//   private:
//     // Pointer to the inner base elements
//     std::unique_ptr<detail::OrbitalElementsInnerBase> _ptr;

//     // Members
//     EnumType _setId;

//     // Ensure the pointer actually points to something
//     detail::OrbitalElementsInnerBase const* ptr() const;
//     detail::OrbitalElementsInnerBase* ptr();

//     OrbitalElements convert_impl(const ElementSet& newSet, const AstrodynamicsSystem& system) const;
//     void check_same_set(const OrbitalElements& other) const
//     {
//         if (!same_set(other)) { throw std::runtime_error("Cannot add 2 orbital elements of different element sets."); }
//     }
// };

} // namespace astro