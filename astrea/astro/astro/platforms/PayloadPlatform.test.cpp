/*
 * The GNU Lesser General Public License (LGPL)
 *
 * Copyright (c) 2025 Jay Iuliano
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtest/gtest.h>

#include <math/test_util.hpp>
#include <units/units.hpp>

#include <astro/platforms/PayloadPlatform.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::N;
using mp_units::si::unit_symbols::s;

// Minimal test platform that implements only the bare minimum required by PayloadPlatform
class MinimalTestPlatform : public PayloadPlatform<Thruster> {
  public:
    MinimalTestPlatform() :
        _id(id_counter++)
    {
    }

    // Required pure virtual function from PayloadPlatform
    std::size_t get_id() const override { return _id; }

    // Required pure virtual function from FrameReference
    std::string get_name() const override { return "MinimalTestPlatform"; }
    CartesianVector<Distance, frames::earth::icrf> get_inertial_position(const Date& date) const override
    {
        return { 0.0 * km, 0.0 * km, 0.0 * km };
    }
    CartesianVector<Velocity, frames::earth::icrf> get_inertial_velocity(const Date& date) const override
    {
        return { 0.0 * (km / s), 0.0 * (km / s), 0.0 * (km / s) };
    }

  private:
    std::size_t _id;
    static std::size_t id_counter;
};

// Static member initialization
std::size_t MinimalTestPlatform::id_counter = 1;

class PayloadPlatformTest : public testing::Test {
  public:
    PayloadPlatformTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    Force thrust1{ 1.0 * N };
    Force thrust2{ 2.0 * N };
    Force thrust3{ 3.0 * N };
    astro::RadiusVector<astro::frames::dynamic::ric> boresight1{ -1.0 * km, 0.0 * km, 0.0 * km };
    astro::RadiusVector<astro::frames::dynamic::ric> boresight2{ 0.0 * km, -1.0 * km, 0.0 * km };
    ThrusterParameters params1{ thrust1, boresight1 };
    ThrusterParameters params2{ thrust2, boresight2 };
    ThrusterParameters params3{ thrust3 };
    MinimalTestPlatform platform;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(PayloadPlatformTest, GetId)
{
    std::size_t id = platform.get_id();
    ASSERT_GT(id, 0u);
}

TEST_F(PayloadPlatformTest, GetMass)
{
    Mass mass = platform.get_mass();
    ASSERT_EQ(mass.numerical_value_in(kg), 0.0);
}

TEST_F(PayloadPlatformTest, AttachSinglePayload)
{
    ASSERT_NO_THROW(platform.attach_payload(params1));
    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);
}

TEST_F(PayloadPlatformTest, AttachMultiplePayloadsIndividually)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);
    platform.attach_payload(params3);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 3u);
}

TEST_F(PayloadPlatformTest, AttachPayloadsVectorEmpty)
{
    std::vector<ThrusterParameters> emptyParams;
    ASSERT_NO_THROW(platform.attach_payloads(emptyParams));
    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 0u);
}

TEST_F(PayloadPlatformTest, AttachPayloadsVectorSingle)
{
    std::vector<ThrusterParameters> paramVec = { params1 };
    platform.attach_payloads(paramVec);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);
}

TEST_F(PayloadPlatformTest, AttachPayloadsVectorMultiple)
{
    std::vector<ThrusterParameters> paramVec = { params1, params2, params3 };
    platform.attach_payloads(paramVec);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 3u);
}

TEST_F(PayloadPlatformTest, GetPayloadsEmpty)
{
    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 0u);
    ASSERT_TRUE(payloads.empty());
}

TEST_F(PayloadPlatformTest, GetPayloadsNonEmpty)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 2u);
    ASSERT_FALSE(payloads.empty());
}

TEST_F(PayloadPlatformTest, GetPayloadsConst)
{
    platform.attach_payload(params1);

    const MinimalTestPlatform& constPlatform = platform;
    const auto& payloads                     = constPlatform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);
}

TEST_F(PayloadPlatformTest, PayloadParentAfterAttachment)
{
    platform.attach_payload(params1);
    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);

    const auto* parent = payloads[0].get_parent();
    ASSERT_NE(parent, nullptr);
    ASSERT_EQ(parent, &platform);
}

TEST_F(PayloadPlatformTest, MultiplePayloadsHaveCorrectParent)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);
    platform.attach_payload(params3);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 3u);

    for (const auto& payload : payloads) {
        const auto* parent = payload.get_parent();
        ASSERT_NE(parent, nullptr);
        ASSERT_EQ(parent, &platform);
    }
}

TEST_F(PayloadPlatformTest, PayloadParametersPreserved)
{
    platform.attach_payload(params1);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);

    auto retrievedParams = payloads[0].get_parameters();
    ASSERT_EQ_QUANTITY(retrievedParams.get_thrust(), thrust1, REL_TOL);

    auto boresight = retrievedParams.get_boresight();
    ASSERT_EQ_QUANTITY(boresight.get_x(), boresight1.get_x(), REL_TOL);
    ASSERT_EQ_QUANTITY(boresight.get_y(), boresight1.get_y(), REL_TOL);
    ASSERT_EQ_QUANTITY(boresight.get_z(), boresight1.get_z(), REL_TOL);
}

TEST_F(PayloadPlatformTest, CopyConstructor)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    MinimalTestPlatform platformCopy(platform);

    auto& originalPayloads = platform.get_payloads();
    auto& copiedPayloads   = platformCopy.get_payloads();

    ASSERT_EQ(originalPayloads.size(), copiedPayloads.size());
    ASSERT_EQ(copiedPayloads.size(), 2u);

    // Check that payloads in copy have correct parent
    for (const auto& payload : copiedPayloads) {
        ASSERT_EQ(payload.get_parent(), &platformCopy);
    }
}

TEST_F(PayloadPlatformTest, MoveConstructor)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    MinimalTestPlatform platformMoved(std::move(platform));

    auto& movedPayloads = platformMoved.get_payloads();
    ASSERT_EQ(movedPayloads.size(), 2u);

    // Check that payloads have correct parent after move
    for (const auto& payload : movedPayloads) {
        ASSERT_EQ(payload.get_parent(), &platformMoved);
    }
}

TEST_F(PayloadPlatformTest, CopyAssignment)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    MinimalTestPlatform platformCopy;
    platformCopy = platform;

    auto& originalPayloads = platform.get_payloads();
    auto& copiedPayloads   = platformCopy.get_payloads();

    ASSERT_EQ(originalPayloads.size(), copiedPayloads.size());
    ASSERT_EQ(copiedPayloads.size(), 2u);

    // Check that payloads in copy have correct parent
    for (const auto& payload : copiedPayloads) {
        ASSERT_EQ(payload.get_parent(), &platformCopy);
    }
}

TEST_F(PayloadPlatformTest, MoveAssignment)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    MinimalTestPlatform platformMoved;
    platformMoved = std::move(platform);

    auto& movedPayloads = platformMoved.get_payloads();
    ASSERT_EQ(movedPayloads.size(), 2u);

    // Check that payloads have correct parent after move
    for (const auto& payload : movedPayloads) {
        ASSERT_EQ(payload.get_parent(), &platformMoved);
    }
}

TEST_F(PayloadPlatformTest, SelfAssignment)
{
    platform.attach_payload(params1);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wself-assign-overloaded"
    platform = platform;
#pragma GCC diagnostic pop

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 1u);

    // Parent should still be correct
    ASSERT_EQ(payloads[0].get_parent(), &platform);
}

TEST_F(PayloadPlatformTest, AttachPayloadsAfterCopy)
{
    platform.attach_payload(params1);
    MinimalTestPlatform platformCopy(platform);

    // Add another payload to the copy
    platformCopy.attach_payload(params2);

    auto& originalPayloads = platform.get_payloads();
    auto& copiedPayloads   = platformCopy.get_payloads();

    ASSERT_EQ(originalPayloads.size(), 1u);
    ASSERT_EQ(copiedPayloads.size(), 2u);
}

TEST_F(PayloadPlatformTest, ModifyPayloadsInVector)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 2u);

    // Access individual payloads and verify they work
    for (auto& payload : payloads) {
        ASSERT_GE(payload.get_id(), 0u);
        ASSERT_EQ(payload.get_parent(), &platform);
    }
}

TEST_F(PayloadPlatformTest, LargeNumberOfPayloads)
{
    const size_t numPayloads = 100;
    std::vector<ThrusterParameters> paramVec;

    for (size_t i = 0; i < numPayloads; ++i) {
        paramVec.emplace_back(ThrusterParameters{ (i + 1.0) * N });
    }

    platform.attach_payloads(paramVec);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), numPayloads);

    // Verify all have correct parent
    for (const auto& payload : payloads) {
        ASSERT_EQ(payload.get_parent(), &platform);
    }
}

TEST_F(PayloadPlatformTest, PayloadIdsAreUnique)
{
    platform.attach_payload(params1);
    platform.attach_payload(params2);
    platform.attach_payload(params3);

    auto& payloads = platform.get_payloads();
    ASSERT_EQ(payloads.size(), 3u);

    std::size_t id1 = payloads[0].get_id();
    std::size_t id2 = payloads[1].get_id();
    std::size_t id3 = payloads[2].get_id();

    // All three should have different IDs due to different thrust values
    ASSERT_NE(id1, id2);
    ASSERT_NE(id2, id3);
    ASSERT_NE(id1, id3);
}
