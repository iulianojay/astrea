#include <astro/propagation/equations_of_motion/StateTransitionMatrix.hpp>

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

using namespace mp_units;

namespace astrea {
namespace astro {


StateTransitionMatrix::StateTransitionMatrix(const EquationsOfMotion& eom, const State& state, const Vehicle& vehicle)
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
     * It might be possible to use fancy metaprogramming to deduce the units of each element based on the element type but
     * that seems like a huge headache. For now, we force the elements into unitless quantities, converted using their
     * underlying units, and then force a conversion back. This makes this function implicity unsafe from a unit perspective.
     */

    const AstrodynamicsSystem& sys = state.get_system();
    const std::vector<Unitless> s0 = state.force_to_vector();
    const std::size_t typeIdx      = state.get_elements().index();
    const std::vector<Unitless> f0 = eom(state, vehicle).force_to_vector();

    // The size of dsi will have different sensitivity based on the element type so we use a relative perturbation
    const Unitless relPerturbation = 1.0e-8 * one;
    for (std::size_t ii = 0; ii < 6; ++ii) {
        const auto& si     = s0[ii];
        const Unitless dsi = si * relPerturbation;

        for (std::size_t jj = 0; jj < 6; ++jj) {
            // Perturb state
            std::vector<Unitless> sPlusDs  = s0;
            std::vector<Unitless> sMinusDs = s0;
            sPlusDs[ii] += dsi;
            sMinusDs[ii] -= dsi;

            // Convert back to OrbitalElements
            const State statePlus  = State::from_vector(sPlusDs, typeIdx, sys);
            const State stateMinus = State::from_vector(sMinusDs, typeIdx, sys);

            // Compute f(s + dsi)
            const std::vector<Unitless> fPerturbedPlus  = eom(statePlus, vehicle).force_to_vector();
            const std::vector<Unitless> fPerturbedMinus = eom(stateMinus, vehicle).force_to_vector();

            // Compute partial derivative
            _stm[jj][ii] = (fPerturbedPlus[jj] - fPerturbedMinus[jj]) / (2 * dsi);
        }
    }
}


std::vector<Unitless> StateTransitionMatrix::force_to_vector() const
{
    std::vector<Unitless> stmVector(36);
    for (std::size_t ii = 0; ii < 6; ++ii) {
        for (std::size_t jj = 0; jj < 6; ++jj) {
            stmVector[ii * 6 + jj] = _stm[ii][jj];
        }
    }
    return stmVector;
}

} // namespace astro
} // namespace astrea