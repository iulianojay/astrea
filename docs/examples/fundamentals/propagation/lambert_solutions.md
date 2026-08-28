[[PLACEHOLDER]]

# Lambert Solutions

Astrea provides a robust implementation of Lambert's problem solver for determining orbital trajectories between two position vectors in a specified time of flight. This capability is essential for trajectory design, rendezvous planning, and interplanetary transfer analysis.

## Lambert's Problem Overview

Lambert's problem involves finding the orbital trajectory that connects two position vectors in space within a given time constraint. The solution provides the required velocity vectors at both positions, enabling mission designers to compute transfer orbits and maneuver requirements.

**Given:**
- Initial position vector r₁
- Final position vector r₂
- Time of flight Δt
- Central body gravitational parameter μ

**Find:**
- Initial velocity vector v₁
- Final velocity vector v₂
- Orbital parameters of transfer trajectory

## LambertSolver Interface

The LambertSolver provides static methods for solving Lambert's problem:

```cpp
#include <astro/propagation/analytic/LambertSolver.hpp>

class LambertSolver {
public:
    enum class OrbitDirection : EnumType {
        PROGRADE,   // Normal orbital direction
        RETROGRADE  // Reverse orbital direction
    };

    // Static solver methods
    static LambertSolution solve(
        const RadiusVector<icrf>& r1,
        const RadiusVector<icrf>& r2,
        const Time& timeOfFlight,
        const GravParam& mu,
        OrbitDirection direction = OrbitDirection::PROGRADE,
        int revolutions = 0
    );
};
```

## Basic Lambert Solution

### Single Revolution Transfer

```cpp
// Define trajectory endpoints
RadiusVector<icrf> r1(7000.0 * km, 0.0 * km, 0.0 * km);
RadiusVector<icrf> r2(0.0 * km, 8000.0 * km, 0.0 * km);

// Transfer time
Time transferTime = 3.0 * hour;

// Earth gravitational parameter
GravParam mu = 398600.44189 * pow<3>(km) / pow<2>(s);

// Solve Lambert's problem
LambertSolution solution = LambertSolver::solve(
    r1, r2, transferTime, mu,
    LambertSolver::OrbitDirection::PROGRADE
);

// Extract velocity vectors
VelocityVector<icrf> v1 = solution.get_initial_velocity();
VelocityVector<icrf> v2 = solution.get_final_velocity();

// Compute required delta-V
VelocityVector<icrf> currentVel1 = /* current velocity at r1 */;
VelocityVector<icrf> deltaV1 = v1 - currentVel1;
Velocity deltaVMagnitude = magnitude(deltaV1);
```

### Multi-Revolution Transfers

```cpp
// Long-duration transfer with multiple revolutions
Time longTransferTime = 2.5 * day;
int numberOfRevolutions = 2;

LambertSolution multiRevSolution = LambertSolver::solve(
    r1, r2, longTransferTime, mu,
    LambertSolver::OrbitDirection::PROGRADE,
    numberOfRevolutions
);

// Multi-revolution transfers may have multiple solutions
std::vector<LambertSolution> allSolutions =
    LambertSolver::solve_all_branches(r1, r2, longTransferTime, mu, numberOfRevolutions);

// Select optimal solution based on delta-V
LambertSolution optimalSolution = select_minimum_energy_solution(allSolutions);
```

### Minimum Energy Solutions

```cpp
// Find minimum energy transfer
LambertSolution find_minimum_energy_transfer(
    const RadiusVector<icrf>& r1,
    const RadiusVector<icrf>& r2,
    const GravParam& mu
) {

    // Compute minimum energy (Hohmann-like) transfer time
    Distance semiMajorAxis = (magnitude(r1) + magnitude(r2)) / 2.0;
    Time minimumEnergyTime = pi * sqrt(pow<3>(semiMajorAxis) / mu);

    return LambertSolver::solve(r1, r2, minimumEnergyTime, mu);
}
```
