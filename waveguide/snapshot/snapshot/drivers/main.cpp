#include <iostream>
#include <string>

#include <cpr/cpr.h>

int main()
{
    cpr::Url url             = "https://satdb.ethz.ch/api/satellitedata";
    cpr::Authentication auth = { "user", "pass", cpr::AuthMode::BASIC };
    cpr::Parameters params   = {
          { "start-datetime", "20230409T0000" }, // start date YYYYMMDDThhmm
          { "end-datetime", "20230410T0000" },   // end date
          { "before", "3" },                     // days before
          { "after", "3" },                      // days after
          { "norad-id", "25544" },               // exact norad id
          { "without-frequency-data", "True" },  // include frequency data
                                                 // { "frequency-list", "[10.7-12.7,13.85-14.5]" },
    };

    cpr::Response r = cpr::Get(url, auth, params);

    std::cout << r.status_code << std::endl;
    std::cout << r.header["content-type"] << std::endl;
    std::cout << r.text << std::endl;
    return 0;
}
