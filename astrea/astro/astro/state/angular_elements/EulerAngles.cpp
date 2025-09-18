#include <astro/state/angular_elements/instances/EulerAngles.hpp>

namespace astrea {
namespace astro {


EulerAngles::EulerAngles(
    const std::array<Angle, 3>& angles,
    const EulerAngleSequence& sequence,
    const EulerAngleType& type   = EulerAngleType::EULER,
    const RotationType& rotation = RotationType::INTRINSIC
) :
    _angles(angles),
    _sequence(sequence),
    _type(type),
    _rotation(rotation)
{
}

Angle& EulerAngles::operator[](const std::size_t index) { return _angles[index]; }
const Angle& EulerAngles::operator[](const std::size_t index) const { return _angles[index]; }

Angle& EulerAngles::get_phi() { return _angles[0]; }
const Angle& EulerAngles::get_phi() const { return _angles[0]; }

Angle& EulerAngles::get_theta() { return _angles[1]; }
const Angle& EulerAngles::get_theta() const { return _angles[1]; }

Angle& EulerAngles::get_psi() { return _angles[2]; }
const Angle& EulerAngles::get_psi() const { return _angles[2]; }

std::array<Angle, 3>& EulerAngles::get_angles() { return _angles; }
const std::array<Angle, 3>& EulerAngles::get_angles() const { return _angles; }

EulerAngleSequence EulerAngles::get_sequence() const { return _sequence; }
EulerAngleType EulerAngles::get_type() const { return _type; }
RotationType EulerAngles::get_rotation() const { return _rotation; }


} // namespace astro
} // namespace astrea