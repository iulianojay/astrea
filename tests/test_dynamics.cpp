
#include "astro.hpp"

int main() {
    return 0;
}

int test_two_body_dyanmics() {

    // Setup system
    AstrodynamicsSystem sys;

    // Build spacecraft
    element_array state0 = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    OrbitalElements elements0(state0, ElementSet::COE, &sys);
    Spacecraft sat(elements0, "Jan-01-2030 00:00:00.0");

    // Build Integrator
    Integrator integrator;
    LambertSolver lambertSolver;
    
    integrator.set_abs_tol(1.0e-8);
    integrator.set_rel_tol(1.0e-8);

    // Build EoMs
    EquationsOfMotion eoms;
    eoms.switch_dynamics("two body");

    // Set parameters
    integrator.set_abs_tol(1.0e-9);
    integrator.set_rel_tol(1.0e-9);

    eoms.switch_dynamics("two body");

    // Run integration
    double t0 = 0.0;
    double tf = 86400.0;

    integrator.propagate(0, 86400.0, sat, eoms);

    return 0;
}