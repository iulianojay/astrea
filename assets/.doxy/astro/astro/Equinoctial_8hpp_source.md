

# File Equinoctial.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_elements**](dir_6eb62f1e639545772a8b9a71f7b1d0b7.md) **>** [**Equinoctial.hpp**](Equinoctial_8hpp.md)

[Go to the documentation of this file](Equinoctial_8hpp.md)


```C++

#pragma once

#include <iosfwd>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

template <IsFrame auto _frame_>
class Equinoctial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, Equinoctial<frame> const&);
    friend class OrbitalElements;

  public:
    static constexpr auto frame = _frame_; 
    template <IsFrame auto F>
    using BaseType = Equinoctial<F>;

    Equinoctial(Unitless scale = 0.0 * astrea::detail::unitless) :
        _semilatus(scale * astrea::detail::distance_unit),
        _f(scale * astrea::detail::unitless),
        _g(scale * astrea::detail::unitless),
        _h(scale * astrea::detail::unitless),
        _k(scale * astrea::detail::unitless),
        _trueLongitude(scale * astrea::detail::angle_unit)
    {
    }

    Equinoctial(const Distance& semilatus, const Unitless& f, const Unitless& g, const Unitless& h, const Unitless& k, const Angle& trueLongitude) :
        _semilatus(semilatus),
        _f(f),
        _g(g),
        _h(h),
        _k(k),
        _trueLongitude(trueLongitude)
    {
    }

    Equinoctial(const Equinoctial<_frame_>& elements, const GravParam& mu) :
        Equinoctial(elements)
    {
    }

    Equinoctial(const Keplerian<_frame_>& elements, const GravParam& mu);

    Equinoctial(const Cartesian<_frame_>& elements, const GravParam& mu) :
        Equinoctial(Keplerian<_frame_>(elements, mu), mu)
    {
    }

    static Equinoctial LEO(const GravParam& mu);

    static Equinoctial LMEO(const GravParam& mu);

    static Equinoctial GPS(const GravParam& mu);

    static Equinoctial HMEO(const GravParam& mu);

    static Equinoctial GEO(const GravParam& mu);

    Equinoctial(const Equinoctial<_frame_>&);

    Equinoctial(Equinoctial<_frame_>&& other) noexcept;

    Equinoctial& operator=(Equinoctial<_frame_>&& other) noexcept;

    Equinoctial& operator=(const Equinoctial<_frame_>& other);

    ~Equinoctial() = default;

    template <IsFrame auto target_frame>
    Equinoctial<target_frame> in_frame(const Date& epoch, const GravParam& mu) const;

    bool operator==(const Equinoctial<_frame_>& other) const;

    bool operator!=(const Equinoctial<_frame_>& other) const;

    Equinoctial operator+(const Equinoctial<_frame_>& other) const;

    Equinoctial& operator+=(const Equinoctial<_frame_>& other);

    Equinoctial operator-(const Equinoctial<_frame_>& other) const;

    Equinoctial& operator-=(const Equinoctial<_frame_>& other);

    Equinoctial operator*(const Unitless& multiplier) const;

    Equinoctial& operator*=(const Unitless& multiplier);

    EquinoctialPartial<_frame_> operator/(const Time& time) const;

    Equinoctial operator/(const Unitless& divisor) const;

    Equinoctial& operator/=(const Unitless& divisor);

    const Distance& get_semilatus() const { return _semilatus; }

    const Unitless& get_f() const { return _f; }

    const Unitless& get_g() const { return _g; }

    const Unitless& get_h() const { return _h; }

    const Unitless& get_k() const { return _k; }

    const Angle& get_true_longitude() const { return _trueLongitude; }

    std::vector<double> force_to_double_vector() const;

    Equinoctial
        interpolate(const Time& thisTime, const Time& otherTime, const Equinoctial<_frame_>& other, const GravParam& mu, const Time& targetTime) const;

  private:
    Distance _semilatus;  
    Unitless _f;          
    Unitless _g;          
    Unitless _h;          
    Unitless _k;          
    Angle _trueLongitude; 

    static Equinoctial from_double_vector(const std::vector<double>& vec);
};

template <IsFrame auto _frame_>
class EquinoctialPartial {

    template <IsFrame auto frame>
    friend std::ostream& operator<<(std::ostream&, EquinoctialPartial<frame> const&);

  public:
    static constexpr auto frame = _frame_; 

    EquinoctialPartial() = default;

    EquinoctialPartial(
        const Velocity& semilatusPartial,
        const UnitlessPerTime& fPartial,
        const UnitlessPerTime& gPartial,
        const UnitlessPerTime& hPartial,
        const UnitlessPerTime& kPartial,
        const AngularVelocity& trueLongitudePartial
    ) :
        _semilatusPartial(semilatusPartial),
        _fPartial(fPartial),
        _gPartial(gPartial),
        _hPartial(hPartial),
        _kPartial(kPartial),
        _trueLongitudePartial(trueLongitudePartial)
    {
    }

    Equinoctial<_frame_> operator*(const Time& time) const;

    std::vector<double> force_to_double_vector() const;

  private:
    Velocity _semilatusPartial;            
    UnitlessPerTime _fPartial;             
    UnitlessPerTime _gPartial;             
    UnitlessPerTime _hPartial;             
    UnitlessPerTime _kPartial;             
    AngularVelocity _trueLongitudePartial; 
};

} // namespace astro
} // namespace astrea

#include <astro/state/orbital_elements/Equinoctial.ipp>
```


