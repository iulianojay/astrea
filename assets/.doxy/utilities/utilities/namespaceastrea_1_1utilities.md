

# Namespace astrea::utilities



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**utilities**](namespaceastrea_1_1utilities.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**IdProvider**](classastrea_1_1utilities_1_1IdProvider.md) <br> |
| class | [**ProgressBar**](classastrea_1_1utilities_1_1ProgressBar.md) <br>_A simple console progress bar utility._  |
| class | [**StopWatch**](classastrea_1_1utilities_1_1StopWatch.md) <br>_A simple stopwatch utility for measuring elapsed time._  |
| struct | [**double\_wrapper**](structastrea_1_1utilities_1_1double__wrapper.md) <br> |
| struct | [**f\_to\_string\_t**](classastrea_1_1utilities_1_1f__to__string__t.md) &lt;N, typename char\_type&gt;<br>_Provides the ability to convert a floating-point number to a string at compile-time._  |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  constexpr [**f\_to\_string\_t**](classastrea_1_1utilities_1_1f__to__string__t.md)&lt; N, char\_type &gt; | [**f\_to\_string**](#variable-f_to_string)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**clean\_entry**](#function-clean_entry) (const nlohmann::json & entry) <br>_Cleans a JSON entry by removing quotes and returning it as a string._  |
|  T | [**extract\_from\_json**](#function-extract_from_json) (const nlohmann::json & json, const std::string & key) <br>_Extracts a value of type T from a JSON object using the specified key._  |
|  std::optional&lt; T &gt; | [**extract\_optional\_from\_json**](#function-extract_optional_from_json) (const nlohmann::json & json, const std::string & key) <br>_Extracts an optional value of type T from a JSON object using the specified key._  |
|  std::optional&lt; std::string &gt; | [**extract\_optional\_string\_from\_json**](#function-extract_optional_string_from_json) (const nlohmann::json & json, const std::string & key) <br>_Extracts an optional string value from a JSON object using the specified key._  |
|  std::string | [**extract\_string\_from\_json**](#function-extract_string_from_json) (const nlohmann::json & json, const std::string & key) <br>_Extracts a string value from a JSON object using the specified key._  |
|  std::string | [**get\_type\_name**](#function-get_type_name) () <br>_Gets the demangled(ish) type name of a given type._  |
|  std::string | [**replace\_all**](#function-replace_all) (std::string const & original, std::string const & before, std::string const & after) <br>_Replaces all occurrences of a substring with another substring in a string._  |
|  std::vector&lt; std::string &gt; | [**split**](#function-split) (std::string s, const std::string & delimiter) <br>_Splits a string into a vector of substrings based on a delimiter._  |
|  std::string | [**trim**](#function-trim) (const std::string & str, const std::string & whitespace=" \t") <br>_Trims whitespace from both ends of a string._  |




























## Public Attributes Documentation




### variable f\_to\_string 

```C++
constexpr f_to_string_t<N, char_type> astrea::utilities::f_to_string;
```



Simplifies use of `f_to_string_t` from `f_to_string_t <N>()` to `f_to_string<N>`. 


        

<hr>
## Public Functions Documentation




### function clean\_entry 

_Cleans a JSON entry by removing quotes and returning it as a string._ 
```C++
std::string astrea::utilities::clean_entry (
    const nlohmann::json & entry
) 
```





**Parameters:**


* `entry` The JSON entry to clean. 



**Returns:**

A cleaned string without quotes. 





        

<hr>



### function extract\_from\_json 

_Extracts a value of type T from a JSON object using the specified key._ 
```C++
template<typename T>
T astrea::utilities::extract_from_json (
    const nlohmann::json & json,
    const std::string & key
) 
```





**Template parameters:**


* `T` The type of the value to extract. 



**Parameters:**


* `json` The JSON object to extract from. 
* `key` The key to look for in the JSON object. 



**Returns:**

The extracted value of type T. 




**Exception:**


* `std::runtime_error` if the key is not found or if the value is null. 




        

<hr>



### function extract\_optional\_from\_json 

_Extracts an optional value of type T from a JSON object using the specified key._ 
```C++
template<typename T>
std::optional< T > astrea::utilities::extract_optional_from_json (
    const nlohmann::json & json,
    const std::string & key
) 
```





**Template parameters:**


* `T` The type of the value to extract. 



**Parameters:**


* `json` The JSON object to extract from. 
* `key` The key to look for in the JSON object. 



**Returns:**

An std::optional containing the extracted value, or std::nullopt if the key is not found or the value is null. 




**Exception:**


* `std::runtime_error` if the key is not found. 




        

<hr>



### function extract\_optional\_string\_from\_json 

_Extracts an optional string value from a JSON object using the specified key._ 
```C++
std::optional< std::string > astrea::utilities::extract_optional_string_from_json (
    const nlohmann::json & json,
    const std::string & key
) 
```





**Parameters:**


* `json` The JSON object to extract from. 
* `key` The key to look for in the JSON object. 



**Returns:**

An std::optional containing the extracted string value, or std::nullopt if the key is not found or the value is null. 




**Exception:**


* `std::runtime_error` if the key is not found. 




        

<hr>



### function extract\_string\_from\_json 

_Extracts a string value from a JSON object using the specified key._ 
```C++
std::string astrea::utilities::extract_string_from_json (
    const nlohmann::json & json,
    const std::string & key
) 
```





**Parameters:**


* `json` The JSON object to extract from. 
* `key` The key to look for in the JSON object. 



**Returns:**

The extracted string value. 




**Exception:**


* `std::runtime_error` if the key is not found or if the value is null. 




        

<hr>



### function get\_type\_name 

_Gets the demangled(ish) type name of a given type._ 
```C++
template<typename T>
std::string astrea::utilities::get_type_name () 
```





**Template parameters:**


* `T` The type to get the name of. 



**Returns:**

The demangled type name as a string. 





        

<hr>



### function replace\_all 

_Replaces all occurrences of a substring with another substring in a string._ 
```C++
std::string astrea::utilities::replace_all (
    std::string const & original,
    std::string const & before,
    std::string const & after
) 
```





**Parameters:**


* `original` The original string. 
* `before` The substring to be replaced. 
* `after` The substring to replace with. 



**Returns:**

A new string with all occurrences replaced. 





        

<hr>



### function split 

_Splits a string into a vector of substrings based on a delimiter._ 
```C++
std::vector< std::string > astrea::utilities::split (
    std::string s,
    const std::string & delimiter
) 
```





**Parameters:**


* `s` The string to split. 
* `delimiter` The delimiter to split by. 



**Returns:**

A vector of substrings.




**Note:**

Taken from [https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c](https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c) 





        

<hr>



### function trim 

_Trims whitespace from both ends of a string._ 
```C++
std::string astrea::utilities::trim (
    const std::string & str,
    const std::string & whitespace=" \t"
) 
```





**Parameters:**


* `str` The string to trim. 
* `whitespace` The characters to trim (default is space and tab). 



**Returns:**

A trimmed string. 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/utilities/utilities/IdProvider.hpp`

