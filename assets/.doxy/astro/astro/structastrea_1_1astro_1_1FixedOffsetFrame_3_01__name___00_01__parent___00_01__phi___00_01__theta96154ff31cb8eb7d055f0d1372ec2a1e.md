

# Struct astrea::astro::FixedOffsetFrame&lt; \_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;

**template &lt;mp\_units::symbol\_text \_name\_, IsFrame auto \_parent\_, Angle \_phi\_, Angle \_theta\_, Angle \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_, auto... Args&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__phi___00_01__theta96154ff31cb8eb7d055f0d1372ec2a1e.md)



_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for an angular offset with no spatial misalignment that lets the name be specified._[More...](#detailed-description)

* `#include <FixedOffsetFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)














































































































## Detailed Description




**Template parameters:**


* `_name_` The name of the frame. 
* `_parent_` The parent frame from which this frame is derived. Must satisfy the IsFrame concept. 
* `_phi_` The fixed offset angle around the x-axis from the parent frame. 
* `_theta_` The fixed offset angle around the y-axis from the parent frame. 
* `_psi_` The fixed offset angle around the z-axis from the parent frame. 
* `_sequence_` The rotation sequence for applying the angular offsets. 




    

------------------------------
The documentation for this class was generated from the following file `astrea/astro/astro/frames/framework/FixedOffsetFrame.hpp`

