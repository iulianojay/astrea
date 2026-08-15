

# Struct astrea::astro::TopocentricFrame

**template &lt;mp\_units::symbol\_text \_name\_, IsBodyFixedFrame auto \_parent\_, Angle \_lat\_, Angle \_lon\_, Distance \_alt\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**TopocentricFrame**](structastrea_1_1astro_1_1TopocentricFrame.md)



_A frame that is topocentric to a given body, defined relative to some body-fixed frame by a specific latitude, longitude, and altitude._ [More...](#detailed-description)

* `#include <TopocentricFrame.hpp>`



Inherits the following classes: [astrea::astro::FixedOffsetFrame](structastrea_1_1astro_1_1FixedOffsetFrame.md)


























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr auto | [**alt**](#variable-alt)   = `\_alt\_`<br>_The altitude of the topocentric frame relative to the parent body._  |
|  constexpr auto | [**body**](#variable-body)   = `\_parent\_.origin`<br>_The celestial body associated with the parent body-fixed frame._  |
|  constexpr auto | [**lat**](#variable-lat)   = `\_lat\_`<br>_The latitude of the topocentric frame relative to the parent body._  |
|  constexpr auto | [**lon**](#variable-lon)   = `\_lon\_`<br>_The longitude of the topocentric frame relative to the parent body._  |




















































































## Detailed Description




**Template parameters:**


* `_name_` The name of the topocentric frame. 
* `_parent_` The parent body-fixed frame from which this topocentric frame is derived. Must satisfy the IsBodyFixedFrame concept. 
* `_lat_` The latitude in the parent frame. 
* `_lon_` The longitude in the parent frame. 
* `_alt_` The altitude in the parent frame. 




    
## Public Static Attributes Documentation




### variable alt 

_The altitude of the topocentric frame relative to the parent body._ 
```C++
constexpr auto astrea::astro::TopocentricFrame< _name_, _parent_, _lat_, _lon_, _alt_ >::alt;
```




<hr>



### variable body 

_The celestial body associated with the parent body-fixed frame._ 
```C++
constexpr auto astrea::astro::TopocentricFrame< _name_, _parent_, _lat_, _lon_, _alt_ >::body;
```




<hr>



### variable lat 

_The latitude of the topocentric frame relative to the parent body._ 
```C++
constexpr auto astrea::astro::TopocentricFrame< _name_, _parent_, _lat_, _lon_, _alt_ >::lat;
```




<hr>



### variable lon 

_The longitude of the topocentric frame relative to the parent body._ 
```C++
constexpr auto astrea::astro::TopocentricFrame< _name_, _parent_, _lat_, _lon_, _alt_ >::lon;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/TopocentricFrame.hpp`

