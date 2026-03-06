

# Class astrea::astro::Date



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Date**](classastrea_1_1astro_1_1Date.md)



_Class representing a date in the astrea astro library._ [More...](#detailed-description)

* `#include <Date.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Date**](#function-date-12) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) & jdate=J2000) <br>_Construct a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from a JulianDate._ |
|   | [**Date**](#function-date-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string & epoch, [**const**](classastrea_1_1astro_1_1CartesianVector.md) std::string & format="%Y-%m-%[**d**](classastrea_1_1astro_1_1CartesianVector.md) %[**H:**](classastrea_1_1astro_1_1CartesianVector.md)%[**M:**](classastrea_1_1astro_1_1CartesianVector.md)%[**S"**](classastrea_1_1astro_1_1CartesianVector.md)) <br>_Construct a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from a JulianDate._ |
|  std::string | [**epoch**](#function-epoch) () const<br>_Get the epoch of this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object as a string._ |
|  [**Angle**](classastrea_1_1astro_1_1CartesianVector.md) | [**gmst**](#function-gmst) () const<br>_Get the Greenwich Mean Sidereal Time (GMST) for this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  std::chrono::time\_point&lt; std::chrono::gps\_clock &gt; | [**gps**](#function-gps) () const<br>_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in GPS clock format._ |
|  std::chrono::time\_point&lt; [**Clock\_T**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**in\_clock**](#function-in_clock) () const<br>_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in a specified clock format._ |
|  [**JulianDate**](namespaceastrea_1_1astro.md#typedef-juliandate) | [**jd**](#function-jd) () const<br>_Get the Julian date representation of this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**double**](classastrea_1_1astro_1_1CartesianVector.md) | [**jdn**](#function-jdn) () const<br>_Get the Julian date in days since the epoch._  |
|  std::chrono::duration&lt; [**double**](classastrea_1_1astro_1_1CartesianVector.md), std::ratio&lt; 86400 &gt; &gt; | [**mjd**](#function-mjd) () const<br>_Get the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _(MJD) representation of this_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**operator+**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) const<br>_Add a Time object to this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**Date**](classastrea_1_1astro_1_1Date.md) & | [**operator+=**](#function-operator_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) <br>_Add a Time object to this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object in place._ |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**operator-**](#function-operator-) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) const<br>_Subtract a Time object from this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**Time**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator-**](#function-operator-_1) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & other) const<br>_Subtract another_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from this_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**Date**](classastrea_1_1astro_1_1Date.md) & | [**operator-=**](#function-operator-_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) <br>_Subtract a Time object from this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object in place._ |
|  [**auto**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator&lt;=&gt;**](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & other) const<br>_Compare this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object with another_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  [**bool**](classastrea_1_1astro_1_1CartesianVector.md) | [**operator==**](#function-operator_2) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & other) const<br>_Check if this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object is equal to another_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |
|  std::chrono::time\_point&lt; std::chrono::system\_clock &gt; | [**sys**](#function-sys) () const<br>_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in TT clock format._ |
|  std::chrono::time\_point&lt; std::chrono::tai\_clock &gt; | [**tai**](#function-tai) () const<br>_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in TAI clock format._ |
|  std::chrono::time\_point&lt; std::chrono::utc\_clock &gt; | [**utc**](#function-utc) () const<br>_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in UTC clock format._ |
|   | [**~Date**](#function-date) () = default<br>_Destructor for_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._ |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) | [**now**](#function-now) () noexcept<br>_Get the current date and time as a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._ |


























## Detailed Description


This class provides functionality for handling dates, including conversions to and from Julian dates, sidereal time calculations, and various clock conversions. 


    
## Public Functions Documentation




### function Date [1/2]

_Construct a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from a JulianDate._
```C++
inline astrea::astro::Date::Date (
    const  JulianDate & jdate=J2000
) 
```





**Parameters:**


* `jdate` The JulianDate to initialize the [**Date**](classastrea_1_1astro_1_1Date.md) object. 




        

<hr>



### function Date [2/2]

_Construct a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from a JulianDate._
```C++
inline astrea::astro::Date::Date (
    const std::string & epoch,
    const std::string & format="%Y-%m-% d % H: % M: % S"
) 
```





**Parameters:**


* `epoch` The JulianDate to initialize the [**Date**](classastrea_1_1astro_1_1Date.md) object. 
* `format` The format of the date string, default is "%Y-%m-%d %H:%M:%S". 




        

<hr>



### function epoch 

_Get the epoch of this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object as a string._
```C++
std::string astrea::astro::Date::epoch () const
```





**Returns:**

std::string The epoch of this [**Date**](classastrea_1_1astro_1_1Date.md) object formatted as a string. 





        

<hr>



### function gmst 

_Get the Greenwich Mean Sidereal Time (GMST) for this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
Angle astrea::astro::Date::gmst () const
```





**Returns:**

Angle The Greenwich Mean Sidereal Time for this [**Date**](classastrea_1_1astro_1_1Date.md) object. 





        

<hr>



### function gps 

_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in GPS clock format._
```C++
inline std::chrono::time_point< std::chrono::gps_clock > astrea::astro::Date::gps () const
```





**Returns:**

std::chrono::time\_point&lt;std::chrono::gps\_clock&gt; 





        

<hr>



### function in\_clock 

_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in a specified clock format._
```C++
template<typename  Clock_T>
inline std::chrono::time_point< Clock_T > astrea::astro::Date::in_clock () const
```





**Template parameters:**


* `Clock_T` The clock type to convert to. 



**Returns:**

std::chrono::time\_point&lt;Clock\_T&gt; The [**Date**](classastrea_1_1astro_1_1Date.md) in the specified clock format. 





        

<hr>



### function jd 

_Get the Julian date representation of this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
inline JulianDate astrea::astro::Date::jd () const
```





**Returns:**

JulianDate The Julian date representation of this [**Date**](classastrea_1_1astro_1_1Date.md) object. 





        

<hr>



### function jdn 

_Get the Julian date in days since the epoch._ 
```C++
inline double astrea::astro::Date::jdn () const
```





**Returns:**

double The Julian date in days since the epoch. 





        

<hr>



### function mjd 

_Get the Modified Julian_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _(MJD) representation of this_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
inline std::chrono::duration< double , std::ratio< 86400 > > astrea::astro::Date::mjd () const
```





**Returns:**

std::chrono::duration&lt;double, std::ratio&lt;86400&gt;&gt; The Modified Julian [**Date**](classastrea_1_1astro_1_1Date.md) representation of this [**Date**](classastrea_1_1astro_1_1Date.md) object. 





        

<hr>



### function operator+ 

_Add a Time object to this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
Date astrea::astro::Date::operator+ (
    const  Time & time
) const
```





**Parameters:**


* `time` The Time object to add. 



**Returns:**

[**Date**](classastrea_1_1astro_1_1Date.md) A new [**Date**](classastrea_1_1astro_1_1Date.md) object representing the result of the addition. 





        

<hr>



### function operator+= 

_Add a Time object to this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object in place._
```C++
Date & astrea::astro::Date::operator+= (
    const  Time & time
) 
```





**Parameters:**


* `time` The Time object to add. 



**Returns:**

[**Date**](classastrea_1_1astro_1_1Date.md)& A reference to this [**Date**](classastrea_1_1astro_1_1Date.md) object after the addition. 





        

<hr>



### function operator- 

_Subtract a Time object from this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
Date astrea::astro::Date::operator- (
    const  Time & time
) const
```





**Parameters:**


* `time` The Time object to subtract. 



**Returns:**

[**Date**](classastrea_1_1astro_1_1Date.md) A new [**Date**](classastrea_1_1astro_1_1Date.md) object representing the result of the subtraction. 





        

<hr>



### function operator- 

_Subtract another_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object from this_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
Time astrea::astro::Date::operator- (
    const  Date & other
) const
```





**Parameters:**


* `other` The [**Date**](classastrea_1_1astro_1_1Date.md) object to subtract. 



**Returns:**

Time A Time object representing the difference between the two dates. 





        

<hr>



### function operator-= 

_Subtract a Time object from this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object in place._
```C++
Date & astrea::astro::Date::operator-= (
    const  Time & time
) 
```





**Parameters:**


* `time` The Time object to subtract. 



**Returns:**

[**Date**](classastrea_1_1astro_1_1Date.md)& A reference to this [**Date**](classastrea_1_1astro_1_1Date.md) object after the subtraction. 





        

<hr>



### function operator&lt;=&gt; 

_Compare this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object with another_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
inline auto astrea::astro::Date::operator<=> (
    const  Date & other
) const
```





**Parameters:**


* `other` The [**Date**](classastrea_1_1astro_1_1Date.md) object to compare with. 



**Returns:**

std::strong\_ordering A strong ordering result indicating the comparison. 





        

<hr>



### function operator== 

_Check if this_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object is equal to another_[_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
inline bool astrea::astro::Date::operator== (
    const  Date & other
) const
```





**Parameters:**


* `other` The [**Date**](classastrea_1_1astro_1_1Date.md) object to compare with. 



**Returns:**

bool True if the two [**Date**](classastrea_1_1astro_1_1Date.md) objects are equal, false otherwise. 





        

<hr>



### function sys 

_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in TT clock format._
```C++
inline std::chrono::time_point< std::chrono::system_clock > astrea::astro::Date::sys () const
```





**Returns:**

std::chrono::time\_point&lt;std::chrono::tt\_clock&gt;


Get the [**Date**](classastrea_1_1astro_1_1Date.md) in sys clock format.




**Returns:**

std::chrono::time\_point&lt;std::chrono::system\_clock&gt; 





        

<hr>



### function tai 

_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in TAI clock format._
```C++
inline std::chrono::time_point< std::chrono::tai_clock > astrea::astro::Date::tai () const
```





**Returns:**

std::chrono::time\_point&lt;std::chrono::tai\_clock&gt; 





        

<hr>



### function utc 

_Get the_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _in UTC clock format._
```C++
inline std::chrono::time_point< std::chrono::utc_clock > astrea::astro::Date::utc () const
```





**Returns:**

std::chrono::time\_point&lt;std::chrono::utc\_clock&gt; 





        

<hr>



### function ~Date 

_Destructor for_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _._
```C++
astrea::astro::Date::~Date () = default
```




<hr>
## Public Static Functions Documentation




### function now 

_Get the current date and time as a_ [_**Date**_](classastrea_1_1astro_1_1Date.md) _object._
```C++
static const  Date astrea::astro::Date::now () noexcept
```





**Returns:**

const [**Date**](classastrea_1_1astro_1_1Date.md) The current date and time. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/Date.hpp`

