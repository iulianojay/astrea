

# Class astrea::utilities::StopWatch



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md) **>** [**StopWatch**](classastrea_1_1utilities_1_1StopWatch.md)



_A simple stopwatch utility for measuring elapsed time._ [More...](#detailed-description)

* `#include <StopWatch.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StopWatch**](#function-stopwatch) () <br>_Constructs a_ [_**StopWatch**_](classastrea_1_1utilities_1_1StopWatch.md) _and starts timing._ |
|  Time | [**measure**](#function-measure) () const<br>_Measures the elapsed time in seconds since the last reset or construction._  |
|  void | [**reset**](#function-reset) () <br>_Resets the stopwatch to the current time._  |




























## Detailed Description


The [**StopWatch**](classastrea_1_1utilities_1_1StopWatch.md) class provides a convenient way to measure elapsed time in seconds. It uses the high-resolution clock from the &lt;chrono&gt; library to provide accurate timing. 


    
## Public Functions Documentation




### function StopWatch 

_Constructs a_ [_**StopWatch**_](classastrea_1_1utilities_1_1StopWatch.md) _and starts timing._
```C++
inline astrea::utilities::StopWatch::StopWatch () 
```




<hr>



### function measure 

_Measures the elapsed time in seconds since the last reset or construction._ 
```C++
inline Time astrea::utilities::StopWatch::measure () const
```





**Returns:**

Time The elapsed time. 





        

<hr>



### function reset 

_Resets the stopwatch to the current time._ 
```C++
inline void astrea::utilities::StopWatch::reset () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/StopWatch.hpp`

