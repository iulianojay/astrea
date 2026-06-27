

# Class astrea::trace::DatabaseOutputManager



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**DatabaseOutputManager**](classastrea_1_1trace_1_1DatabaseOutputManager.md)



_A class for managing database output operations with a single database instance._ [More...](#detailed-description)

* `#include <output.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef decltype(make\_database\_storage(std::filesystem::path{})) | [**DatabaseStorage**](#typedef-databasestorage)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DatabaseOutputManager**](#function-databaseoutputmanager) (const std::filesystem::path & dbPath, const bool overwrite=false) <br>_Constructs a_ [_**DatabaseOutputManager**_](classastrea_1_1trace_1_1DatabaseOutputManager.md) _with the specified database path._ |
|  void | [**clear\_all\_tables**](#function-clear_all_tables) () <br>_Clears all data from all tables in the database._  |
|  DatabaseStorage & | [**get\_storage**](#function-get_storage-12) () <br>_Gets a reference to the underlying database storage._  |
|  const DatabaseStorage & | [**get\_storage**](#function-get_storage-22) () const<br>_Gets a const reference to the underlying database storage._  |
|  void | [**save\_access\_metrics**](#function-save_access_metrics) (const [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) & stats, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the access metrics to the database in a structured format._  |
|  void | [**save\_ground\_locations**](#function-save_ground_locations) (const U & grounds) <br>_Saves ground location coordinates to the database._  |
|  void | [**save\_ground\_track**](#function-save_ground_track) (const astro::Constellation&lt; T &gt; & satellites, const astro::Date & startDate, const astro::Date & endDate, const Time & resolution) <br>_Saves satellite ground track positions (latitude/longitude over time) to the database._  |
|  void | [**save\_number\_of\_folds**](#function-save_number_of_folds) (const [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) & folds, const astro::Constellation&lt; T &gt; & satellites, const U & grounds) <br>_Saves the number of folds coverage data to the database in a structured format._  |
|  void | [**save\_receiver\_riseset\_metrics**](#function-save_receiver_riseset_metrics) (const [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) & stats, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the receiver RiseSet metrics to the database in a structured format._  |
|  void | [**save\_results**](#function-save_results) (const [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) & folds, const [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) & stats, const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves all results to the database in a structured format._  |
|  void | [**save\_riseset\_metrics**](#function-save_riseset_metrics) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the RiseSet metrics to the database in a structured format._  |
|  void | [**save\_risesets**](#function-save_risesets) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const astro::Constellation&lt; T &gt; & satellites, const U & grounds=U()) <br>_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to the database in a structured format._ |




























## Detailed Description


This class creates or loads a database on construction and provides methods to save various types of analysis data using the same database connection. 


    
## Public Types Documentation




### typedef DatabaseStorage 

```C++
using astrea::trace::DatabaseOutputManager::DatabaseStorage =  decltype(make_database_storage(std::filesystem::path{}));
```




<hr>
## Public Functions Documentation




### function DatabaseOutputManager 

_Constructs a_ [_**DatabaseOutputManager**_](classastrea_1_1trace_1_1DatabaseOutputManager.md) _with the specified database path._
```C++
inline explicit astrea::trace::DatabaseOutputManager::DatabaseOutputManager (
    const std::filesystem::path & dbPath,
    const bool overwrite=false
) 
```





**Parameters:**


* `dbPath` The path to the database file. Will be created if it doesn't exist. 
* `overwrite` If true, the existing database will be overwritten. Default is false. 




        

<hr>



### function clear\_all\_tables 

_Clears all data from all tables in the database._ 
```C++
inline void astrea::trace::DatabaseOutputManager::clear_all_tables () 
```



This is useful when you want to completely reset the database before saving new analysis results. 


        

<hr>



### function get\_storage [1/2]

_Gets a reference to the underlying database storage._ 
```C++
inline DatabaseStorage & astrea::trace::DatabaseOutputManager::get_storage () 
```





**Returns:**

DatabaseStorage& Reference to the database storage instance. 





        

<hr>



### function get\_storage [2/2]

_Gets a const reference to the underlying database storage._ 
```C++
inline const DatabaseStorage & astrea::trace::DatabaseOutputManager::get_storage () const
```





**Returns:**

const DatabaseStorage& Const reference to the database storage instance. 





        

<hr>



### function save\_access\_metrics 

_Saves the access metrics to the database in a structured format._ 
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_access_metrics (
    const AccessStats & stats,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `stats` The [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) containing the metrics to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_ground\_locations 

_Saves ground location coordinates to the database._ 
```C++
template<typename U>
inline void astrea::trace::DatabaseOutputManager::save_ground_locations (
    const U & grounds
) 
```





**Template parameters:**


* `U` The type of the ground container (e.g., [**Grid**](classastrea_1_1trace_1_1Grid.md), [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md)). 



**Parameters:**


* `grounds` The container of ground objects to save. 




        

<hr>



### function save\_ground\_track 

_Saves satellite ground track positions (latitude/longitude over time) to the database._ 
```C++
template<typename T>
inline void astrea::trace::DatabaseOutputManager::save_ground_track (
    const astro::Constellation< T > & satellites,
    const astro::Date & startDate,
    const astro::Date & endDate,
    const Time & resolution
) 
```





**Template parameters:**


* `T` The spacecraft type used in the Constellation. 



**Parameters:**


* `satellites` The constellation whose satellites' ground tracks are to be saved. 
* `startDate` The start of the simulation epoch. 
* `endDate` The end of the simulation epoch. 
* `resolution` The time step between saved ground track points. 




        

<hr>



### function save\_number\_of\_folds 

_Saves the number of folds coverage data to the database in a structured format._ 
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_number_of_folds (
    const FoldsOfCoverage & folds,
    const astro::Constellation< T > & satellites,
    const U & grounds
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `folds` The [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) containing the folds data to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_receiver\_riseset\_metrics 

_Saves the receiver RiseSet metrics to the database in a structured format._ 
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_receiver_riseset_metrics (
    const AccessStats & stats,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `stats` The [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) containing the statistics to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_results 

_Saves all results to the database in a structured format._ 
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_results (
    const FoldsOfCoverage & folds,
    const AccessStats & stats,
    const AccessArray & accesses,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `folds` The [**FoldsOfCoverage**](classastrea_1_1trace_1_1FoldsOfCoverage.md) containing the fold statistics to be saved. 
* `stats` The [**AccessStats**](structastrea_1_1trace_1_1AccessStats.md) containing the access statistics to be saved. 
* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_riseset\_metrics 

_Saves the RiseSet metrics to the database in a structured format._ 
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_riseset_metrics (
    const AccessArray & accesses,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>



### function save\_risesets 

_Saves the_ [_**AccessArray**_](classastrea_1_1trace_1_1AccessArray.md) _to the database in a structured format._
```C++
template<typename T, typename U>
inline void astrea::trace::DatabaseOutputManager::save_risesets (
    const AccessArray & accesses,
    const astro::Constellation< T > & satellites,
    const U & grounds=U()
) 
```





**Template parameters:**


* `T` The type of Spacecraft used in the Constellation. 
* `U` The type of the ground container. 



**Parameters:**


* `accesses` The [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) containing the access times to be saved. 
* `satellites` The Constellation containing the Spacecraft for which access times are being saved. 
* `grounds` The [**GroundArchitecture**](classastrea_1_1trace_1_1GroundArchitecture.md) containing the ground stations for which access times are being saved 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/io/output.hpp`

