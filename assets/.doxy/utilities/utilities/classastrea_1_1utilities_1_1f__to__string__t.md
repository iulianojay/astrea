

# Struct astrea::utilities::f\_to\_string\_t

**template &lt;[**double\_wrapper**](structastrea_1_1utilities_1_1double__wrapper.md) N, typename char\_type&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md) **>** [**f\_to\_string\_t**](classastrea_1_1utilities_1_1f__to__string__t.md)



_Provides the ability to convert a floating-point number to a string at compile-time._ [More...](#detailed-description)

* `#include <string_util.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr auto & | [**back**](#function-back-12) () noexcept<br> |
|  constexpr const auto & | [**back**](#function-back-22) () noexcept const<br> |
|  constexpr auto | [**begin**](#function-begin-12) () noexcept<br> |
|  constexpr auto | [**begin**](#function-begin-22) () noexcept const<br> |
|  constexpr auto | [**data**](#function-data-12) () noexcept<br> |
|  constexpr auto | [**data**](#function-data-22) () noexcept const<br> |
|  constexpr auto | [**end**](#function-end-12) () noexcept<br> |
|  constexpr auto | [**end**](#function-end-22) () noexcept const<br> |
|  constexpr | [**f\_to\_string\_t**](#function-f_to_string_t) () noexcept<br> |
|  constexpr auto & | [**front**](#function-front-12) () noexcept<br> |
|  constexpr const auto & | [**front**](#function-front-22) () noexcept const<br> |
|  constexpr | [**operator char\_type \***](#function-operator-char_type-*) () noexcept<br> |
|  constexpr | [**operator const char\_type \***](#function-operator-const-char_type-*) () noexcept const<br> |
|  constexpr auto & | [**operator[]**](#function-operator) (unsigned int i) noexcept<br> |
|  constexpr const auto & | [**operator[]**](#function-operator_1) (unsigned int i) noexcept const<br> |
|  constexpr auto | [**size**](#function-size) () noexcept const<br> |




























## Detailed Description




**Template parameters:**


* `N` Number to convert 




    
## Public Functions Documentation




### function back [1/2]

```C++
inline constexpr auto & astrea::utilities::f_to_string_t::back () noexcept
```




<hr>



### function back [2/2]

```C++
inline constexpr const auto & astrea::utilities::f_to_string_t::back () noexcept const
```




<hr>



### function begin [1/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::begin () noexcept
```




<hr>



### function begin [2/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::begin () noexcept const
```




<hr>



### function data [1/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::data () noexcept
```




<hr>



### function data [2/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::data () noexcept const
```




<hr>



### function end [1/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::end () noexcept
```




<hr>



### function end [2/2]

```C++
inline constexpr auto astrea::utilities::f_to_string_t::end () noexcept const
```




<hr>



### function f\_to\_string\_t 

```C++
inline constexpr astrea::utilities::f_to_string_t::f_to_string_t () noexcept
```



Constructs the object, filling `buf` with the string representation of N. 


        

<hr>



### function front [1/2]

```C++
inline constexpr auto & astrea::utilities::f_to_string_t::front () noexcept
```




<hr>



### function front [2/2]

```C++
inline constexpr const auto & astrea::utilities::f_to_string_t::front () noexcept const
```




<hr>



### function operator char\_type \* 

```C++
inline constexpr astrea::utilities::f_to_string_t::operator char_type * () noexcept
```




<hr>



### function operator const char\_type \* 

```C++
inline constexpr astrea::utilities::f_to_string_t::operator const char_type * () noexcept const
```




<hr>



### function operator[] 

```C++
inline constexpr auto & astrea::utilities::f_to_string_t::operator[] (
    unsigned int i
) noexcept
```




<hr>



### function operator[] 

```C++
inline constexpr const auto & astrea::utilities::f_to_string_t::operator[] (
    unsigned int i
) noexcept const
```




<hr>



### function size 

```C++
inline constexpr auto astrea::utilities::f_to_string_t::size () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/string_util.hpp`

