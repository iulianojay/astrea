

# Class astrea::astro::StateTransitionMatrix



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**StateTransitionMatrix**](classastrea_1_1astro_1_1StateTransitionMatrix.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StateTransitionMatrix**](#function-statetransitionmatrix-12) () = default<br>_Default constructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _._ |
|   | [**StateTransitionMatrix**](#function-statetransitionmatrix-22) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**EquationsOfMotion**](classastrea_1_1astro_1_1EquationsOfMotion.md) & eom, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**State**](classastrea_1_1astro_1_1State.md) & state, [**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) & vehicle) <br>_Constructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _. Uses the provided equations of motion and state to initialize the STM numerically._ |
|  std::vector&lt; [**Unitless**](classastrea_1_1astro_1_1CartesianVector.md) &gt; | [**force\_to\_vector**](#function-force_to_vector) () const<br>_Convert the STM to a vector of unitless quantities._  |
|  [**void**](classastrea_1_1astro_1_1CartesianVector.md) | [**set**](#function-set) ([**const**](classastrea_1_1astro_1_1CartesianVector.md) [**Value\_T**](classastrea_1_1astro_1_1CartesianVector.md) & value) <br>_Set the STM element at (ii, jj) to the provided value._  |
|   | [**~StateTransitionMatrix**](#function-statetransitionmatrix) () = default<br>_Default destructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _._ |




























## Public Functions Documentation




### function StateTransitionMatrix [1/2]

_Default constructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _._
```C++
astrea::astro::StateTransitionMatrix::StateTransitionMatrix () = default
```




<hr>



### function StateTransitionMatrix [2/2]

_Constructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _. Uses the provided equations of motion and state to initialize the STM numerically._
```C++
astrea::astro::StateTransitionMatrix::StateTransitionMatrix (
    const  EquationsOfMotion & eom,
    const  State & state,
    const  Vehicle & vehicle
) 
```





**Parameters:**


* `eom` Equations of motion object 
* `date` Current date 
* `state` Current orbital elements state vector 
* `vehicle` [**Vehicle**](classastrea_1_1astro_1_1Vehicle.md) object 




        

<hr>



### function force\_to\_vector 

_Convert the STM to a vector of unitless quantities._ 
```C++
std::vector< Unitless > astrea::astro::StateTransitionMatrix::force_to_vector () const
```





**Returns:**

std::vector&lt;Unitless&gt; Vector representation of the STM. 





        

<hr>



### function set 

_Set the STM element at (ii, jj) to the provided value._ 
```C++
template<std::size_t ii, std::size_t jj, mp_units::Quantity Value_T>
inline void astrea::astro::StateTransitionMatrix::set (
    const  Value_T & value
) 
```





**Template parameters:**


* `ii` Row index 
* `jj` Column index 



**Parameters:**


* `value` Value to set



**Note:**

The value's unit will be forced to a unitless representation inside the STM. It is on the user to ensure that the correct units are used for the STM elements. I'm sorry. 





        

<hr>



### function ~StateTransitionMatrix 

_Default destructor for_ [_**StateTransitionMatrix**_](classastrea_1_1astro_1_1StateTransitionMatrix.md) _._
```C++
astrea::astro::StateTransitionMatrix::~StateTransitionMatrix () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/equations_of_motion/state_transition_matrix/StateTransitionMatrix.hpp`

