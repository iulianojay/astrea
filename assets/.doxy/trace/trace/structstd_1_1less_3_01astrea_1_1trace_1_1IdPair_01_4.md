

# Struct std::less&lt; astrea::trace::IdPair &gt;

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**std**](namespacestd.md) **>** [**less&lt; astrea::trace::IdPair &gt;**](structstd_1_1less_3_01astrea_1_1trace_1_1IdPair_01_4.md)



_Specialization of std::less for IdPair to allow it to be used in ordered containers._ 

* `#include <IdPair.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator()**](#function-operator) (const [**astrea::trace::IdPair**](structastrea_1_1trace_1_1IdPair.md) & lhs, const [**astrea::trace::IdPair**](structastrea_1_1trace_1_1IdPair.md) & rhs) const<br>_Compares two IdPairs for ordering._  |




























## Public Functions Documentation




### function operator() 

_Compares two IdPairs for ordering._ 
```C++
inline bool std::less< astrea::trace::IdPair >::operator() (
    const astrea::trace::IdPair & lhs,
    const astrea::trace::IdPair & rhs
) const
```





**Parameters:**


* `lhs` The first IdPair to compare. 
* `rhs` The second IdPair to compare. 



**Returns:**

True if lhs is less than rhs, false otherwise. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/types/IdPair.hpp`

