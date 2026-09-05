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

#include <gtest/gtest.h>

#include <filesystem>

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Vehicle.hpp>
#include <astro/propagation/force_models/ForceModel.hpp>
#include <astro/propagation/force_models/PerturbingForce.hpp>
#include <astro/propagation/force_models/space_weather/SpaceWeatherData.hpp>
#include <astro/propagation/force_models/space_weather/SpaceWeatherProvider.hpp>
#include <astro/state/State.hpp>
#include <astro/state/orbital_elements/Cartesian.hpp>
#include <astro/systems/system_utilities.hpp>
#include <astro/time/Date.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

class DummyForce : public PerturbingForce {
  public:
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        return Perturbation{ .force = { 0.0 * N }, .torque = { 0.0 * N * m } };
    }

    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<DummyForce>(*this); }
};

class ProviderAwareDummyForce : public PerturbingForce {
  public:
    Perturbation compute_perturbation(const State& state, const Vehicle& vehicle) const override
    {
        return Perturbation{ .force = { 0.0 * N }, .torque = { 0.0 * N * m } };
    }

    std::unique_ptr<PerturbingForce> clone() const override { return std::make_unique<ProviderAwareDummyForce>(*this); }

    void bind_space_weather_provider(std::shared_ptr<const SpaceWeatherProvider> provider) override
    {
        _provider = std::move(provider);
    }

    [[nodiscard]] const std::shared_ptr<const SpaceWeatherProvider>& provider() const noexcept { return _provider; }

  private:
    std::shared_ptr<const SpaceWeatherProvider> _provider;
};

class ForceModelTest : public testing::Test {
  public:
    ForceModelTest() {};
    void SetUp() override {}

    DummyForce force;
    Date date;
    Vehicle vehicle;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


TEST(ForceModelTest, DefaultConstructor) { ASSERT_NO_THROW(ForceModel()); }

TEST(ForceModelTest, AddForce)
{
    ForceModel model;
    auto& ptr = model.add<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelTest, ComputeForces)
{
    ForceModel model;
    model.add<DummyForce>();

    Vehicle vehicle;
    Date date;
    Cartesian<frames::primary> cart;
    State state(cart, date);

    auto [accel, torque] = model.compute_perturbations(state, vehicle);
    EXPECT_EQ(accel.get_x(), 0.0 * N);
    EXPECT_EQ(accel.get_y(), 0.0 * N);
    EXPECT_EQ(accel.get_z(), 0.0 * N);
    EXPECT_EQ(torque.get_x(), 0.0 * N * m);
    EXPECT_EQ(torque.get_y(), 0.0 * N * m);
    EXPECT_EQ(torque.get_z(), 0.0 * N * m);
}

TEST(ForceModelTest, AtByName)
{
    ForceModel model;
    model.add<DummyForce>();
    std::string name = typeid(DummyForce).name();
    auto& ptr        = model.at(name);
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelTest, GetByType)
{
    ForceModel model;
    model.add<DummyForce>();
    auto& ptr = model.get<DummyForce>();
    EXPECT_NE(ptr.get(), nullptr);
}

TEST(ForceModelTest, ConstructWithExplicitSpaceWeatherDataPtr)
{
    auto data = std::make_shared<const SpaceWeatherData>();
    ForceModel model(data);

    ASSERT_NE(model.space_weather_provider(), nullptr);
    EXPECT_EQ(model.space_weather_provider()->data(), data);
}

TEST(ForceModelTest, ConstructWithForwardedSpaceWeatherDataArgs)
{
    const std::filesystem::path infile = std::string(_ASTRO_ROOT_) + "/data/space_weather/SpaceWeather-All-v1.2.txt";
    ForceModel model(std::in_place, infile);

    ASSERT_NE(model.space_weather_provider(), nullptr);
    ASSERT_NE(model.space_weather_provider()->data(), nullptr);
    EXPECT_GT(model.space_weather_provider()->data()->size(), 0U);
}

TEST(ForceModelTest, AddForceBindsProvider)
{
    auto data = std::make_shared<const SpaceWeatherData>();
    ForceModel model(data);

    auto& base = model.add<ProviderAwareDummyForce>();
    auto* ptr  = dynamic_cast<ProviderAwareDummyForce*>(base.get());

    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->provider(), model.space_weather_provider());
}

TEST(ForceModelTest, CopyModelRebindsProviderOnClonedForces)
{
    auto data = std::make_shared<const SpaceWeatherData>();
    ForceModel model(data);
    model.add<ProviderAwareDummyForce>();

    ForceModel copied(model);
    auto& base = copied.get<ProviderAwareDummyForce>();
    auto* ptr  = dynamic_cast<ProviderAwareDummyForce*>(base.get());

    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->provider(), copied.space_weather_provider());
}
