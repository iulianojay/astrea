#include <astro/systems/planetary_bodies/JplEphemerisTable.hpp>

// Standard Library Includes
#include <stdexcept>

namespace astrea {
namespace astro {

const Date JplEphemerisTable::START_DATE = Date("2000-01-01 12:00:00");
const Date JplEphemerisTable::STOP_DATE  = Date("2100-01-01 12:00:00");

double JplEphemerisTable::get_index(const Date& date, const Time& timePerPoly)
{
    if (date < START_DATE || date > STOP_DATE) {
        throw std::out_of_range(
            "JplEphemerisTable::get_index() - Value provided for date is outside of the valid range "
            "for the Chebyshev polynomial coefficients. Valid range: 1/1/2000 12:00:00 to 1/1/2100 "
            "12:00:00."
        );
    }
    return static_cast<double>(((date - START_DATE) / timePerPoly).numerical_value_in(mp_units::one));
}

} // namespace astro
} // namespace astrea
