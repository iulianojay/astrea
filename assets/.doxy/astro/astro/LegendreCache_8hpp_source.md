

# File LegendreCache.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**LegendreCache.hpp**](LegendreCache_8hpp.md)

[Go to the documentation of this file](LegendreCache_8hpp.md)


```C++

#pragma once

#include <array>
#include <memory>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/framework/frame_concepts.hpp>
#include <astro/systems/system_concepts.hpp>

namespace astrea {
namespace astro {

template <IsCelestialBody auto _body_, std::size_t _degree_ = 2, std::size_t _order_ = 0>
class LegendreCache {

    static_assert(_degree_ >= _order_, "Degree must be greater than or equal to the order");
    static_assert(_degree_ >= 2 && _order_ >= 0, "Degree must be at least 2 and order must be non-negative");

  public:
    LegendreCache();

    ~LegendreCache() = default;

    const Unitless& get_cosine_coefficient(const std::size_t& n, const std::size_t& m) const;

    const Unitless& get_sine_coefficient(const std::size_t& n, const std::size_t& m) const;

  private:
    static constexpr std::size_t _span = _order_ + 1;
    std::array<Unitless, _span*(_degree_ + 1)> _C{}; 
    std::array<Unitless, _span*(_degree_ + 1)> _S{}; 
};

} // namespace astro
} // namespace astrea

#include <astro/propagation/force_models/LegendreCache.ipp>
```


