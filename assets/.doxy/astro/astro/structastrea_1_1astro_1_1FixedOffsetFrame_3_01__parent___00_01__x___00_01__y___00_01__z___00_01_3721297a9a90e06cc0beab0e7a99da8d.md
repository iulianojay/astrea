

# Struct astrea::astro::FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;

**template &lt;IsFrame [**auto**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_parent\_, [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_x\_, [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_y\_, [**Distance**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_z\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_phi\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_theta\_, [**Angle**](classastrea_1_1astro_1_1DirectionCosineMatrix.md) \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_, auto... Args&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetFrame&lt; \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__parent___00_01__x___00_01__y___00_01__z___00_01_3721297a9a90e06cc0beab0e7a99da8d.md)



_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset._[More...](#detailed-description)

* `#include <FixedOffsetFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)














































































































## Detailed Description




**Template parameters:**


* `_parent_` The parent frame from which this frame is derived. Must satisfy the IsFrame concept. 
* `_x_` The fixed offset in the x direction from the parent frame. 
* `_y_` The fixed offset in the y direction from the parent frame. 
* `_z_` The fixed offset in the z direction from the parent frame. 
* `_phi_` The fixed offset angle around the x-axis from the parent frame. 
* `_theta_` The fixed offset angle around the y-axis from the parent frame. 
* `_psi_` The fixed offset angle around the z-axis from the parent frame. 
* `_sequence_` The rotation sequence for applying the angular offsets. 




    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

