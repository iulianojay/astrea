

# Namespace astrea::snapshot



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**snapshot**](namespaceastrea_1_1snapshot.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) &lt;class T&gt;<br>_Database utility wrapper for the snapshot module._  |
| class | [**EthzClient**](classastrea_1_1snapshot_1_1EthzClient.md) <br>[_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _class for interacting with the ETHZ satellite database API._ |
| class | [**SpaceTrackClient**](classastrea_1_1snapshot_1_1SpaceTrackClient.md) <br>[_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _class for interacting with the SpaceTrack API._ |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint32\_t | [**EnumType**](#typedef-enumtype)  <br>_Enumeration type for the snapshot module._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  auto | [**get\_snapshot**](#function-get_snapshot) () <br>_Gets the snapshot database instance._  |
|  [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md)&lt; typename std::decay&lt; T &gt;::type &gt; | [**make\_database**](#function-make_database) (T && database) <br>_Creates a_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _instance for the given database._ |
|  auto | [**make\_snapshot\_wrapper**](#function-make_snapshot_wrapper) () <br>_Creates a_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _for the snapshot database._ |




























## Public Types Documentation




### typedef EnumType 

_Enumeration type for the snapshot module._ 
```C++
using astrea::snapshot::EnumType = typedef uint32_t;
```




<hr>
## Public Functions Documentation




### function get\_snapshot 

_Gets the snapshot database instance._ 
```C++
inline auto astrea::snapshot::get_snapshot () 
```



This function creates and returns a SQLite storage instance for the snapshot database.




**Returns:**

A sqlite\_orm::Storage instance configured for the snapshot database. 





        

<hr>



### function make\_database 

_Creates a_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _instance for the given database._
```C++
template<typename T>
DatabaseUtilityWrapper < typename std::decay< T >::type > astrea::snapshot::make_database (
    T && database
) 
```



This function is a convenience wrapper to create a [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) for the provided database instance.




**Template parameters:**


* `T` The type of the database (e.g., sqlite\_orm::Storage&lt;GeneralPerturbations&gt;). 



**Parameters:**


* `database` The database instance to wrap. 



**Returns:**

A [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) instance wrapping the provided database. 





        

<hr>



### function make\_snapshot\_wrapper 

_Creates a_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _for the snapshot database._
```C++
inline auto astrea::snapshot::make_snapshot_wrapper () 
```



This function creates a [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) instance for the snapshot database, allowing easy access to GeneralPerturbations data and other database operations.




**Returns:**

A [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) instance wrapping the snapshot database. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/snapshot/snapshot/database/Database.hpp`

