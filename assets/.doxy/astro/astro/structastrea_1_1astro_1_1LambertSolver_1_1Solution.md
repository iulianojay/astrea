

# Struct astrea::astro::LambertSolver::Solution

**template &lt;IsFrame auto \_frame\_&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**LambertSolver**](classastrea_1_1astro_1_1LambertSolver.md) **>** [**Solution**](structastrea_1_1astro_1_1LambertSolver_1_1Solution.md)



_Result structure for optimal Lambert solutions._ 

* `#include <LambertSolver.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  Time | [**tof**](#variable-tof)  <br>_Time of flight for the transfer._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; | [**v0**](#variable-v0)  <br>_Initial velocity vector at r0._  |
|  [**VelocityVector**](namespaceastrea_1_1astro.md#typedef-velocityvector)&lt; \_frame\_ &gt; | [**vf**](#variable-vf)  <br>_Final velocity vector at rf._  |












































## Public Attributes Documentation




### variable tof 

_Time of flight for the transfer._ 
```C++
Time astrea::astro::LambertSolver::Solution< _frame_ >::tof;
```




<hr>



### variable v0 

_Initial velocity vector at r0._ 
```C++
VelocityVector<_frame_> astrea::astro::LambertSolver::Solution< _frame_ >::v0;
```




<hr>



### variable vf 

_Final velocity vector at rf._ 
```C++
VelocityVector<_frame_> astrea::astro::LambertSolver::Solution< _frame_ >::vf;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/propagation/analytic/LambertSolver.hpp`

