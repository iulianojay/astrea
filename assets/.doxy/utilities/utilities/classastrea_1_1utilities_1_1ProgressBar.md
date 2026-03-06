

# Class astrea::utilities::ProgressBar



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md) **>** [**ProgressBar**](classastrea_1_1utilities_1_1ProgressBar.md)



_A simple console progress bar utility._ 

* `#include <ProgressBar.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**ProgressBar**](#function-progressbar) (const std::size\_t & maxRecords, const std::string & title="Progress", const std::size\_t & frequency=0, const std::size\_t & barWidth=50) <br>_Constructs a_ [_**ProgressBar**_](classastrea_1_1utilities_1_1ProgressBar.md) _instance._ |
|  std::size\_t | [**get\_progress**](#function-get_progress) () const<br>_Increments the progress by one record._  |
|  void | [**operator()**](#function-operator) () <br>_Updates the progress bar and prints it to the console._  |
|  void | [**reset**](#function-reset) () <br>_Resets the progress bar to the initial state._  |
|   | [**~ProgressBar**](#function-progressbar) () = default<br>_Default destructor for_ [_**ProgressBar**_](classastrea_1_1utilities_1_1ProgressBar.md) _._ |




























## Public Functions Documentation




### function ProgressBar 

_Constructs a_ [_**ProgressBar**_](classastrea_1_1utilities_1_1ProgressBar.md) _instance._
```C++
inline astrea::utilities::ProgressBar::ProgressBar (
    const std::size_t & maxRecords,
    const std::string & title="Progress",
    const std::size_t & frequency=0,
    const std::size_t & barWidth=50
) 
```





**Parameters:**


* `maxRecords` The maximum number of records to process. 
* `title` The title of the progress bar. 
* `frequency` The frequency of updates (in terms of records processed). 
* `barWidth` The width of the progress bar in characters. 




        

<hr>



### function get\_progress 

_Increments the progress by one record._ 
```C++
inline std::size_t astrea::utilities::ProgressBar::get_progress () const
```




<hr>



### function operator() 

_Updates the progress bar and prints it to the console._ 
```C++
inline void astrea::utilities::ProgressBar::operator() () 
```



This method should be called periodically to update the progress bar. 


        

<hr>



### function reset 

_Resets the progress bar to the initial state._ 
```C++
inline void astrea::utilities::ProgressBar::reset () 
```




<hr>



### function ~ProgressBar 

_Default destructor for_ [_**ProgressBar**_](classastrea_1_1utilities_1_1ProgressBar.md) _._
```C++
astrea::utilities::ProgressBar::~ProgressBar () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/ProgressBar.hpp`

