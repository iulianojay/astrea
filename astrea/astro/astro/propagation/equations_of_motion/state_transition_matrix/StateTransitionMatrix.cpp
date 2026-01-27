#include <astro/propagation/equations_of_motion/state_transition_matrix/StateTransitionMatrix.hpp>

namespace astrea {
namespace astro {


StateTransitionMatrix::StateTransitionMatrix(const EquationsOfMotion& eom, const OrbitalElements& state, const Vehicle& vehicle)
{
    /**
     * f(s) = [f0(s), f1(s), ..., fn(s)] where fi is the ith component of the equations of motion
     *
     * df/ds = |df0/ds0, df0/ds1, ..., df0/dsn| where dfi/ds is the partial derivative of the ith component with respect to the state vector
     *         |df1/ds0, df1/ds1, ..., df1/dsn|
     *         | ...                          |
     *         |dfn/ds0, dfn/ds1, ..., dfn/dsn|
     *
     * df/dsi = f(s + dsi) - f(s) / dsi
     * units  = (OEP - OEP)/OEi = OEP/OEi -> i.e. [da/dt]/[a], [de/dt]/[a], [di/dt]/[a], [dOmega/dt]/[a], [domega/dt]/[a], [dM/dt]/[a]
     *
     */
}

} // namespace astro
} // namespace astrea