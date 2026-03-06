

# Struct std::hash&lt; astrea::trace::IdPair &gt;

**template &lt;&gt;**



[**ClassList**](annotated.md) **>** [**std**](namespacestd.md) **>** [**hash&lt; astrea::trace::IdPair &gt;**](structstd_1_1hash_3_01astrea_1_1trace_1_1IdPair_01_4.md)



_Specialization of std::hash for IdPair to allow it to be used as a key in hash-based containers._ 

* `#include <IdPair.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  std::size\_t | [**operator()**](#function-operator) (const [**astrea::trace::IdPair**](structastrea_1_1trace_1_1IdPair.md) & k) const<br>_Computes a hash value for an IdPair._  |




























## Public Functions Documentation




### function operator() 

_Computes a hash value for an IdPair._ 
```C++
inline std::size_t std::hash< astrea::trace::IdPair >::operator() (
    const astrea::trace::IdPair & k
) const
```





**Parameters:**


* `k` The IdPair to hash. 



**Returns:**

A hash value for the IdPair. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/trace/trace/types/IdPair.hpp`

