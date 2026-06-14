

# Struct astrea::astro::FixedOffsetFrame

**template &lt;auto...&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetFrame**](structastrea_1_1astro_1_1FixedOffsetFrame.md)



_Class representing a fixed offset frame, which is defined by a fixed spatial and/or angular offset from a parent frame._ [More...](#detailed-description)


































































## Detailed Description


This class allows for the definition of frames that are not aligned with their parent frame, such as a spacecraft body frame that is offset from an inertial frame.




**Template parameters:**


* `_parent_` The parent frame from which this frame is derived. Must satisfy the IsFrame concept. 
* `Args` A variadic list of template parameters that define the spatial and/or angular offsets. These can be distances for spatial offsets or angles for angular offsets, along with an optional rotation sequence for the angular offsets. 




    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

