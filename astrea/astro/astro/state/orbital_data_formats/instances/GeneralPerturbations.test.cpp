#include <astro/astro.hpp>
#include <astro/state/orbital_data_formats/instances/GeneralPerturbations.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace astrea;
using namespace astro;

class GeneralPerturbationsTest : public testing::Test {
  public:
    GeneralPerturbationsTest() = default;
    void SetUp() override
    {
        data = { { "APOAPSIS", "500.0" },
                 { "ARG_OF_PERICENTER", "120.0" },
                 { "BSTAR", "0.0001" },
                 { "CCSDS_OMM_VERS", "2.0" },
                 { "CENTER_NAME", "EARTH" },
                 { "CLASSIFICATION_TYPE", "U" },
                 { "COMMENT", "Test satellite" },
                 { "COUNTRY_CODE", "USA" },
                 { "CREATION_DATE", "2025-09-08" },
                 { "DECAY_DATE", "2026-01-01" },
                 { "ECCENTRICITY", "0.001" },
                 { "ELEMENT_SET_NO", "1" },
                 { "EPHEMERIS_TYPE", "2" },
                 { "EPOCH", "2025-09-08T00:00:00" },
                 { "FILE", "123456" },
                 { "GP_ID", "99" },
                 { "INCLINATION", "51.6" },
                 { "LAUNCH_DATE", "2025-01-01" },
                 { "MEAN_ANOMALY", "0.0" },
                 { "MEAN_ELEMENT_THEORY", "SGP4" },
                 { "MEAN_MOTION", "15.7" },
                 { "MEAN_MOTION_DDOT", "0.0" },
                 { "MEAN_MOTION_DOT", "0.0" },
                 { "NORAD_CAT_ID", "25544" },
                 { "OBJECT_ID", "1998-067A" },
                 { "OBJECT_NAME", "ISS (ZARYA)" },
                 { "OBJECT_TYPE", "Payload" },
                 { "ORIGINATOR", "NASA" },
                 { "PERIAPSIS", "400.0" },
                 { "PERIOD", "92.0" },
                 { "RA_OF_ASC_NODE", "247.5" },
                 { "RCS_SIZE", "Medium" },
                 { "REF_FRAME", "TEME" },
                 { "REV_AT_EPOCH", "63537" },
                 { "SEMIMAJOR_AXIS", "6786.0" },
                 { "SITE", "KSC" },
                 { "TIME_SYSTEM", "UTC" },
                 { "TLE_LINE0", "ISS (ZARYA)" },
                 { "TLE_LINE1", "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927" },
                 { "TLE_LINE2", "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537" } };
    }

    nlohmann::json data;
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(GeneralPerturbationsTest, DefaultConstructor) { ASSERT_NO_THROW(GeneralPerturbations()); }

TEST_F(GeneralPerturbationsTest, JsonConstructor) { ASSERT_NO_THROW(GeneralPerturbations gp(data)); }

TEST_F(GeneralPerturbationsTest, OutputStreamOperator)
{
    GeneralPerturbations gp;
    std::stringstream ss;
    ss << gp;
    ASSERT_FALSE(ss.str().empty());
}

// Add a test for each public member (getter-like access)
TEST_F(GeneralPerturbationsTest, MemberAccess)
{
    GeneralPerturbations gp(data);
    ASSERT_EQ(gp.DB_ID, -1);
    ASSERT_EQ(gp.GP_ID, 99u);
    ASSERT_EQ(gp.NORAD_CAT_ID, 25544u);
    ASSERT_EQ(gp.CCSDS_OMM_VERS, "2.0");
    ASSERT_EQ(gp.CENTER_NAME, "EARTH");
    ASSERT_EQ(gp.COMMENT, "Test satellite");
    ASSERT_EQ(gp.MEAN_ELEMENT_THEORY, "SGP4");
    ASSERT_EQ(gp.ORIGINATOR, "NASA");
    ASSERT_EQ(gp.REF_FRAME, "TEME");
    ASSERT_EQ(gp.TIME_SYSTEM, "UTC");

    // Optionals
    ASSERT_TRUE(gp.APOAPSIS.has_value());
    ASSERT_DOUBLE_EQ(gp.APOAPSIS.value(), 500.0);

    ASSERT_TRUE(gp.ARG_OF_PERICENTER.has_value());
    ASSERT_DOUBLE_EQ(gp.ARG_OF_PERICENTER.value(), 120.0);

    ASSERT_TRUE(gp.BSTAR.has_value());
    ASSERT_DOUBLE_EQ(gp.BSTAR.value(), 0.0001);

    ASSERT_TRUE(gp.CLASSIFICATION_TYPE.has_value());
    ASSERT_EQ(gp.CLASSIFICATION_TYPE.value(), 'U');

    ASSERT_TRUE(gp.COUNTRY_CODE.has_value());
    ASSERT_EQ(gp.COUNTRY_CODE.value(), "USA");

    ASSERT_TRUE(gp.CREATION_DATE.has_value());
    ASSERT_EQ(gp.CREATION_DATE.value(), "2025-09-08");

    ASSERT_TRUE(gp.DECAY_DATE.has_value());
    ASSERT_EQ(gp.DECAY_DATE.value(), "2026-01-01");

    ASSERT_TRUE(gp.ECCENTRICITY.has_value());
    ASSERT_DOUBLE_EQ(gp.ECCENTRICITY.value(), 0.001);

    ASSERT_TRUE(gp.ELEMENT_SET_NO.has_value());
    ASSERT_EQ(gp.ELEMENT_SET_NO.value(), 1);

    ASSERT_TRUE(gp.EPHEMERIS_TYPE.has_value());
    ASSERT_EQ(gp.EPHEMERIS_TYPE.value(), 2);

    ASSERT_TRUE(gp.EPOCH.has_value());
    ASSERT_EQ(gp.EPOCH.value(), "2025-09-08T00:00:00");

    ASSERT_TRUE(gp.FILE.has_value());
    ASSERT_EQ(gp.FILE.value(), 123456);

    ASSERT_TRUE(gp.INCLINATION.has_value());
    ASSERT_DOUBLE_EQ(gp.INCLINATION.value(), 51.6);

    ASSERT_TRUE(gp.LAUNCH_DATE.has_value());
    ASSERT_EQ(gp.LAUNCH_DATE.value(), "2025-01-01");

    ASSERT_TRUE(gp.MEAN_ANOMALY.has_value());
    ASSERT_DOUBLE_EQ(gp.MEAN_ANOMALY.value(), 0.0);

    ASSERT_TRUE(gp.MEAN_MOTION.has_value());
    ASSERT_DOUBLE_EQ(gp.MEAN_MOTION.value(), 15.7);

    ASSERT_TRUE(gp.MEAN_MOTION_DDOT.has_value());
    ASSERT_DOUBLE_EQ(gp.MEAN_MOTION_DDOT.value(), 0.0);

    ASSERT_TRUE(gp.MEAN_MOTION_DOT.has_value());
    ASSERT_DOUBLE_EQ(gp.MEAN_MOTION_DOT.value(), 0.0);

    ASSERT_TRUE(gp.OBJECT_ID.has_value());
    ASSERT_EQ(gp.OBJECT_ID.value(), "1998-067A");

    ASSERT_TRUE(gp.OBJECT_NAME.has_value());
    ASSERT_EQ(gp.OBJECT_NAME.value(), "ISS (ZARYA)");

    ASSERT_TRUE(gp.OBJECT_TYPE.has_value());
    ASSERT_EQ(gp.OBJECT_TYPE.value(), "Payload");

    ASSERT_TRUE(gp.PERIAPSIS.has_value());
    ASSERT_DOUBLE_EQ(gp.PERIAPSIS.value(), 400.0);

    ASSERT_TRUE(gp.PERIOD.has_value());
    ASSERT_DOUBLE_EQ(gp.PERIOD.value(), 92.0);

    ASSERT_TRUE(gp.RA_OF_ASC_NODE.has_value());
    ASSERT_DOUBLE_EQ(gp.RA_OF_ASC_NODE.value(), 247.5);

    ASSERT_TRUE(gp.RCS_SIZE.has_value());
    ASSERT_EQ(gp.RCS_SIZE.value(), "Medium");

    ASSERT_TRUE(gp.REV_AT_EPOCH.has_value());
    ASSERT_EQ(gp.REV_AT_EPOCH.value(), 63537u);

    ASSERT_TRUE(gp.SEMIMAJOR_AXIS.has_value());
    ASSERT_DOUBLE_EQ(gp.SEMIMAJOR_AXIS.value(), 6786.0);

    ASSERT_TRUE(gp.SITE.has_value());
    ASSERT_EQ(gp.SITE.value(), "KSC");

    ASSERT_TRUE(gp.TLE_LINE0.has_value());
    ASSERT_EQ(gp.TLE_LINE0.value(), "ISS (ZARYA)");

    ASSERT_TRUE(gp.TLE_LINE1.has_value());
    ASSERT_EQ(gp.TLE_LINE1.value(), "1 25544U 98067A   08264.51782528 -.00002182  00000-0 -11606-4 0  2927");

    ASSERT_TRUE(gp.TLE_LINE2.has_value());
    ASSERT_EQ(gp.TLE_LINE2.value(), "2 25544  51.6416 247.4627 0006703 130.5360 325.0288 15.72125391563537");
}
