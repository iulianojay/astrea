

# Namespace astrea::astro::plotting



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**plotting**](namespaceastrea_1_1astro_1_1plotting.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**compare\_attitudes**](#function-compare_attitudes) (const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Compares the attitudes of multiple trajectories by plotting their Euler angles and angular rates._  |
|  void | [**compare\_orbital\_elements**](#function-compare_orbital_elements) (const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Compares multiple trajectories by plotting their orbital elements._  |
|  void | [**compare\_trajectories**](#function-compare_trajectories) (const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Compares multiple trajectories by plotting their_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _components._ |
|  void | [**plot\_attitude**](#function-plot_attitude) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & trajectory, const std::filesystem::path & outfile) <br>_Plots the attitude (XYZ intrinsic Euler angles and body angular rates) of a trajectory._  |
|  void | [**plot\_difference\_attitude**](#function-plot_difference_attitude) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) expected, const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Plots the attitude difference between an expected trajectory and a set of trajectories._  |
|  void | [**plot\_difference\_orbital\_elements**](#function-plot_difference_orbital_elements) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) expected, const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Compares multiple trajectories by plotting their orbital elements._  |
|  void | [**plot\_difference\_trajectories**](#function-plot_difference_trajectories) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) expected, const std::vector&lt; [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) &gt; & trajectories, const std::vector&lt; std::string &gt; & labels, const std::filesystem::path & outfile) <br>_Compares multiple trajectories by plotting their_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _components._ |
|  void | [**plot\_orbital\_elements**](#function-plot_orbital_elements) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & trajectory, const std::filesystem::path & outfile) <br>_Plots the orbital elements of a trajectory._  |
|  void | [**plot\_trajectory**](#function-plot_trajectory) (const [**StateHistory**](classastrea_1_1astro_1_1StateHistory.md) & trajectory, const std::filesystem::path & outfile) <br>_Plots the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _trajectory._ |




























## Public Functions Documentation




### function compare\_attitudes 

_Compares the attitudes of multiple trajectories by plotting their Euler angles and angular rates._ 
```C++
void astrea::astro::plotting::compare_attitudes (
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectories` A vector of state histories representing the trajectories. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the comparison plot. 




        

<hr>



### function compare\_orbital\_elements 

_Compares multiple trajectories by plotting their orbital elements._ 
```C++
void astrea::astro::plotting::compare_orbital_elements (
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectories` A vector of state histories representing the trajectories. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the comparison plot. 




        

<hr>



### function compare\_trajectories 

_Compares multiple trajectories by plotting their_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _components._
```C++
void astrea::astro::plotting::compare_trajectories (
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectories` A vector of state histories representing the trajectories. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the comparison plot. 




        

<hr>



### function plot\_attitude 

_Plots the attitude (XYZ intrinsic Euler angles and body angular rates) of a trajectory._ 
```C++
void astrea::astro::plotting::plot_attitude (
    const StateHistory & trajectory,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectory` The state history representing the trajectory. 
* `outfile` The path to the file to save the plot. 




        

<hr>



### function plot\_difference\_attitude 

_Plots the attitude difference between an expected trajectory and a set of trajectories._ 
```C++
void astrea::astro::plotting::plot_difference_attitude (
    const StateHistory expected,
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```



Differences are computed per Euler angle component (XYZ intrinsic) and per angular rate component.




**Parameters:**


* `expected` The expected state history used as the reference. 
* `trajectories` A vector of state histories representing the trajectories to compare. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the plot. 




        

<hr>



### function plot\_difference\_orbital\_elements 

_Compares multiple trajectories by plotting their orbital elements._ 
```C++
void astrea::astro::plotting::plot_difference_orbital_elements (
    const StateHistory expected,
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectories` A vector of state histories representing the trajectories. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the comparison plot. 




        

<hr>



### function plot\_difference\_trajectories 

_Compares multiple trajectories by plotting their_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _components._
```C++
void astrea::astro::plotting::plot_difference_trajectories (
    const StateHistory expected,
    const std::vector< StateHistory > & trajectories,
    const std::vector< std::string > & labels,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectories` A vector of state histories representing the trajectories. 
* `labels` A vector of labels for each trajectory. 
* `outfile` The path to the file to save the comparison plot. 




        

<hr>



### function plot\_orbital\_elements 

_Plots the orbital elements of a trajectory._ 
```C++
void astrea::astro::plotting::plot_orbital_elements (
    const StateHistory & trajectory,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectory` The state history representing the trajectory. 
* `outfile` The path to the file to save the plot. 




        

<hr>



### function plot\_trajectory 

_Plots the_ [_**Cartesian**_](classastrea_1_1astro_1_1Cartesian.md) _trajectory._
```C++
void astrea::astro::plotting::plot_trajectory (
    const StateHistory & trajectory,
    const std::filesystem::path & outfile
) 
```





**Parameters:**


* `trajectory` The state history representing the trajectory. 
* `outfile` The path to the file to save the plot. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/utilities/plotting.cpp`

