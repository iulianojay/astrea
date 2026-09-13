# Lambert Solutions

Astrea provides a robust implementation of Lambert's problem and it's various iterations. This includes single revolution transfers, multi-revolution transfers, and minimum energy solutions, etc. The LambertSolver class provides a static interface for solving Lambert's problem, allowing users to compute the required velocity vectors for a transfer orbit between two position vectors in space.

The `LambertSolver` provides static methods for solving Lambert's problem. The following forms are currently supported:

1. Solve for the final state given an initial state and a time of flight.
```cpp
Cartesian<frame> solve(
    const Cartesian<frame>& state0, 
    const Time& dt, 
    const GravParam& mu
)
```

2. Solve for initial and final velocity vectors given two position vectors, a time of flight, and a direction.
```cpp
std::pair<VelocityVector<frame>, VelocityVector<frame>> solve(
    const RadiusVector<frame>& r0, 
    const RadiusVector<frame>& rf, 
    const Time& dt, 
    const GravParam& mu, 
    const OrbitDirection& direction
)
```

3. Solve for initial and final velocity vectors given two position vectors, a direction, and a specific solution type (e.g., minimum energy or minimum time).
```cpp
Solution<frame> solve(
    const RadiusVector<frame>& r0, 
    const RadiusVector<frame>& rf, 
    const GravParam& mu, 
    const OrbitDirection& direction, 
    const SolutionType& solutionType
)
```

4. Solve for initial and final velocity vectors given two position vectors, a time of flight, a direction, a specific number of revolutions, and the multi-rev "branch" of the target solution.
```cpp
std::pair<VelocityVector<frame>, VelocityVector<frame>> solve(
    const RadiusVector<frame>& r0, 
    const RadiusVector<frame>& rf, 
    const Time& dt, 
    const GravParam& mu, 
    const OrbitDirection& direction, 
    unsigned N, 
    const MultiRevBranch& branch
)
```

These are not exhaustive of all possible Lambert problems, but it covers the most common use cases.
