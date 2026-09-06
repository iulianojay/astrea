

# File ForceModel.cpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**propagation**](dir_55ae0edd352c6621ebfa1115f28a0fff.md) **>** [**force\_models**](dir_0ce51a85166db93c377c5b7f000b236c.md) **>** [**ForceModel.cpp**](ForceModel_8cpp.md)

[Go to the documentation of this file](ForceModel_8cpp.md)


```C++
/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025-2026 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <astro/propagation/force_models/ForceModel.hpp>

#include <astro/frames/definitions.hpp>
#include <astro/frames/framework/CartesianVector.hpp>

namespace astrea {
namespace astro {

ForceModel::ForceModel() :
    _spaceWeatherProvider(std::make_shared<SpaceWeatherProvider>())
{
}

ForceModel::ForceModel(std::shared_ptr<const SpaceWeatherData> data) :
    _spaceWeatherProvider(std::make_shared<SpaceWeatherProvider>(std::move(data)))
{
}

ForceModel::ForceModel(SpaceWeatherProvider provider) :
    _spaceWeatherProvider(std::make_shared<SpaceWeatherProvider>(std::move(provider)))
{
}

ForceModel::ForceModel(SpaceWeatherData data) :
    _spaceWeatherProvider(std::make_shared<SpaceWeatherProvider>(std::move(data)))
{
}

ForceModel::ForceModel(const ForceModel& other)
{
    _spaceWeatherProvider = other._spaceWeatherProvider;
    for (const auto& [name, force] : other.forces) {
        auto clonedForce = force->clone();
        clonedForce->bind_space_weather_provider(_spaceWeatherProvider);
        forces.emplace(name, std::move(clonedForce));
    }
}

ForceModel& ForceModel::operator=(const ForceModel& other)
{
    if (this != &other) {
        _spaceWeatherProvider = other._spaceWeatherProvider;
        forces.clear();
        for (const auto& [name, force] : other.forces) {
            auto clonedForce = force->clone();
            clonedForce->bind_space_weather_provider(_spaceWeatherProvider);
            forces.emplace(name, std::move(clonedForce));
        }
    }
    return *this;
}

Perturbation ForceModel::compute_perturbations(const State& state, const Vehicle& vehicle) const
{
    Perturbation sum; // defaults to zero
    for (const auto& [name, force] : forces) {
        const auto result = force->compute_perturbation(state, vehicle);
        for (std::size_t ii = 0; ii < 3; ++ii) {
            sum.force[ii] += result.force[ii];
            sum.torque[ii] += result.torque[ii];
        }
    }
    return sum;
}

const std::unique_ptr<PerturbingForce>& ForceModel::at(const std::string& name) const { return forces.at(name); }


void ForceModel::set_space_weather_provider(std::shared_ptr<const SpaceWeatherProvider> provider)
{
    _spaceWeatherProvider = std::move(provider);
    for (auto& [name, force] : forces) {
        force->bind_space_weather_provider(_spaceWeatherProvider);
    }
}

void ForceModel::set_space_weather_provider(SpaceWeatherProvider provider)
{
    set_space_weather_provider(std::make_shared<SpaceWeatherProvider>(std::move(provider)));
}

void ForceModel::set_space_weather_provider(SpaceWeatherData data)
{
    set_space_weather_provider(std::make_shared<SpaceWeatherProvider>(std::move(data)));
}

} // namespace astro
} // namespace astrea
```


