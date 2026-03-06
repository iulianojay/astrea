

# File StateTransitionMatrix.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**equations\_of\_motion**](dir_0a1395a4617b025941a2198784f446c5.md) **>** [**state\_transition\_matrix**](dir_7a22b679029b3e67ce8dbba97ffb681f.md) **>** [**StateTransitionMatrix.cpp**](StateTransitionMatrix_8cpp.md)

[Go to the documentation of this file](StateTransitionMatrix_8cpp.md)


```C++
#include <astro/propagation/equations_of_motion/state_transition_matrix/StateTransitionMatrix.hpp>

#include <astro/propagation/equations_of_motion/EquationsOfMotion.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/OrbitalElements.hpp>

using namespace mp_units;

namespace astrea {
namespace astro {


StateTransitionMatrix::StateTransitionMatrix(const EquationsOfMotion& eom, const State& state, const Vehicle& vehicle)
{
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
```


