#pragma once

#include <astro/types/typedefs.hpp>

namespace astro {

class Interval {
  public:
    Interval(const Time& start, const Time& end) :
        start(start),
        end(end){};
    ~Interval(){};

    Time start;
    Time end;
};

} // namespace astro