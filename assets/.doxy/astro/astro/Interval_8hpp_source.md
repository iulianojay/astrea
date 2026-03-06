

# File Interval.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**time**](dir_0abd23a91674297917c73da93ecec0fe.md) **>** [**Interval.hpp**](Interval_8hpp.md)

[Go to the documentation of this file](Interval_8hpp.md)


```C++

#pragma once

#include <units/units.hpp>

namespace astrea {
namespace astro {

class Interval {
  public:
    Interval(const Time& start, const Time& end) :
        start(start),
        propTime(end){};

    ~Interval() = default;

    Time start;    
    Time propTime; 
};

} // namespace astro
} // namespace astrea
```


