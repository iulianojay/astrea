

# Class astrea::astro::Spacecraft



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md)



_A class representing a spacecraft in the astrea astro platform. This class encapsulates the properties of a spacecraft, including its mass, dynamic coefficients, and surface areas._ 

* `#include <Spacecraft.hpp>`



Inherits the following classes: [astrea::astro::PayloadPlatform](classastrea_1_1astro_1_1PayloadPlatform.md)
































## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr Unitless | [**DEFAULT\_COEFFICIENT\_OF\_DRAG**](#variable-default_coefficient_of_drag)   = `2.2 \* astrea::detail::unitless`<br> |
|  constexpr Unitless | [**DEFAULT\_COEFFICIENT\_OF\_LIFT**](#variable-default_coefficient_of_lift)   = `0.9 \* astrea::detail::unitless`<br> |
|  constexpr Unitless | [**DEFAULT\_COEFFICIENT\_OF\_REFLECTIVITY**](#variable-default_coefficient_of_reflectivity)   = `/* multi line expression */`<br> |
|  constexpr SurfaceArea | [**DEFAULT\_LIFT\_AREA**](#variable-default_lift_area)   = `1.0 \* mp\_units::pow&lt;2&gt;(astrea::detail::minor\_distance\_unit)`<br> |
|  constexpr Mass | [**DEFAULT\_MASS**](#variable-default_mass)   = `1000.0 \* astrea::detail::mass\_unit`<br> |
|  constexpr SurfaceArea | [**DEFAULT\_RAM\_AREA**](#variable-default_ram_area)   = `1.0 \* mp\_units::pow&lt;2&gt;(astrea::detail::minor\_distance\_unit)`<br> |
|  constexpr SurfaceArea | [**DEFAULT\_SOLAR\_AREA**](#variable-default_solar_area)   = `1.0 \* mp\_units::pow&lt;2&gt;(astrea::detail::minor\_distance\_unit)`<br> |










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Spacecraft**](#function-spacecraft-12) () <br>_Default constructor for_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._ |
|   | [**Spacecraft**](#function-spacecraft-22) (const [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) & gp, const [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) & sys) <br>_Constructs a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _with a_[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _object and an_[_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _._ |
|  Unitless | [**get\_coefficient\_of\_drag**](#function-get_coefficient_of_drag) () const<br>_Gets the coefficients of drag, lift, and reflectivity._  |
|  Unitless | [**get\_coefficient\_of\_lift**](#function-get_coefficient_of_lift) () const<br>_Gets the coefficient of lift._  |
|  Unitless | [**get\_coefficient\_of\_reflectivity**](#function-get_coefficient_of_reflectivity) () const<br>_Gets the coefficient of reflectivity._  |
| virtual std::size\_t | [**get\_id**](#function-get_id) () const<br>_Gets the unique identifier of the spacecraft._  |
| virtual [**RadiusVector**](namespaceastrea_1_1astro.md#typedef-radiusvector)&lt; frames::earth::icrf &gt; | [**get\_inertial\_position**](#function-get_inertial_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) override const<br>_Gets the inertial position of the spacecraft at a specific date._  |
| virtual [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; frames::earth::icrf &gt; | [**get\_inertial\_velocity**](#function-get_inertial_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) override const<br>_Gets the inertial velocity of the spacecraft at a specific date._  |
|  [**State**](classastrea_1_1astro_1_1State.md) & | [**get\_initial\_state**](#function-get_initial_state-12) () <br>_Gets the initial state of the spacecraft._  |
|  const [**State**](classastrea_1_1astro_1_1State.md) & | [**get\_initial\_state**](#function-get_initial_state-22) () const<br>_Gets the initial state of the spacecraft._  |
|  SurfaceArea | [**get\_lift\_area**](#function-get_lift_area) () const<br>_Gets the lift area of the spacecraft._  |
| virtual Mass | [**get\_mass**](#function-get_mass) () const<br>_Gets the mass of the spacecraft._  |
| virtual std::string | [**get\_name**](#function-get_name) () const<br>_Gets the name of the spacecraft._  |
|  SurfaceArea | [**get\_ram\_area**](#function-get_ram_area) () const<br>_Gets the surface areas for ram, solar, and lift._  |
|  SurfaceArea | [**get\_solar\_area**](#function-get_solar_area) () const<br>_Gets the solar area of the spacecraft._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & | [**get\_state\_history**](#function-get_state_history-12) () <br>_Gets the state history of the spacecraft._  |
|  const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & | [**get\_state\_history**](#function-get_state_history-22) () const<br>_Gets the state history of the spacecraft._  |
|  bool | [**operator==**](#function-operator) (const [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) & other) const<br>_Equality operator to compare two_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _objects._ |
|  void | [**set\_coefficient\_of\_drag**](#function-set_coefficient_of_drag) (const Unitless & cd) <br>_Sets the coefficients of drag._  |
|  void | [**set\_coefficient\_of\_lift**](#function-set_coefficient_of_lift) (const Unitless & cl) <br>_Sets the coefficient of lift._  |
|  void | [**set\_coefficient\_of\_reflectivity**](#function-set_coefficient_of_reflectivity) (const Unitless & cr) <br>_Sets the coefficient of reflectivity._  |
|  void | [**set\_lift\_area**](#function-set_lift_area) (const SurfaceArea & liftArea) <br>_Sets the lift area of the spacecraft._  |
|  void | [**set\_mass**](#function-set_mass) (const Mass & mass) <br>_Sets the mass of the spacecraft._  |
|  void | [**set\_name**](#function-set_name) (const std::string & name) <br>_Sets the name of the spacecraft._  |
|  void | [**set\_ram\_area**](#function-set_ram_area) (const SurfaceArea & ramArea) <br>_Sets the surface area for ram._  |
|  void | [**set\_solar\_area**](#function-set_solar_area) (const SurfaceArea & solarArea) <br>_Sets the solar area of the spacecraft._  |
|  void | [**set\_state\_history**](#function-set_state_history) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & history) <br>_Stores the state history of the spacecraft._  |
|  void | [**store\_state**](#function-store_state) (const [**State**](classastrea_1_1astro_1_1State.md) & state) <br>_Stores a single state in the spacecraft's state history._  |
| virtual  | [**~Spacecraft**](#function-spacecraft) () = default<br>_Virtual destructor for_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._ |


## Public Functions inherited from astrea::astro::PayloadPlatform

See [astrea::astro::PayloadPlatform](classastrea_1_1astro_1_1PayloadPlatform.md)

| Type | Name |
| ---: | :--- |
|  void | [**attach\_payload**](classastrea_1_1astro_1_1PayloadPlatform.md#function-attach_payload) (const PayloadParameters\_T & parameters) <br>_Attaches a single payload to the platform._  |
|  void | [**attach\_payloads**](classastrea_1_1astro_1_1PayloadPlatform.md#function-attach_payloads) (const std::vector&lt; PayloadParameters\_T &gt; & parameterPack) <br>_Attaches multiple payloads to the platform._  |
| virtual std::size\_t | [**get\_id**](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_id) () const = 0<br>_Get the ID of the payload._  |
| virtual Mass | [**get\_mass**](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_mass) () const<br>_Get the mass of the platform._  |
|  std::vector&lt; Payload\_T &gt; & | [**get\_payloads**](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_payloads-12) () <br>_Retrieves the list of payloads attached to the platform._  |
|  const std::vector&lt; Payload\_T &gt; & | [**get\_payloads**](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_payloads-22) () const<br>_Retrieves the list of payloads attached to the platform (const version)._  |


## Public Functions inherited from astrea::astro::FrameReference

See [astrea::astro::FrameReference](classastrea_1_1astro_1_1FrameReference.md)

| Type | Name |
| ---: | :--- |
|   | [**FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default constructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Acceleration, frames::earth::icrf &gt; | [**get\_inertial\_acceleration**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_acceleration) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const<br>_Get the acceleration of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Distance, frames::earth::icrf &gt; | [**get\_inertial\_position**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the position of the frame in Earth-Centered Inertial coordinates._  |
| virtual [**CartesianVector**](classastrea_1_1astro_1_1CartesianVector.md)&lt; Velocity, frames::earth::icrf &gt; | [**get\_inertial\_velocity**](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity) (const [**Date**](classastrea_1_1astro_1_1Date.md) & date) const = 0<br>_Get the velocity of the frame in Earth-Centered Inertial coordinates._  |
| virtual std::string | [**get\_name**](classastrea_1_1astro_1_1FrameReference.md#function-get_name) () const = 0<br>_Get the name of the frame reference._  |
| virtual  | [**~FrameReference**](classastrea_1_1astro_1_1FrameReference.md#function-framereference) () = default<br>_Default destructor for_ [_**FrameReference**_](classastrea_1_1astro_1_1FrameReference.md) _._ |




















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  Unitless | [**\_coefficientOfDrag**](#variable-_coefficientofdrag)   = `DEFAULT\_COEFFICIENT\_OF\_DRAG`<br>_Coefficient of drag._  |
|  Unitless | [**\_coefficientOfLift**](#variable-_coefficientoflift)   = `DEFAULT\_COEFFICIENT\_OF\_LIFT`<br>_Coefficient of lift._  |
|  Unitless | [**\_coefficientOfReflectivity**](#variable-_coefficientofreflectivity)   = `DEFAULT\_COEFFICIENT\_OF\_REFLECTIVITY`<br>_Coefficient of reflectivity._  |
|  std::size\_t | [**\_id**](#variable-_id)  <br> |
|  SurfaceArea | [**\_liftArea**](#variable-_liftarea)   = `DEFAULT\_LIFT\_AREA`<br>_Lift area of the spacecraft._  |
|  Mass | [**\_mass**](#variable-_mass)   = `DEFAULT\_MASS`<br>_Mass of the spacecraft._  |
|  std::string | [**\_name**](#variable-_name)  <br> |
|  SurfaceArea | [**\_ramArea**](#variable-_ramarea)   = `DEFAULT\_RAM\_AREA`<br>_Ram area of the spacecraft._  |
|  [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) | [**\_stateHistory**](#variable-_statehistory)  <br> |
|  SurfaceArea | [**\_sunArea**](#variable-_sunarea)   = `DEFAULT\_SOLAR\_AREA`<br>_Solar area of the spacecraft._  |


## Protected Attributes inherited from astrea::astro::PayloadPlatform

See [astrea::astro::PayloadPlatform](classastrea_1_1astro_1_1PayloadPlatform.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; Payload\_T &gt; | [**\_payloads**](classastrea_1_1astro_1_1PayloadPlatform.md#variable-_payloads)  <br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**generate\_id**](#function-generate_id) () <br>_Generates a unique identifier for the spacecraft based on its properties. This method is called in the constructor to ensure that each spacecraft has a unique ID._  |


## Protected Functions inherited from astrea::astro::PayloadPlatform

See [astrea::astro::PayloadPlatform](classastrea_1_1astro_1_1PayloadPlatform.md)

| Type | Name |
| ---: | :--- |
|   | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md#function-payloadplatform-13) () = default<br>_Default constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md#function-payloadplatform-23) (const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|   | [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md#function-payloadplatform-33) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move constructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](classastrea_1_1astro_1_1PayloadPlatform.md#function-operator) (const [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & other) <br>_Copy assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  [**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) & | [**operator=**](classastrea_1_1astro_1_1PayloadPlatform.md#function-operator_1) ([**PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md) && other) noexcept<br>_Move assignment operator for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |
|  void | [**reset\_payload\_parentage**](classastrea_1_1astro_1_1PayloadPlatform.md#function-reset_payload_parentage) () <br>_Resets the parentage of all payloads attached to the platform to this._  |
| virtual  | [**~PayloadPlatform**](classastrea_1_1astro_1_1PayloadPlatform.md#function-payloadplatform) () = default<br>_Default destructor for_ [_**PayloadPlatform**_](classastrea_1_1astro_1_1PayloadPlatform.md) _._ |










## Public Static Attributes Documentation




### variable DEFAULT\_COEFFICIENT\_OF\_DRAG 

```C++
constexpr Unitless astrea::astro::Spacecraft::DEFAULT_COEFFICIENT_OF_DRAG;
```




<hr>



### variable DEFAULT\_COEFFICIENT\_OF\_LIFT 

```C++
constexpr Unitless astrea::astro::Spacecraft::DEFAULT_COEFFICIENT_OF_LIFT;
```




<hr>



### variable DEFAULT\_COEFFICIENT\_OF\_REFLECTIVITY 

```C++
constexpr Unitless astrea::astro::Spacecraft::DEFAULT_COEFFICIENT_OF_REFLECTIVITY;
```




<hr>



### variable DEFAULT\_LIFT\_AREA 

```C++
constexpr SurfaceArea astrea::astro::Spacecraft::DEFAULT_LIFT_AREA;
```




<hr>



### variable DEFAULT\_MASS 

```C++
constexpr Mass astrea::astro::Spacecraft::DEFAULT_MASS;
```




<hr>



### variable DEFAULT\_RAM\_AREA 

```C++
constexpr SurfaceArea astrea::astro::Spacecraft::DEFAULT_RAM_AREA;
```




<hr>



### variable DEFAULT\_SOLAR\_AREA 

```C++
constexpr SurfaceArea astrea::astro::Spacecraft::DEFAULT_SOLAR_AREA;
```




<hr>
## Public Functions Documentation




### function Spacecraft [1/2]

_Default constructor for_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._
```C++
inline astrea::astro::Spacecraft::Spacecraft () 
```




<hr>



### function Spacecraft [2/2]

_Constructs a_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _with a_[_**GeneralPerturbations**_](structastrea_1_1astro_1_1GeneralPerturbations.md) _object and an_[_**AstrodynamicsSystem**_](classastrea_1_1astro_1_1AstrodynamicsSystem.md) _._
```C++
astrea::astro::Spacecraft::Spacecraft (
    const GeneralPerturbations & gp,
    const AstrodynamicsSystem & sys
) 
```





**Parameters:**


* `gp` The [**GeneralPerturbations**](structastrea_1_1astro_1_1GeneralPerturbations.md) object containing initial parameters. 
* `sys` The [**AstrodynamicsSystem**](classastrea_1_1astro_1_1AstrodynamicsSystem.md) to which this spacecraft belongs. 




        

<hr>



### function get\_coefficient\_of\_drag 

_Gets the coefficients of drag, lift, and reflectivity._ 
```C++
Unitless astrea::astro::Spacecraft::get_coefficient_of_drag () const
```





**Returns:**

Unitless The coefficient of drag. 





        

<hr>



### function get\_coefficient\_of\_lift 

_Gets the coefficient of lift._ 
```C++
Unitless astrea::astro::Spacecraft::get_coefficient_of_lift () const
```





**Returns:**

Unitless The coefficient of lift. 





        

<hr>



### function get\_coefficient\_of\_reflectivity 

_Gets the coefficient of reflectivity._ 
```C++
Unitless astrea::astro::Spacecraft::get_coefficient_of_reflectivity () const
```





**Returns:**

Unitless The coefficient of reflectivity. 





        

<hr>



### function get\_id 

_Gets the unique identifier of the spacecraft._ 
```C++
inline virtual std::size_t astrea::astro::Spacecraft::get_id () const
```





**Returns:**

std::size\_t The unique identifier of the spacecraft. 





        
Implements [*astrea::astro::PayloadPlatform::get\_id*](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_id)


<hr>



### function get\_inertial\_position 

_Gets the inertial position of the spacecraft at a specific date._ 
```C++
virtual RadiusVector < frames::earth::icrf > astrea::astro::Spacecraft::get_inertial_position (
    const Date & date
) override const
```





**Parameters:**


* `date` The date at which to retrieve the position. 



**Returns:**

RadiusVector&lt;frames::earth::icrf&gt; The inertial position of the spacecraft. 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_position*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_position)


<hr>



### function get\_inertial\_velocity 

_Gets the inertial velocity of the spacecraft at a specific date._ 
```C++
virtual VelocityVector < frames::earth::icrf > astrea::astro::Spacecraft::get_inertial_velocity (
    const Date & date
) override const
```





**Parameters:**


* `date` The date at which to retrieve the velocity. 



**Returns:**

VelocityVector&lt;frames::earth::icrf&gt; The inertial velocity of the spacecraft. 





        
Implements [*astrea::astro::FrameReference::get\_inertial\_velocity*](classastrea_1_1astro_1_1FrameReference.md#function-get_inertial_velocity)


<hr>



### function get\_initial\_state [1/2]

_Gets the initial state of the spacecraft._ 
```C++
inline State & astrea::astro::Spacecraft::get_initial_state () 
```





**Returns:**

[**State**](classastrea_1_1astro_1_1State.md)& A reference to the initial state of the spacecraft. 





        

<hr>



### function get\_initial\_state [2/2]

_Gets the initial state of the spacecraft._ 
```C++
inline const State & astrea::astro::Spacecraft::get_initial_state () const
```





**Returns:**

const [**State**](classastrea_1_1astro_1_1State.md)& A reference to the initial state of the spacecraft. 





        

<hr>



### function get\_lift\_area 

_Gets the lift area of the spacecraft._ 
```C++
SurfaceArea astrea::astro::Spacecraft::get_lift_area () const
```





**Returns:**

SurfaceArea The lift area of the spacecraft. 





        

<hr>



### function get\_mass 

_Gets the mass of the spacecraft._ 
```C++
virtual Mass astrea::astro::Spacecraft::get_mass () const
```





**Returns:**

Mass The mass of the spacecraft. 





        
Implements [*astrea::astro::PayloadPlatform::get\_mass*](classastrea_1_1astro_1_1PayloadPlatform.md#function-get_mass)


<hr>



### function get\_name 

_Gets the name of the spacecraft._ 
```C++
inline virtual std::string astrea::astro::Spacecraft::get_name () const
```





**Returns:**

std::string The name of the spacecraft. 





        
Implements [*astrea::astro::FrameReference::get\_name*](classastrea_1_1astro_1_1FrameReference.md#function-get_name)


<hr>



### function get\_ram\_area 

_Gets the surface areas for ram, solar, and lift._ 
```C++
SurfaceArea astrea::astro::Spacecraft::get_ram_area () const
```





**Returns:**

SurfaceArea The ram area of the spacecraft. 





        

<hr>



### function get\_solar\_area 

_Gets the solar area of the spacecraft._ 
```C++
SurfaceArea astrea::astro::Spacecraft::get_solar_area () const
```





**Returns:**

SurfaceArea The solar area of the spacecraft. 





        

<hr>



### function get\_state\_history [1/2]

_Gets the state history of the spacecraft._ 
```C++
StateHistory & astrea::astro::Spacecraft::get_state_history () 
```





**Returns:**

[**StateHistory**](classastrea_1_1astro_1_1StateHistory.md)& A reference to the state history of the spacecraft. 





        

<hr>



### function get\_state\_history [2/2]

_Gets the state history of the spacecraft._ 
```C++
const StateHistory & astrea::astro::Spacecraft::get_state_history () const
```





**Returns:**

const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md)& A reference to the state history of the spacecraft. 





        

<hr>



### function operator== 

_Equality operator to compare two_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _objects._
```C++
bool astrea::astro::Spacecraft::operator== (
    const Spacecraft & other
) const
```





**Parameters:**


* `other` The other [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) to compare with. 



**Returns:**

true if the [**Spacecraft**](classastrea_1_1astro_1_1Spacecraft.md) objects are equal, false otherwise. 





        

<hr>



### function set\_coefficient\_of\_drag 

_Sets the coefficients of drag._ 
```C++
void astrea::astro::Spacecraft::set_coefficient_of_drag (
    const Unitless & cd
) 
```





**Parameters:**


* `cd` The coefficient of drag to set. 




        

<hr>



### function set\_coefficient\_of\_lift 

_Sets the coefficient of lift._ 
```C++
void astrea::astro::Spacecraft::set_coefficient_of_lift (
    const Unitless & cl
) 
```





**Parameters:**


* `cl` The coefficient of lift to set. 




        

<hr>



### function set\_coefficient\_of\_reflectivity 

_Sets the coefficient of reflectivity._ 
```C++
void astrea::astro::Spacecraft::set_coefficient_of_reflectivity (
    const Unitless & cr
) 
```





**Parameters:**


* `cr` The coefficient of reflectivity to set. 




        

<hr>



### function set\_lift\_area 

_Sets the lift area of the spacecraft._ 
```C++
void astrea::astro::Spacecraft::set_lift_area (
    const SurfaceArea & liftArea
) 
```





**Parameters:**


* `liftArea` The lift area to set. 




        

<hr>



### function set\_mass 

_Sets the mass of the spacecraft._ 
```C++
void astrea::astro::Spacecraft::set_mass (
    const Mass & mass
) 
```





**Parameters:**


* `mass` The new mass to set for the spacecraft. 




        

<hr>



### function set\_name 

_Sets the name of the spacecraft._ 
```C++
void astrea::astro::Spacecraft::set_name (
    const std::string & name
) 
```





**Parameters:**


* `name` The name to set for the spacecraft. 




        

<hr>



### function set\_ram\_area 

_Sets the surface area for ram._ 
```C++
void astrea::astro::Spacecraft::set_ram_area (
    const SurfaceArea & ramArea
) 
```





**Parameters:**


* `ramArea` The ram area to set. 




        

<hr>



### function set\_solar\_area 

_Sets the solar area of the spacecraft._ 
```C++
void astrea::astro::Spacecraft::set_solar_area (
    const SurfaceArea & solarArea
) 
```





**Parameters:**


* `solarArea` The solar area to set. 




        

<hr>



### function set\_state\_history 

_Stores the state history of the spacecraft._ 
```C++
void astrea::astro::Spacecraft::set_state_history (
    const StateHistory & history
) 
```





**Parameters:**


* `history` The [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) object to store. 




        

<hr>



### function store\_state 

_Stores a single state in the spacecraft's state history._ 
```C++
void astrea::astro::Spacecraft::store_state (
    const State & state
) 
```





**Parameters:**


* `state` The [**State**](classastrea_1_1astro_1_1State.md) object to store. 




        

<hr>



### function ~Spacecraft 

_Virtual destructor for_ [_**Spacecraft**_](classastrea_1_1astro_1_1Spacecraft.md) _._
```C++
virtual astrea::astro::Spacecraft::~Spacecraft () = default
```




<hr>
## Protected Attributes Documentation




### variable \_coefficientOfDrag 

_Coefficient of drag._ 
```C++
Unitless astrea::astro::Spacecraft::_coefficientOfDrag;
```




<hr>



### variable \_coefficientOfLift 

_Coefficient of lift._ 
```C++
Unitless astrea::astro::Spacecraft::_coefficientOfLift;
```




<hr>



### variable \_coefficientOfReflectivity 

_Coefficient of reflectivity._ 
```C++
Unitless astrea::astro::Spacecraft::_coefficientOfReflectivity;
```




<hr>



### variable \_id 

```C++
std::size_t astrea::astro::Spacecraft::_id;
```




<hr>



### variable \_liftArea 

_Lift area of the spacecraft._ 
```C++
SurfaceArea astrea::astro::Spacecraft::_liftArea;
```




<hr>



### variable \_mass 

_Mass of the spacecraft._ 
```C++
Mass astrea::astro::Spacecraft::_mass;
```




<hr>



### variable \_name 

```C++
std::string astrea::astro::Spacecraft::_name;
```




<hr>



### variable \_ramArea 

_Ram area of the spacecraft._ 
```C++
SurfaceArea astrea::astro::Spacecraft::_ramArea;
```




<hr>



### variable \_stateHistory 

```C++
StateHistory astrea::astro::Spacecraft::_stateHistory;
```




<hr>



### variable \_sunArea 

_Solar area of the spacecraft._ 
```C++
SurfaceArea astrea::astro::Spacecraft::_sunArea;
```




<hr>
## Protected Functions Documentation




### function generate\_id 

_Generates a unique identifier for the spacecraft based on its properties. This method is called in the constructor to ensure that each spacecraft has a unique ID._ 
```C++
void astrea::astro::Spacecraft::generate_id () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/platforms/vehicles/Spacecraft.hpp`

