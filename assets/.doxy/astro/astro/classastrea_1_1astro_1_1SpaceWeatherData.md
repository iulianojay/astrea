

# Class astrea::astro::SpaceWeatherData



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md)



_Class to hold space weather data read from a file._ [More...](#detailed-description)

* `#include <SpaceWeatherData.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SpaceWeatherData**](#function-spaceweatherdata-12) () = default<br>_Default constructor for_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _._ |
|   | [**SpaceWeatherData**](#function-spaceweatherdata-22) (const std::filesystem::path & infile, std::optional&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; startDate=std::nullopt, std::optional&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; endDate=std::nullopt) <br>_Construct a_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _object by reading space weather data from a file._ |
|  const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**at**](#function-at-14) (std::size\_t index) const<br>_Access the space weather parameters at the specified index with bounds checking._  |
|  [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**at**](#function-at-24) (std::size\_t index) <br>_Access the space weather parameters at the specified index with bounds checking._  |
|  const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**at**](#function-at-34) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Access the space weather parameters for the specified date._  |
|  [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**at**](#function-at-44) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) <br>_Access the space weather parameters for the specified date._  |
|  const std::vector&lt; [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) &gt; & | [**data**](#function-data) () const<br>_Returns a const reference to the vector of space weather parameters._  |
|  bool | [**empty**](#function-empty) () noexcept const<br>_Checks if the space weather data is empty._  |
|  const std::optional&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; & | [**endDate**](#function-enddate) () noexcept const<br>_Access the optional end date for filtering the data._  |
|  const std::filesystem::path & | [**infile**](#function-infile) () noexcept const<br>_Returns the path to the space weather data file._  |
|  const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**operator[]**](#function-operator) (std::size\_t index) const<br>_Access the space weather parameters at the specified index._  |
|  [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) & | [**operator[]**](#function-operator_1) (std::size\_t index) <br>_Access the space weather parameters at the specified index._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of space weather data entries._  |
|  const std::optional&lt; [**Date**](classastrea_1_1astro_1_1Date.md) &gt; & | [**startDate**](#function-startdate) () noexcept const<br>_Access the optional start date for filtering the data._  |
|   | [**~SpaceWeatherData**](#function-spaceweatherdata) () = default<br>_Default destructor for_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _._ |




























## Detailed Description


This class contains a vector of [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md) and provides methods to access the data. 


    
## Public Functions Documentation




### function SpaceWeatherData [1/2]

_Default constructor for_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _._
```C++
astrea::astro::SpaceWeatherData::SpaceWeatherData () = default
```




<hr>



### function SpaceWeatherData [2/2]

_Construct a_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _object by reading space weather data from a file._
```C++
astrea::astro::SpaceWeatherData::SpaceWeatherData (
    const std::filesystem::path & infile,
    std::optional< Date > startDate=std::nullopt,
    std::optional< Date > endDate=std::nullopt
) 
```





**Parameters:**


* `infile` Path to the space weather data file. 
* `startDate` Optional start date for filtering the data. If provided, only data on or after this date will be included. 
* `endDate` Optional end date for filtering the data. If provided, only data on or before this date will be included. 




        

<hr>



### function at [1/4]

_Access the space weather parameters at the specified index with bounds checking._ 
```C++
const SpaceWeatherParameters & astrea::astro::SpaceWeatherData::at (
    std::size_t index
) const
```





**Parameters:**


* `index` Index of the space weather parameters to access. 



**Returns:**

const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters at the specified index. 




**Exception:**


* `std::out_of_range` If the index is out of range. 




        

<hr>



### function at [2/4]

_Access the space weather parameters at the specified index with bounds checking._ 
```C++
SpaceWeatherParameters & astrea::astro::SpaceWeatherData::at (
    std::size_t index
) 
```





**Parameters:**


* `index` Index of the space weather parameters to access. 



**Returns:**

[**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters at the specified index. 




**Exception:**


* `std::out_of_range` If the index is out of range. 




        

<hr>



### function at [3/4]

_Access the space weather parameters for the specified date._ 
```C++
const SpaceWeatherParameters & astrea::astro::SpaceWeatherData::at (
    const Date & date
) const
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) of the space weather parameters to access. 



**Returns:**

const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters for the specified date. 




**Exception:**


* `std::out_of_range` If no data exists for the specified date. 




        

<hr>



### function at [4/4]

_Access the space weather parameters for the specified date._ 
```C++
SpaceWeatherParameters & astrea::astro::SpaceWeatherData::at (
    const Date & date
) 
```





**Parameters:**


* `date` [**Date**](classastrea_1_1astro_1_1Date.md) of the space weather parameters to access. 



**Returns:**

[**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters for the specified date. 




**Exception:**


* `std::out_of_range` If no data exists for the specified date. 




        

<hr>



### function data 

_Returns a const reference to the vector of space weather parameters._ 
```C++
const std::vector< SpaceWeatherParameters > & astrea::astro::SpaceWeatherData::data () const
```





**Returns:**

const std::vector&lt;SpaceWeatherParameters&gt;& The vector of space weather parameters. 





        

<hr>



### function empty 

_Checks if the space weather data is empty._ 
```C++
bool astrea::astro::SpaceWeatherData::empty () noexcept const
```





**Returns:**

true If there are no space weather data entries. 




**Returns:**

false If there are space weather data entries. 





        

<hr>



### function endDate 

_Access the optional end date for filtering the data._ 
```C++
const std::optional< Date > & astrea::astro::SpaceWeatherData::endDate () noexcept const
```





**Returns:**

const std::optional&lt;Date&gt;& Optional end date. 





        

<hr>



### function infile 

_Returns the path to the space weather data file._ 
```C++
const std::filesystem::path & astrea::astro::SpaceWeatherData::infile () noexcept const
```





**Returns:**

const std::filesystem::path& The path to the space weather data file. 





        

<hr>



### function operator[] 

_Access the space weather parameters at the specified index._ 
```C++
const SpaceWeatherParameters & astrea::astro::SpaceWeatherData::operator[] (
    std::size_t index
) const
```





**Parameters:**


* `index` Index of the space weather parameters to access. 



**Returns:**

const [**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters at the specified index. 





        

<hr>



### function operator[] 

_Access the space weather parameters at the specified index._ 
```C++
SpaceWeatherParameters & astrea::astro::SpaceWeatherData::operator[] (
    std::size_t index
) 
```





**Parameters:**


* `index` Index of the space weather parameters to access. 



**Returns:**

[**SpaceWeatherParameters**](structastrea_1_1astro_1_1SpaceWeatherParameters.md)& Reference to the space weather parameters at the specified index. 





        

<hr>



### function size 

_Returns the number of space weather data entries._ 
```C++
std::size_t astrea::astro::SpaceWeatherData::size () const
```





**Returns:**

std::size\_t The number of entries in the space weather data. 





        

<hr>



### function startDate 

_Access the optional start date for filtering the data._ 
```C++
const std::optional< Date > & astrea::astro::SpaceWeatherData::startDate () noexcept const
```





**Returns:**

const std::optional&lt;Date&gt;& Optional start date. 





        

<hr>



### function ~SpaceWeatherData 

_Default destructor for_ [_**SpaceWeatherData**_](classastrea_1_1astro_1_1SpaceWeatherData.md) _._
```C++
astrea::astro::SpaceWeatherData::~SpaceWeatherData () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/SpaceWeatherData.hpp`

