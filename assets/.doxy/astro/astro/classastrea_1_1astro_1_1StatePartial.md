

# Class astrea::astro::StatePartial



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**StatePartial**](classastrea_1_1astro_1_1StatePartial.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StatePartial**](#function-statepartial-12) () = default<br>_Default constructor for_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _._ |
|   | [**StatePartial**](#function-statepartial-22) (const [**Date**](classastrea_1_1astro_1_1Date.md) & epoch, const [**OrbitalElementPartials**](classastrea_1_1astro_1_1OrbitalElementPartials.md) & elementPartials, const std::optional&lt; [**AttitudePartials**](classastrea_1_1astro_1_1AttitudePartials.md) &gt; & attitudePartial=std::nullopt) <br>_Constructs a_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _with given orbital element partials and astrodynamics system._ |
|  std::vector&lt; double &gt; | [**force\_to\_double\_vector**](#function-force_to_double_vector) () const<br>_Converts the_ [_**State**_](classastrea_1_1astro_1_1State.md) _to a vector of Unitless values._ |
|  const [**Date**](classastrea_1_1astro_1_1Date.md) & | [**get\_epoch**](#function-get_epoch) () const<br>_Gets the epoch of the state partial._  |
|  [**State**](classastrea_1_1astro_1_1State.md) | [**operator\***](#function-operator) (const Time & time) const<br>_Multiplies the_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _by a time to get a_[_**State**_](classastrea_1_1astro_1_1State.md) _._ |




























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
    const Date & epoch,
    const OrbitalElementPartials & elementPartials,
    const std::optional< AttitudePartials > & attitudePartial=std::nullopt
) 
```





**Parameters:**


* `epoch` The epoch of the state. 
* `sys` The astrodynamics system associated with the state. 
* `elementPartials` The orbital element partials of the state. 
* `attitudePartial` The attitude partial of the state, represented as a quaternion derivative. 




        

<hr>



### function force\_to\_double\_vector 

_Converts the_ [_**State**_](classastrea_1_1astro_1_1State.md) _to a vector of Unitless values._
```C++
inline std::vector< double > astrea::astro::StatePartial::force_to_double_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector containing the orbital element partials and attitude partials as unitless values. 





        

<hr>



### function get\_epoch 

_Gets the epoch of the state partial._ 
```C++
const Date & astrea::astro::StatePartial::get_epoch () const
```





**Returns:**

const [**Date**](classastrea_1_1astro_1_1Date.md)& Reference to the epoch of the state partial. 





        

<hr>



### function operator\* 

_Multiplies the_ [_**StatePartial**_](classastrea_1_1astro_1_1StatePartial.md) _by a time to get a_[_**State**_](classastrea_1_1astro_1_1State.md) _._
```C++
State astrea::astro::StatePartial::operator* (
    const Time & time
) const
```





**Parameters:**


* `time` The time to multiply with. 



**Returns:**

[**State**](classastrea_1_1astro_1_1State.md) The resulting [**State**](classastrea_1_1astro_1_1State.md) after multiplication. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/state/State.hpp`

