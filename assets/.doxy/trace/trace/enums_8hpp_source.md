

# File enums.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**trace**](dir_e30098dbada9bbfb44888190c04e2af0.md) **>** [**trace**](dir_f04035ba8afac2675c737f654641e7b5.md) **>** [**types**](dir_99d9bc6205d35ba61d9e386839c646c4.md) **>** [**enums.hpp**](enums_8hpp.md)

[Go to the documentation of this file](enums_8hpp.md)


```C++

#pragma once

#include <array>
#include <string>

#include <gtl/phmap.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

enum class StatType : EnumType {
    MIN, 
    AVG, 
    MAX, 
    PCT  
};

static const std::array<StatType, 4> ALL_STAT_TYPES = { StatType::MIN, StatType::AVG, StatType::MAX, StatType::PCT };
static const gtl::flat_hash_map<StatType, std::string> STAT_TYPE_STRINGS = { { StatType::MIN, "MIN" },
                                                                             { StatType::AVG, "AVG" },
                                                                             { StatType::MAX, "MAX" },
                                                                             { StatType::PCT, "PCT" } };

enum class RiseSetMetric : EnumType {
    GAP,        
    ACCESS_TIME 
};

static const std::array<RiseSetMetric, 2> ALL_RISE_SET_METRICS = { RiseSetMetric::GAP, RiseSetMetric::ACCESS_TIME };
static const gtl::flat_hash_map<RiseSetMetric, std::string> RISE_SET_METRIC_STRINGS = { { RiseSetMetric::GAP, "GAP" },
                                                                                        { RiseSetMetric::ACCESS_TIME, "ACCESS_TIME" } };
enum class AccessMetric : EnumType {
    MTTA,         
    AVG_DAILY_VIS 
};

static const std::array<AccessMetric, 2> ALL_ACCESS_METRICS = { AccessMetric::MTTA, AccessMetric::AVG_DAILY_VIS };
static const gtl::flat_hash_map<AccessMetric, std::string> ACCESS_METRIC_STRINGS = { { AccessMetric::MTTA, "MTTA" },
                                                                                     { AccessMetric::AVG_DAILY_VIS, "AVG_DAILY_VIS" } };

enum class GridType : EnumType {
    UNIFORM,     
    EQUAL_AREA,  
    WEIGHTED_NS, 
    WEIGHTED_EW, 
    MANUAL       
};

static const std::array<GridType, 5> ALL_GRID_TYPES                      = { GridType::UNIFORM,
                                                                             GridType::EQUAL_AREA,
                                                                             GridType::WEIGHTED_NS,
                                                                             GridType::WEIGHTED_EW,
                                                                             GridType::MANUAL };
static const gtl::flat_hash_map<GridType, std::string> GRID_TYPE_STRINGS = { { GridType::UNIFORM, "UNIFORM" },
                                                                             { GridType::EQUAL_AREA, "EQUAL_AREA" },
                                                                             { GridType::WEIGHTED_NS, "WEIGHTED_NS" },
                                                                             { GridType::WEIGHTED_EW, "WEIGHTED_EW" },
                                                                             { GridType::MANUAL, "MANUAL" } };

} // namespace trace
} // namespace astrea
```


