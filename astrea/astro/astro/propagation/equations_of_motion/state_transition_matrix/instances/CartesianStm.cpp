#include <astro/propagation/equations_of_motion/state_transition_matrix/instances/CartesianStm.hpp>

#include <astro/state/orbital_elements/instances/Cartesian.hpp>

namespace astrea {
namespace astro {

CartesianStm::CartesianStm(const EquationsOfMotion& eom, const Cartesian& state)
{
    // do this numerically
}

std::vector<Unitless> CartesianStm::force_to_vector() const
{
    // Fill in the STM elements in row-major order
    std::vector<Unitless> stmVector(36);
    for (std::size_t ii = 0; ii < 6; ++ii) {
        for (std::size_t jj = 0; jj < 6; ++jj) {
            Unitless value;
            if (ii < 3 && jj < 3) {
                const VelPosPartial value_ = _dvdr[ii][jj];
                value                      = value_.numerical_value_in(value_.unit);
            }
            else if (ii < 3 && jj >= 3) {
                const VelVelPartial value_ = _dvdv[ii][jj - 3];
                value                      = value_.numerical_value_in(value_.unit);
            }
            else if (ii >= 3 && jj < 3) {
                const AccelPosPartial value_ = _dadr[ii - 3][jj];
                value                        = value_.numerical_value_in(value_.unit);
            }
            else { // ii >= 3 && jj >= 3
                const AccelVelPartial value_ = _dadv[ii - 3][jj - 3];
                value                        = value_.numerical_value_in(value_.unit);
            }
            stmVector[ii * 6 + jj] = value;
        }
    }

    return stmVector;
}

} // namespace astro
} // namespace astrea