#include <algorithm>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>
#include <sqlite_orm/sqlite_orm.h>

#include <astro/time/Date.hpp>

#include <snapshot/database/Database.hpp>
#include <snapshot/http-queries/spacetrack/SpaceTrackClient.hpp>
#include <snapshot/http-queries/spacetrack/SpaceTrackGP.hpp>


int main(int argc, char** argv)
{
    // Build connection and connect
    using namespace astrea;
    using namespace snapshot;
    using namespace sqlite_orm;

    // Build database
    auto snapshot = get_snapshot();
    snapshot.sync_schema();

    // Query SpaceTrack
    SpaceTrackClient spaceTrack;
    nlohmann::json spaceTrackData = spaceTrack.retrieve_all(argv[1], argv[2]);

    // Store in DB
    std::size_t barWidth = 50;
    std::size_t iRecord  = 0;
    std::size_t nRecords = spaceTrackData.size();
    for (const auto& data : spaceTrackData) {

        // Progress bar
        if (iRecord % 10 == 0) {
            std::cout << "\tProgress: [";
            double progress = static_cast<double>(iRecord) / static_cast<double>(nRecords);
            std::size_t pos = barWidth * progress;
            for (std::size_t ii = 0; ii < barWidth; ++ii) {
                if (ii < pos)
                    std::cout << "=";
                else if (ii == pos)
                    std::cout << ">";
                else
                    std::cout << " ";
            }
            std::cout << "] " << int(progress * 100.0) << " %\r";
            std::cout.flush();
        }

        // Build object
        const SpaceTrackGP gp(data);

        // Insert or update
        auto all = snapshot.get_all<SpaceTrackGP>(where(c(&SpaceTrackGP::NORAD_CAT_ID) == gp.NORAD_CAT_ID));
        if (all.size() == 0) { snapshot.insert(gp); }
        else {
            snapshot.update(gp);
        }

        ++iRecord;
    }

    return 0;
}
