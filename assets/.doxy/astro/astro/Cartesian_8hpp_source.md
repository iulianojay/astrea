

# File Cartesian.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**instances**](dir_2296e922a578ce2ef4a64c83384e553c.md) **>** [**Cartesian.hpp**](Cartesian_8hpp.md)

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
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frames.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

class Cartesian {

    friend std::ostream& operator<<(std::ostream&, Cartesian const&);
    friend class OrbitalElements;

  public:
    Cartesian(Unitless scale = 0.0 * astrea::detail::unitless) :
        _r(scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit, scale * astrea::detail::distance_unit),
        _v(scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit,
           scale * astrea::detail::distance_unit / astrea::detail::time_unit)
    {
    }

    Cartesian(const RadiusVector<frames::earth::icrf>& r, const VelocityVector<frames::earth::icrf>& v) :
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

    Cartesian(const Keplerian& elements, const GravParam& mu);

    Cartesian(const Equinoctial& elements, const GravParam& mu);

    Cartesian(const OrbitalElements& elements, const GravParam& mu);

    static Cartesian LEO(const GravParam& mu);

    static Cartesian LMEO(const GravParam& mu);

    static Cartesian GPS(const GravParam& mu);

    static Cartesian HMEO(const GravParam& mu);

    static Cartesian GEO(const GravParam& mu);

    Cartesian(const Cartesian&);

    Cartesian(Cartesian&&) noexcept;

    Cartesian& operator=(Cartesian&&) noexcept;

    Cartesian& operator=(const Cartesian&);

    ~Cartesian() = default;

    bool operator==(const Cartesian& other) const;

    bool operator!=(const Cartesian& other) const;

    Cartesian operator+(const Cartesian& other) const;

    Cartesian operator+(const RadiusVector<frames::earth::icrf>& r) const;
    Cartesian operator+(const VelocityVector<frames::earth::icrf>& v) const;

    Cartesian& operator+=(const Cartesian& other);

    Cartesian& operator+=(const RadiusVector<frames::earth::icrf>& r);
    Cartesian& operator+=(const VelocityVector<frames::earth::icrf>& v);

    Cartesian operator-(const Cartesian& other) const;

    Cartesian operator-(const RadiusVector<frames::earth::icrf>& r) const;
    Cartesian operator-(const VelocityVector<frames::earth::icrf>& v) const;

    Cartesian& operator-=(const Cartesian& other);

    Cartesian& operator-=(const RadiusVector<frames::earth::icrf>& r);
    Cartesian& operator-=(const VelocityVector<frames::earth::icrf>& v);

    Cartesian operator*(const Unitless& multiplier) const; // TODO: Add left-hand version (i.e. scalar * state)

    Cartesian& operator*=(const Unitless& multiplier);

    CartesianPartial operator/(const Time& time) const;

    std::vector<Unitless> operator/(const Cartesian& other) const;

    Cartesian operator/(const Unitless& divisor) const;

    Cartesian& operator/=(const Unitless& divisor);

    const RadiusVector<frames::earth::icrf>& get_position() const { return _r; }

    const VelocityVector<frames::earth::icrf>& get_velocity() const { return _v; }

    const Distance& get_x() const { return _r.get_x(); }

    const Distance& get_y() const { return _r.get_y(); }

    const Distance& get_z() const { return _r.get_z(); }

    const Velocity& get_vx() const { return _v.get_x(); }

    const Velocity& get_vy() const { return _v.get_y(); }

    const Velocity& get_vz() const { return _v.get_z(); }

    std::vector<Unitless> force_to_vector() const;

    Cartesian interpolate(const Time& thisTime, const Time& otherTime, const Cartesian& other, const GravParam& mu, const Time& targetTime) const;

  private:
    RadiusVector<frames::earth::icrf> _r;   
    VelocityVector<frames::earth::icrf> _v; 

    static Cartesian from_vector(const std::vector<Unitless>& vec);
};

class CartesianPartial {

    friend std::ostream& operator<<(std::ostream&, CartesianPartial const&);

  public:
    CartesianPartial() = default;

    CartesianPartial(const Velocity& vx, const Velocity& vy, const Velocity& vz, const Acceleration& ax, const Acceleration& ay, const Acceleration& az) :
        _v(vx, vy, vz),
        _a(ax, ay, az)
    {
    }

    CartesianPartial(const VelocityVector<frames::earth::icrf>& v, const AccelerationVector<frames::earth::icrf>& a) :
        _v(v),
        _a(a)
    {
    }

    Cartesian operator*(const Time& time) const;

    std::vector<Unitless> force_to_vector() const;

  private:
    VelocityVector<frames::earth::icrf> _v;     
    AccelerationVector<frames::earth::icrf> _a; 
};

} // namespace astro
} // namespace astrea


// namespace avro {

// template <>
// struct codec_traits<astrea::astro::Cartesian> {
//     static void encode(Encoder& encoder, const astrea::astro::Cartesian& cartesian)
//     {
//         avro::encode(encoder, cartesian.get_x());
//         avro::encode(encoder, cartesian.get_y());
//         avro::encode(encoder, cartesian.get_z());
//         avro::encode(encoder, cartesian.get_vx());
//         avro::encode(encoder, cartesian.get_vy());
//         avro::encode(encoder, cartesian.get_vz());
//     }
//     static void decode(Decoder& decoder, astrea::astro::Cartesian& cartesian)
//     {
//         astrea::Distance x{}, y{}, z{};
//         astrea::Velocity vx{}, vy{}, vz{};

//         avro::decode(decoder, x);
//         avro::decode(decoder, y);
//         avro::decode(decoder, z);
//         avro::decode(decoder, vx);
//         avro::decode(decoder, vy);
//         avro::decode(decoder, vz);

//         cartesian = astrea::astro::Cartesian(x, y, z, vx, vy, vz);
//     }
// };

// } // namespace avro
```


