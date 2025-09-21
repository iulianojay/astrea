#include <astro/systems/JplEphemerisTable.hpp>

// Standard Library Includes
#include <stdexcept>

namespace astrea {
namespace astro {
namespace jpl_ephemeris {

std::size_t JplEphemerisTable::get_index(const Date& date, const double& daysPerPoly)
{
    if (date < _startDate || date > _stopDate) {
        throw std::out_of_range(
            "JplEphemerisTable::get_index() - Value provided for date is outside of the valid range "
            "for the Chebyshev polynomial coefficients. Valid range: 1/1/2000 12:00:00 to 1/1/2100 "
            "12:00:00."
        );
    }

    return static_cast<std::size_t>(((date - _startDate) / timePerPoly).numerical_value_in(mp_units::one));
}

} // namespace jpl_ephemeris
} // namespace astro
} // namespace astrea
