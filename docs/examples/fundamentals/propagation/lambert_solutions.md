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
        const CartesianVector<Distance, ECI>& r1,
        const CartesianVector<Distance, ECI>& r2,
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
CartesianVector<Distance, ECI> r1(7000.0 * km, 0.0 * km, 0.0 * km);
CartesianVector<Distance, ECI> r2(0.0 * km, 8000.0 * km, 0.0 * km);

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
CartesianVector<Velocity, ECI> v1 = solution.get_initial_velocity();
CartesianVector<Velocity, ECI> v2 = solution.get_final_velocity();

// Compute required delta-V
CartesianVector<Velocity, ECI> currentVel1 = /* current velocity at r1 */;
CartesianVector<Velocity, ECI> deltaV1 = v1 - currentVel1;
Speed deltaVMagnitude = magnitude(deltaV1);
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

## Mission Applications

### Rendezvous Planning

```cpp
// Spacecraft rendezvous scenario
class RendezvousPlan {
public:
    static std::vector<ManeuverPlan> plan_rendezvous(
        const State& chaserState,
        const State& targetState,
        const Time& rendezvousTime
    ) {

        // Current positions
        CartesianVector<Distance, ECI> chaserPos = chaserState.get_position();
        CartesianVector<Distance, ECI> targetPos = targetState.get_position();

        // Predict target position at rendezvous time
        CartesianVector<Distance, ECI> futureTargetPos =
            propagate_position(targetState, rendezvousTime);

        // Solve Lambert's problem
        Time timeOfFlight = rendezvousTime - chaserState.get_epoch();
        LambertSolution solution = LambertSolver::solve(
            chaserPos, futureTargetPos, timeOfFlight,
            chaserState.get_system().get_central_body().get_gravitational_parameter()
        );

        // Compute maneuver requirements
        CartesianVector<Velocity, ECI> currentVel = chaserState.get_velocity();
        CartesianVector<Velocity, ECI> requiredVel = solution.get_initial_velocity();
        CartesianVector<Velocity, ECI> deltaV = requiredVel - currentVel;

        return create_maneuver_sequence(deltaV, chaserState.get_epoch());
    }
};

// Plan rendezvous maneuvers
Std::vector<ManeuverPlan> maneuvers = RendezvousPlan::plan_rendezvous(
    chaserSatellite, targetSatellite, rendezvousTime
);
```

### Interplanetary Transfers

```cpp
// Earth-Mars transfer using Lambert solver
class InterplanetaryTransfer {
public:
    static TransferWindow analyze_earth_mars_transfer(const Time& departureWindow) {

        AstrodynamicsSystem solarSystem(
            CelestialBodyId::SUN,
            {CelestialBodyId::EARTH, CelestialBodyId::MARS}
        );

        std::vector<TransferOpportunity> opportunities;

        // Scan departure window
        for (Time departure = departureWindow.start;
             departure <= departureWindow.end;
             departure += 1.0 * day) {

            // Get planetary positions at departure
            CartesianVector<Distance, helio::icrf> earthPos =
                solarSystem.get_body_position(CelestialBodyId::EARTH, departure);

            // Scan arrival times
            for (Time flightTime = 180.0 * day; flightTime <= 300.0 * day; flightTime += 5.0 * day) {

                Time arrival = departure + flightTime;
                CartesianVector<Distance, helio::icrf> marsPos =
                    solarSystem.get_body_position(CelestialBodyId::MARS, arrival);

                // Solve heliocentric Lambert problem
                GravParam sunMu = solarSystem.get_central_body().get_gravitational_parameter();
                LambertSolution solution = LambertSolver::solve(
                    earthPos, marsPos, flightTime, sunMu
                );

                // Compute total delta-V requirement
                Speed totalDeltaV = compute_interplanetary_deltav(solution, departure, arrival);

                opportunities.emplace_back(departure, arrival, totalDeltaV, solution);
            }
        }

        return find_optimal_transfer_window(opportunities);
    }
};
```

### Formation Flying

```cpp
// Formation flying Lambert solutions
class FormationControl {
public:
    static ManeuverSequence maintain_formation(
        const State& leaderState,
        const State& followerState,
        const CartesianVector<Distance, RIC>& desiredOffset,
        const Time& controlPeriod
    ) {

        // Convert desired offset to inertial frame
        CartesianVector<Distance, ECI> desiredPosECI =
            transform<ECI, RIC>(desiredOffset, leaderState.get_epoch(), leaderState);

        CartesianVector<Distance, ECI> targetPosition =
            leaderState.get_position() + desiredPosECI;

        // Solve for formation maintenance trajectory
        LambertSolution maintainSolution = LambertSolver::solve(
            followerState.get_position(),
            targetPosition,
            controlPeriod,
            followerState.get_system().get_central_body().get_gravitational_parameter()
        );

        // Generate station-keeping maneuvers
        return generate_formation_maneuvers(maintainSolution, followerState);
    }
};
```

## Advanced Lambert Techniques

### Minimum Energy Solutions

```cpp
// Find minimum energy transfer
LambertSolution find_minimum_energy_transfer(
    const CartesianVector<Distance, ECI>& r1,
    const CartesianVector<Distance, ECI>& r2,
    const GravParam& mu
) {

    // Compute minimum energy (Hohmann-like) transfer time
    Distance semiMajorAxis = (magnitude(r1) + magnitude(r2)) / 2.0;
    Time minimumEnergyTime = pi * sqrt(pow<3>(semiMajorAxis) / mu);

    return LambertSolver::solve(r1, r2, minimumEnergyTime, mu);
}
```

### Multi-Impulse Transfers

```cpp
// Bi-elliptic transfer using multiple Lambert solutions
struct BiEllipticTransfer {
    LambertSolution firstLeg;
    LambertSolution secondLeg;
    Distance intermediateRadius;
    Speed totalDeltaV;
};

BiEllipticTransfer design_bielliptic_transfer(
    const CartesianVector<Distance, ECI>& r1,
    const CartesianVector<Distance, ECI>& r2,
    const Distance& intermediateRadius,
    const GravParam& mu
) {

    // Define intermediate point on transfer orbit
    CartesianVector<Distance, ECI> rIntermediate(
        intermediateRadius, 0.0 * km, 0.0 * km
    );

    // First leg: r1 to intermediate point
    LambertSolution firstLeg = LambertSolver::solve(
        r1, rIntermediate,
        compute_transfer_time(r1, rIntermediate, mu), mu
    );

    // Second leg: intermediate point to r2
    LambertSolution secondLeg = LambertSolver::solve(
        rIntermediate, r2,
        compute_transfer_time(rIntermediate, r2, mu), mu
    );

    // Compute total delta-V
    Speed deltaV1 = magnitude(firstLeg.get_initial_velocity() -
                             compute_circular_velocity(r1, mu));
    Speed deltaV2 = magnitude(secondLeg.get_initial_velocity() -
                             firstLeg.get_final_velocity());
    Speed deltaV3 = magnitude(compute_circular_velocity(r2, mu) -
                             secondLeg.get_final_velocity());

    return BiEllipticTransfer{
        firstLeg, secondLeg, intermediateRadius, deltaV1 + deltaV2 + deltaV3
    };
}
```

## Solution Validation

```cpp
// Validate Lambert solution accuracy
void validate_lambert_solution(
    const LambertSolution& solution,
    const CartesianVector<Distance, ECI>& r1,
    const CartesianVector<Distance, ECI>& r2,
    const Time& timeOfFlight,
    const GravParam& mu
) {

    // Propagate initial state using solution velocities
    Cartesian initialElements(
        r1.x(), r1.y(), r1.z(),  // Position
        solution.get_initial_velocity().x(),
        solution.get_initial_velocity().y(),
        solution.get_initial_velocity().z()   // Velocity
    );

    State initialState(initialElements, Time(0.0 * s), earthSystem);

    // Propagate for the time of flight
    TwoBody equations;  // Keplerian propagation
    State finalState = propagate(initialState, equations, timeOfFlight);

    // Check final position accuracy
    CartesianVector<Distance, ECI> propagatedR2 = finalState.get_position();
    Distance positionError = magnitude(propagatedR2 - r2);

    // Verify solution accuracy
    assert(positionError < 1.0 * m);  // Sub-meter accuracy expected

    std::cout << "Lambert solution validated. Position error: "
              << positionError << std::endl;
}
```

This Lambert solver implementation provides the foundation for comprehensive trajectory design and mission planning capabilities, enabling precise transfer orbit calculations for a wide range of astrodynamics applications.
