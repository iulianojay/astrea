

# Struct astrea::trace::PairResult



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**trace**](namespaceastrea_1_1trace.md) **>** [**PairResult**](structastrea_1_1trace_1_1PairResult.md)



_Per-viewer result for one (viewer, ground-point) work item._ 






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) | [**platformAccess**](#variable-platformaccess)  <br>_Union over all sensors._  |
|  std::vector&lt; std::pair&lt; std::size\_t, [**RiseSetArray**](classastrea_1_1trace_1_1RiseSetArray.md) &gt; &gt; | [**sensorAccesses**](#variable-sensoraccesses)  <br>_(sensor\_idx, access\_windows)_  |












































## Public Attributes Documentation




### variable platformAccess 

_Union over all sensors._ 
```C++
RiseSetArray astrea::trace::PairResult::platformAccess;
```




<hr>



### variable sensorAccesses 

_(sensor\_idx, access\_windows)_ 
```C++
std::vector<std::pair<std::size_t, RiseSetArray> > astrea::trace::PairResult::sensorAccesses;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/analysis/AccessAnalyzer.cpp`

