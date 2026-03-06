

# Struct mp\_units::quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**mp\_units**](namespacemp__units.md) **>** [**quantity\_point\_like\_traits&lt; astrea::astro::Date &gt;**](structmp__units_1_1quantity__point__like__traits_3_01astrea_1_1astro_1_1Date_01_4.md)



_Specialization of mp\_units::quantity\_point\_like\_traits for the Date class._ [More...](#detailed-description)

* `#include <Date.hpp>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef long double | [**rep**](#typedef-rep)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**explicit\_export**](#variable-explicit_export)   = `true`<br> |
|  constexpr bool | [**explicit\_import**](#variable-explicit_import)   = `false`<br> |
|  constexpr auto | [**point\_origin**](#variable-point_origin)   = `astrea::astro::J2K`<br> |
|  constexpr auto | [**reference**](#variable-reference)   = `non\_si::day`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**astrea::astro::Date**](classastrea_1_1astro_1_1Date.md) | [**from\_numerical\_value**](#function-from_numerical_value) (rep v) <br> |
|  constexpr rep | [**to\_numerical\_value**](#function-to_numerical_value) ([**astrea::astro::Date**](classastrea_1_1astro_1_1Date.md) date) <br> |


























## Detailed Description


This specialization provides the necessary traits for using Date with mp-units. 


    
## Public Types Documentation




### typedef rep 

```C++
using mp_units::quantity_point_like_traits< astrea::astro::Date >::rep =  long double;
```




<hr>
## Public Static Attributes Documentation




### variable explicit\_export 

```C++
constexpr bool mp_units::quantity_point_like_traits< astrea::astro::Date >::explicit_export;
```




<hr>



### variable explicit\_import 

```C++
constexpr bool mp_units::quantity_point_like_traits< astrea::astro::Date >::explicit_import;
```




<hr>



### variable point\_origin 

```C++
constexpr auto mp_units::quantity_point_like_traits< astrea::astro::Date >::point_origin;
```




<hr>



### variable reference 

```C++
constexpr auto mp_units::quantity_point_like_traits< astrea::astro::Date >::reference;
```




<hr>
## Public Static Functions Documentation




### function from\_numerical\_value 

```C++
static inline constexpr astrea::astro::Date mp_units::quantity_point_like_traits< astrea::astro::Date >::from_numerical_value (
    rep v
) 
```




<hr>



### function to\_numerical\_value 

```C++
static inline constexpr rep mp_units::quantity_point_like_traits< astrea::astro::Date >::to_numerical_value (
    astrea::astro::Date date
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/time/Date.hpp`

