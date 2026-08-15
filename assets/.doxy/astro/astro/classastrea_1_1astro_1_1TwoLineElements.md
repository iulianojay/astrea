

# Class astrea::astro::TwoLineElements



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md)



_Class representing the two-line element (TLE) format for orbital data._ 

* `#include <TwoLineElements.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TwoLineElements**](#function-twolineelements-15) () = default<br>_Default constructor._  |
|   | [**TwoLineElements**](#function-twolineelements-25) (const std::array&lt; std::string, 3 &gt; rawTle) <br>_Construct a new Two Line Elements object from modern TLEs._  |
|   | [**TwoLineElements**](#function-twolineelements-35) (const std::array&lt; std::string, 2 &gt; rawTle) <br>_Construct a new Two Line Elements object from classic TLEs._  |
|   | [**TwoLineElements**](#function-twolineelements-45) (const [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & other) <br>_Copy constructor._  |
|   | [**TwoLineElements**](#function-twolineelements-55) ([**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) && other) noexcept<br>_Move constructor._  |
|  std::string | [**get\_1st\_line**](#function-get_1st_line) () const<br>_Get the 1st line of the TLE._  |
|  std::string | [**get\_2nd\_line**](#function-get_2nd_line) () const<br>_Get the 2nd line of the TLE._  |
|  Angle | [**get\_argument\_of\_perigee**](#function-get_argument_of_perigee) () const<br>_Get the argument of perigee of the satellite._  |
|  BallisticCoefficient | [**get\_ballistic\_coefficient**](#function-get_ballistic_coefficient) () const<br>_Get the ballistic coefficient of the satellite._  |
|  unsigned | [**get\_catalogue\_number**](#function-get_catalogue_number) () const<br>_Get the catalogue number of the satellite._  |
|  std::size\_t | [**get\_check\_sum1**](#function-get_check_sum1) () const<br>_Get the 1st checksum of the satellite._  |
|  std::size\_t | [**get\_check\_sum2**](#function-get_check_sum2) () const<br>_Get the 2nd checksum of the satellite._  |
|  std::string | [**get\_classification**](#function-get_classification) () const<br>_Get the classification of the satellite._  |
|  Unitless | [**get\_eccentricity**](#function-get_eccentricity) () const<br>_Get the eccentricity of the satellite._  |
|  std::size\_t | [**get\_element\_set\_number**](#function-get_element_set_number) () const<br>_Get the element set number of the satellite._  |
|  std::size\_t | [**get\_ephemeris\_type**](#function-get_ephemeris_type) () const<br>_Get the ephemeris type of the satellite._  |
|  [**Date**](classastrea_1_1astro_1_1Date.md) | [**get\_epoch**](#function-get_epoch) () const<br>_Get the epoch of the satellite._  |
|  Angle | [**get\_inclination**](#function-get_inclination) () const<br>_Get the inclination of the satellite._  |
|  std::string | [**get\_launch\_number**](#function-get_launch_number) () const<br>_Get the launch number of the satellite._  |
|  std::string | [**get\_launch\_piece**](#function-get_launch_piece) () const<br>_Get the launch piece of the satellite._  |
|  std::string | [**get\_launch\_year**](#function-get_launch_year) () const<br>_Get the launch year of the satellite._  |
|  MeanMotion | [**get\_mean\_motion**](#function-get_mean_motion) () const<br>_Get the mean motion of the satellite._  |
|  MeanMotion1stDer | [**get\_mean\_motion\_1st\_derivative**](#function-get_mean_motion_1st_derivative) () const<br>_Get the 1st derivative of the mean motion._  |
|  MeanMotion2ndDer | [**get\_mean\_motion\_2nd\_derivative**](#function-get_mean_motion_2nd_derivative) () const<br>_Get the 2nd derivative of the mean motion._  |
|  std::string | [**get\_name**](#function-get_name) () const<br>_Get the name of the satellite._  |
|  std::array&lt; std::string, 2 &gt; | [**get\_raw\_tle**](#function-get_raw_tle) () const<br>_Get the raw TLE data._  |
|  unsigned | [**get\_rev\_number**](#function-get_rev_number) () const<br>_Get the revolution number of the satellite._  |
|  Angle | [**get\_right\_ascension**](#function-get_right_ascension) () const<br>_Get the right ascension of the satellite._  |
|  Distance | [**get\_semimajor**](#function-get_semimajor) () const<br>_Get the semimajor axis of the satellite._  |
|  Angle | [**get\_true\_anomaly**](#function-get_true_anomaly) () const<br>_Get the true anomaly of the satellite._  |
|  bool | [**operator!=**](#function-operator) (const [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & other) const<br>_Inequality operator._  |
|  [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & | [**operator=**](#function-operator_1) ([**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) && other) noexcept<br>_Move assignment operator._  |
|  [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & | [**operator=**](#function-operator_2) (const [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & other) <br>_Copy assignment operator._  |
|  bool | [**operator==**](#function-operator_3) (const [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) & other) const<br>_Equality operator._  |
|   | [**~TwoLineElements**](#function-twolineelements) () = default<br>_Default destructor._  |




























## Public Functions Documentation




### function TwoLineElements [1/5]

_Default constructor._ 
```C++
astrea::astro::TwoLineElements::TwoLineElements () = default
```




<hr>



### function TwoLineElements [2/5]

_Construct a new Two Line Elements object from modern TLEs._ 
```C++
astrea::astro::TwoLineElements::TwoLineElements (
    const std::array< std::string, 3 > rawTle
) 
```





**Parameters:**


* `rawTle` The raw TLE data. 
* `sys` The astrodynamics system. 




        

<hr>



### function TwoLineElements [3/5]

_Construct a new Two Line Elements object from classic TLEs._ 
```C++
astrea::astro::TwoLineElements::TwoLineElements (
    const std::array< std::string, 2 > rawTle
) 
```





**Parameters:**


* `rawTle` The raw TLE data. 
* `sys` The astrodynamics system. 




        

<hr>



### function TwoLineElements [4/5]

_Copy constructor._ 
```C++
astrea::astro::TwoLineElements::TwoLineElements (
    const TwoLineElements & other
) 
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to copy from. 




        

<hr>



### function TwoLineElements [5/5]

_Move constructor._ 
```C++
astrea::astro::TwoLineElements::TwoLineElements (
    TwoLineElements && other
) noexcept
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to move from. 




        

<hr>



### function get\_1st\_line 

_Get the 1st line of the TLE._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_1st_line () const
```





**Returns:**

std::string The 1st line of the TLE. 





        

<hr>



### function get\_2nd\_line 

_Get the 2nd line of the TLE._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_2nd_line () const
```





**Returns:**

std::string The 2nd line of the TLE. 





        

<hr>



### function get\_argument\_of\_perigee 

_Get the argument of perigee of the satellite._ 
```C++
inline Angle astrea::astro::TwoLineElements::get_argument_of_perigee () const
```





**Returns:**

Angle The argument of perigee of the satellite. 





        

<hr>



### function get\_ballistic\_coefficient 

_Get the ballistic coefficient of the satellite._ 
```C++
inline BallisticCoefficient astrea::astro::TwoLineElements::get_ballistic_coefficient () const
```





**Returns:**

BallisticCoefficient The ballistic coefficient of the satellite. 





        

<hr>



### function get\_catalogue\_number 

_Get the catalogue number of the satellite._ 
```C++
inline unsigned astrea::astro::TwoLineElements::get_catalogue_number () const
```





**Returns:**

unsigned The catalogue number of the satellite. 





        

<hr>



### function get\_check\_sum1 

_Get the 1st checksum of the satellite._ 
```C++
inline std::size_t astrea::astro::TwoLineElements::get_check_sum1 () const
```





**Returns:**

std::size\_t The 1st checksum of the satellite. 





        

<hr>



### function get\_check\_sum2 

_Get the 2nd checksum of the satellite._ 
```C++
inline std::size_t astrea::astro::TwoLineElements::get_check_sum2 () const
```





**Returns:**

std::size\_t The 2nd checksum of the satellite. 





        

<hr>



### function get\_classification 

_Get the classification of the satellite._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_classification () const
```





**Returns:**

std::string The classification of the satellite. 





        

<hr>



### function get\_eccentricity 

_Get the eccentricity of the satellite._ 
```C++
inline Unitless astrea::astro::TwoLineElements::get_eccentricity () const
```





**Returns:**

Unitless The eccentricity of the satellite. 





        

<hr>



### function get\_element\_set\_number 

_Get the element set number of the satellite._ 
```C++
inline std::size_t astrea::astro::TwoLineElements::get_element_set_number () const
```





**Returns:**

std::size\_t The element set number of the satellite. 





        

<hr>



### function get\_ephemeris\_type 

_Get the ephemeris type of the satellite._ 
```C++
inline std::size_t astrea::astro::TwoLineElements::get_ephemeris_type () const
```





**Returns:**

std::size\_t The ephemeris type of the satellite. 





        

<hr>



### function get\_epoch 

_Get the epoch of the satellite._ 
```C++
inline Date astrea::astro::TwoLineElements::get_epoch () const
```





**Returns:**

[**Date**](classastrea_1_1astro_1_1Date.md) The epoch of the satellite. 





        

<hr>



### function get\_inclination 

_Get the inclination of the satellite._ 
```C++
inline Angle astrea::astro::TwoLineElements::get_inclination () const
```





**Returns:**

Angle The inclination of the satellite. 





        

<hr>



### function get\_launch\_number 

_Get the launch number of the satellite._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_launch_number () const
```





**Returns:**

std::string The launch number of the satellite. 





        

<hr>



### function get\_launch\_piece 

_Get the launch piece of the satellite._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_launch_piece () const
```





**Returns:**

std::string The launch piece of the satellite. 





        

<hr>



### function get\_launch\_year 

_Get the launch year of the satellite._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_launch_year () const
```





**Returns:**

std::string The launch year of the satellite. 





        

<hr>



### function get\_mean\_motion 

_Get the mean motion of the satellite._ 
```C++
inline MeanMotion astrea::astro::TwoLineElements::get_mean_motion () const
```





**Returns:**

MeanMotion The mean motion of the satellite. 





        

<hr>



### function get\_mean\_motion\_1st\_derivative 

_Get the 1st derivative of the mean motion._ 
```C++
inline MeanMotion1stDer astrea::astro::TwoLineElements::get_mean_motion_1st_derivative () const
```





**Returns:**

MeanMotion1stDer The 1st derivative of the mean motion. 





        

<hr>



### function get\_mean\_motion\_2nd\_derivative 

_Get the 2nd derivative of the mean motion._ 
```C++
inline MeanMotion2ndDer astrea::astro::TwoLineElements::get_mean_motion_2nd_derivative () const
```





**Returns:**

MeanMotion2ndDer The 2nd derivative of the mean motion. 





        

<hr>



### function get\_name 

_Get the name of the satellite._ 
```C++
inline std::string astrea::astro::TwoLineElements::get_name () const
```





**Returns:**

std::string The name of the satellite. 





        

<hr>



### function get\_raw\_tle 

_Get the raw TLE data._ 
```C++
inline std::array< std::string, 2 > astrea::astro::TwoLineElements::get_raw_tle () const
```





**Returns:**

std::array&lt;std::string, 2&gt; The raw TLE data. 





        

<hr>



### function get\_rev\_number 

_Get the revolution number of the satellite._ 
```C++
inline unsigned astrea::astro::TwoLineElements::get_rev_number () const
```





**Returns:**

unsigned The revolution number of the satellite. 





        

<hr>



### function get\_right\_ascension 

_Get the right ascension of the satellite._ 
```C++
inline Angle astrea::astro::TwoLineElements::get_right_ascension () const
```





**Returns:**

Angle The right ascension of the satellite. 





        

<hr>



### function get\_semimajor 

_Get the semimajor axis of the satellite._ 
```C++
inline Distance astrea::astro::TwoLineElements::get_semimajor () const
```





**Returns:**

Distance The semimajor axis of the satellite. 





        

<hr>



### function get\_true\_anomaly 

_Get the true anomaly of the satellite._ 
```C++
inline Angle astrea::astro::TwoLineElements::get_true_anomaly () const
```





**Returns:**

Angle The true anomaly of the satellite. 





        

<hr>



### function operator!= 

_Inequality operator._ 
```C++
bool astrea::astro::TwoLineElements::operator!= (
    const TwoLineElements & other
) const
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to compare with. 



**Returns:**

true if the objects are not equal, false otherwise. 





        

<hr>



### function operator= 

_Move assignment operator._ 
```C++
TwoLineElements & astrea::astro::TwoLineElements::operator= (
    TwoLineElements && other
) noexcept
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to move from.



**Returns:**

[**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md)& Reference to this object after assignment. 





        

<hr>



### function operator= 

_Copy assignment operator._ 
```C++
TwoLineElements & astrea::astro::TwoLineElements::operator= (
    const TwoLineElements & other
) 
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to copy from.



**Returns:**

[**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md)& Reference to this object after assignment. 





        

<hr>



### function operator== 

_Equality operator._ 
```C++
bool astrea::astro::TwoLineElements::operator== (
    const TwoLineElements & other
) const
```





**Parameters:**


* `other` The other [**TwoLineElements**](classastrea_1_1astro_1_1TwoLineElements.md) object to compare with. 



**Returns:**

true if the objects are equal, false otherwise. 





        

<hr>



### function ~TwoLineElements 

_Default destructor._ 
```C++
astrea::astro::TwoLineElements::~TwoLineElements () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/orbital_data_formats/TwoLineElements.hpp`

