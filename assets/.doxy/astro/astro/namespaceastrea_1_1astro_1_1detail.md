

# Namespace astrea::astro::detail



[**Namespace List**](namespaces.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**detail**](namespaceastrea_1_1astro_1_1detail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**AxisBase**](structastrea_1_1astro_1_1detail_1_1AxisBase.md) <br> |
| struct | [**BarycenterBase**](structastrea_1_1astro_1_1detail_1_1BarycenterBase.md) <br> |
| struct | [**BodyFixedFrameBase**](structastrea_1_1astro_1_1detail_1_1BodyFixedFrameBase.md) <br> |
| struct | [**CelestialBodyBase**](structastrea_1_1astro_1_1detail_1_1CelestialBodyBase.md) <br> |
| struct | [**EventInner**](structastrea_1_1astro_1_1detail_1_1EventInner.md) &lt;typename T&gt;<br>_A template class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._ |
| struct | [**EventInnerBase**](structastrea_1_1astro_1_1detail_1_1EventInnerBase.md) <br>_Pure virtual base class for_ [_**Event**_](classastrea_1_1astro_1_1Event.md) _inner implementations._ |
| struct | [**FrameBase**](structastrea_1_1astro_1_1detail_1_1FrameBase.md) <br>_Empty base class for all frames in astrea. This allows us to use std::derived\_from to check if a type is a frame._  |
| struct | [**OriginBase**](structastrea_1_1astro_1_1detail_1_1OriginBase.md) <br> |
| struct | [**SynodicFrameBase**](structastrea_1_1astro_1_1detail_1_1SynodicFrameBase.md) <br> |
| struct | [**VehicleInner**](structastrea_1_1astro_1_1detail_1_1VehicleInner.md) &lt;typename T&gt;<br>_A template class for vehicle inner implementations._  |
| struct | [**VehicleInnerBase**](structastrea_1_1astro_1_1detail_1_1VehicleInnerBase.md) <br>_Pure virtual base class for vehicle inner implementations._  |
| struct | [**apply\_nttp\_template**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template.md) &lt;T, typename Tuple&gt;<br> |
| struct | [**apply\_nttp\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__nttp__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) &lt;T, Frames&gt;<br> |
| struct | [**apply\_template**](structastrea_1_1astro_1_1detail_1_1apply__template.md) &lt;T, typename Tuple&gt;<br> |
| struct | [**apply\_template&lt; T, std::tuple&lt; Frames... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1apply__template_3_01T_00_01std_1_1tuple_3_01Frames_8_8_8_01_4_01_4.md) &lt;T, Frames&gt;<br> |
| struct | [**multi\_tuple\_cat**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat.md) &lt;Tuples&gt;<br> |
| struct | [**multi\_tuple\_cat&lt; First, Rest... &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01First_00_01Rest_8_8_8_01_4.md) &lt;typename First, Rest&gt;<br> |
| struct | [**multi\_tuple\_cat&lt; Only &gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_01Only_01_4.md) &lt;typename Only&gt;<br> |
| struct | [**multi\_tuple\_cat&lt;&gt;**](structastrea_1_1astro_1_1detail_1_1multi__tuple__cat_3_4.md) &lt;&gt;<br> |
| struct | [**tuple\_cat\_types**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types.md) &lt;typename TupleA, typename TupleB&gt;<br> |
| struct | [**tuple\_cat\_types&lt; std::tuple&lt; As... &gt;, std::tuple&lt; Bs... &gt; &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types_3_01std_1_1tuple_3_01As_8_8_8_01_4_00_01std8cf8a2c8692dfec60c2615039d60391f.md) &lt;As, Bs&gt;<br> |
| struct | [**tuple\_to\_variant**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant.md) &lt;typename Tuple, Extra&gt;<br> |
| struct | [**tuple\_to\_variant&lt; std::tuple&lt; Ts... &gt;, Extra... &gt;**](structastrea_1_1astro_1_1detail_1_1tuple__to__variant_3_01std_1_1tuple_3_01Ts_8_8_8_01_4_00_01Extra_8_8_8_01_4.md) &lt;Ts, Extra&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename [**tuple\_cat\_types**](structastrea_1_1astro_1_1detail_1_1tuple__cat__types.md)&lt; [**AutomaticallyRegisteredFrames**](namespaceastrea_1_1astro.md#typedef-automaticallyregisteredframes), typename [**ExtraRegisteredFrames**](structastrea_1_1astro_1_1ExtraRegisteredFrames.md)&lt;&gt;::type &gt;::type | [**AllRegisteredFrames**](#typedef-allregisteredframes)  <br>_Alias for the full tuple of registered frames (built-in + user-registered)._  |
















































## Public Types Documentation




### typedef AllRegisteredFrames 

_Alias for the full tuple of registered frames (built-in + user-registered)._ 
```C++
using astrea::astro::detail::AllRegisteredFrames = typedef typename tuple_cat_types<AutomaticallyRegisteredFrames, typename ExtraRegisteredFrames<>::type>::type;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/definitions/frame_registry.hpp`

