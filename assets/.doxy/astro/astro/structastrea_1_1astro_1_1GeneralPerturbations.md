

# Struct astrea::astro::GeneralPerturbations



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md)



[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _structure representing a Ground Position (GP) object from SpaceTrack._[More...](#detailed-description)

* `#include <GeneralPerturbations.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::optional&lt; double &gt; | [**APOAPSIS**](#variable-apoapsis)  <br>_Apoapsis altitude in kilometers._  |
|  std::optional&lt; long double &gt; | [**ARG\_OF\_PERICENTER**](#variable-arg_of_pericenter)  <br>_Argument of pericenter in degrees._  |
|  std::optional&lt; long double &gt; | [**BSTAR**](#variable-bstar)  <br>_B\* drag term (BSTAR) in inverse Earth radii._  |
|  std::string | [**CCSDS\_OMM\_VERS**](#variable-ccsds_omm_vers)  <br>_CCSDS OMM version._  |
|  std::string | [**CENTER\_NAME**](#variable-center_name)  <br>_Name of the center._  |
|  std::optional&lt; char &gt; | [**CLASSIFICATION\_TYPE**](#variable-classification_type)  <br>_Classification type._  |
|  std::string | [**COMMENT**](#variable-comment)  <br>_Comment._  |
|  std::optional&lt; std::string &gt; | [**COUNTRY\_CODE**](#variable-country_code)  <br>_Country code._  |
|  std::optional&lt; std::string &gt; | [**CREATION\_DATE**](#variable-creation_date)  <br>_Creation date._  |
|  int | [**DB\_ID**](#variable-db_id)  <br>_Database ID for the GP object._  |
|  std::optional&lt; std::string &gt; | [**DECAY\_DATE**](#variable-decay_date)  <br>_Decay date._  |
|  std::optional&lt; long double &gt; | [**ECCENTRICITY**](#variable-eccentricity)  <br>_Eccentricity._  |
|  std::optional&lt; short &gt; | [**ELEMENT\_SET\_NO**](#variable-element_set_no)  <br>_Element set number._  |
|  std::optional&lt; short unsigned &gt; | [**EPHEMERIS\_TYPE**](#variable-ephemeris_type)  <br>_Ephemeris type._  |
|  std::optional&lt; std::string &gt; | [**EPOCH**](#variable-epoch)  <br>_Epoch._  |
|  std::optional&lt; long unsigned &gt; | [**FILE**](#variable-file)  <br>_File number._  |
|  unsigned | [**GP\_ID**](#variable-gp_id)  <br>_General Perturbations ID._  |
|  std::optional&lt; long double &gt; | [**INCLINATION**](#variable-inclination)  <br>_Inclination in degrees._  |
|  std::optional&lt; std::string &gt; | [**LAUNCH\_DATE**](#variable-launch_date)  <br>_Launch date._  |
|  std::optional&lt; double &gt; | [**MEAN\_ANOMALY**](#variable-mean_anomaly)  <br>_Mean anomaly in degrees._  |
|  std::string | [**MEAN\_ELEMENT\_THEORY**](#variable-mean_element_theory)  <br>_Mean element theory._  |
|  std::optional&lt; long double &gt; | [**MEAN\_MOTION**](#variable-mean_motion)  <br>_Mean motion in revolutions per day._  |
|  std::optional&lt; long double &gt; | [**MEAN\_MOTION\_DDOT**](#variable-mean_motion_ddot)  <br>_Mean motion derivative in revolutions per day squared._  |
|  std::optional&lt; long double &gt; | [**MEAN\_MOTION\_DOT**](#variable-mean_motion_dot)  <br>_Mean motion second derivative in revolutions per day cubed._  |
|  unsigned | [**NORAD\_CAT\_ID**](#variable-norad_cat_id)  <br>_NORAD catalog ID._  |
|  std::optional&lt; std::string &gt; | [**OBJECT\_ID**](#variable-object_id)  <br>_Object ID._  |
|  std::optional&lt; std::string &gt; | [**OBJECT\_NAME**](#variable-object_name)  <br>_Object name._  |
|  std::optional&lt; std::string &gt; | [**OBJECT\_TYPE**](#variable-object_type)  <br>_Object type._  |
|  std::string | [**ORIGINATOR**](#variable-originator)  <br>_Originator of the data._  |
|  std::optional&lt; double &gt; | [**PERIAPSIS**](#variable-periapsis)  <br>_Periapsis altitude in kilometers._  |
|  std::optional&lt; double &gt; | [**PERIOD**](#variable-period)  <br>_Orbital period in minutes._  |
|  std::optional&lt; long double &gt; | [**RA\_OF\_ASC\_NODE**](#variable-ra_of_asc_node)  <br>_Right ascension of ascending node in degrees._  |
|  std::optional&lt; std::string &gt; | [**RCS\_SIZE**](#variable-rcs_size)  <br>_Radar cross-section size._  |
|  std::string | [**REF\_FRAME**](#variable-ref_frame)  <br>_Reference frame._  |
|  std::optional&lt; unsigned &gt; | [**REV\_AT\_EPOCH**](#variable-rev_at_epoch)  <br>_Revolution number at epoch._  |
|  std::optional&lt; double &gt; | [**SEMIMAJOR\_AXIS**](#variable-semimajor_axis)  <br>_Semimajor axis in kilometers._  |
|  std::optional&lt; std::string &gt; | [**SITE**](#variable-site)  <br>_Site of the GP object._  |
|  std::string | [**TIME\_SYSTEM**](#variable-time_system)  <br>_Time system used for the GP object._  |
|  std::optional&lt; std::string &gt; | [**TLE\_LINE0**](#variable-tle_line0)  <br>_TLE line 0 (usually the satellite name)_  |
|  std::optional&lt; std::string &gt; | [**TLE\_LINE1**](#variable-tle_line1)  <br>_TLE line 1 (first line of TLE data)_  |
|  std::optional&lt; std::string &gt; | [**TLE\_LINE2**](#variable-tle_line2)  <br>_TLE line 2 (second line of TLE data)_  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**GeneralPerturbations**](#function-generalperturbations-12) () = default<br>_Default constructor for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._ |
|   | [**GeneralPerturbations**](#function-generalperturbations-22) (const nlohmann::json & data) <br>_Constructor that initializes_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _from a JSON object._ |
|   | [**~GeneralPerturbations**](#function-generalperturbations) () = default<br>_Default destructor for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._ |




























## Detailed Description


This structure is used to hold data retrieved from the SpaceTrack API, specifically for GP objects. It includes various attributes such as APOAPSIS, ECCENTRICITY, and others, which are relevant to satellite tracking and orbital mechanics.
* 

**Note:**

: definition can be found here [https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html](https://www.space-track.org/basicspacedata/modeldef/class/gp/format/html) 







    
## Public Attributes Documentation




### variable APOAPSIS 

_Apoapsis altitude in kilometers._ 
```C++
std::optional<double> astrea::astro::GeneralPerturbations::APOAPSIS;
```




<hr>



### variable ARG\_OF\_PERICENTER 

_Argument of pericenter in degrees._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::ARG_OF_PERICENTER;
```




<hr>



### variable BSTAR 

_B\* drag term (BSTAR) in inverse Earth radii._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::BSTAR;
```




<hr>



### variable CCSDS\_OMM\_VERS 

_CCSDS OMM version._ 
```C++
std::string astrea::astro::GeneralPerturbations::CCSDS_OMM_VERS;
```




<hr>



### variable CENTER\_NAME 

_Name of the center._ 
```C++
std::string astrea::astro::GeneralPerturbations::CENTER_NAME;
```




<hr>



### variable CLASSIFICATION\_TYPE 

_Classification type._ 
```C++
std::optional<char> astrea::astro::GeneralPerturbations::CLASSIFICATION_TYPE;
```




<hr>



### variable COMMENT 

_Comment._ 
```C++
std::string astrea::astro::GeneralPerturbations::COMMENT;
```




<hr>



### variable COUNTRY\_CODE 

_Country code._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::COUNTRY_CODE;
```




<hr>



### variable CREATION\_DATE 

_Creation date._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::CREATION_DATE;
```




<hr>



### variable DB\_ID 

_Database ID for the GP object._ 
```C++
int astrea::astro::GeneralPerturbations::DB_ID;
```




<hr>



### variable DECAY\_DATE 

_Decay date._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::DECAY_DATE;
```




<hr>



### variable ECCENTRICITY 

_Eccentricity._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::ECCENTRICITY;
```




<hr>



### variable ELEMENT\_SET\_NO 

_Element set number._ 
```C++
std::optional<short> astrea::astro::GeneralPerturbations::ELEMENT_SET_NO;
```




<hr>



### variable EPHEMERIS\_TYPE 

_Ephemeris type._ 
```C++
std::optional<short unsigned> astrea::astro::GeneralPerturbations::EPHEMERIS_TYPE;
```




<hr>



### variable EPOCH 

_Epoch._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::EPOCH;
```




<hr>



### variable FILE 

_File number._ 
```C++
std::optional<long unsigned> astrea::astro::GeneralPerturbations::FILE;
```




<hr>



### variable GP\_ID 

_General Perturbations ID._ 
```C++
unsigned astrea::astro::GeneralPerturbations::GP_ID;
```




<hr>



### variable INCLINATION 

_Inclination in degrees._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::INCLINATION;
```




<hr>



### variable LAUNCH\_DATE 

_Launch date._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::LAUNCH_DATE;
```




<hr>



### variable MEAN\_ANOMALY 

_Mean anomaly in degrees._ 
```C++
std::optional<double> astrea::astro::GeneralPerturbations::MEAN_ANOMALY;
```




<hr>



### variable MEAN\_ELEMENT\_THEORY 

_Mean element theory._ 
```C++
std::string astrea::astro::GeneralPerturbations::MEAN_ELEMENT_THEORY;
```




<hr>



### variable MEAN\_MOTION 

_Mean motion in revolutions per day._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::MEAN_MOTION;
```




<hr>



### variable MEAN\_MOTION\_DDOT 

_Mean motion derivative in revolutions per day squared._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::MEAN_MOTION_DDOT;
```




<hr>



### variable MEAN\_MOTION\_DOT 

_Mean motion second derivative in revolutions per day cubed._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::MEAN_MOTION_DOT;
```




<hr>



### variable NORAD\_CAT\_ID 

_NORAD catalog ID._ 
```C++
unsigned astrea::astro::GeneralPerturbations::NORAD_CAT_ID;
```




<hr>



### variable OBJECT\_ID 

_Object ID._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::OBJECT_ID;
```




<hr>



### variable OBJECT\_NAME 

_Object name._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::OBJECT_NAME;
```




<hr>



### variable OBJECT\_TYPE 

_Object type._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::OBJECT_TYPE;
```




<hr>



### variable ORIGINATOR 

_Originator of the data._ 
```C++
std::string astrea::astro::GeneralPerturbations::ORIGINATOR;
```




<hr>



### variable PERIAPSIS 

_Periapsis altitude in kilometers._ 
```C++
std::optional<double> astrea::astro::GeneralPerturbations::PERIAPSIS;
```




<hr>



### variable PERIOD 

_Orbital period in minutes._ 
```C++
std::optional<double> astrea::astro::GeneralPerturbations::PERIOD;
```




<hr>



### variable RA\_OF\_ASC\_NODE 

_Right ascension of ascending node in degrees._ 
```C++
std::optional<long double> astrea::astro::GeneralPerturbations::RA_OF_ASC_NODE;
```




<hr>



### variable RCS\_SIZE 

_Radar cross-section size._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::RCS_SIZE;
```




<hr>



### variable REF\_FRAME 

_Reference frame._ 
```C++
std::string astrea::astro::GeneralPerturbations::REF_FRAME;
```




<hr>



### variable REV\_AT\_EPOCH 

_Revolution number at epoch._ 
```C++
std::optional<unsigned> astrea::astro::GeneralPerturbations::REV_AT_EPOCH;
```




<hr>



### variable SEMIMAJOR\_AXIS 

_Semimajor axis in kilometers._ 
```C++
std::optional<double> astrea::astro::GeneralPerturbations::SEMIMAJOR_AXIS;
```




<hr>



### variable SITE 

_Site of the GP object._ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::SITE;
```




<hr>



### variable TIME\_SYSTEM 

_Time system used for the GP object._ 
```C++
std::string astrea::astro::GeneralPerturbations::TIME_SYSTEM;
```




<hr>



### variable TLE\_LINE0 

_TLE line 0 (usually the satellite name)_ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::TLE_LINE0;
```




<hr>



### variable TLE\_LINE1 

_TLE line 1 (first line of TLE data)_ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::TLE_LINE1;
```




<hr>



### variable TLE\_LINE2 

_TLE line 2 (second line of TLE data)_ 
```C++
std::optional<std::string> astrea::astro::GeneralPerturbations::TLE_LINE2;
```




<hr>
## Public Functions Documentation




### function GeneralPerturbations [1/2]

_Default constructor for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._
```C++
astrea::astro::GeneralPerturbations::GeneralPerturbations () = default
```




<hr>



### function GeneralPerturbations [2/2]

_Constructor that initializes_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _from a JSON object._
```C++
astrea::astro::GeneralPerturbations::GeneralPerturbations (
    const nlohmann::json & data
) 
```





**Parameters:**


* `data` The JSON object containing the GP data. 




        

<hr>



### function ~GeneralPerturbations 

_Default destructor for_ [_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _._
```C++
astrea::astro::GeneralPerturbations::~GeneralPerturbations () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_data_formats/GeneralPerturbations.hpp`

