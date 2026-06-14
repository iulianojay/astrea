

# Struct astrea::astro::FixedOffsetFrame&lt; \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_phi\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_theta\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_, auto... Args&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetFrame&lt; \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__phi___00_01__theta___00_01__psi_9e091a834f5483531831878cbc7beda5.md)



_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a pure angular offset (no spatial offset)._[More...](#detailed-description)

* `#include <FixedOffsetFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)














































































































## Detailed Description




**Template parameters:**


* `_parent_` The parent frame from which this frame is derived. Must satisfy the IsFrame concept. 
* `_phi_` The fixed offset angle around the x-axis from the parent frame. 
* `_theta_` The fixed offset angle around the y-axis from the parent frame. 
* `_psi_` The fixed offset angle around the z-axis from the parent frame. 
* `_sequence_` The rotation sequence for applying the angular offsets. 
* `Args` Additional template parameters (not used in this specialization). 




    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

