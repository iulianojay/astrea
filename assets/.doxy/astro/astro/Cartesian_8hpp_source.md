

# File Cartesian.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**Cartesian.hpp**](Cartesian_8hpp.md)

[Go to the documentation of this file](Cartesian_8hpp.md)


```C++

#pragma once

#include <iosfwd>

// // avro
// #include <avro/Decoder.hh>
// #include <avro/Encoder.hh>
// #include <avro/Specific.hh>

#include <units/units.hpp>

// astro
#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/CartesianVector.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
class Cartesian {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Cartesian<frame> const&);
    friend class OrbitalElements;

  public:
    static constexpr auto frame = _frame_; 
    template <IsFrame auto F>
    using BaseType = Cartesian<F>;

    Cartesian(Unitless scale = 0.0 * astrea::detail::unitless) :
        _r(scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit),
        _v(scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit)
    {
    }

    Cartesian(const RadiusVector<_frame_>& r, const VelocityVector<_frame_>& v) :
        _r(r),
        _v(v)
    {
    }

    Cartesian(const Distance& x, const Distance& y, const Distance& z, const Velocity& vx, const Velocity& vy, const Velocity& vz) :
        _r(x, y, z),
        _v(vx, vy, vz)
    {
    }

    Cartesian(const Cartesian& elements, const GravParam& mu) :
        Cartesian(elements)
    {
    }

    Cartesian(const Keplerian<_frame_>& elements, const GravParam& mu);

    Cartesian(const Equinoctial<_frame_>& elements, const GravParam& mu);

    static Cartesian LEO(const GravParam& mu);

    static Cartesian LMEO(const GravParam& mu);

    static Cartesian GPS(const GravParam& mu);

    static Cartesian HMEO(const GravParam& mu);

    static Cartesian GEO(const GravParam& mu);

    Cartesian(const Cartesian<_frame_>&);

    Cartesian(Cartesian<_frame_>&&) noexcept = default;

    Cartesian& operator=(Cartesian<_frame_>&&) noexcept;

    Cartesian& operator=(const Cartesian<_frame_>&);

    ~Cartesian() = default;

    bool operator==(const Cartesian<_frame_>& other) const;

    bool operator!=(const Cartesian<_frame_>& other) const;

    Cartesian operator+(const Cartesian<_frame_>& other) const;

    Cartesian operator+(const RadiusVector<_frame_>& r) const;
    Cartesian operator+(const VelocityVector<_frame_>& v) const;

    Cartesian& operator+=(const Cartesian<_frame_>& other);

    Cartesian& operator+=(const RadiusVector<_frame_>& r);
    Cartesian& operator+=(const VelocityVector<_frame_>& v);

    Cartesian operator-(const Cartesian<_frame_>& other) const;

    Cartesian operator-(const RadiusVector<_frame_>& r) const;
    Cartesian operator-(const VelocityVector<_frame_>& v) const;

    Cartesian& operator-=(const Cartesian<_frame_>& other);

    Cartesian& operator-=(const RadiusVector<_frame_>& r);
    Cartesian& operator-=(const VelocityVector<_frame_>& v);

    Cartesian operator*(const Unitless& multiplier) const; // TODO: Add left-hand version (i.e. scalar * state)

    Cartesian& operator*=(const Unitless& multiplier);

    CartesianPartial<_frame_> operator/(const Time& time) const;

    std::vector<Unitless> operator/(const Cartesian<_frame_>& other) const;

    Cartesian operator/(const Unitless& divisor) const;

    Cartesian& operator/=(const Unitless& divisor);

    template <IsFrame auto target_frame>
    Cartesian<target_frame> in_frame(const Date& epoch) const
    {
        if constexpr (equivalent(frame, target_frame)) { return *this; }
        const CartesianVector<Distance, target_frame> rTarget = _r.template in_frame<target_frame>(epoch);
        const CartesianVector<Velocity, target_frame> vTarget = _v.template in_frame<target_frame>(epoch, _r);
        return Cartesian<target_frame>(rTarget, vTarget);
    }

    template <IsFrame auto target_frame>
    Cartesian<target_frame> in_frame(const Date& epoch, const GravParam& /*mu*/) const
    {
        return in_frame<target_frame>(epoch);
    }

    const RadiusVector<_frame_>& get_position() const { return _r; }

    const VelocityVector<_frame_>& get_velocity() const { return _v; }

    const Distance& get_x() const { return _r.get_x(); }

    const Distance& get_y() const { return _r.get_y(); }

    const Distance& get_z() const { return _r.get_z(); }

    const Velocity& get_vx() const { return _v.get_x(); }

    const Velocity& get_vy() const { return _v.get_y(); }

    const Velocity& get_vz() const { return _v.get_z(); }

    std::vector<double> force_to_double_vector() const;

    Cartesian interpolate(const Time& thisTime, const Time& otherTime, const Cartesian<_frame_>& other, const GravParam& mu, const Time& targetTime) const;

  private:
    RadiusVector<_frame_> _r;   
    VelocityVector<_frame_> _v; 

    static Cartesian from_double_vector(const std::vector<double>& vec);
};

template <IsFrame auto _frame_>
class CartesianPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, CartesianPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; 

    CartesianPartial() = default;

    CartesianPartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _v(vx, vy, vz),
        _a(ax, ay, az)
    {
    }

    CartesianPartial(const VelocityVector<_frame_>& v, const AccelerationVector<_frame_>& a) :
        _v(v),
        _a(a)
    {
    }

    Velocity get_vx() const { return _v.get_x(); }

    Velocity get_vy() const { return _v.get_y(); }

    Velocity get_vz() const { return _v.get_z(); }

    Acceleration get_ax() const { return _a.get_x(); }

    Acceleration get_ay() const { return _a.get_y(); }

    Acceleration get_az() const { return _a.get_z(); }

    Cartesian<_frame_> operator*(const Time& time) const;

    std::vector<double> force_to_double_vector() const;

  private:
    VelocityVector<_frame_> _v;     
    AccelerationVector<_frame_> _a; 
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Cartesian.ipp>
```


