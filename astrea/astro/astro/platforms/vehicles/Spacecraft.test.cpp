#include <gtest/gtest.h>

#include <astro/astro.hpp>

using namespace astrea;
using namespace astro;
using namespace mp_units;

using mp_units::angular::unit_symbols::deg;
using mp_units::angular::unit_symbols::rad;
using mp_units::si::unit_symbols::kg;
using mp_units::si::unit_symbols::km;
using mp_units::si::unit_symbols::m;
using mp_units::si::unit_symbols::s;

class SpacecraftTest : public testing::Test {
  public:
    SpacecraftTest() = default;
    void SetUp() override
    {
        StateHistory history;
        history[Date()] = State();
        spacecraftWithHistory.store_state_history(history);
    }

    AstrodynamicsSystem sys;
    Spacecraft spacecraft;
    Spacecraft spacecraftWithHistory;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(SpacecraftTest, DefaultConstructor) { ASSERT_NO_THROW(Spacecraft()); }

TEST_F(SpacecraftTest, CopyConstructor) { ASSERT_NO_THROW(Spacecraft s(spacecraft)); }

TEST_F(SpacecraftTest, GpConstructor)
{
    GeneralPerturbations gp;
    ASSERT_ANY_THROW(Spacecraft s(gp, sys));

    gp.NORAD_CAT_ID   = 25544;
    gp.OBJECT_NAME    = "ISS";
    gp.SEMIMAJOR_AXIS = 6786.0;
    gp.ECCENTRICITY   = 0.001;
    gp.INCLINATION    = 51.6;
    gp.RA_OF_ASC_NODE = 0.0;
    ASSERT_ANY_THROW(Spacecraft s(gp, sys));

    gp.ARG_OF_PERICENTER = 0.0;
    gp.MEAN_ANOMALY      = 0.0;
    ASSERT_NO_THROW(Spacecraft s(gp, sys));
}

TEST_F(SpacecraftTest, AssignmentOperator)
{
    Spacecraft other;
    ASSERT_NO_THROW(other = spacecraft);
}

TEST_F(SpacecraftTest, EqualityOperator)
{
    Spacecraft other = spacecraft;
    ASSERT_TRUE(spacecraft == other);
    other.set_name("DifferentName");
    ASSERT_FALSE(spacecraft == other);
}

TEST_F(SpacecraftTest, UpdateState)
{
    State state;
    ASSERT_NO_THROW(spacecraft.update_state(state));
}

TEST_F(SpacecraftTest, GetState) { ASSERT_EQ(spacecraft.get_state(), State()); }

TEST_F(SpacecraftTest, GetInitialState) { ASSERT_EQ(spacecraft.get_initial_state(), State()); }

TEST_F(SpacecraftTest, GetMass) { ASSERT_EQ(spacecraft.get_mass(), Spacecraft::DEFAULT_MASS); }

TEST_F(SpacecraftTest, GetRamArea) { ASSERT_EQ(spacecraft.get_ram_area(), Spacecraft::DEFAULT_RAM_AREA); }

TEST_F(SpacecraftTest, GetLiftArea) { ASSERT_EQ(spacecraft.get_lift_area(), Spacecraft::DEFAULT_LIFT_AREA); }

TEST_F(SpacecraftTest, GetSolarArea) { ASSERT_EQ(spacecraft.get_solar_area(), Spacecraft::DEFAULT_SOLAR_AREA); }

TEST_F(SpacecraftTest, GetCoefficientOfDrag)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_drag(), Spacecraft::DEFAULT_COEFFICIENT_OF_DRAG);
}

TEST_F(SpacecraftTest, GetCoefficientOfLift)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_lift(), Spacecraft::DEFAULT_COEFFICIENT_OF_LIFT);
}

TEST_F(SpacecraftTest, GetCoefficientOfReflectivity)
{
    ASSERT_EQ(spacecraft.get_coefficient_of_reflectivity(), Spacecraft::DEFAULT_COEFFICIENT_OF_REFLECTIVITY);
}

TEST_F(SpacecraftTest, GetName) { ASSERT_TRUE(spacecraft.get_name().empty()); }

TEST_F(SpacecraftTest, GetId) { ASSERT_NO_THROW(spacecraft.get_id()); }

TEST_F(SpacecraftTest, SetMass)
{
    Mass newMass = 1234.5 * kg;
    spacecraft.set_mass(newMass);
    ASSERT_EQ(spacecraft.get_mass(), newMass);
}

TEST_F(SpacecraftTest, SetCoefficientOfDrag)
{
    Unitless newCd = 3.3 * mp_units::one;
    spacecraft.set_coefficient_of_drag(newCd);
    ASSERT_EQ(spacecraft.get_coefficient_of_drag(), newCd);
}

TEST_F(SpacecraftTest, SetCoefficientOfLift)
{
    Unitless newCl = 2.2 * mp_units::one;
    spacecraft.set_coefficient_of_lift(newCl);
    ASSERT_EQ(spacecraft.get_coefficient_of_lift(), newCl);
}

TEST_F(SpacecraftTest, SetCoefficientOfReflectivity)
{
    Unitless newCr = 4.4 * mp_units::one;
    spacecraft.set_coefficient_of_reflectivity(newCr);
    ASSERT_EQ(spacecraft.get_coefficient_of_reflectivity(), newCr);
}

TEST_F(SpacecraftTest, SetRamArea)
{
    SurfaceArea newArea = 5.5 * mp_units::pow<2>(m);
    spacecraft.set_ram_area(newArea);
    ASSERT_EQ(spacecraft.get_ram_area(), newArea);
}

TEST_F(SpacecraftTest, SetSolarArea)
{
    SurfaceArea newArea = 6.6 * mp_units::pow<2>(m);
    spacecraft.set_solar_area(newArea);
    ASSERT_EQ(spacecraft.get_solar_area(), newArea);
}

TEST_F(SpacecraftTest, SetLiftArea)
{
    SurfaceArea newArea = 7.7 * mp_units::pow<2>(m);
    spacecraft.set_lift_area(newArea);
    ASSERT_EQ(spacecraft.get_lift_area(), newArea);
}

TEST_F(SpacecraftTest, SetName)
{
    std::string newName = "TestCraft";
    spacecraft.set_name(newName);
    ASSERT_EQ(spacecraft.get_name(), newName);
}

TEST_F(SpacecraftTest, GetStateHistory)
{
    ASSERT_EQ(spacecraftWithHistory.get_state_history()[Date()], State());
    ASSERT_EQ(static_cast<const Spacecraft&>(spacecraftWithHistory).get_state_history().at(Date()), State());
}

TEST_F(SpacecraftTest, GetCartesianState)
{
    ASSERT_ANY_THROW(spacecraft.get_cartesian_state(Date()));
    ASSERT_NO_THROW(spacecraftWithHistory.get_cartesian_state(Date()));
}

TEST_F(SpacecraftTest, GetInertialPosition)
{
    ASSERT_ANY_THROW(spacecraft.get_inertial_position(Date()));
    ASSERT_NO_THROW(spacecraftWithHistory.get_inertial_position(Date()));
}

TEST_F(SpacecraftTest, GetInertialVelocity)
{
    ASSERT_ANY_THROW(spacecraft.get_inertial_velocity(Date()));
    ASSERT_NO_THROW(spacecraftWithHistory.get_inertial_velocity(Date()));
}
