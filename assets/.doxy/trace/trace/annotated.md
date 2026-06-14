
# Class List


Here are the classes, structs, unions and interfaces with brief descriptions:

* **namespace** [**astrea**](namespaceastrea.md)     
    * **namespace** [**trace**](namespaceastrea_1_1trace.md)     
        * **class** [**AccessAnalyzer**](classastrea_1_1trace_1_1AccessAnalyzer.md)     
        * **class** [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) _Represents a collection of access times indexed by sender and receiver IDs. This class provides methods to manipulate and query access times for different sender-receiver pairs._     
        * **struct** [**AccessInfo**](structastrea_1_1trace_1_1AccessInfo.md)     
        * **struct** [**AccessMetricsRecord**](structastrea_1_1trace_1_1AccessMetricsRecord.md)     
        * **class** [**AccessObject**](classastrea_1_1trace_1_1AccessObject.md) _Base class for objects that can visually access other objects._     
        * **struct** [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) _The_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _struct represents statistics for access times based on an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._    
        * **class** [**Antenna**](classastrea_1_1trace_1_1Antenna.md) _Represents an antenna with properties such as diameter, efficiency, frequency, and power._     
        * **class** [**AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md) _Class for storing and managing antenna parameters._     
        * **class** [**CircularFieldOfView**](classastrea_1_1trace_1_1CircularFieldOfView.md) _Circular field of view implementation._     
        * **class** [**DatabaseOutputManager**](classastrea_1_1trace_1_1DatabaseOutputManager.md) _A class for managing database output operations with a single database instance._     
        * **class** [**FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) _Base class for Field of View (FoV) representations._     
        * **class** [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) _The_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _class represents the folds of coverage (simultaneous accesses) for each receiver ID over time._    
        * **struct** [**FoldsRecord**](structastrea_1_1trace_1_1FoldsRecord.md)     
        * **struct** [**GeographicBin**](structastrea_1_1trace_1_1GeographicBin.md) _Geographic bin for spatial partitioning._     
        * **class** [**Grid**](classastrea_1_1trace_1_1Grid.md) _Class representing a grid of ground points on the surface of a celestial body._     
        * **class** [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) _A collection of ground stations on the surface of a celestial body._     
        * **struct** [**GroundLocationRecord**](structastrea_1_1trace_1_1GroundLocationRecord.md)     
        * **class** [**GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) _Represents a point on the surface of a celestial body with latitude, longitude, and altitude._     
        * **class** [**GroundStation**](classastrea_1_1trace_1_1GroundStation.md) _Ground station on the surface of a celestial body, with sensors._     
        * **struct** [**HyperStats**](structastrea_1_1trace_1_1HyperStats.md) _The_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _struct represents statistics of statistics, allowing for the calculation of statistics on a vector of Stats&lt;T&gt;._    
        * **struct** [**IdPair**](structastrea_1_1trace_1_1IdPair.md) _Represents a pair of IDs for sender and receiver._     
        * **class** [**PolygonalFieldOfView**](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _Polygonal field of view implementation._     
        * **class** [**PositionCache**](classastrea_1_1trace_1_1PositionCache.md) _Contiguous memory cache for platform positions across time._     
        * **struct** [**ReceiverRiseSetMetricsRecord**](structastrea_1_1trace_1_1ReceiverRiseSetMetricsRecord.md)     
        * **class** [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) _Represents an array of rise and set times._     
        * **struct** [**RiseSetMetricsRecord**](structastrea_1_1trace_1_1RiseSetMetricsRecord.md)     
        * **struct** [**RiseSetRecord**](structastrea_1_1trace_1_1RiseSetRecord.md)     
        * **struct** [**RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) _The_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _struct represents statistics for rise and set times based on a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._    
        * **class** [**Sensor**](classastrea_1_1trace_1_1Sensor.md) [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._    
        * **class** [**SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) _Class for storing and managing sensor parameters._     
        * **class** [**SpatialIndex**](classastrea_1_1trace_1_1SpatialIndex.md) _Spatial index for efficient ground point queries._     
        * **struct** [**Stats**](structastrea_1_1trace_1_1Stats.md) _The_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct represents basic statistics (min, max, average, and percentiles) for a vector of values of type T._    
        * **class** [**Viewer**](classastrea_1_1trace_1_1Viewer.md) [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._    
        * **namespace** [**plotting**](namespaceastrea_1_1trace_1_1plotting.md)     
            * **class** [**Plotter**](classastrea_1_1trace_1_1plotting_1_1Plotter.md)     
* **namespace** [**plotting**](namespaceastrea_1_1trace_1_1plotting_1_1_0d2.md) 
* **namespace** [**astro**](namespaceastro.md) 
* **namespace** [**frames**](namespaceastro_1_1frames.md) 
* **namespace** [**matplot**](namespacematplot.md) 
* **namespace** [**mp\_units**](namespacemp__units.md) 
* **namespace** [**angular**](namespacemp__units_1_1angular.md) 
* **namespace** [**snapshot**](namespacesnapshot.md) 
* **namespace** [**sqlite\_orm**](namespacesqlite__orm.md) 
* **namespace** [**std**](namespacestd.md)     
    * **struct** [**hash&lt; astrea::trace::IdPair &gt;**](structstd_1_1hash_3_01astrea_1_1trace_1_1IdPair_01_4.md) _Specialization of std::hash for IdPair to allow it to be used as a key in hash-based containers._     
    * **struct** [**less&lt; astrea::trace::IdPair &gt;**](structstd_1_1less_3_01astrea_1_1trace_1_1IdPair_01_4.md) _Specialization of std::less for IdPair to allow it to be used in ordered containers._     

