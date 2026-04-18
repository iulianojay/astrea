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

#include <math/operations.hpp>
#include <units/units.hpp>

#include <astro/platforms/Payload.hpp>
#include <astro/platforms/thrusters/Thruster.hpp>
#include <astro/platforms/vehicles/Spacecraft.hpp>
#include <astro/state/StateHistory.hpp>
#include <tests/utilities/comparisons.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::N;

class PayloadParametersTest : public testing::Test {
  public:
    PayloadParametersTest() {}

    void SetUp() override {}

    const Unitless REL_TOL = 1.0e-6;

    astro::RadiusVector<astro::frames::dynamic::ric> boresight{ -1.0 * km, 0.0 * km, 0.0 * km };
    astro::RadiusVector<astro::frames::dynamic::ric> attachmentPoint{ 0.0 * km, 0.0 * km, 0.0 * km };
};

class PayloadTest : public testing::Test {
  public:
    PayloadTest() {}

    void SetUp() override
    {
        StateHistory history;
        history.insert(State());
        satWithHistory.set_state_history(history);
    }

    const Unitless REL_TOL = 1.0e-6;

    Thrust thrust{ 1.0 * N };
    astro::RadiusVector<astro::frames::dynamic::ric> boresight{ -1.0 * km, 0.0 * km, 0.0 * km };
    astro::RadiusVector<astro::frames::dynamic::ric> attachmentPoint{ 0.5 * km, 0.2 * km, 0.1 * km };
    ThrusterParameters params{ thrust, boresight, attachmentPoint };
    ThrusterParameters paramsCenter{ thrust, boresight, CENTER };
    Spacecraft sat;
    Spacecraft satWithHistory;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// PayloadParameters Tests

TEST_F(PayloadParametersTest, DefaultBoresight)
{
    ThrusterParameters params{ 1.0 * N };
    auto boresightVec = params.get_boresight();
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_x(), Distance(-1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_z(), Distance(0.0 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, DefaultAttachmentPoint)
{
    ThrusterParameters params{ 1.0 * N };
    auto attachPt = params.get_attachment_point();
    ASSERT_TRUE(math::nearly_equal(attachPt.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(attachPt.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(attachPt.get_z(), Distance(0.0 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, CustomBoresight)
{
    astro::RadiusVector<astro::frames::dynamic::ric> customBoresight{ 1.0 * km, 2.0 * km, 3.0 * km };
    ThrusterParameters params{ 1.0 * N, customBoresight };
    auto boresightVec = params.get_boresight();
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_x(), Distance(1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_y(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(boresightVec.get_z(), Distance(3.0 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, CustomAttachmentPoint)
{
    astro::RadiusVector<astro::frames::dynamic::ric> customAttach{ 0.5 * km, 0.6 * km, 0.7 * km };
    ThrusterParameters params{ 1.0 * N, NADIR_RIC, customAttach };
    auto attachPt = params.get_attachment_point();
    ASSERT_TRUE(math::nearly_equal(attachPt.get_x(), Distance(0.5 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(attachPt.get_y(), Distance(0.6 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(attachPt.get_z(), Distance(0.7 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, GetBoresight)
{
    ThrusterParameters params{ 1.0 * N, boresight, attachmentPoint };
    auto retrievedBoresight = params.get_boresight();
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_x(), boresight.get_x(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_y(), boresight.get_y(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_z(), boresight.get_z(), REL_TOL));
}

TEST_F(PayloadParametersTest, GetAttachmentPoint)
{
    ThrusterParameters params{ 1.0 * N, boresight, attachmentPoint };
    auto retrievedAttachment = params.get_attachment_point();
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_x(), attachmentPoint.get_x(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_y(), attachmentPoint.get_y(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_z(), attachmentPoint.get_z(), REL_TOL));
}

TEST_F(PayloadParametersTest, SetBoresight)
{
    ThrusterParameters params{ 1.0 * N };
    astro::RadiusVector<astro::frames::dynamic::ric> newBoresight{ 2.0 * km, 3.0 * km, 4.0 * km };
    params.set_boresight(newBoresight);
    auto retrievedBoresight = params.get_boresight();
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_x(), Distance(2.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_y(), Distance(3.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_z(), Distance(4.0 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, SetAttachmentPoint)
{
    ThrusterParameters params{ 1.0 * N };
    astro::RadiusVector<astro::frames::dynamic::ric> newAttachment{ 1.5 * km, 2.5 * km, 3.5 * km };
    params.set_attachment_point(newAttachment);
    auto retrievedAttachment = params.get_attachment_point();
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_x(), Distance(1.5 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_y(), Distance(2.5 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_z(), Distance(3.5 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, NADIRRICConstant)
{
    ASSERT_TRUE(math::nearly_equal(NADIR_RIC.get_x(), Distance(-1.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(NADIR_RIC.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(NADIR_RIC.get_z(), Distance(0.0 * km), REL_TOL));
}

TEST_F(PayloadParametersTest, CENTERConstant)
{
    ASSERT_TRUE(math::nearly_equal(CENTER.get_x(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(CENTER.get_y(), Distance(0.0 * km), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(CENTER.get_z(), Distance(0.0 * km), REL_TOL));
}

// Payload Tests (using Thruster as concrete implementation)

TEST_F(PayloadTest, Constructor) { ASSERT_NO_THROW(Thruster(sat, params)); }

TEST_F(PayloadTest, GetParent)
{
    Thruster thruster(sat, params);
    const auto* parent = thruster.get_parent();
    ASSERT_NE(parent, nullptr);
    ASSERT_EQ(parent, &sat);
}

TEST_F(PayloadTest, GetParameters)
{
    Thruster thruster(sat, params);
    auto retrievedParams     = thruster.get_parameters();
    auto retrievedBoresight  = retrievedParams.get_boresight();
    auto retrievedAttachment = retrievedParams.get_attachment_point();

    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_x(), boresight.get_x(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_y(), boresight.get_y(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedBoresight.get_z(), boresight.get_z(), REL_TOL));

    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_x(), attachmentPoint.get_x(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_y(), attachmentPoint.get_y(), REL_TOL));
    ASSERT_TRUE(math::nearly_equal(retrievedAttachment.get_z(), attachmentPoint.get_z(), REL_TOL));
}

TEST_F(PayloadTest, GetId)
{
    Thruster thruster(sat, params);
    std::size_t id = thruster.get_id();
    ASSERT_GE(id, 0u);
}

TEST_F(PayloadTest, DifferentThrustersHaveDifferentIds)
{
    Thruster thruster1(sat, params);
    ThrusterParameters params2{ 2.0 * N };
    Thruster thruster2(sat, params2);

    // Different thrust values should produce different IDs
    ASSERT_NE(thruster1.get_id(), thruster2.get_id());
}

TEST_F(PayloadTest, PayloadWithDifferentParent)
{
    Spacecraft sat2;
    Thruster thruster1(sat, params);
    Thruster thruster2(sat2, params);

    // Both should be valid but have different parents
    ASSERT_NE(thruster1.get_parent(), thruster2.get_parent());
    ASSERT_EQ(thruster1.get_parent(), &sat);
    ASSERT_EQ(thruster2.get_parent(), &sat2);
}

TEST_F(PayloadTest, ThrusterParametersGetThrust)
{
    ThrusterParameters thrusterParams{ thrust, boresight, attachmentPoint };
    ASSERT_TRUE(math::nearly_equal(thrusterParams.get_thrust(), thrust, REL_TOL));
}

TEST_F(PayloadTest, MultiplePayloadsWithSameParameters)
{
    Thruster thruster1(sat, params);
    Thruster thruster2(sat, params);

    // Same parameters should not produce same ID
    ASSERT_NE(thruster1.get_id(), thruster2.get_id());

    // But they should be different objects
    ASSERT_NE(&thruster1, &thruster2);
}

TEST_F(PayloadTest, GetName)
{
    Thruster thruster(sat, params);
    ASSERT_EQ(thruster.get_name(), "Payload");
}

TEST_F(PayloadTest, GetInertialPositionThrowsWithoutHistory)
{
    Thruster thruster(sat, paramsCenter);
    ASSERT_ANY_THROW({ auto pos = thruster.get_inertial_position(Date()); });
}

TEST_F(PayloadTest, GetInertialPositionNoThrowWithHistory)
{
    Thruster thruster(satWithHistory, paramsCenter);
    ASSERT_NO_THROW({ auto pos = thruster.get_inertial_position(Date()); });
}

TEST_F(PayloadTest, GetInertialPositionMatchesParentWithCenterAttachment)
{
    Thruster thruster(satWithHistory, paramsCenter);
    const auto payloadPos = thruster.get_inertial_position(Date());
    const auto parentPos  = satWithHistory.get_inertial_position(Date());
    ASSERT_EQ_QUANTITY(payloadPos.get_x(), parentPos.get_x(), REL_TOL);
    ASSERT_EQ_QUANTITY(payloadPos.get_y(), parentPos.get_y(), REL_TOL);
    ASSERT_EQ_QUANTITY(payloadPos.get_z(), parentPos.get_z(), REL_TOL);
}

TEST_F(PayloadTest, GetInertialVelocityThrowsWithoutHistory)
{
    Thruster thruster(sat, params);
    ASSERT_ANY_THROW({ auto vel = thruster.get_inertial_velocity(Date()); });
}

TEST_F(PayloadTest, GetInertialVelocityNoThrowWithHistory)
{
    Thruster thruster(satWithHistory, params);
    ASSERT_NO_THROW({ auto vel = thruster.get_inertial_velocity(Date()); });
}

TEST_F(PayloadTest, GetInertialVelocityMatchesParent)
{
    Thruster thruster(satWithHistory, params);
    const auto payloadVel = thruster.get_inertial_velocity(Date());
    const auto parentVel  = satWithHistory.get_inertial_velocity(Date());
    ASSERT_EQ_QUANTITY(payloadVel.get_x(), parentVel.get_x(), REL_TOL);
    ASSERT_EQ_QUANTITY(payloadVel.get_y(), parentVel.get_y(), REL_TOL);
    ASSERT_EQ_QUANTITY(payloadVel.get_z(), parentVel.get_z(), REL_TOL);
}
