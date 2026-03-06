

# Class astrea::trace::plotting::Plotter



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**plotting**](namespaceastrea_1_1trace_1_1plotting.md) **>** [**Plotter**](classastrea_1_1trace_1_1plotting_1_1Plotter.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Plotter**](#function-plotter) () = default<br> |
|  void | [**plot\_access\_metrics**](#function-plot_access_metrics) (const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const std::filesystem::path & outfile) <br> |
|  void | [**plot\_number\_of\_folds**](#function-plot_number_of_folds) (const [**ViewerConstellation**](namespaceastrea_1_1trace.md#typedef-viewerconstellation) & satellites, const [**Grid**](classastrea_1_1trace_1_1Grid.md) & grounds, const [**AccessArray**](classastrea_1_1trace_1_1AccessArray.md) & accesses, const Time & resolution, const Time & start, const Time & end) <br> |
|  void | [**set\_output\_directory**](#function-set_output_directory) (const std::filesystem::path & outputDir) <br> |




























## Public Functions Documentation




### function Plotter 

```C++
astrea::trace::plotting::Plotter::Plotter () = default
```




<hr>



### function plot\_access\_metrics 

```C++
void astrea::trace::plotting::Plotter::plot_access_metrics (
    const AccessArray & accesses,
    const std::filesystem::path & outfile
) 
```




<hr>



### function plot\_number\_of\_folds 

```C++
void astrea::trace::plotting::Plotter::plot_number_of_folds (
    const ViewerConstellation & satellites,
    const Grid & grounds,
    const AccessArray & accesses,
    const Time & resolution,
    const Time & start,
    const Time & end
) 
```




<hr>



### function set\_output\_directory 

```C++
inline void astrea::trace::plotting::Plotter::set_output_directory (
    const std::filesystem::path & outputDir
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/plots/Plotter.hpp`

