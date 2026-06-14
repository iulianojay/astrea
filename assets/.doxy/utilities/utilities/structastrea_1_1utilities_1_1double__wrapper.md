

# Struct astrea::utilities::double\_wrapper



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md) **>** [**double\_wrapper**](structastrea_1_1utilities_1_1double__wrapper.md)



[More...](#detailed-description)

* `#include <string_util.hpp>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  long long int | [**frac**](#variable-frac)   = `0`<br> |
|  long long int | [**whole**](#variable-whole)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**double\_wrapper**](#function-double_wrapper) (double v, int prec=5) <br> |




























## Detailed Description


Credit to [https://github.com/tcsullivan/constexpr-to-string/tree/master](https://github.com/tcsullivan/constexpr-to-string/tree/master) for the following implementation of `f_to_string` 


    
## Public Attributes Documentation




### variable frac 

```C++
long long int astrea::utilities::double_wrapper::frac;
```




<hr>



### variable whole 

```C++
long long int astrea::utilities::double_wrapper::whole;
```




<hr>
## Public Functions Documentation




### function double\_wrapper 

```C++
inline constexpr astrea::utilities::double_wrapper::double_wrapper (
    double v,
    int prec=5
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/string_util.hpp`

