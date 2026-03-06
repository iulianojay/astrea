

# Class astrea::astro::StatePartial



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StatePartial**](#function-statepartial-12) () = default<br>_Default constructor for_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _._ |
|   | [**StatePartial**](#function-statepartial-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & elementPartials, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys) <br>_Constructs a_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _with given orbital element partials and astrodynamics system._ |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Date**](classastrea_1_1astro_1_1Date.md) & | [**get\_epoch**](#function-get_epoch) () const<br>_Gets the epoch of the state partial._  |
|  [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & | [**get\_system**](#function-get_system) () const<br>_Gets the astrodynamics system associated with the state._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**operator\***](#function-operator) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Time**](classastrea_1_1astro_1_1CartesianVector.md) & time) const<br>_Multiplies the_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _by a time to get a_[_**State**_](classastrea_1_1astro_1_1State.md) _._ |




























## Public Functions Documentation




### function StatePartial [1/2]

_Default constructor for_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _._
```C++
astrea::astro::StatePartial::StatePartial () = default
```




<hr>



### function StatePartial [2/2]

_Constructs a_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _with given orbital element partials and astrodynamics system._
```C++
inline astrea::astro::StatePartial::StatePartial (
    const  OrbitalElementPartials & elementPartials,
    const  Date & epoch,
    const  AstrodynamicsSystem & sys
) 
```





**Parameters:**


* `elementPartials` The orbital element partials of the state. 
* `epoch` The epoch of the state. 
* `sys` The astrodynamics system associated with the state. 




        

<hr>



### function get\_epoch 

_Gets the epoch of the state partial._ 
```C++
const  Date & astrea::astro::StatePartial::get_epoch () const
```





**Returns:**

const [**Date**](classastrea_1_1astro_1_1Date.md)& Reference to the epoch of the state partial. 





        

<hr>



### function get\_system 

_Gets the astrodynamics system associated with the state._ 
```C++
const  AstrodynamicsSystem & astrea::astro::StatePartial::get_system () const
```





**Returns:**

const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md)& Reference to the astrodynamics system. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _by a time to get a_[_**State**_](classastrea_1_1astro_1_1State.md) _._
```C++
State astrea::astro::StatePartial::operator* (
    const  Time & time
) const
```





**Parameters:**


* `time` The time to multiply with. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) The resulting [**State**](classastrea_1_1astro_1_1State.md) after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/State.hpp`

