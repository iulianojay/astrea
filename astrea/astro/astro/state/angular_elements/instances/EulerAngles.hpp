#pragma once

#include <array>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/types/typedefs.hpp>

namespace astrea {
namespace astro {

enum class EulerAngleSequence : EnumType { XYX, XZX, YXY, YZY, ZXZ, ZYZ, XYZ, XZY, YXZ, YZX, ZXY, ZYX };
enum class EulerAngleType : EnumType { EULER, TAIT_BRYAN };
enum class RotationType : EnumType { INTRINSIC, EXTRINSIC };

class EulerAngles {
  public:
    EulerAngles(
        const std::array<Angle, 3>& angles,
        const EulerAngleSequence& sequence,
        const EulerAngleType& type   = EulerAngleType::EULER,
        const RotationType& rotation = RotationType::INTRINSIC
    );
    ~EulerAngles() = default;

    Angle& operator[](const std::size_t index);
    const Angle& operator[](const std::size_t index) const;

    Angle& get_phi();
    const Angle& get_phi() const;

    Angle& get_theta();
    const Angle& get_theta() const;

    Angle& get_psi();
    const Angle& get_psi() const;

    std::array<Angle, 3>& get_angles();
    const std::array<Angle, 3>& get_angles() const;

    EulerAngleSequence get_sequence() const;
    EulerAngleType get_type() const;
    RotationType get_rotation() const;

  private:
    std::array<Angle, 3> _angles; //!< Euler angles
    EulerAngleSequence _sequence; //!< Sequence of axes for the Euler angles
    EulerAngleType _type;         //!< Type of Euler angles
    RotationType _rotation;       //!< Type of rotation
};

class EulerAngleRates {
  public:
    EulerAngleRates()  = default;
    ~EulerAngleRates() = default;

  private:
    std::array<AngularRate, 3> _angularRates; //!< Euler angular rates
    EulerAngleSequence _sequence;             //!< Sequence of axes for the Euler angles
    EulerAngleType _type;                     //!< Type of Euler angles
    RotationType _rotation;                   //!< Type of rotation
};


} // namespace astro
} // namespace astrea