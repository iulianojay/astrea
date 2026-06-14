

# Class astrea::snapshot::SpaceTrackClient



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**snapshot**](namespaceastrea_1_1snapshot.md) **>** [**SpaceTrackClient**](classastrea_1_1snapshot_1_1SpaceTrackClient.md)



[_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _class for interacting with the SpaceTrack API._[More...](#detailed-description)

* `#include <SpaceTrackClient.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum [**EnumType**](namespaceastrea_1_1snapshot.md#typedef-enumtype) | [**Action**](#enum-action)  <br>_Enumeration for the different actions that can be performed in SpaceTrack._  |
| enum [**EnumType**](namespaceastrea_1_1snapshot.md#typedef-enumtype) | [**Controller**](#enum-controller)  <br>_Enumeration for the different controllers available in SpaceTrack._  |
| enum [**EnumType**](namespaceastrea_1_1snapshot.md#typedef-enumtype) | [**PublicFilesClass**](#enum-publicfilesclass)  <br>_Enumeration for the different classes of public files available in SpaceTrack._  |
| typedef std::variant&lt; [**SpaceDataClass**](classastrea_1_1snapshot_1_1SpaceTrackClient.md#enum-spacedataclass), [**PublicFilesClass**](classastrea_1_1snapshot_1_1SpaceTrackClient.md#enum-publicfilesclass) &gt; | [**RequestClass**](#typedef-requestclass)  <br>_Type alias for the request class, which can be either SpaceDataClass or PublicFilesClass._  |
| enum [**EnumType**](namespaceastrea_1_1snapshot.md#typedef-enumtype) | [**SpaceDataClass**](#enum-spacedataclass)  <br>_Enumeration for the different classes of space data available in SpaceTrack._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SpaceTrackClient**](#function-spacetrackclient) () = default<br>_Default constructor for_ [_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _._ |
|  void | [**login**](#function-login) (const std::string & username, const std::string & password) <br>_Logs in to the SpaceTrack API._  |
|  nlohmann::json | [**query**](#function-query) (const std::string & username, const std::string & password, const [**Controller**](classastrea_1_1snapshot_1_1SpaceTrackClient.md#enum-controller) & controller=Controller::BASIC\_SPACE\_DATA, const [**Action**](classastrea_1_1snapshot_1_1SpaceTrackClient.md#enum-action) & action=Action::QUERY, const [**RequestClass**](classastrea_1_1snapshot_1_1SpaceTrackClient.md#typedef-requestclass) & requestClass=SpaceDataClass::GP, const std::vector&lt; std::pair&lt; std::string, std::string &gt; &gt; predicates={}) <br>_Queries the SpaceTrack API for data._  |
|  nlohmann::json | [**retrieve\_all**](#function-retrieve_all) (const std::string & username, const std::string & password) <br>_Retrieves all data from the SpaceTrack API._  |
|   | [**~SpaceTrackClient**](#function-spacetrackclient) () = default<br>_Default destructor for_ [_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _._ |




























## Detailed Description


This class provides methods to login, query data, and retrieve information from the SpaceTrack API. It supports various controllers and actions to access different types of space data. 

**Note:**

WARNING: Do NOT use this for automated scripts. I have NOT setup a check to make sure we're within the automated script limits and you could get your SpaceTrack account banned. 





    
## Public Types Documentation




### enum Action 

_Enumeration for the different actions that can be performed in SpaceTrack._ 
```C++
enum astrea::snapshot::SpaceTrackClient::Action {
    QUERY,
    MODEL_DEF
};
```



This enumeration defines the various actions that can be performed when querying data from the SpaceTrack API. 


        

<hr>



### enum Controller 

_Enumeration for the different controllers available in SpaceTrack._ 
```C++
enum astrea::snapshot::SpaceTrackClient::Controller {
    BASIC_SPACE_DATA,
    PUBLIC_FILES
};
```



This enumeration defines the various controllers that can be used to access different types of data from the SpaceTrack API. 


        

<hr>



### enum PublicFilesClass 

_Enumeration for the different classes of public files available in SpaceTrack._ 
```C++
enum astrea::snapshot::SpaceTrackClient::PublicFilesClass {
    DIRS,
    DOWNLOAD,
    FILES,
    LOAD_PUBLIC_DATA
};
```



This enumeration defines the various classes of public files that can be accessed from the SpaceTrack API. 


        

<hr>



### typedef RequestClass 

_Type alias for the request class, which can be either SpaceDataClass or PublicFilesClass._ 
```C++
using astrea::snapshot::SpaceTrackClient::RequestClass =  std::variant<SpaceDataClass, PublicFilesClass>;
```



This type alias allows for a unified way to handle different types of requests in the [**SpaceTrackClient**](classastrea_1_1snapshot_1_1SpaceTrackClient.md). 


        

<hr>



### enum SpaceDataClass 

_Enumeration for the different classes of space data available in SpaceTrack._ 
```C++
enum astrea::snapshot::SpaceTrackClient::SpaceDataClass {
    ANNOUNCEMENT,
    BOX_SCORE,
    CDM_PUBLIC,
    DECAY,
    GP,
    GP_HISTORY,
    LAUNCH_SITE,
    SATCAT,
    SATCAT_CHANGE,
    SATCAT_DEBUT,
    TIP
};
```



This enumeration defines the various classes of space data that can be queried from the SpaceTrack API. 


        

<hr>
## Public Functions Documentation




### function SpaceTrackClient 

_Default constructor for_ [_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _._
```C++
astrea::snapshot::SpaceTrackClient::SpaceTrackClient () = default
```



Initializes the [**SpaceTrackClient**](classastrea_1_1snapshot_1_1SpaceTrackClient.md) instance. 


        

<hr>



### function login 

_Logs in to the SpaceTrack API._ 
```C++
void astrea::snapshot::SpaceTrackClient::login (
    const std::string & username,
    const std::string & password
) 
```



This function authenticates the user with the SpaceTrack API using the provided username and password.




**Parameters:**


* `username` The username for the SpaceTrack account. 
* `password` The password for the SpaceTrack account. 




        

<hr>



### function query 

_Queries the SpaceTrack API for data._ 
```C++
nlohmann::json astrea::snapshot::SpaceTrackClient::query (
    const std::string & username,
    const std::string & password,
    const Controller & controller=Controller::BASIC_SPACE_DATA,
    const Action & action=Action::QUERY,
    const RequestClass & requestClass=SpaceDataClass::GP,
    const std::vector< std::pair< std::string, std::string > > predicates={}
) 
```



This function sends a query to the SpaceTrack API using the specified parameters and returns the response as a JSON object.




**Parameters:**


* `username` The username for the SpaceTrack account. 
* `password` The password for the SpaceTrack account. 
* `controller` The controller to use for the query. 
* `action` The action to perform (e.g., QUERY, MODEL\_DEF). 
* `requestClass` The class of data to request (e.g., GP, SATCAT). 
* `predicates` Optional predicates to filter the query results. 



**Returns:**

A JSON object containing the query results. 





        

<hr>



### function retrieve\_all 

_Retrieves all data from the SpaceTrack API._ 
```C++
nlohmann::json astrea::snapshot::SpaceTrackClient::retrieve_all (
    const std::string & username,
    const std::string & password
) 
```



This function retrieves all data available in the SpaceTrack API for the specified user.




**Parameters:**


* `username` The username for the SpaceTrack account. 
* `password` The password for the SpaceTrack account. 



**Returns:**

A JSON object containing all available data. 





        

<hr>



### function ~SpaceTrackClient 

_Default destructor for_ [_**SpaceTrackClient**_](classastrea_1_1snapshot_1_1SpaceTrackClient.md) _._
```C++
astrea::snapshot::SpaceTrackClient::~SpaceTrackClient () = default
```



Cleans up the [**SpaceTrackClient**](classastrea_1_1snapshot_1_1SpaceTrackClient.md) instance. 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/snapshot/snapshot/http-queries/spacetrack/SpaceTrackClient.hpp`

