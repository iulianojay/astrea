#include <iomanip>
#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include <astro/time/Date.hpp>

#include <snapshot/http-queries/EthzQuerier.hpp>

using namespace snapshot;

int main()
{
    const astro::Date startDate("2024-01-01 00:00:00.0");
    const astro::Date endDate("2024-01-02 00:00:00.0");
    // const unsigned noradId = 44714;
    const std::string name = "NAVSTAR";

    EthzQuerier ethz;

    // std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, noradId) << std::endl;
    std::cout << std::endl << std::setw(4) << ethz.query(startDate, endDate, name, true) << std::endl;

    return 0;
}