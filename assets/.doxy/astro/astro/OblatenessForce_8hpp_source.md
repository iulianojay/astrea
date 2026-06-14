

# File OblatenessForce.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**OblatenessForce.hpp**](OblatenessForce_8hpp.md)

[Go to the documentation of this file](OblatenessForce_8hpp.md)


```C++

#pragma once

#include <array>
#include <memory>
#include <vector>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_, std::size_t _degree_ = 2, std::size_t _order_ = 0>
class LegendreCache {
  public:
    LegendreCache();

    ~LegendreCache() = default;

    Unitless get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const;

    Unitless get_sine_coefficient(const std::size_t& n, const std::size_t& m) const;

    // /**
    //  * @brief Computes the Legendre polynomial coefficients for the oblateness force.
    //  *
    //  * @param x Value at which to evaluate the Legendre polynomial
    //  * @param degree Degree of the spherical harmonics
    //  * @param order Order of the spherical harmonics
    //  */
    // std::vector<std::vector<Unitless>>
    //     get_legendre_coefficients(const std::size_t& degree, const std::size_t& order, const Unitless& x) const;

  private:
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _C{}; 
    std::array<std::array<Unitless, _order_ + 1>, _degree_ + 1> _S{}; 
};

template <IsCelestialBody auto _body_, std::size_t _degree_ = 2, std::size_t _order_ = 0>
class OblatenessForce : public PerturbingForce {
  public:
    OblatenessForce() = default;

    ~OblatenessForce() = default;

    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const;

  private:
    const LegendreCache<_body_, _degree_, _order_> _legendreCache; 
};

} // namespace astro
} // namespace astrea

#include <astro/propagation/force_models/OblatenessForce.ipp>
```


