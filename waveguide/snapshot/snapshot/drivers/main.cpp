#include <iomanip>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/http-queries/EthzClient.hpp>
#include <snapshot/http-queries/SpaceTrackClient.hpp>

using namespace snapshot;

void query_ethz_database();
void query_spacetrack(int argc, char** argv);

int main(int argc, char** argv)
{
    // query_ethz_database();
    query_spacetrack(argc, argv);

    return 0;
}

void query_ethz_database()
{
    const astro::Date startDate("2024-01-01 00:00:00.0");
    const astro::Date endDate("2024-01-02 00:00:00.0");
    // const unsigned noradId = 44714;
    const std::string name = "NAVSTAR";

    EthzClient ethz;

    // std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, noradId) << std::endl;
    std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, name, true) << std::endl;
}

void query_spacetrack(int argc, char** argv)
{
    // // Login
    // const cpr::Url loginUrl     = std::string("https://www.space-track.org/ajaxauth/login");
    // cpr::Payload loginParams    = { { "identity", argv[1] }, { "password", argv[2] } };
    // cpr::Response loginResponse = cpr::Post(loginUrl, loginParams);

    // // Query
    // const cpr::Url url = std::string("https://www.space-track.org/basicspacedata/query/class/decay/DECAY_EPOCH/"
    //                                  "2012-07-02--2012-07-09/orderby/NORAD_CAT_ID,PRECEDENCE/format/json");

    // cpr::Response r = cpr::Get(url, loginResponse.cookies);

    // // Extract response into json
    // nlohmann::json response = nlohmann::json::parse(r.text);

    // // if (response["results"].size() == 0) {
    // std::ostringstream errorStream;
    // // errorStream << "Query failed. No data matching search was found.\n\n";
    // errorStream << "Query Data: \n";
    // errorStream << "    Status Code: " << std::to_string(r.status_code) << "\n";
    // errorStream << "    Text: " << r.text << "\n";
    // errorStream << "    Url: " << r.url << "\n";
    // errorStream << "    Error: " << r.error.message << "\n";
    // errorStream << "    Status Line: " << r.status_line << "\n";
    // errorStream << "    Reason: " << r.reason << "\n";
    // // errorStream << "    Raw Header: \n\n" << r.raw_header;

    // std::cout << errorStream.str();
    // }


    SpaceTrackClient spaceTrack;
    spaceTrack.query(argv[1], argv[2]);
}