
#include "astro.hpp"

int main() {
    return 0;
}

int test_two_body_dyanmics() {

    // Build satellite
    Spacecraft sat;
    Integrator integrator;
    EquationsOfMotion eoms;

    // Set parameters
    integrator.set_abs_tol(1.0e-9);
    integrator.set_rel_tol(1.0e-9);

    eoms.switch_dynamics("two body");
    sat.set_epoch("Jan-01-2030 00:00:00.0");

    // Get initial state
    double coes[6] = {10000.0, 0.0, 45.0, 0.0, 0.0, 0.0};
    double state0[6] = {0.0};

    // Run integration
    double t0 = 0.0;
    double tf = 86400.0;

    integrator.integrate(t0, tf, state0);

    return 0;
}