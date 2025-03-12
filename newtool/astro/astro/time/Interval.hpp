#pragma once

#include <astro/time/Time.hpp>

class Interval {
public:
    Interval(const Time& start, const Time& end) : start(start), end(end) {};
    ~Interval() {};

    Time start;
    Time end;
};