

# Class astrea::snapshot::EthzClient



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**snapshot**](namespaceastrea_1_1snapshot.md) **>** [**EthzClient**](classastrea_1_1snapshot_1_1EthzClient.md)



[_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _class for interacting with the ETHZ satellite database API._[More...](#detailed-description)

* `#include <EthzClient.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EthzClient**](#function-ethzclient) () <br>_Default constructor for_ [_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _._ |
|  nlohmann::json | [**query**](#function-query-12) (const astro::Date & startDate, const astro::Date & endDate, const std::string & name, const bool & includeFrequencyData=false) <br>_Queries the ETHZ satellite database for satellite data._  |
|  nlohmann::json | [**query**](#function-query-22) (const astro::Date & startDate, const astro::Date & endDate, const unsigned & noradId, const bool & includeFrequencyData=false) <br>_Queries the ETHZ satellite database for satellite data by NORAD ID._  |
|   | [**~EthzClient**](#function-ethzclient) () = default<br>_Default destructor for_ [_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _._ |




























## Detailed Description


This class provides methods to query satellite data from the ETHZ satellite database. It supports querying by date range and satellite name or NORAD ID, and can include frequency data if requested. 


    
## Public Functions Documentation




### function EthzClient 

_Default constructor for_ [_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _._
```C++
inline astrea::snapshot::EthzClient::EthzClient () 
```



Initializes the [**EthzClient**](classastrea_1_1snapshot_1_1EthzClient.md) with a minimum start date of 2023-03-10 00:00:00.0. 


        

<hr>



### function query [1/2]

_Queries the ETHZ satellite database for satellite data._ 
```C++
nlohmann::json astrea::snapshot::EthzClient::query (
    const astro::Date & startDate,
    const astro::Date & endDate,
    const std::string & name,
    const bool & includeFrequencyData=false
) 
```



This function sends a request to the ETHZ satellite database API to retrieve satellite data within the specified date range and optionally includes frequency data.




**Parameters:**


* `startDate` The start date for the query. 
* `endDate` The end date for the query. 
* `name` Optional name of the satellite to filter results. 
* `noradId` Optional NORAD ID of the satellite to filter results. 
* `includeFrequencyData` Whether to include frequency data in the results (default is false). 



**Returns:**

A JSON object containing the query results. 





        

<hr>



### function query [2/2]

_Queries the ETHZ satellite database for satellite data by NORAD ID._ 
```C++
nlohmann::json astrea::snapshot::EthzClient::query (
    const astro::Date & startDate,
    const astro::Date & endDate,
    const unsigned & noradId,
    const bool & includeFrequencyData=false
) 
```



This function sends a request to the ETHZ satellite database API to retrieve satellite data for a specific NORAD ID within the specified date range and optionally includes frequency data.




**Parameters:**


* `startDate` The start date for the query. 
* `endDate` The end date for the query. 
* `noradId` The NORAD ID of the satellite to filter results. 
* `includeFrequencyData` Whether to include frequency data in the results (default is false). 



**Returns:**

A JSON object containing the query results. 





        

<hr>



### function ~EthzClient 

_Default destructor for_ [_**EthzClient**_](classastrea_1_1snapshot_1_1EthzClient.md) _._
```C++
astrea::snapshot::EthzClient::~EthzClient () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/snapshot/snapshot/http-queries/ethz/EthzClient.hpp`

