

# Class astrea::snapshot::DatabaseUtilityWrapper

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**snapshot**](namespaceastrea_1_1snapshot.md) **>** [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md)



_Database utility wrapper for the snapshot module._ [More...](#detailed-description)

* `#include <Database.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DatabaseUtilityWrapper**](#function-databaseutilitywrapper) (T && db) <br>_Default constructor for_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _._ |
|  std::vector&lt; astro::GeneralPerturbations &gt; | [**get\_all**](#function-get_all) (Args &&... args) const<br>_Gets all GeneralPerturbations records from the database._  |
|  const T & | [**get\_database**](#function-get_database) () const<br>_Gets the underlying database instance._  |
|  astro::GeneralPerturbations | [**get\_sat\_from\_norad\_id**](#function-get_sat_from_norad_id) (const unsigned & id) const<br>_Gets a GeneralPerturbations record by its NORAD ID._  |
|  std::vector&lt; astro::GeneralPerturbations &gt; | [**get\_sats\_by\_name**](#function-get_sats_by_name) (const std::string & name) const<br>_Gets a GeneralPerturbations record by its name._  |
|  std::vector&lt; astro::GeneralPerturbations &gt; | [**get\_sats\_in\_range**](#function-get_sats_in_range) (const Distance & minPeriapsis, const Distance & maxApoapsis) const<br>_Gets GeneralPerturbations records within a specified range of periapsis and apoapsis._  |
|   | [**~DatabaseUtilityWrapper**](#function-databaseutilitywrapper) () = default<br>_Default destructor for_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _._ |




























## Detailed Description


This class provides a wrapper around the SQLite database used in the snapshot module, allowing for easy access to GeneralPerturbations data and other database operations.




**Template parameters:**


* `T` The type of the database (e.g., sqlite\_orm::Storage&lt;GeneralPerturbations&gt;). 




    
## Public Functions Documentation




### function DatabaseUtilityWrapper 

_Default constructor for_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _._
```C++
inline astrea::snapshot::DatabaseUtilityWrapper::DatabaseUtilityWrapper (
    T && db
) 
```



Initializes the [**DatabaseUtilityWrapper**](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) with the provided database instance.




**Parameters:**


* `db` The database instance to wrap. 




        

<hr>



### function get\_all 

_Gets all GeneralPerturbations records from the database._ 
```C++
template<typename... Args>
std::vector< astro::GeneralPerturbations > astrea::snapshot::DatabaseUtilityWrapper::get_all (
    Args &&... args
) const
```





**Template parameters:**


* `Args` Types of the optional arguments. 



**Parameters:**


* `args` Optional arguments to pass to the database query. 



**Returns:**

A vector containing all GeneralPerturbations records. 





        

<hr>



### function get\_database 

_Gets the underlying database instance._ 
```C++
const T & astrea::snapshot::DatabaseUtilityWrapper::get_database () const
```





**Returns:**

A reference to the wrapped database instance. 





        

<hr>



### function get\_sat\_from\_norad\_id 

_Gets a GeneralPerturbations record by its NORAD ID._ 
```C++
astro::GeneralPerturbations astrea::snapshot::DatabaseUtilityWrapper::get_sat_from_norad_id (
    const unsigned & id
) const
```





**Parameters:**


* `id` The NORAD ID of the GeneralPerturbations record to retrieve. 



**Returns:**

A GeneralPerturbations object corresponding to the given NORAD ID. 





        

<hr>



### function get\_sats\_by\_name 

_Gets a GeneralPerturbations record by its name._ 
```C++
std::vector< astro::GeneralPerturbations > astrea::snapshot::DatabaseUtilityWrapper::get_sats_by_name (
    const std::string & name
) const
```





**Parameters:**


* `name` The name of the GeneralPerturbations record to retrieve. 



**Returns:**

A GeneralPerturbations object corresponding to the given name. 





        

<hr>



### function get\_sats\_in\_range 

_Gets GeneralPerturbations records within a specified range of periapsis and apoapsis._ 
```C++
std::vector< astro::GeneralPerturbations > astrea::snapshot::DatabaseUtilityWrapper::get_sats_in_range (
    const Distance & minPeriapsis,
    const Distance & maxApoapsis
) const
```





**Parameters:**


* `minPeriapsis` The minimum periapsis distance. 
* `maxApoapsis` The maximum apoapsis distance. 



**Returns:**

A vector containing GeneralPerturbations records that fall within the specified range. 





        

<hr>



### function ~DatabaseUtilityWrapper 

_Default destructor for_ [_**DatabaseUtilityWrapper**_](classastrea_1_1snapshot_1_1DatabaseUtilityWrapper.md) _._
```C++
astrea::snapshot::DatabaseUtilityWrapper::~DatabaseUtilityWrapper () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/snapshot/snapshot/database/Database.hpp`

