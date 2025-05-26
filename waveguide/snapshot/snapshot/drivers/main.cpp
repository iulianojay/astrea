#include <iostream>
#include <memory>
#include <optional>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <sqlite_orm/sqlite_orm.h>

#include <astro/time/Date.hpp>

// https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html
struct SpaceTrackGP {
    int DB_ID;
    std::optional<double> APOAPSIS;
    std::optional<long double> ARG_OF_PERICENTER;
    std::optional<long double> BSTAR;
    std::string CCSDS_OMM_VERS;
    std::string CENTER_NAME;
    std::optional<char> CLASSIFICATION_TYPE;
    std::string COMMENT;
    std::optional<std::string> COUNTRY_CODE;
    std::optional<std::string> CREATION_DATE;
    std::optional<std::string> DECAY_DATE;
    std::optional<long double> ECCENTRICITY;
    std::optional<short> ELEMENT_SET_NO;
    std::optional<short unsigned> EPHEMERIS_TYPE;
    std::optional<std::string> EPOCH;
    std::optional<long unsigned> FILE;
    unsigned GP_ID;
    std::optional<long double> INCLINATION;
    std::optional<std::string> LAUNCH_DATE;
    std::optional<double> MEAN_ANOMALY;
    std::string MEAN_ELEMENT_THEORY;
    std::optional<long double> MEAN_MOTION;
    std::optional<long double> MEAN_MOTION_DDOT;
    std::optional<long double> MEAN_MOTION_DOT;
    unsigned NORAD_CAT_ID;
    std::optional<std::string> OBJECT_ID;
    std::optional<std::string> OBJECT_NAME;
    std::optional<std::string> OBJECT_TYPE;
    std::string ORIGINATOR;
    std::optional<double> PERIAPSIS;
    std::optional<double> PERIOD;
    std::optional<long double> RA_OF_ASC_NODE;
    std::optional<std::string> RCS_SIZE;
    std::string REF_FRAME;
    std::optional<unsigned> REV_AT_EPOCH;
    std::optional<double> SEMIMAJOR_AXIS;
    std::optional<std::string> SITE;
    std::string TIME_SYSTEM;
    std::optional<std::string> TLE_LINE0;
    std::optional<std::string> TLE_LINE1;
    std::optional<std::string> TLE_LINE2;
};

int main()
{
    // Build connection and connect
    using namespace sqlite_orm;

    auto storage = make_storage(
        "./waveguide/snapshot/snapshot/data/snapshot.db",
        make_table(
            "SpaceTrackGP",
            make_column("DB_ID", &SpaceTrackGP::DB_ID, primary_key().autoincrement()),
            make_column("APOAPSIS", &SpaceTrackGP::APOAPSIS),
            make_column("ARG_OF_PERICENTER", &SpaceTrackGP::ARG_OF_PERICENTER),
            make_column("BSTAR", &SpaceTrackGP::BSTAR),
            make_column("CCSDS_OMM_VERS", &SpaceTrackGP::CCSDS_OMM_VERS),
            make_column("CENTER_NAME", &SpaceTrackGP::CENTER_NAME),
            make_column("CLASSIFICATION_TYPE", &SpaceTrackGP::CLASSIFICATION_TYPE),
            make_column("COMMENT", &SpaceTrackGP::COMMENT),
            make_column("COUNTRY_CODE", &SpaceTrackGP::COUNTRY_CODE),
            make_column("CREATION_DATE", &SpaceTrackGP::CREATION_DATE),
            make_column("DECAY_DATE", &SpaceTrackGP::DECAY_DATE),
            make_column("ECCENTRICITY", &SpaceTrackGP::ECCENTRICITY),
            make_column("ELEMENT_SET_NO", &SpaceTrackGP::ELEMENT_SET_NO),
            make_column("EPHEMERIS_TYPE", &SpaceTrackGP::EPHEMERIS_TYPE),
            make_column("EPOCH", &SpaceTrackGP::EPOCH),
            make_column("FILE", &SpaceTrackGP::FILE),
            make_column("GP_ID", &SpaceTrackGP::GP_ID, unique()),
            make_column("INCLINATION", &SpaceTrackGP::INCLINATION),
            make_column("LAUNCH_DATE", &SpaceTrackGP::LAUNCH_DATE),
            make_column("MEAN_ANOMALY", &SpaceTrackGP::MEAN_ANOMALY),
            make_column("MEAN_ELEMENT_THEORY", &SpaceTrackGP::MEAN_ELEMENT_THEORY),
            make_column("MEAN_MOTION", &SpaceTrackGP::MEAN_MOTION),
            make_column("MEAN_MOTION_DDOT", &SpaceTrackGP::MEAN_MOTION_DDOT),
            make_column("MEAN_MOTION_DOT", &SpaceTrackGP::MEAN_MOTION_DOT),
            make_column("NORAD_CAT_ID", &SpaceTrackGP::NORAD_CAT_ID, unique()),
            make_column("OBJECT_ID", &SpaceTrackGP::OBJECT_ID),
            make_column("OBJECT_NAME", &SpaceTrackGP::OBJECT_NAME),
            make_column("OBJECT_TYPE", &SpaceTrackGP::OBJECT_TYPE),
            make_column("ORIGINATOR", &SpaceTrackGP::ORIGINATOR),
            make_column("PERIAPSIS", &SpaceTrackGP::PERIAPSIS),
            make_column("PERIOD", &SpaceTrackGP::PERIOD),
            make_column("RA_OF_ASC_NODE", &SpaceTrackGP::RA_OF_ASC_NODE),
            make_column("RCS_SIZE", &SpaceTrackGP::RCS_SIZE),
            make_column("REF_FRAME", &SpaceTrackGP::REF_FRAME),
            make_column("REV_AT_EPOCH", &SpaceTrackGP::REV_AT_EPOCH),
            make_column("SEMIMAJOR_AXIS", &SpaceTrackGP::SEMIMAJOR_AXIS),
            make_column("SITE", &SpaceTrackGP::SITE),
            make_column("TIME_SYSTEM", &SpaceTrackGP::TIME_SYSTEM),
            make_column("TLE_LINE0", &SpaceTrackGP::TLE_LINE0),
            make_column("TLE_LINE1", &SpaceTrackGP::TLE_LINE1),
            make_column("TLE_LINE2", &SpaceTrackGP::TLE_LINE2)
        )
    );
    storage.sync_schema();
    // storage.remove_all<SpaceTrackGP>();

    SpaceTrackGP data{ -1,
                       3821.689,                            //     APOAPSIS - double
                       179.7370,                            //     ARG_OF_PERICENTER - long double
                       0.00006359500000,                    //     BSTAR - long double
                       "3.0",                               //     CCSDS_OMM_VERS - std::string
                       "EARTH",                             //     CENTER_NAME - std::string
                       'U',                                 //     CLASSIFICATION_TYPE - char
                       "GENERATED VIA SPACE-TRACK.ORG API", //     COMMENT - std::string
                       "US",                                //     COUNTRY_CODE - std::string
                       "2025-05-23T17:34:23",               //     CREATION_DATE - std::string
                       std::nullopt,                        //     DECAY_DATE - std::string
                       0.18410540,                          //     ECCENTRICITY - long double
                       999,                                 //     ELEMENT_SET_NO - short
                       0,                                   //     EPHEMERIS_TYPE - short unsigned
                       "2025-05-23T02:32:01.903776",        //     EPOCH - std::string
                       4737198,                             //     FILE - long unsigned
                       288180510,                           //     GP_ID - unsigned
                       34.2476,                             //     INCLINATION - long double
                       "1958-03-17",                        //     LAUNCH_DATE - std::string
                       180.4527,                            //     MEAN_ANOMALY - double
                       "SGP4",                              //     MEAN_ELEMENT_THEORY - std::string
                       10.85923616,                         //     MEAN_MOTION - long double
                       0.0000000000000,                     //     MEAN_MOTION_DDOT - long double
                       0.00000058,                          //     MEAN_MOTION_DOT - long double
                       5,                                   //     NORAD_CAT_ID - unsigned
                       "1958-002B",                         //     OBJECT_ID - std::string
                       "VANGUARD 1",                        //     OBJECT_NAME - std::string
                       "PAYLOAD",                           //     OBJECT_TYPE - std::string
                       "18 SPCS",                           //     ORIGINATOR - std::string
                       649.940,                             //     PERIAPSIS - double
                       132.606,                             //     PERIOD - double
                       78.2911,                             //     RA_OF_ASC_NODE - long double
                       "SMALL",                             //     RCS_SIZE - std::string
                       "TEME",                              //     REF_FRAME - std::string
                       40087,                               //     REV_AT_EPOCH - unsigned
                       8613.950,                            //     SEMIMAJOR_AXIS - double
                       "AFETR",                             //     SITE - std::string
                       "UTC",                               //     TIME_SYSTEM - std::string
                       "0 VANGUARD 1",                      //     TLE_LINE0 - std::string
                       "1 00005U 58002B   25143.10557759  .00000058  00000-0  63595-4 0  9999", //     TLE_LINE1 - std::string
                       "2 00005  34.2476  78.2911 1841054 179.7370 180.4527 10.85923616400875" }; //     TLE_LINE2 - std::string

    std::cout << "NORAD_CAT_ID = " << data.NORAD_CAT_ID << std::endl;
    std::cout << "GP_ID = " << data.GP_ID << std::endl;
    auto insertedId = storage.insert(data);
    std::cout << "insertedId = " << insertedId << std::endl;

    try {
        auto gp = storage.get<SpaceTrackGP>(insertedId);
        std::cout << "NORAD_CAT_ID = " << gp.NORAD_CAT_ID << std::endl;
        std::cout << "GP_ID = " << gp.GP_ID << std::endl;
    }
    catch (std::system_error e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "unknown exeption" << std::endl;
    }

    // user.firstName = "Nicholas";
    // user.imageUrl =
    //     std::make_unique<std::string>("https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png");
    // storage.update(user);

    // storage.update_all(set(c(&User::lastName) = "Hardey", c(&User::typeId) = 2), where(c(&User::firstName) == "Tom"));

    // storage.remove<User>(insertedId);

    // auto allUsers = storage.get_all<User>();

    // std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
    // for (auto& user : allUsers) {
    //     std::cout
    //         << storage.dump(user)
    //         << std::endl; //  dump returns std::string with json-like style object info. For example: { id : '1', first_name
    //                       //  : 'Jonh', last_name : 'Doe', birth_date : '664416000', image_url :
    //                       //  'https://cdn1.iconfinder.com/data/icons/man-icon-set/100/man_icon-21-512.png', type_id : '3' }
    // }

    // auto allUsersList = storage.get_all<User, std::list<User>>();

    // for (auto& user : storage.iterate<User>()) {
    //     std::cout << storage.dump(user) << std::endl;
    // }

    return 0;
}