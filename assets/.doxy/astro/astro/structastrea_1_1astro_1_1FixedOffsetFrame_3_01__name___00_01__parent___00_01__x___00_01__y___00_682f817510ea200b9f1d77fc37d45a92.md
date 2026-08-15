

# Struct astrea::astro::FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;

**template &lt;mp\_units::symbol\_text \_name\_, IsFrame auto \_parent\_, Distance \_x\_, Distance \_y\_, Distance \_z\_, Angle \_phi\_, Angle \_theta\_, Angle \_psi\_, [**RotationSequence**](namespaceastrea_1_1astro.md#enum-rotationsequence) \_sequence\_, auto... Args&gt;**



[**ClassList**](annotated.md) **>** [**astrea**](namespaceastrea.md) **>** [**astro**](namespaceastrea_1_1astro.md) **>** [**FixedOffsetFrame&lt; \_name\_, \_parent\_, \_x\_, \_y\_, \_z\_, \_phi\_, \_theta\_, \_psi\_, \_sequence\_, Args... &gt;**](structastrea_1_1astro_1_1FixedOffsetFrame_3_01__name___00_01__parent___00_01__x___00_01__y___00_682f817510ea200b9f1d77fc37d45a92.md)



_Specialization of_ [_**FixedOffsetFrame**_](structastrea_1_1astro_1_1FixedOffsetFrame.md) _for a combined spatial and angular offset that lets the name be specified._[More...](#detailed-description)

* `#include <FixedOffsetFrame.hpp>`



Inherits the following classes: [astrea::astro::Frame](structastrea_1_1astro_1_1Frame.md)














































































































## Detailed Description




**Template parameters:**


* `_name_` The name of the frame. 
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

