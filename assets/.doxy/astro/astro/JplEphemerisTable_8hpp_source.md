

# File JplEphemerisTable.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**systems**](dir_a5d35e082abd602943cf6d70fa2a6872.md) **>** [**celestial\_bodies**](dir_b988f8927672605e377af1c3b431ef9b.md) **>** [**JplEphemerisTable.hpp**](JplEphemerisTable_8hpp.md)

[Go to the documentation of this file](JplEphemerisTable_8hpp.md)


```C++

#pragma once

#include <astro/time/Date.hpp>

namespace astrea {
namespace astro {

struct JplEphemerisTable {

  protected:
    JplEphemerisTable()  = delete; // Prevent construction
    ~JplEphemerisTable() = delete;

    static std::size_t get_index(const Date& date, const Time& timePerPoly);

    static const Date START_DATE;

    static const Date STOP_DATE;
};

} // namespace astro
} // namespace astrea
```


