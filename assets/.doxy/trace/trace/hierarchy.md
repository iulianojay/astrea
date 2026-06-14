
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**astrea::trace::AccessAnalyzer**](classastrea_1_1trace_1_1AccessAnalyzer.md) 
* **class** [**astrea::trace::AccessArray**](classastrea_1_1trace_1_1AccessArray.md) _Represents a collection of access times indexed by sender and receiver IDs. This class provides methods to manipulate and query access times for different sender-receiver pairs._ 
* **class** [**astrea::trace::AccessObject**](classastrea_1_1trace_1_1AccessObject.md) _Base class for objects that can visually access other objects._     
    * **class** [**astrea::trace::GroundPoint**](classastrea_1_1trace_1_1GroundPoint.md) _Represents a point on the surface of a celestial body with latitude, longitude, and altitude._     
        * **class** [**astrea::trace::GroundStation**](classastrea_1_1trace_1_1GroundStation.md) _Ground station on the surface of a celestial body, with sensors._ 
    * **class** [**astrea::trace::Sensor**](classastrea_1_1trace_1_1Sensor.md) [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._    
        * **class** [**astrea::trace::Antenna**](classastrea_1_1trace_1_1Antenna.md) _Represents an antenna with properties such as diameter, efficiency, frequency, and power._ 
    * **class** [**astrea::trace::Viewer**](classastrea_1_1trace_1_1Viewer.md) [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._
* **class** [**astrea::trace::FieldOfView**](classastrea_1_1trace_1_1FieldOfView.md) _Base class for Field of View (FoV) representations._     
    * **class** [**astrea::trace::CircularFieldOfView**](classastrea_1_1trace_1_1CircularFieldOfView.md) _Circular field of view implementation._ 
    * **class** [**astrea::trace::PolygonalFieldOfView**](classastrea_1_1trace_1_1PolygonalFieldOfView.md) _Polygonal field of view implementation._ 
* **class** [**astrea::trace::DatabaseOutputManager**](classastrea_1_1trace_1_1DatabaseOutputManager.md) _A class for managing database output operations with a single database instance._ 
* **class** [**astrea::trace::FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) _The_ [_**FoldsOfCoverage**_](classastrea_1_1trace_1_1FoldsOfCoverage.md) _class represents the folds of coverage (simultaneous accesses) for each receiver ID over time._
* **class** [**astrea::trace::Grid**](classastrea_1_1trace_1_1Grid.md) _Class representing a grid of ground points on the surface of a celestial body._ 
* **class** [**astrea::trace::GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) _A collection of ground stations on the surface of a celestial body._ 
* **class** [**astrea::trace::PositionCache**](classastrea_1_1trace_1_1PositionCache.md) _Contiguous memory cache for platform positions across time._ 
* **class** [**astrea::trace::RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) _Represents an array of rise and set times._ 
* **class** [**astrea::trace::SpatialIndex**](classastrea_1_1trace_1_1SpatialIndex.md) _Spatial index for efficient ground point queries._ 
* **class** [**astrea::trace::plotting::Plotter**](classastrea_1_1trace_1_1plotting_1_1Plotter.md) 
* **struct** [**astrea::trace::AccessInfo**](structastrea_1_1trace_1_1AccessInfo.md) 
* **struct** [**astrea::trace::AccessMetricsRecord**](structastrea_1_1trace_1_1AccessMetricsRecord.md) 
* **struct** [**astrea::trace::AccessStats**](structastrea_1_1trace_1_1AccessStats.md) _The_ [_**AccessStats**_](structastrea_1_1trace_1_1AccessStats.md) _struct represents statistics for access times based on an_[_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _._
* **struct** [**astrea::trace::FoldsRecord**](structastrea_1_1trace_1_1FoldsRecord.md) 
* **struct** [**astrea::trace::GeographicBin**](structastrea_1_1trace_1_1GeographicBin.md) _Geographic bin for spatial partitioning._ 
* **struct** [**astrea::trace::GroundLocationRecord**](structastrea_1_1trace_1_1GroundLocationRecord.md) 
* **struct** [**astrea::trace::HyperStats**](structastrea_1_1trace_1_1HyperStats.md) _The_ [_**HyperStats**_](structastrea_1_1trace_1_1HyperStats.md) _struct represents statistics of statistics, allowing for the calculation of statistics on a vector of Stats&lt;T&gt;._
* **struct** [**astrea::trace::IdPair**](structastrea_1_1trace_1_1IdPair.md) _Represents a pair of IDs for sender and receiver._ 
* **struct** [**astrea::trace::ReceiverRiseSetMetricsRecord**](structastrea_1_1trace_1_1ReceiverRiseSetMetricsRecord.md) 
* **struct** [**astrea::trace::RiseSetMetricsRecord**](structastrea_1_1trace_1_1RiseSetMetricsRecord.md) 
* **struct** [**astrea::trace::RiseSetRecord**](structastrea_1_1trace_1_1RiseSetRecord.md) 
* **struct** [**astrea::trace::RiseSetStats**](structastrea_1_1trace_1_1RiseSetStats.md) _The_ [_**RiseSetStats**_](structastrea_1_1trace_1_1RiseSetStats.md) _struct represents statistics for rise and set times based on a_[_**RiseSetArray**_](classastrea_1_1trace_1_1RiseSetArray.md) _and a RiseSetMetric._
* **struct** [**astrea::trace::Stats**](structastrea_1_1trace_1_1Stats.md) _The_ [_**Stats**_](structastrea_1_1trace_1_1Stats.md) _struct represents basic statistics (min, max, average, and percentiles) for a vector of values of type T._
* **struct** [**std::hash&lt; astrea::trace::IdPair &gt;**](structstd_1_1hash_3_01astrea_1_1trace_1_1IdPair_01_4.md) _Specialization of std::hash for IdPair to allow it to be used as a key in hash-based containers._ 
* **struct** [**std::less&lt; astrea::trace::IdPair &gt;**](structstd_1_1less_3_01astrea_1_1trace_1_1IdPair_01_4.md) _Specialization of std::less for IdPair to allow it to be used in ordered containers._ 
* **class** **astro::Payload< Sensor, SensorParameters >**    
    * **class** [**astrea::trace::Sensor**](classastrea_1_1trace_1_1Sensor.md) [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._    
        * **class** [**astrea::trace::Antenna**](classastrea_1_1trace_1_1Antenna.md) _Represents an antenna with properties such as diameter, efficiency, frequency, and power._ 
    * **class** [**astrea::trace::Sensor**](classastrea_1_1trace_1_1Sensor.md) [_**Sensor**_](classastrea_1_1trace_1_1Sensor.md) _class representing a sensor on a platform._    
        * **class** [**astrea::trace::Antenna**](classastrea_1_1trace_1_1Antenna.md) _Represents an antenna with properties such as diameter, efficiency, frequency, and power._ 
* **class** **astro::PayloadParameters**    
    * **class** [**astrea::trace::SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) _Class for storing and managing sensor parameters._     
        * **class** [**astrea::trace::AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md) _Class for storing and managing antenna parameters._ 
    * **class** [**astrea::trace::SensorParameters**](classastrea_1_1trace_1_1SensorParameters.md) _Class for storing and managing sensor parameters._     
        * **class** [**astrea::trace::AntennaParameters**](classastrea_1_1trace_1_1AntennaParameters.md) _Class for storing and managing antenna parameters._ 
* **class** **SensorPlatform**    
    * **class** [**astrea::trace::GroundStation**](classastrea_1_1trace_1_1GroundStation.md) _Ground station on the surface of a celestial body, with sensors._ 
    * **class** [**astrea::trace::Viewer**](classastrea_1_1trace_1_1Viewer.md) [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._
* **class** **astro::Spacecraft**    
    * **class** [**astrea::trace::Viewer**](classastrea_1_1trace_1_1Viewer.md) [_**Viewer**_](classastrea_1_1trace_1_1Viewer.md) _class for managing access and sensors on a spacecraft. This class inherits from Spacecraft,_[_**AccessObject**_](classastrea_1_1trace_1_1AccessObject.md) _, and SensorPlatform. It provides functionality to manage sensors and access rights for the spacecraft._

