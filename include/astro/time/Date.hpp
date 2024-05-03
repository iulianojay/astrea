#pragma once

#include <string>

#include "Time.hpp"
#include "JulianDateClock.hpp"

class Date {
public:
    Date(std::string calendarDate);
    Date(JulianDateTime<double> julianDate);

    ~Date();

private:
    std::string calendarDate;
    JulianDateTime<double> julianDate;

};