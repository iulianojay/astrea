#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

#include "astro/propagation/force_models/Force.hpp"

#include "astro/propagation/force_models/AtmosphericForce.hpp"
#include "astro/propagation/force_models/NBodyForce.hpp"
#include "astro/propagation/force_models/OblatenessForce.hpp"
#include "astro/propagation/force_models/SolarRadiationPressureForce.hpp"


enum class DynamicForce : uint32_t {
    ATMOSPHERIC,
    NBODY,
    OBLATENESS,
    SRP
};

struct EnumClassHash {
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

class ForceModel {
private:

    using UnqForcePtr = std::unique_ptr<Force>;
    using builder_function = std::function<UnqForcePtr()>;

public:
    ForceModel() = default;
    ~ForceModel() = default;

    const UnqForcePtr& build(const DynamicForce& force) {
        if (forces.count(force) == 0) {
            forces[force] = builders.at(force)();
        }
        return forces[force];
    }

    basis_array compute_forces(const double &julianDate, const OrbitalElements &state, const Spacecraft &vehicle, const AstrodynamicsSystem &sys) {
        basis_array sum;
        for (auto& [_, force] : forces) {
            const auto result = force->compute_force(julianDate, state, vehicle, sys);
            for (size_t ii = 0; ii < 3; ++ii) {
                sum[ii] += result[ii];
            }
        }
        return sum;
    }

private:

    std::unordered_map<DynamicForce, builder_function> builders = {
        {DynamicForce::ATMOSPHERIC, std::bind(build_atmospheric)},
        {DynamicForce::NBODY,       std::bind(build_nbody)},
        {DynamicForce::OBLATENESS,  std::bind(build_oblateness)},
        {DynamicForce::SRP,         std::bind(build_srp)}
    };
    std::unordered_map<DynamicForce, UnqForcePtr> forces;

    static UnqForcePtr build_atmospheric() { return UnqForcePtr(new AtmosphericForce()); }
    static UnqForcePtr build_nbody()       { return UnqForcePtr(new NBodyForce()); }
    static UnqForcePtr build_oblateness()  { return UnqForcePtr(new OblatenessForce()); }
    static UnqForcePtr build_srp()         { return UnqForcePtr(new SolarRadiationPressureForce()); }
};