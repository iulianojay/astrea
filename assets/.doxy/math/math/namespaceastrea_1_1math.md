

# Namespace astrea::math



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**math**](namespaceastrea_1_1math.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::MP\_UNITS\_IS\_VALUE\_WORKAROUND(isq::angular\_measure)&gt; auto | [**acos**](#function-acos) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric arccosine function for dimensionless quantities._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::MP\_UNITS\_IS\_VALUE\_WORKAROUND(isq::angular\_measure)&gt; auto | [**asin**](#function-asin) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric arcsine function for dimensionless quantities._  |
|  constexpr mp\_units::quantity&lt; mp\_units::one, Rep &gt; | [**assoc\_legendre**](#function-assoc_legendre) (const unsigned int & n, const unsigned int & m, const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the associated Legendre function of the first kind._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::MP\_UNITS\_IS\_VALUE\_WORKAROUND(isq::angular\_measure)&gt; auto | [**atan**](#function-atan) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric arctangent function for dimensionless quantities._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::MP\_UNITS\_IS\_VALUE\_WORKAROUND(isq::angular\_measure)&gt; auto | [**atan2**](#function-atan2) (const mp\_units::quantity&lt; R, Rep &gt; & y, const mp\_units::quantity&lt; R, Rep &gt; & x) noexcept<br>_2D trigonometric arctangent function._  |
|  T | [**atan3**](#function-atan3) (T y, T x) <br> |
|  mp\_units::quantity&lt; R, Rep &gt; | [**clamp**](#function-clamp) (const mp\_units::quantity&lt; R, Rep &gt; & q, const mp\_units::quantity&lt; R, Rep &gt; & low, const mp\_units::quantity&lt; R, Rep &gt; & high) noexcept<br> |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**cos**](#function-cos) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric cosine function for angular quantities._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**cosh**](#function-cosh) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the hyperbolic cosine of a given angle in radians._  |
|  constexpr mp\_units::quantity&lt; mp\_units::one, Rep &gt; | [**cyl\_bessel\_j**](#function-cyl_bessel_j) (const Rep & nu, const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the Bessel function of the first kind of order zero._  |
|  double | [**evaluate\_chebyshev\_derivative**](#function-evaluate_chebyshev_derivative) (double x, double lb, double ub, const std::array&lt; double, N &gt; & coeff, double extrapolationTol=1.0e-6) <br>_Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._  |
|  double | [**evaluate\_chebyshev\_derivative**](#function-evaluate_chebyshev_derivative) (double x, const std::array&lt; double, N &gt; & boundsCoeff, double extrapolationTol=1.0e-6) <br>_Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._  |
|  double | [**evaluate\_chebyshev\_polynomial**](#function-evaluate_chebyshev_polynomial) (const double & x, const double & lb, const double & ub, const std::array&lt; double, N &gt; & coeff, const double & coeffZeroFactor=0.5, const double & extrapolationTol=1.0e-6) <br>_Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._  |
|  double | [**evaluate\_chebyshev\_polynomial**](#function-evaluate_chebyshev_polynomial) (const double & x, const std::array&lt; double, N &gt; & boundsCoeff, const double & coeffZeroFactor=0.5, const double & extrapolationTol=1.0e-6) <br>_Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._  |
|  Y | [**fast\_interpolate**](#function-fast_interpolate) (const std::array&lt; X, 2 &gt; & x, const std::array&lt; Y, 2 &gt; & y, const X & sx) <br>_Fast linear interpolation for two points, with bounds checking._  |
|  Y | [**interpolate**](#function-interpolate) (const std::vector&lt; X &gt; & x, const std::vector&lt; Y &gt; & y, const X & sx) <br>_Linear interpolation for a single point, with bounds checking._  |
|  mp\_units::quantity&lt; R, Rep &gt; | [**max**](#function-max) (const mp\_units::quantity&lt; R, Rep &gt; & q1, const mp\_units::quantity&lt; R, Rep &gt; & q2) noexcept<br>_Returns the maximum of two quantities of the same unit._  |
|  mp\_units::quantity&lt; R, Rep &gt; | [**min**](#function-min) (const mp\_units::quantity&lt; R, Rep &gt; & q1, const mp\_units::quantity&lt; R, Rep &gt; & q2) noexcept<br>_Returns the minimum of two quantities of the same unit._  |
|  constexpr bool | [**nearly\_equal**](#function-nearly_equal) (const mp\_units::quantity&lt; R1, Rep &gt; & x, const mp\_units::quantity&lt; R2, Rep &gt; & y, const mp\_units::quantity&lt; mp\_units::one, Rep &gt; & relTol=0.0 \*mp\_units::one, const mp\_units::quantity&lt; mp\_units::one, Rep &gt; & absTol=0.0 \*mp\_units::one) noexcept<br>_Check if two quantities of the same unit are nearly equal within a relative and absolute tolerance._  |
|  mp\_units::quantity&lt; mp\_units::one, Rep1 &gt; | [**pow**](#function-pow) (const mp\_units::quantity&lt; R1, Rep1 &gt; & q, const mp\_units::quantity&lt; R2, Rep2 &gt; & n) noexcept<br>_Returns the result of raising a dimensionless quantity to the power of another dimensionless quantity._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**sin**](#function-sin) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric sine function for angular quantities._  |
|  constexpr auto | [**sin\_cos\_pack**](#function-sin_cos_pack) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the sine and cosine of a given angle in radians._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**sinc**](#function-sinc) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the sinc function for a given angle in radians._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**sinh**](#function-sinh) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Computes the hyperbolic sine of a given angle in radians._  |
|  constexpr mp\_units::QuantityOf&lt; mp\_units::dimensionless &gt; auto | [**tan**](#function-tan) (const mp\_units::quantity&lt; R, Rep &gt; & q) noexcept<br>_Trigonometric tangent function for angular quantities._  |
|  double | [**transform\_from\_chebyshev\_range**](#function-transform_from_chebyshev_range) (const double & x, const double & lb, const double & ub) <br>_Transform variable from the Chebyshev range of [-1, 1] to the range [lb, ub]._  |
|  double | [**transform\_to\_chebyshev\_range**](#function-transform_to_chebyshev_range) (const double & x, const double & lb, const double & ub) <br>_Transform variable from the range [lb, ub] to the Chebyshev range of [-1, 1]._  |




























## Public Functions Documentation




### function acos 

_Trigonometric arccosine function for dimensionless quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto astrea::math::acos (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the input (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The dimensionless quantity. 



**Returns:**

The arccosine of the quantity as an angular measure (radians). 





        

<hr>



### function asin 

_Trigonometric arcsine function for dimensionless quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto astrea::math::asin (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the input (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The dimensionless quantity. 



**Returns:**

The arcsine of the quantity as an angular measure (radians). 





        

<hr>



### function assoc\_legendre 

_Computes the associated Legendre function of the first kind._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R, typename Rep>
constexpr mp_units::quantity< mp_units::one, Rep > astrea::math::assoc_legendre (
    const unsigned int & n,
    const unsigned int & m,
    const mp_units::quantity< R, Rep > & q
) noexcept
```



This function computes the associated Legendre function P\_n^m(x) for given n, m, and x. It is defined as P\_n^m(x) = (1/2^n n!) (d/dx)^n ((1 - x^2)^n) P\_m^n(x).




**Template parameters:**


* `R` The reference type for the input value (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `n` The degree of the polynomial. 
* `m` The order of the polynomial. 
* `q` The input value. 



**Returns:**

The value of the associated Legendre function at the given input. 





        

<hr>



### function atan 

_Trigonometric arctangent function for dimensionless quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto astrea::math::atan (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the input (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The dimensionless quantity. 



**Returns:**

The arctangent of the quantity as an angular measure (radians). 





        

<hr>



### function atan2 

_2D trigonometric arctangent function._ 
```C++
template<mp_units::Quantity auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto astrea::math::atan2 (
    const mp_units::quantity< R, Rep > & y,
    const mp_units::quantity< R, Rep > & x
) noexcept
```





**Template parameters:**


* `R` The reference type for the input (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `y` The first dimensionless quantity (numerator). 
* `x` The second dimensionless quantity (denominator). 



**Returns:**

The arctangent of the ratio y/x as an angular measure (radians). 





        

<hr>



### function atan3 

```C++
template<typename T>
T astrea::math::atan3 (
    T y,
    T x
) 
```




<hr>



### function clamp 

```C++
template<auto R, typename Rep>
inline mp_units::quantity< R, Rep > astrea::math::clamp (
    const mp_units::quantity< R, Rep > & q,
    const mp_units::quantity< R, Rep > & low,
    const mp_units::quantity< R, Rep > & high
) noexcept
```




<hr>



### function cos 

_Trigonometric cosine function for angular quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::cos (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle quantity. 



**Returns:**

The cosine of the angle as a dimensionless quantity. 





        

<hr>



### function cosh 

_Computes the hyperbolic cosine of a given angle in radians._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::cosh (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle in radians. 



**Returns:**

The value of the hyperbolic cosine at the given angle. 





        

<hr>



### function cyl\_bessel\_j 

_Computes the Bessel function of the first kind of order zero._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R, typename Rep>
constexpr mp_units::quantity< mp_units::one, Rep > astrea::math::cyl_bessel_j (
    const Rep & nu,
    const mp_units::quantity< R, Rep > & q
) noexcept
```



This function computes the Bessel function of the first kind of order zero for a given value. It is defined as J\_0(x) = (1/π) ∫\_0^π cos(x sin(θ)) dθ.




**Template parameters:**


* `R` The reference type for the input value (e.g., dimensionless). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The input value. 



**Returns:**

The value of the Bessel function of the first kind of order zero at the given input. 





        

<hr>



### function evaluate\_chebyshev\_derivative 

_Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._ 
```C++
template<size_t N>
double astrea::math::evaluate_chebyshev_derivative (
    double x,
    double lb,
    double ub,
    const std::array< double, N > & coeff,
    double extrapolationTol=1.0e-6
) 
```



Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder




**Parameters:**


* `x` Value at which the Chebyshev polynomial is to be evaluated at 
* `lb` Lower bound of the function range 
* `ub` Upper bound of the function range 
* `coeff` Chebyshev coefficients evaluated using chebyshev\_coefficients function 
* `extrapolationTol` Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.



**Returns:**

Corresponding Chebyshev coefficient values




**Template parameters:**


* `N` Size of the array



**Exception:**


* `std::invalid_argument` If coeff has less than one value, or if extrapolation occurs 




        

<hr>



### function evaluate\_chebyshev\_derivative 

_Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._ 
```C++
template<size_t N>
double astrea::math::evaluate_chebyshev_derivative (
    double x,
    const std::array< double, N > & boundsCoeff,
    double extrapolationTol=1.0e-6
) 
```





**Note:**

The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary coefficients from CSpice


Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder




**Parameters:**


* `x` Value at which the Chebyshev polynomial is to be evaluated at 
* `boundsCoeff` Vector containing lb, ub, and Chebyshev coefficients evaluated using chebyshev\_coefficients function 
* `extrapolationTol` Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.



**Returns:**

Corresponding Chebyshev coefficient values




**Template parameters:**


* `N` Size of the array



**Exception:**


* `std::invalid_argument` If coeff has less than one value, or if extrapolation occurs 




        

<hr>



### function evaluate\_chebyshev\_polynomial 

_Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._ 
```C++
template<std::size_t N>
double astrea::math::evaluate_chebyshev_polynomial (
    const double & x,
    const double & lb,
    const double & ub,
    const std::array< double, N > & coeff,
    const double & coeffZeroFactor=0.5,
    const double & extrapolationTol=1.0e-6
) 
```



Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev




**Parameters:**


* `x` Value at which the Chebyshev polynomial is to be evaluated at 
* `lb` Lower bound of the function range 
* `ub` Upper bound of the function range 
* `coeff` Chebyshev coefficients evaluated using chebyshev\_coefficients function 
* `coeffZeroFactor` Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0] has already been multiplied by 0.5, so set factor to 1.0 
* `extrapolationTol` Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.



**Returns:**

Corresponding Chebyshev coefficient values




**Template parameters:**


* `N` Size of the array



**Exception:**


* `std::invalid_argument` If coeff has less than one value, or if extrapolation occurs 




        

<hr>



### function evaluate\_chebyshev\_polynomial 

_Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using Clenshaw's recurrence formula._ 
```C++
template<std::size_t N>
double astrea::math::evaluate_chebyshev_polynomial (
    const double & x,
    const std::array< double, N > & boundsCoeff,
    const double & coeffZeroFactor=0.5,
    const double & extrapolationTol=1.0e-6
) 
```





**Note:**

The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary coefficients from CSpice


Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev




**Parameters:**


* `x` Value at which the Chebyshev polynomial is to be evaluated at 
* `boundsCoeff` Array containing lb, ub, and Chebyshev coefficients evaluated using chebyshev\_coefficients function 
* `coeffZeroFactor` Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0] has already been multiplied by 0.5, so set factor to 1.0 
* `extrapolationTol` Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.



**Returns:**

Corresponding Chebyshev coefficient values




**Template parameters:**


* `N` Size of the array



**Exception:**


* `std::invalid_argument` If coeff has less than one value, or if extrapolation occurs 




        

<hr>



### function fast\_interpolate 

_Fast linear interpolation for two points, with bounds checking._ 
```C++
template<typename X, typename Y>
inline Y astrea::math::fast_interpolate (
    const std::array< X, 2 > & x,
    const std::array< Y, 2 > & y,
    const X & sx
) 
```





**Template parameters:**


* `X` Type of the x values (e.g. time). 
* `Y` Type of the y values (e.g. distance, angle). Must support arithmetic operations. 



**Parameters:**


* `x` Two x values corresponding to the y values. Must be in ascending order. 
* `y` Two y values corresponding to the x values. 
* `sx` The x value to interpolate at. Must be between x[0] and x[1]. 



**Returns:**

Y The interpolated y value at sx. 




**Exception:**


* `std::runtime_error` if sx is outside the bounds of x. 




        

<hr>



### function interpolate 

_Linear interpolation for a single point, with bounds checking._ 
```C++
template<typename X, typename Y>
inline Y astrea::math::interpolate (
    const std::vector< X > & x,
    const std::vector< Y > & y,
    const X & sx
) 
```





**Template parameters:**


* `X` Type of the x values (e.g. time). 
* `Y` Type of the y values (e.g. distance, angle). Must support arithmetic operations. 



**Parameters:**


* `x` Vector of x values corresponding to the y values. Must be in ascending order. 
* `y` Vector of y values corresponding to the x values. 
* `sx` The x value to interpolate at. Must be between x[0] and x.back(). 



**Returns:**

Y The interpolated y value at sx. 




**Exception:**


* `std::runtime_error` if sx is outside the bounds of x. 




        

<hr>



### function max 

_Returns the maximum of two quantities of the same unit._ 
```C++
template<auto R, typename Rep>
inline mp_units::quantity< R, Rep > astrea::math::max (
    const mp_units::quantity< R, Rep > & q1,
    const mp_units::quantity< R, Rep > & q2
) noexcept
```





**Template parameters:**


* `R` The unit type (e.g., distance, time). 
* `Rep` The representation type (e.g., double). 



**Parameters:**


* `q1` First quantity to compare. 
* `q2` Second quantity to compare. 



**Returns:**

The maximum of the two quantities. 





        

<hr>



### function min 

_Returns the minimum of two quantities of the same unit._ 
```C++
template<auto R, typename Rep>
inline mp_units::quantity< R, Rep > astrea::math::min (
    const mp_units::quantity< R, Rep > & q1,
    const mp_units::quantity< R, Rep > & q2
) noexcept
```





**Template parameters:**


* `R` The unit type (e.g., distance, time). 
* `Rep` The representation type (e.g., double). 



**Parameters:**


* `q1` First quantity to compare. 
* `q2` Second quantity to compare. 



**Returns:**

The minimum of the two quantities. 





        

<hr>



### function nearly\_equal 

_Check if two quantities of the same unit are nearly equal within a relative and absolute tolerance._ 
```C++
template<auto R1, auto R2, typename Rep>
constexpr bool astrea::math::nearly_equal (
    const mp_units::quantity< R1, Rep > & x,
    const mp_units::quantity< R2, Rep > & y,
    const mp_units::quantity< mp_units::one, Rep > & relTol=0.0 *mp_units::one,
    const mp_units::quantity< mp_units::one, Rep > & absTol=0.0 *mp_units::one
) noexcept
```





**Template parameters:**


* `R` The unit type (e.g., distance, time). 
* `Rep` The representation type (e.g., double). 



**Parameters:**


* `x` First quantity to compare. 
* `y` Second quantity to compare. 
* `relTol` Relative tolerance for comparison. Default is 0, which means relative differences are not considered. 
* `absTol` Absolute tolerance for comparison. Default is 0, which means absolute differences are not considered. 



**Returns:**

true if the two quantities are nearly equal within the specified tolerance. 




**Returns:**

false if they are not nearly equal. 





        

<hr>



### function pow 

_Returns the result of raising a dimensionless quantity to the power of another dimensionless quantity._ 
```C++
template<mp_units::ReferenceOf< mp_units::dimensionless > auto R1, mp_units::ReferenceOf< mp_units::dimensionless > auto R2, typename Rep1, typename Rep2>
inline mp_units::quantity< mp_units::one, Rep1 > astrea::math::pow (
    const mp_units::quantity< R1, Rep1 > & q,
    const mp_units::quantity< R2, Rep2 > & n
) noexcept
```





**Template parameters:**


* `R` The unit type (must be dimensionless). 
* `Rep` The representation type (e.g., double). 



**Parameters:**


* `q` The quantity to be raised to a power. 
* `n` The exponent quantity. 



**Returns:**

The result of raising q to the power of n, with the same unit as q (which is dimensionless). 





        

<hr>



### function sin 

_Trigonometric sine function for angular quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::sin (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle quantity. 



**Returns:**

The sine of the angle as a dimensionless quantity. 





        

<hr>



### function sin\_cos\_pack 

_Computes the sine and cosine of a given angle in radians._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr auto astrea::math::sin_cos_pack (
    const mp_units::quantity< R, Rep > & q
) noexcept
```



This function computes both the sine and cosine of a given angle and returns them as a pair.




**Parameters:**


* `angle` The angle in radians. 



**Returns:**

A pair containing the sine and cosine of the angle. 





        

<hr>



### function sinc 

_Computes the sinc function for a given angle in radians._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::sinc (
    const mp_units::quantity< R, Rep > & q
) noexcept
```



The sinc function is defined as sin(x)/x, where x is in radians. This function handles both integral and floating-point types.




**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle in radians. 



**Returns:**

The value of the sinc function at the given angle. 





        

<hr>



### function sinh 

_Computes the hyperbolic sine of a given angle in radians._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::sinh (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle in radians. 



**Returns:**

The value of the hyperbolic sine at the given angle. 





        

<hr>



### function tan 

_Trigonometric tangent function for angular quantities._ 
```C++
template<mp_units::ReferenceOf< mp_units::MP_UNITS_IS_VALUE_WORKAROUND(isq::angular_measure)> auto R, typename Rep>
inline constexpr mp_units::QuantityOf< mp_units::dimensionless > auto astrea::math::tan (
    const mp_units::quantity< R, Rep > & q
) noexcept
```





**Template parameters:**


* `R` The reference type for the angle (e.g., radian). 
* `Rep` The representation type (e.g., double, float). 



**Parameters:**


* `q` The angle quantity. 



**Returns:**

The tangent of the angle as a dimensionless quantity. 





        

<hr>



### function transform\_from\_chebyshev\_range 

_Transform variable from the Chebyshev range of [-1, 1] to the range [lb, ub]._ 
```C++
double astrea::math::transform_from_chebyshev_range (
    const double & x,
    const double & lb,
    const double & ub
) 
```



Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10




**Parameters:**


* `x` Variable in the Chebyshev range 
* `lb` Lower bound of the function range 
* `ub` Upper bound of the function range



**Returns:**

Variable in the range [lb, ub] 





        

<hr>



### function transform\_to\_chebyshev\_range 

_Transform variable from the range [lb, ub] to the Chebyshev range of [-1, 1]._ 
```C++
double astrea::math::transform_to_chebyshev_range (
    const double & x,
    const double & lb,
    const double & ub
) 
```



Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10




**Parameters:**


* `x` Variable in the range [lb, ub] 
* `lb` Lower bound of the function range 
* `ub` Upper bound of the function range



**Returns:**

Variable in the Chebyshev range [-1, 1] 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/math/math/chebyshev_util.cpp`

