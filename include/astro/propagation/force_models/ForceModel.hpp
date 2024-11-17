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

    using BuilderFunc = std::function<std::unique_ptr<Force>()>;

public:
    ForceModel() = default;
    ~ForceModel() = default;

    const std::unique_ptr<Force>& build(const DynamicForce& force) {
        if (forces.count(force) == 0) {
            forces[force] = builders.at(force)();
        }
        return forces[force];
    }

    basis_array compute_forces(const double &julianDate, const OrbitalElements &state, const Spacecraft &vehicle, const AstrodynamicsSystem &sys) {
        basis_array sum = {0.0, 0.0, 0.0};
        for (auto& [forceName, force] : forces) {
            if (toggles[forceName]) {
                const auto result = force->compute_force(julianDate, state, vehicle, sys);
                for (size_t ii = 0; ii < 3; ++ii) {
                    sum[ii] += result[ii];
                }
            }
        }
        return sum;
    }

    std::unique_ptr<Force>& operator[](const DynamicForce& force) {
        return forces[force];
    }

    const std::unique_ptr<Force>& at(const DynamicForce& force) const {
        return forces.at(force);
    }

    void toggle_force(DynamicForce force, bool onOff) {
        if (toggles.count(force) > 0) {
            toggles[force] = onOff;
        }
    }

private:

    const std::unordered_map<DynamicForce, BuilderFunc> builders = {
        {DynamicForce::ATMOSPHERIC, build_atmospheric},
        {DynamicForce::NBODY,       build_nbody},
        {DynamicForce::OBLATENESS,  build_oblateness},
        {DynamicForce::SRP,         build_srp}
    };

    std::unordered_map<DynamicForce, std::unique_ptr<Force>> forces;

    std::unordered_map<DynamicForce, bool> toggles {
        {DynamicForce::ATMOSPHERIC, false},
        {DynamicForce::NBODY,       false},
        {DynamicForce::OBLATENESS,  false},
        {DynamicForce::SRP,         false}
    };
};