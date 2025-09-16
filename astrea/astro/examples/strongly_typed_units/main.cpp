#include <iostream>

#include <units/units.hpp>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::si::unit_symbols::s;

int main()
{
    // Astrea relies on the mp-units library to handle units. This allows for strong typing of physical quantities,
    // and compile-time unit checking, while also forcing developers to be explicit about units. This process helps
    // avoid hard-to-see coversion issues, implicit units declarations, and inconsistencies in rounding and precision.

    // In general, the mp-units library is highly generalized for any united quantity, but Astrea uses simple type
    // wrappers for consistency and convenience. These definitions are held in <units/typedefs.hpp>.
    quantity<s> t = 1.0 * s; // mp-units explicit style
    Time time     = 1.0 * s; // Astrea implicit style

    std::cout << "Quantity Time: " << t << std::endl;
    std::cout << "Astrea Time: " << time << std::endl;

    // Ultimately, both representations are identical. The type-wrapping does allow for more universal unit usage between
    // different Astrea toolsets (which avoids a lot of implicit conversions), but it is largely for convenience.
    static_assert(std::is_same_v<decltype(t), decltype(time)>);

    // Currently, Astrea does use the complete isq definitions provided by mp-units, but this will change in future releases.

    return 0;
}