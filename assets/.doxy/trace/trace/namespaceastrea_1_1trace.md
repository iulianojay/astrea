

# Namespace astrea::trace



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**plotting**](namespaceastrea_1_1trace_1_1plotting.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**AccessAnalyzer**](classastrea_1_1trace_1_1AccessAnalyzer.md) <br> |
| class | [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) <br>_Represents a collection of access times indexed by sender and receiver IDs. This class provides methods to manipulate and query access times for different sender-receiver pairs._  |
| struct | [**AccessInfo**](structastrea_1_1trace_1_1AccessInfo.md) <br> |
| class | [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md) <br>_Base class for objects that can visually access other objects._  |
| struct | [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) <br>_The_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _struct represents statistics for access times based on an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
| class | [**Antenna**](classastrea_1_1trace_1_1Antenna.md) <br>_Represents an antenna with properties such as diameter, efficiency, frequency, and power._  |
| class | [**AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md) <br>_Class for storing and managing antenna parameters._  |
| class | [**CircularFieldOfView**](classastrea_1_1trace_1_1CircularFieldOfView.md) <br>_Circular field of view implementation._  |
| class | [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) <br>_Base class for Field of View (FoV) representations._  |
| class | [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) <br>_The_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _class represents the folds of coverage (simultaneous accesses) for each receiver ID over time._ |
| struct | [**GeographicBin**](structastrea_1_1trace_1_1GeographicBin.md) <br>_Geographic bin for spatial partitioning._  |
| class | [**Grid**](classastrea_1_1trace_1_1Grid.md) <br>_Class representing a grid of ground points._  |
| class | [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) <br>[_**GroundArchitecture**_](classastrea_1_1trace_1_1GroundArchitecture.md) _class represents a collection of ground stations._ |
| class | [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) <br>_Represents a point on the ground with latitude, longitude, and altitude._  |
| class | [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) <br>_Ground station class for managing ground-based access. This class inherits from_ [_**GroundPoint**_](classastrea_1_1trace_1_1GroundPoint.md) _,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It represents a ground station with a specific latitude, longitude, altitude, and a collection of sensors. It also provides methods to manage access and sensor functionalities._ |
| struct | [**HyperStats**](structastrea_1_1trace_1_1HyperStats.md) &lt;class T&gt;<br>_The_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _struct represents statistics of statistics, allowing for the calculation of statistics on a vector of Stats&lt;T&gt;._ |
| struct | [**IdPair**](structastrea_1_1trace_1_1IdPair.md) <br>_Represents a pair of IDs for sender and receiver._  |
| class | [**PolygonalFieldOfView**](classastrea_1_1trace_1_1PolygonalFieldOfView.md) <br>_Polygonal field of view implementation._  |
| class | [**PositionCache**](classastrea_1_1trace_1_1PositionCache.md) <br>_Contiguous memory cache for platform positions across time._  |
| class | [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) <br>_Represents an array of rise and set times._  |
| struct | [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) <br>_The_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _struct represents statistics for rise and set times based on a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._ |
| class | [**Sensor**](classastrea_1_1trace_1_1Sensor.md) <br>[_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._ |
| class | [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) <br>_Class for storing and managing sensor parameters._  |
| class | [**SpatialIndex**](classastrea_1_1trace_1_1SpatialIndex.md) <br>_Spatial index for efficient ground point queries._  |
| struct | [**Stats**](structastrea_1_1trace_1_1Stats.md) &lt;class T&gt;<br>_The_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct represents basic statistics (min, max, average, and percentiles) for a vector of values of type T._ |
| class | [**Viewer**](classastrea_1_1trace_1_1Viewer.md) <br>[_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._ |


## Public Types

| Type | Name |
| ---: | :--- |
| enum [**EnumType**](namespaceastrea_1_1trace.md#typedef-enumtype) | [**AccessMetric**](#enum-accessmetric)  <br>_Enumeration for different access metrics._  |
| typedef std::vector&lt; astro::Date &gt; | [**DateVector**](#typedef-datevector)  <br>_Type alias for a vector of time values._  |
| typedef astro::RadiusVector&lt; astro::frames::earth::earth\_fixed &gt; | [**EcefRadiusVec**](#typedef-ecefradiusvec)  <br> |
| typedef astro::RadiusVector&lt; astro::frames::earth::icrf &gt; | [**EciRadiusVec**](#typedef-eciradiusvec)  <br> |
| typedef uint32\_t | [**EnumType**](#typedef-enumtype)  <br>_Type definition for enumeration types._  |
| enum [**EnumType**](namespaceastrea_1_1trace.md#typedef-enumtype) | [**GridType**](#enum-gridtype)  <br>_Enumeration for different grid types._  |
| typedef std::vector&lt; std::shared\_ptr&lt; [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) &gt; &gt; | [**GroundPointRefVec**](#typedef-groundpointrefvec)  <br> |
| typedef std::vector&lt; std::shared\_ptr&lt; [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) &gt; &gt; | [**GroundStationRefVec**](#typedef-groundstationrefvec)  <br> |
| typedef std::pair&lt; Angle, Angle &gt; | [**LatLon**](#typedef-latlon)  <br>_Latitude/Longitude coordinate pair._  |
| typedef std::vector&lt; std::pair&lt; std::size\_t, std::size\_t &gt; &gt; | [**PairVec**](#typedef-pairvec)  <br> |
| enum  | [**PatternApproximation**](#enum-patternapproximation)  <br>_Enum class for different antenna pattern approximations._  |
| enum [**EnumType**](namespaceastrea_1_1trace.md#typedef-enumtype) | [**RiseSetMetric**](#enum-risesetmetric)  <br>_Enumeration for different rise/set metrics._  |
| typedef astro::PayloadPlatform&lt; [**Sensor**](classastrea_1_1trace_1_1Sensor.md) &gt; | [**SensorPlatform**](#typedef-sensorplatform)  <br>_Type definition for sensor platforms._  |
| enum [**EnumType**](namespaceastrea_1_1trace.md#typedef-enumtype) | [**StatType**](#enum-stattype)  <br>_Enumeration of statistical measures for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._ |
| typedef astro::Constellation&lt; [**Viewer**](classastrea_1_1trace_1_1Viewer.md) &gt; | [**ViewerConstellation**](#typedef-viewerconstellation)  <br>_Type alias for a constellation of_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _objects._ |
| typedef std::vector&lt; std::shared\_ptr&lt; [**Viewer**](classastrea_1_1trace_1_1Viewer.md) &gt; &gt; | [**ViewerRefVec**](#typedef-viewerrefvec)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const gtl::btree\_map&lt; [**AccessMetric**](namespaceastrea_1_1trace.md#enum-accessmetric), std::string &gt; | [**ACCESS\_METRIC\_STRINGS**](#variable-access_metric_strings)   = `/* multi line expression */`<br> |
|  const std::array&lt; [**AccessMetric**](namespaceastrea_1_1trace.md#enum-accessmetric), 2 &gt; | [**ALL\_ACCESS\_METRICS**](#variable-all_access_metrics)   = `{ AccessMetric::MTTA, AccessMetric::AVG\_DAILY\_VIS }`<br> |
|  const std::array&lt; [**GridType**](namespaceastrea_1_1trace.md#enum-gridtype), 5 &gt; | [**ALL\_GRID\_TYPES**](#variable-all_grid_types)   = `/* multi line expression */`<br> |
|  const std::array&lt; [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric), 2 &gt; | [**ALL\_RISE\_SET\_METRICS**](#variable-all_rise_set_metrics)   = `{ RiseSetMetric::GAP, RiseSetMetric::ACCESS\_TIME }`<br> |
|  const std::array&lt; [**StatType**](namespaceastrea_1_1trace.md#enum-stattype), 4 &gt; | [**ALL\_STAT\_TYPES**](#variable-all_stat_types)   = `{ StatType::MIN, StatType::AVG, StatType::MAX, StatType::PCT }`<br> |
|  const std::vector&lt; Unitless &gt; | [**DEFAULT\_PERCENTILES**](#variable-default_percentiles)   = `{ 1, 5, 10, 25, 50, 75, 90, 95, 99 }`<br> |
|  const gtl::btree\_map&lt; [**GridType**](namespaceastrea_1_1trace.md#enum-gridtype), std::string &gt; | [**GRID\_TYPE\_STRINGS**](#variable-grid_type_strings)   = `/* multi line expression */`<br> |
|  const gtl::btree\_map&lt; [**RiseSetMetric**](namespaceastrea_1_1trace.md#enum-risesetmetric), std::string &gt; | [**RISE\_SET\_METRIC\_STRINGS**](#variable-rise_set_metric_strings)   = `/* multi line expression */`<br> |
|  const gtl::btree\_map&lt; [**StatType**](namespaceastrea_1_1trace.md#enum-stattype), std::string &gt; | [**STAT\_TYPE\_STRINGS**](#variable-stat_type_strings)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  Angle | [**calculate\_angle\_between\_vectors**](#function-calculate_angle_between_vectors) (const EciRadiusVec & vector1, const EciRadiusVec & vector2) <br> |
|  Angle | [**calculate\_angle\_between\_vectors**](#function-calculate_angle_between_vectors) (const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & vector1, const astro::CartesianVector&lt; Distance, astro::frames::earth::icrf &gt; & vector2) <br>_Computes the angle between two radius vectors._  |
|  std::string | [**get\_object\_name\_from\_id**](#function-get_object_name_from_id) (std::size\_t id, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br> |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator) (std::ostream & os, const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accessarray) <br>_Overloads the output stream operator for the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._ |
|  std::ostream & | [**operator&lt;&lt;**](#function-operator_1) (std::ostream & os, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & risesets) <br> |
|  bool | [**point\_in\_polygon**](#function-point_in_polygon) (const std::pair&lt; Unitless, Unitless &gt; & point, const std::vector&lt; std::pair&lt; Unitless, Unitless &gt; &gt; & polygon) <br> |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**riseset\_difference**](#function-riseset_difference) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & a, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & b) <br>_Difference of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**riseset\_intersection**](#function-riseset_intersection) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & a, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & b) <br>_Intersection of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**riseset\_union**](#function-riseset_union) (const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & a, const [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) & b) <br>_Union of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._ |
|  void | [**save\_access\_metrics\_to\_file**](#function-save_access_metrics_to_file) (const [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) & stats, const std::filesystem::path & outdir, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._ |
|  void | [**save\_number\_of\_folds\_to\_file**](#function-save_number_of_folds_to_file) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const std::filesystem::path & outdir, const astro::Constellation&lt; T &gt; & satellites, const U & grounds, const Time & resolution, const Time & end) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._ |
|  void | [**save\_receiver\_riseset\_metrics\_to\_file**](#function-save_receiver_riseset_metrics_to_file) (const [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) & stats, const std::filesystem::path & outdir, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._ |
|  void | [**save\_riseset\_metrics\_to\_file**](#function-save_riseset_metrics_to_file) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const std::filesystem::path & outdir, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._ |
|  void | [**save\_risesets\_to\_file**](#function-save_risesets_to_file) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const std::filesystem::path & outdir, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._ |
|  std::string | [**to\_formatted\_string**](#function-to_formatted_string) (Time t) <br>_Converts a Time object to a formatted string._  |




























## Public Types Documentation




### enum AccessMetric 

_Enumeration for different access metrics._ 
```C++
enum astrea::trace::AccessMetric {
    MTTA,
    AVG_DAILY_VIS
};
```




<hr>



### typedef DateVector 

_Type alias for a vector of time values._ 
```C++
using astrea::trace::DateVector = typedef std::vector<astro::Date>;
```




<hr>



### typedef EcefRadiusVec 

```C++
typedef astro::RadiusVector< astro::frames::earth::earth_fixed > astrea::trace::EcefRadiusVec;
```




<hr>



### typedef EciRadiusVec 

```C++
typedef astro::RadiusVector< astro::frames::earth::icrf > astrea::trace::EciRadiusVec;
```




<hr>



### typedef EnumType 

_Type definition for enumeration types._ 
```C++
using astrea::trace::EnumType = typedef uint32_t;
```




<hr>



### enum GridType 

_Enumeration for different grid types._ 
```C++
enum astrea::trace::GridType {
    UNIFORM,
    EQUAL_AREA,
    WEIGHTED_NS,
    WEIGHTED_EW,
    MANUAL
};
```




<hr>



### typedef GroundPointRefVec 

```C++
using astrea::trace::GroundPointRefVec = typedef std::vector<std::shared_ptr<GroundPoint> >;
```




<hr>



### typedef GroundStationRefVec 

```C++
using astrea::trace::GroundStationRefVec = typedef std::vector<std::shared_ptr<GroundStation> >;
```




<hr>



### typedef LatLon 

_Latitude/Longitude coordinate pair._ 
```C++
using astrea::trace::LatLon = typedef std::pair<Angle, Angle>;
```



This type is used to represent a geographic location on the Earth's surface. 


        

<hr>



### typedef PairVec 

```C++
using astrea::trace::PairVec = typedef std::vector<std::pair<std::size_t, std::size_t> >;
```




<hr>



### enum PatternApproximation 

_Enum class for different antenna pattern approximations._ 
```C++
enum astrea::trace::PatternApproximation {
    BESSEL,
    SINC_SQUARED
};
```




<hr>



### enum RiseSetMetric 

_Enumeration for different rise/set metrics._ 
```C++
enum astrea::trace::RiseSetMetric {
    GAP,
    ACCESS_TIME
};
```




<hr>



### typedef SensorPlatform 

_Type definition for sensor platforms._ 
```C++
using astrea::trace::SensorPlatform = typedef astro::PayloadPlatform<Sensor>;
```




<hr>



### enum StatType 

_Enumeration of statistical measures for_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _._
```C++
enum astrea::trace::StatType {
    MIN,
    AVG,
    MAX,
    PCT
};
```




<hr>



### typedef ViewerConstellation 

_Type alias for a constellation of_ [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _objects._
```C++
typedef astro::Constellation< Viewer > astrea::trace::ViewerConstellation;
```




<hr>



### typedef ViewerRefVec 

```C++
using astrea::trace::ViewerRefVec = typedef std::vector<std::shared_ptr<Viewer> >;
```




<hr>
## Public Static Attributes Documentation




### variable ACCESS\_METRIC\_STRINGS 

```C++
const gtl::btree_map<AccessMetric, std::string> astrea::trace::ACCESS_METRIC_STRINGS;
```




<hr>



### variable ALL\_ACCESS\_METRICS 

```C++
const std::array<AccessMetric, 2> astrea::trace::ALL_ACCESS_METRICS;
```




<hr>



### variable ALL\_GRID\_TYPES 

```C++
const std::array<GridType, 5> astrea::trace::ALL_GRID_TYPES;
```




<hr>



### variable ALL\_RISE\_SET\_METRICS 

```C++
const std::array<RiseSetMetric, 2> astrea::trace::ALL_RISE_SET_METRICS;
```




<hr>



### variable ALL\_STAT\_TYPES 

```C++
const std::array<StatType, 4> astrea::trace::ALL_STAT_TYPES;
```




<hr>



### variable DEFAULT\_PERCENTILES 

```C++
const std::vector<Unitless> astrea::trace::DEFAULT_PERCENTILES;
```




<hr>



### variable GRID\_TYPE\_STRINGS 

```C++
const gtl::btree_map<GridType, std::string> astrea::trace::GRID_TYPE_STRINGS;
```




<hr>



### variable RISE\_SET\_METRIC\_STRINGS 

```C++
const gtl::btree_map<RiseSetMetric, std::string> astrea::trace::RISE_SET_METRIC_STRINGS;
```




<hr>



### variable STAT\_TYPE\_STRINGS 

```C++
const gtl::btree_map<StatType, std::string> astrea::trace::STAT_TYPE_STRINGS;
```




<hr>
## Public Functions Documentation




### function calculate\_angle\_between\_vectors 

```C++
Angle astrea::trace::calculate_angle_between_vectors (
    const EciRadiusVec & vector1,
    const EciRadiusVec & vector2
) 
```




<hr>



### function calculate\_angle\_between\_vectors 

_Computes the angle between two radius vectors._ 
```C++
Angle astrea::trace::calculate_angle_between_vectors (
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & vector1,
    const astro::CartesianVector< Distance, astro::frames::earth::icrf > & vector2
) 
```





**Parameters:**


* `vector1` The first radius vector. 
* `vector2` The second radius vector. 



**Returns:**

Angle The angle between the two vectors. 





        

<hr>



### function get\_object\_name\_from\_id 

```C++
template<typename T, typename U>
std::string astrea::trace::get_object_name_from_id (
    std::size_t id,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```




<hr>



### function operator&lt;&lt; 

_Overloads the output stream operator for the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
```C++
std::ostream & astrea::trace::operator<< (
    std::ostream & os,
    const AccessArray & accessarray
) 
```





**Parameters:**


* `os` The output stream. 
* `accessarray` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) to output. 



**Returns:**

std::ostream& The output stream. 





        

<hr>



### function operator&lt;&lt; 

```C++
std::ostream & astrea::trace::operator<< (
    std::ostream & os,
    const RiseSetArray & risesets
) 
```




<hr>



### function point\_in\_polygon 

```C++
bool astrea::trace::point_in_polygon (
    const std::pair< Unitless, Unitless > & point,
    const std::vector< std::pair< Unitless, Unitless > > & polygon
) 
```




<hr>



### function riseset\_difference 

_Difference of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray astrea::trace::riseset_difference (
    const RiseSetArray & a,
    const RiseSetArray & b
) 
```





**Parameters:**


* `a` The first [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 
* `b` The second [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) The difference of the two [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) objects. 





        

<hr>



### function riseset\_intersection 

_Intersection of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray astrea::trace::riseset_intersection (
    const RiseSetArray & a,
    const RiseSetArray & b
) 
```





**Parameters:**


* `a` The first [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 
* `b` The second [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) The intersection of the two [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) objects. 





        

<hr>



### function riseset\_union 

_Union of two_ [_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _objects._
```C++
RiseSetArray astrea::trace::riseset_union (
    const RiseSetArray & a,
    const RiseSetArray & b
) 
```





**Parameters:**


* `a` The first [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 
* `b` The second [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md). 



**Returns:**

[**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) The union of the two [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) objects. 





        

<hr>



### function save\_access\_metrics\_to\_file 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._
```C++
template<typename T, typename U>
void astrea::trace::save_access_metrics_to_file (
    const AccessStats & stats,
    const std::filesystem::path & outdir,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `outdir` The directory to save the file to. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_number\_of\_folds\_to\_file 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._
```C++
template<typename T, typename U>
void astrea::trace::save_number_of_folds_to_file (
    const AccessArray & accesses,
    const std::filesystem::path & outdir,
    const astro::Constellation< T > & satellites,
    const U & grounds,
    const Time & resolution,
    const Time & end
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `outdir` The directory to save the file to. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_receiver\_riseset\_metrics\_to\_file 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._
```C++
template<typename T, typename U>
void astrea::trace::save_receiver_riseset_metrics_to_file (
    const AccessStats & stats,
    const std::filesystem::path & outdir,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `outdir` The directory to save the file to. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_riseset\_metrics\_to\_file 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._
```C++
template<typename T, typename U>
void astrea::trace::save_riseset_metrics_to_file (
    const AccessArray & accesses,
    const std::filesystem::path & outdir,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `outdir` The directory to save the file to. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_risesets\_to\_file 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to a file in a human-readable format._
```C++
template<typename T, typename U>
void astrea::trace::save_risesets_to_file (
    const AccessArray & accesses,
    const std::filesystem::path & outdir,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `outdir` The directory to save the file to. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function to\_formatted\_string 

_Converts a Time object to a formatted string._ 
```C++
std::string astrea::trace::to_formatted_string (
    Time t
) 
```





**Parameters:**


* `t` The Time object to convert. 



**Returns:**

std::string A formatted string representation of the Time object. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/AccessAnalyzer.cpp`

