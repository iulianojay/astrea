

# Class astrea::astro::SpaceWeatherProvider



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**SpaceWeatherProvider**](classastrea_1_1astro_1_1SpaceWeatherProvider.md)



_Lightweight provider that shares an immutable space weather data snapshot. Using this layer of abstraction for now to enable data hot-swapping in the future if needed._ 

* `#include <SpaceWeatherProvider.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; const [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) &gt; | [**DataPtr**](#typedef-dataptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SpaceWeatherProvider**](#function-spaceweatherprovider-14) () = default<br>_Default constructor for_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _._ |
|   | [**SpaceWeatherProvider**](#function-spaceweatherprovider-24) (DataPtr data) <br>_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with an explicit immutable space weather snapshot._ |
|   | [**SpaceWeatherProvider**](#function-spaceweatherprovider-34) ([**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) data) <br>_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with a pre-built space weather data object._ |
|   | [**SpaceWeatherProvider**](#function-spaceweatherprovider-44) (std::in\_place\_t, Args &&... args) <br>_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with a pre-built space weather data object in place._ |
|  const DataPtr & | [**data**](#function-data) () noexcept const<br>_Access the space weather data snapshot._  |
|  bool | [**empty**](#function-empty) () noexcept const<br>_Checks if the space weather data is empty._  |
|  std::size\_t | [**size**](#function-size) () const<br>_Returns the number of space weather data entries._  |




























## Public Types Documentation




### typedef DataPtr 

```C++
using astrea::astro::SpaceWeatherProvider::DataPtr =  std::shared_ptr<const SpaceWeatherData>;
```




<hr>
## Public Functions Documentation




### function SpaceWeatherProvider [1/4]

_Default constructor for_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _._
```C++
astrea::astro::SpaceWeatherProvider::SpaceWeatherProvider () = default
```




<hr>



### function SpaceWeatherProvider [2/4]

_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with an explicit immutable space weather snapshot._
```C++
inline explicit astrea::astro::SpaceWeatherProvider::SpaceWeatherProvider (
    DataPtr data
) 
```





**Parameters:**


* `data` Shared immutable space weather data. 




        

<hr>



### function SpaceWeatherProvider [3/4]

_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with a pre-built space weather data object._
```C++
inline explicit astrea::astro::SpaceWeatherProvider::SpaceWeatherProvider (
    SpaceWeatherData data
) 
```





**Parameters:**


* `data` Space weather data to share. 




        

<hr>



### function SpaceWeatherProvider [4/4]

_Construct a_ [_**SpaceWeatherProvider**_](classastrea_1_1astro_1_1SpaceWeatherProvider.md) _with a pre-built space weather data object in place._
```C++
template<typename... Args>
inline explicit astrea::astro::SpaceWeatherProvider::SpaceWeatherProvider (
    std::in_place_t,
    Args &&... args
) 
```





**Parameters:**


* `args` Arguments to construct the [**SpaceWeatherData**](classastrea_1_1astro_1_1SpaceWeatherData.md) object. 




        

<hr>



### function data 

_Access the space weather data snapshot._ 
```C++
inline const DataPtr & astrea::astro::SpaceWeatherProvider::data () noexcept const
```





**Returns:**

const DataPtr& Shared pointer to the immutable space weather data. 





        

<hr>



### function empty 

_Checks if the space weather data is empty._ 
```C++
inline bool astrea::astro::SpaceWeatherProvider::empty () noexcept const
```





**Returns:**

true If there are no space weather data entries. 




**Returns:**

false If there are space weather data entries. 





        

<hr>



### function size 

_Returns the number of space weather data entries._ 
```C++
inline std::size_t astrea::astro::SpaceWeatherProvider::size () const
```





**Returns:**

std::size\_t The number of space weather data entries. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/force_models/space_weather/SpaceWeatherProvider.hpp`

