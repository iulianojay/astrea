

# File AccessAnalyzer.cpp



[**FileList**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**AccessAnalyzer.cpp**](AccessAnalyzer_8cpp.md)

[Go to the source code of this file](AccessAnalyzer_8cpp_source.md)



* `#include <trace/analysis/AccessAnalyzer.hpp>`
* `#include <algorithm>`
* `#include <execution>`
* `#include <numeric>`
* `#include <unordered_set>`
* `#include <mp-units/math.h>`
* `#include <mp-units/systems/si/math.h>`
* `#include <astro/platforms/space/Constellation.hpp>`
* `#include <astro/state/State.hpp>`
* `#include <astro/state/StateHistory.hpp>`
* `#include <astro/state/orbital_elements/Cartesian.hpp>`
* `#include <astro/systems/system_utilities.hpp>`
* `#include <astro/time/Date.hpp>`
* `#include <astro/utilities/conversions.hpp>`
* `#include <trace/analysis/PositionCache.hpp>`
* `#include <trace/analysis/SpatialIndex.hpp>`
* `#include <trace/platforms/ground/Grid.hpp>`
* `#include <trace/platforms/ground/GroundArchitecture.hpp>`
* `#include <trace/platforms/ground/GroundPoint.hpp>`
* `#include <trace/platforms/ground/GroundStation.hpp>`
* `#include <trace/platforms/vehicles/Viewer.hpp>`
* `#include <trace/types/typedefs.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**astrea**](namespaceastrea.md) <br> |
| namespace | [**trace**](namespaceastrea_1_1trace.md) <br> |
| namespace | [**frames**](namespaceastro_1_1frames.md) <br> |
| namespace | [**mp\_units**](namespacemp__units.md) <br> |
| namespace | [**si**](namespacemp__units_1_1si.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**AccessInfo**](structastrea_1_1trace_1_1AccessInfo.md) <br> |
| struct | [**PairResult**](structastrea_1_1trace_1_1PairResult.md) <br>_Per-viewer result for one (viewer, ground-point) work item._  |



















































------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/AccessAnalyzer.cpp`

