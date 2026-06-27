

# File analysis.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**analysis.hpp**](analysis_8hpp.md)

[Go to the documentation of this file](analysis_8hpp.md)


```C++

#pragma once

#include <trace/analysis/TraceConfig.hpp>
#include <trace/analysis/stats/AccessStats.hpp>
#include <trace/analysis/stats/FoldsOfCoverage.hpp>
#include <trace/risesets/AccessArray.hpp>

namespace astrea {
namespace trace {

struct AnalysisResult {
    AccessArray accesses;  
    AccessStats stats;     
    FoldsOfCoverage folds; 
};

AnalysisResult run_trace_analysis(const TraceConfig& config);

} // namespace trace
} // namespace astrea
```


