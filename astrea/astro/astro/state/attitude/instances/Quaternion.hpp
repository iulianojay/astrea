/**
 * @file Quaternion.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Class representing a quaternion for attitude transformations between state/frames.
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026 Jay Iuliano
 *
 * The GNU Lesser General Public License (LGPL)
 *
 * This file is part of Astrea.
 * Astrea is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Astrea is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details. You should
 * have received a copy of the GNU General Public License along with Astrea. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include <stdexcept>

#include <mp-units/core.h>
#include <mp-units/math.h>
#include <mp-units/systems/angular/math.h>

#include <units/units.hpp>

#include <astro/astro.fwd.hpp>
#include <astro/frames/CartesianVector.hpp>
#include <astro/frames/frame_concepts.hpp>
#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/state/attitude/instances/EulerAngles.hpp>
#include <astro/types/enums.hpp>

namespace astrea {
namespace astro {

/**
 * @brief Class representing a quaternion for attitude rotations between frames.
 *
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 *
 * @note: These are not real quaternions and are not setup to behave properly as quaternions might.
 * These Quaternions are specifically meant to represent frame rotations and are not meant to be used for general
 * quaternion math. They are automatically normalized on construction to avoid tracking the magnitude and to
 * avoid expensive sqrt as much as possible.
 */
template <typename In_Frame_T, typename Out_Frame_T>
class Quaternion {

    friend class Attitude;

  public:
    using in_frame  = In_Frame_T;
    using out_frame = Out_Frame_T;

    /**
     * @brief Default constructor for the Quaternion class. Initializes to the identity quaternion (no rotation).
     */
    Quaternion() :
        _s(1.0 * mp_units::one),
        _u(CartesianVector<Unitless, In_Frame_T>())
    {
        normalize();
    }

    /**
     * @brief Constructor for the Quaternion class from a CartesianVector.
     *
     * @param vec The CartesianVector representing the vector part of the quaternion. The scalar part is set to 0.
     */
    Quaternion(const CartesianVector<Unitless, In_Frame_T>& vec) :
        _s(0.0 * mp_units::one),
        _u(vec)
    {
        normalize();
    }

    /**
     * @brief Constructor for the Quaternion class from a scalar and a CartesianVector.
     *
     * @param s The scalar part of the quaternion.
     * @param vec The CartesianVector representing the vector part of the quaternion.
     */
    Quaternion(const Unitless& s, const CartesianVector<Unitless, In_Frame_T>& vec) :
        _s(s),
        _u(vec)
    {
        normalize();
    }

    /**
     * @brief Constructor for the Quaternion class from individual components.
     * @param s Scalar part of the quaternion (must be between -1 and 1).
     * @param x X component of the vector part of the quaternion (must be between -1 and 1).
     * @param y Y component of the vector part of the quaternion (must be between -1 and 1).
     * @param z Z component of the vector part of the quaternion (must be between -1 and 1).
     *
     * @throws std::invalid_argument if any of the components are outside the range [-1, 1].
     */
    Quaternion(const Unitless& s, const Unitless& x, const Unitless& y, const Unitless& z) :
        _s(s),
        _u(x, y, z)
    {
        normalize();
    }

    /**
     * @brief Default copy constructor
     */
    Quaternion(const Quaternion& other) = default;

    /**
     * @brief Default move constructor
     */
    Quaternion(Quaternion&& other) = default;

    /**
     * @brief Default copy assignment operator
     */
    Quaternion& operator=(const Quaternion& other) = default;

    /**
     * @brief Default move assignment operator
     */
    Quaternion& operator=(Quaternion&& other) = default;

    /**
     * @brief Equality operator for Quaternion.
     *
     * @param other The other Quaternion to compare with.
     * @return true If the two quaternions are equal.
     * @return false If the two quaternions are not equal.
     */
    bool operator==(const Quaternion& other) const { return _s == other._s && _u == other._u; }

    /**
     * @brief Constructor for the Quaternion class from a Direction Cosine Matrix (DCM).
     *
     * @param dcm The direction cosine matrix to convert to a quaternion.
     *
     * @note Uses Shepperd's method for numerical stability. Algorithm branches based on
     * which element provides the most numerically stable computation.
     *
     * @cite Shepperd, S.W. "Quaternion from rotation matrix." Journal of Guidance and Control,
     *       Vol. 1, No. 3, May-June 1978, pp. 223-224.
     * @cite Wertz, J.R. (ed.), "Spacecraft Attitude Determination and Control,"
     *       Kluwer Academic Publishers, 1978, pp. 414-416.
     */
    Quaternion(const DirectionCosineMatrix<In_Frame_T, Out_Frame_T>& dcm)
    {
        // Convert the DCM to a quaternion using Shepperd's numerically stable algorithm
        const auto trace = dcm.trace();
        const auto& xx   = dcm[0, 0];
        const auto& xy   = dcm[0, 1];
        const auto& xz   = dcm[0, 2];
        const auto& yy   = dcm[1, 1];
        const auto& yx   = dcm[1, 0];
        const auto& yz   = dcm[1, 2];
        const auto& zx   = dcm[2, 0];
        const auto& zy   = dcm[2, 1];
        const auto& zz   = dcm[2, 2];

        // Case 1: Trace > 0 - Most numerically stable when rotation angle < 120°
        // Ref: Shepperd (1978), Eq. 15
        if (trace > 0) {
            const auto r = sqrt(trace + 1.0) * 2.0;
            _s           = 0.25 * r;
            _u[0]        = (zy - yz) / r;
            _u[1]        = (xz - zx) / r;
            _u[2]        = (yx - xy) / r;
        }
        // Case 2: xx is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 16 - Stable when rotation is primarily about x-axis
        else if ((xx > yy) && (xx > zz)) {
            const auto r = sqrt(1.0 + xx - yy - zz) * 2.0;
            _s           = (zy - yz) / r;
            _u[0]        = 0.25 * r;
            _u[1]        = (yx + xy) / r;
            _u[2]        = (zx + xz) / r;
        }
        // Case 3: yy is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 17 - Stable when rotation is primarily about y-axis
        else if (yy > zz) {
            const auto r = sqrt(1.0 + yy - xx - zz) * 2.0;
            _s           = (xz - zx) / r;
            _u[0]        = (yx + xy) / r;
            _u[1]        = 0.25 * r;
            _u[2]        = (zy + yz) / r;
        }
        // Case 4: zz is the largest diagonal element
        // Ref: Shepperd (1978), Eq. 18 - Stable when rotation is primarily about z-axis
        else {
            const auto r = sqrt(1.0 + zz - xx - yy) * 2.0;
            _s           = (yx - xy) / r;
            _u[0]        = (zx + xz) / r;
            _u[1]        = (zy + yz) / r;
            _u[2]        = 0.25 * r;
        }
        normalize();
    }

    /**
     * @brief Constructor for the Quaternion class from an Euler angle sequence.
     *
     * @tparam sequence The rotation sequence of the Euler angles (e.g., XYZ, ZYX).
     * @tparam rotationType The type of rotation (extrinsic or intrinsic).
     * @param angleSequence The Euler angle sequence to convert to a quaternion.
     *
     * @note This constructor converts the Euler angles to a DCM and { uses the DCM constructor to create the quaternion.
     */
    template <RotationSequence sequence, RotationType rotation_type>
    Quaternion(const EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T>& angleSequence) :
        Quaternion(angleSequence.to_dcm())
    {
    }

    /**
     * @brief Constructor for the Quaternion class from an angle and rotation axis.
     *
     * @param angle The angle of rotation.
     * @param axis The axis of rotation represented as a CartesianVector. Must be a unit vector.
     *
     * @note This constructor creates a quaternion representing a rotation of "angle" around the "axis" using the
     * formula: q = [cos(angle/2), axis * sin(angle/2)]
     */
    Quaternion(const Angle& angle, const CartesianVector<Unitless, In_Frame_T>& axis) :
        _s(mp_units::angular::cos(angle / 2.0)),
        _u(axis * mp_units::angular::sin(angle / 2.0))
    {
    }

    /**
     * @brief Get the scalar part of the quaternion.
     *
     * @return Unitless The scalar part of the quaternion.
     */
    DirectionCosineMatrix<In_Frame_T, Out_Frame_T> to_dcm() const
    {
        const auto& x = _u.get_x();
        const auto& y = _u.get_y();
        const auto& z = _u.get_z();
        const auto& s = _s;

        return DirectionCosineMatrix<In_Frame_T, Out_Frame_T>{
            { std::array<Unitless, 3>{ s * s + x * x - y * y - z * z, 2.0 * (x * y - s * z), 2.0 * (x * z + s * y) },
              std::array<Unitless, 3>{ 2.0 * (x * y + s * z), s * s - x * x + y * y - z * z, 2.0 * (y * z - s * x) },
              std::array<Unitless, 3>{ 2.0 * (x * z - s * y), 2.0 * (y * z + s * x), s * s - x * x - y * y + z * z } }
        };
    }

    /**
     * @brief Convert the quaternion to an Euler angle sequence.
     *
     * @tparam sequence The rotation sequence of the Euler angles (e.g., XYZ, ZYX).
     * @tparam rotationType The type of rotation (extrinsic or intrinsic).
     * @return EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> The resulting Euler angle sequence.
     *
     * @note This method converts the quaternion to a DCM and then extracts the Euler angles based on the specified
     * sequence and rotation type. It uses this method: https://pmc.ncbi.nlm.nih.gov/articles/PMC9648712/
     */
    template <RotationSequence sequence, RotationType rotation_type>
    EulerAngles<sequence, rotation_type, In_Frame_T, Out_Frame_T> to_euler_angles() const
    {
        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;

        const bool isProper = is_proper_euler_sequence(sequence);
        auto [i, j, k]      = get_sequence_numbers(sequence);

        if (isProper) { k = 6 - i - j; }

        const Unitless eps = (i - j) * (j - k) * (k - i) / 2 * one;

        const Unitless a = isProper ? _s : _s - _u[j - 1];
        const Unitless b = isProper ? _u[i - 1] : _u[i - 1] + _u[k - 1] * eps;
        const Unitless c = isProper ? _u[j - 1] : _u[j - 1] + _s;
        const Unitless d = isProper ? _u[k - 1] * eps : _u[k - 1] * eps - _u[i - 1];

        const Unitless aPlusBSquared = a * a + b * b;
        const Unitless cPlusDSquared = c * c + d * d;
        Angle theta2                 = acos(2.0 * aPlusBSquared / (aPlusBSquared + cPlusDSquared) - 1.0 * one);
        const Angle thetaPlus        = atan2(b, a);
        const Angle thetaMinus       = atan2(d, c);

        Angle theta1, theta3;
        static constexpr Angle piOver2 = std::numbers::pi / 2.0 * rad;
        if (is_eq_zero(theta2)) {
            theta1 = 0.0 * rad;
            theta3 = 2 * thetaPlus - theta1;
        }
        else if (theta2 == piOver2) {
            theta1 = 0.0 * rad;
            theta3 = 2 * thetaMinus + theta1;
        }
        else {
            theta1 = thetaPlus - thetaMinus;
            theta3 = thetaPlus + thetaMinus;
        }

        if (!isProper) {
            theta3 = eps * theta3;
            theta2 = theta2 - piOver2;
        }
        return { theta1, theta2, theta3 };
    }

    /**
     * @brief Addition operator for the Quaternion class.
     *
     * @param other The quaternion to add to this quaternion.
     * @return A new quaternion that is the sum of this quaternion and the other quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator+(const Quaternion<In_Frame_T, Out_Frame_T>& other) const
    {
        return { _s + other._s, _u + other._u };
    }

    /**
     * @brief In-place addition operator for the Quaternion class.
     *
     * @param other The quaternion to add to this quaternion.
     * @return Quaternion& A reference to this quaternion after addition.
     */
    Quaternion<In_Frame_T, Out_Frame_T>& operator+=(const Quaternion<In_Frame_T, Out_Frame_T>& other)
    {
        *this = *this + other;
        normalize();
        return *this;
    }

    /**
     * @brief Unary negation operator for the Quaternion class.
     *
     * @return A new quaternion that is the negation of this quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator-() const { return { -_s, -_u }; }

    /**
     * @brief Subtraction operator for the Quaternion class.
     *
     * @param other The quaternion to subtract from this quaternion.
     * @return A new quaternion that is the difference between this quaternion and the other quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator-(const Quaternion<In_Frame_T, Out_Frame_T>& other) const
    {
        return *this + (-other);
    }

    /**
     * @brief In-place subtraction operator for the Quaternion class.
     *
     * @param other The quaternion to subtract from this quaternion.
     * @return Quaternion& A reference to this quaternion after subtraction.
     */
    Quaternion<In_Frame_T, Out_Frame_T>& operator-=(const Quaternion<In_Frame_T, Out_Frame_T>& other)
    {
        *this = *this - other;
        normalize();
        return *this;
    }

    /**
     * @brief Multiplication operator for the Quaternion class by a scalar unitless quantity.
     *
     * @param scalar The scalar unitless quantity to multiply the quaternion by.
     * @return The original quaternion. NO scaling is applied to the quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator*(const Unitless& scalar) const { return *this; }

    /**
     * @brief Multiplication operator for the Quaternion class by a scalar unitless quantity.
     *
     * @param scalar The scalar unitless quantity to multiply the quaternion by.
     * @return The original quaternion. NO scaling is applied to the quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T>& operator*=(const Unitless& scalar) { return *this; }

    /**
     * @brief Division operator for the Quaternion class by a scalar unitless quantity.
     *
     * @param scalar The scalar unitless quantity to divide the quaternion by.
     * @return The original quaternion. NO scaling is applied to the quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator/(const Unitless& scalar) const { return *this; }

    /**
     * @brief Division operator for the Quaternion class by a scalar unitless quantity.
     *
     * @param scalar The scalar unitless quantity to divide the quaternion by.
     * @return The original quaternion. NO scaling is applied to the quaternion.
     */
    Quaternion<In_Frame_T, Out_Frame_T>& operator/=(const Unitless& scalar) { return *this; }

    /**
     * @brief Multiplication operator for the Quaternion class.
     *
     * @tparam Out_Frame_U The output frame type of the other quaternion.
     * @param other The quaternion to multiply with this quaternion.
     * @return A new quaternion that is the product of this quaternion and the other quaternion.
     */
    template <typename Out_Frame_U>
        requires(!IsSameFrame<In_Frame_T, Out_Frame_U>)
    Quaternion<In_Frame_T, Out_Frame_U> operator*(const Quaternion<Out_Frame_T, Out_Frame_U>& other) const
    {
        const auto& x1 = _u.get_x();
        const auto& y1 = _u.get_y();
        const auto& z1 = _u.get_z();
        const auto& x2 = other.get_vector_part().get_x();
        const auto& y2 = other.get_vector_part().get_y();
        const auto& z2 = other.get_vector_part().get_z();
        const auto& s1 = _s;
        const auto& s2 = other.get_scalar_part();

        return { s1 * s2 - (x1 * x2 + y1 * y2 + z1 * z2),
                 s1 * x2 + x1 * s2 + y1 * z2 - z1 * y2,
                 s1 * y2 - x1 * z2 + y1 * s2 + z1 * x2,
                 s1 * z2 + x1 * y2 - y1 * x2 + z1 * s2 };
    }

    /**
     * @brief Division operator for the Quaternion class by a scalar time quantity, resulting in a QuaternionPartial.
     *
     * @param dt The time quantity to divide the quaternion by, representing the rate of change of the quaternion.
     * @return A new QuaternionPartial that represents the rate of change of the quaternion with respect to time.
     */
    QuaternionPartial<In_Frame_T, Out_Frame_T> operator/(const Time& dt) const
    {
        return QuaternionPartial<In_Frame_T, Out_Frame_T>{ _s / dt, _u / dt };
    }

    /**
     * @brief Rotates a vector from the input frame to the output frame using this quaternion.
     *
     * @tparam Value_T The type of the vector components (e.g., double, quantity).
     * @param vec The vector to rotate, expressed in the input frame.
     * @return A new vector that is the result of rotating the input vector by this quaternion, expressed in the output frame.
     */
    template <typename Value_T>
    CartesianVector<Value_T, Out_Frame_T> rotate_vector(const CartesianVector<Value_T, In_Frame_T>& vec) const
    {
        // Rotate the vector using the quaternion: v' = q * v * q^-1
        // results in a quaternion with vector part 2(u ⋅ v)u + (s2 - u ⋅ u)v + 2s(u * v)
        // This forces a frame conversion because there is no coherent way to keep the strong typing through the
        // intermediate operations and still result in a meaningful rotation. This means we can't have a nice interface
        // where users rotate by calling q * v * q.conjugate() but it's fine for now.
        return (2.0 * _u.dot(vec) * _u + (_s * _s - _u.dot(_u)) * vec + 2.0 * _s * _u.cross(vec)).template force_frame_conversion<Out_Frame_T>();
    }

    /**
     * @brief Computes the conjugate of the quaternion.
     * @return The conjugate of the quaternion.
     */
    Quaternion<Out_Frame_T, In_Frame_T> conjugate() const
    {
        return { _s, -_u.template force_frame_conversion<Out_Frame_T>() };
    }

    /**
     * @brief Computes the inverse of the quaternion.
     * @return The inverse of the quaternion.
     *
     * @throws std::runtime_error if the norm of the quaternion is zero (cannot compute inverse of a zero quaternion).
     */
    Quaternion<Out_Frame_T, In_Frame_T> inverse() const
    {
        const Unitless scale = 1.0 / norm_squared();
        return { _s * scale, -_u.template force_frame_conversion<Out_Frame_T>() * scale };
    }

    /**
     * @brief Computes the norm of the quaternion.
     * @return The norm of the quaternion as a unitless quantity.
     */
    Unitless norm() const
    {
        using namespace mp_units;
        return sqrt(norm_squared());
    }

    /**
     * @brief Computes the square of the magnitude of the quaternion (s^2 + u^2).
     * @return The square of the magnitude of the quaternion as a unitless quantity.
     */
    Unitless norm_squared() const { return _s * _s + _u.dot(_u); }

    /**
     * @brief Normalizes the quaternion to ensure it represents a valid rotation.
     */
    void normalize()
    {
        using namespace mp_units;

        const Unitless nSq = norm_squared();
        if (nSq == 0.0 * one) { throw std::runtime_error("Cannot normalize a quaternion with zero norm."); }
        else if (isnan(nSq) || isinf(nSq)) {
            throw std::runtime_error("Cannot normalize a quaternion with non-finite norm.");
        }

        // https://stackoverflow.com/questions/11667783/quaternion-and-normalization
        if (abs(1.0 * one - nSq) < 2.107342e-08 * one) { _normalize(2.0 * one / (1.0 * one + nSq)); }
        else {
            _normalize(1.0 * one / sqrt(nSq));
        }
    }

    /**
     * @brief Gets the scalar part of the quaternion.
     *
     * @return const Unitless& The scalar part of the quaternion.
     */
    const Unitless& get_scalar_part() const { return _s; }

    /**
     * @brief Gets the vector part of the quaternion as a CartesianVector.
     *
     * @return const CartesianVector<Unitless, In_Frame_T>& The vector part of the quaternion.
     */
    const CartesianVector<Unitless, In_Frame_T>& get_vector_part() const { return _u; }

    /**
     * @brief Converts the quaternion to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the quaternion, in the order [s, u_x, u_y, u_z].
     */
    std::vector<Unitless> force_to_vector() const { return { _s, _u[0], _u[1], _u[2] }; }

    /**
     * @brief Computes the dot product between this quaternion and another quaternion.
     *
     * @param other The other quaternion to compute the dot product with.
     * @return Unitless The dot product of this quaternion and the other quaternion, computed as s1*s2 + u1 ⋅ u2.
     */
    Unitless dot(const Quaternion<In_Frame_T, Out_Frame_T>& other) const { return _s * other._s + _u.dot(other._u); }

    /**
     * @brief Interpolates between this quaternion and another quaternion at a target time using SLERP.
     *
     * @param thisTime The time corresponding to this quaternion.
     * @param otherTime The time corresponding to the other quaternion.
     * @param other The other quaternion to interpolate with.
     * @param targetTime The time at which to interpolate the quaternion.
     * @return Quaternion<In_Frame_T, Out_Frame_T> A new
     * Quaternion that is the interpolation of this quaternion and the other at the target time.
     *
     * @note: https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
     */
    Quaternion<In_Frame_T, Out_Frame_T>
        interpolate(const Time& thisTime, const Time& otherTime, const Quaternion<In_Frame_T, Out_Frame_T>& other, const Time& targetTime) const
    {
        using namespace mp_units;
        using namespace mp_units::angular;
        using mp_units::angular::unit_symbols::rad;

        // Calculate angle between them.
        const Unitless cosHalfTheta = this->dot(other);

        // Return one if quaternions are the same
        if (abs(cosHalfTheta) >= 1.0 * one) { return *this; }

        // Catch inversions
        const auto qOther = (cosHalfTheta < 0.0 * one) ? -other : other;

        // Calculate temporary values.
        const Angle halfTheta       = acos(cosHalfTheta);
        const Unitless sinHalfTheta = sqrt(1.0 * one - cosHalfTheta * cosHalfTheta);

        // if theta = 180 degrees { result is not fully defined
        // we could rotate around any axis normal to either
        if (abs(sinHalfTheta) < 1.0e-3 * one) {
            // Do the math manually to avoid normalization until construction
            return { 0.5 * (_s + qOther._s),
                     0.5 * (_u[0] + qOther._u[0]),
                     0.5 * (_u[1] + qOther._u[1]),
                     0.5 * (_u[2] + qOther._u[2]) };
        }

        // calculate quaternion
        const Unitless tRatio = (targetTime - thisTime) / (otherTime - thisTime);
        const Unitless ratioA = sin((1.0 * one - tRatio) * halfTheta) / sinHalfTheta;
        const Unitless ratioB = sin(tRatio * halfTheta) / sinHalfTheta;

        return { _s * ratioA + qOther._s * ratioB,
                 _u[0] * ratioA + qOther._u[0] * ratioB,
                 _u[1] * ratioA + qOther._u[1] * ratioB,
                 _u[2] * ratioA + qOther._u[2] * ratioB };
    }

  private:
    Unitless _s;                              //!< Scalar part of the quaternion
    CartesianVector<Unitless, In_Frame_T> _u; //!< Vector part of the quaternion

    /**
     * @brief Normalizes the quaternion by scaling its components with the given factor.
     *
     * @param scale The factor to scale the quaternion components by to achieve normalization.
     */
    void _normalize(const Unitless& scale)
    {
        _s *= scale;
        _u[0] *= scale;
        _u[1] *= scale;
        _u[2] *= scale;
    }

    /**
     * @brief Constructs a Quaternion from a vector of Unitless quantities representing the quaternion components.
     *
     * @param vec A std::vector of Unitless quantities representing the components of the quaternion, in the order [s, u_x, u_y, u_z].
     * @return A new Quaternion constructed from the given vector.
     *
     * @throws std::invalid_argument if the input vector does not have exactly 4 components.
     */
    static Quaternion<In_Frame_T, Out_Frame_T> from_vector(const std::vector<Unitless>& vec)
    {
        if (vec.size() != 4) {
            throw std::invalid_argument("Input vector must have exactly 4 components to convert to a Quaternion.");
        }
        return { vec[0], vec[1], vec[2], vec[3] };
    }
};

/**
 * @brief Class representing the partial derivative of a quaternion with respect to time, used for integration.
 *
 * @tparam In_Frame_T The input frame type (e.g., ECI, ECEF).
 * @tparam Out_Frame_T The output frame type (e.g., ECI, ECEF).
 */
template <typename In_Frame_T, typename Out_Frame_T>
class QuaternionPartial {

    friend class AttitudePartial;

  public:
    /**
     * @brief Default constructor for the QuaternionPartial class. Initializes to zero rates of change.
     */
    QuaternionPartial() = default;

    /**
     * @brief Constructor for the QuaternionPartial class from a scalar and a CartesianVector.
     *
     * @param sDot The scalar part of the quaternion derivative.
     * @param uDot The vector part of the quaternion derivative, representing the rate of change of the vector part of the quaternion.
     */
    QuaternionPartial(const UnitlessPerTime& sDot, const CartesianVector<UnitlessPerTime, In_Frame_T>& uDot) :
        _sDot(sDot),
        _uDot(uDot)
    {
    }

    /**
     * @brief Gets the scalar part of the quaternion.
     *
     * @return const UnitlessPerTime& The scalar part of the quaternion.
     */
    const UnitlessPerTime& get_scalar_part() const { return _sDot; }

    /**
     * @brief Gets the vector part of the quaternion as a CartesianVector.
     *
     * @return const CartesianVector<UnitlessPerTime, In_Frame_T>& The vector part of the quaternion.
     */
    const CartesianVector<UnitlessPerTime, In_Frame_T>& get_vector_part() const { return _uDot; }

    /**
     * @brief Multiplies the quaternion derivative by a time quantity to get a quaternion representing the change in attitude over that time interval.
     *
     * @param dt The time quantity to multiply the quaternion derivative by, representing the time interval over which to apply the change in attitude.
     * @return A new Quaternion that represents the change in attitude over the given time interval.
     */
    Quaternion<In_Frame_T, Out_Frame_T> operator*(const Time& dt) const
    {
        return Quaternion<In_Frame_T, Out_Frame_T>{ _sDot * dt, _uDot * dt };
    }

    /**
     * @brief Converts the quaternion derivative to a vector form for use in numerical integration.
     *
     * @return A std::vector of Unitless quantities representing the components of the quaternion derivative, in the order [sDot, uDot_x, uDot_y, uDot_z].
     */
    std::vector<Unitless> force_to_vector() const
    {
        return { _sDot / _sDot.unit, _uDot[0] / _uDot[0].unit, _uDot[1] / _uDot[1].unit, _uDot[2] / _uDot[2].unit };
    }

  private:
    UnitlessPerTime _sDot;                              //!< Scalar part of the quaternion derivative
    CartesianVector<UnitlessPerTime, In_Frame_T> _uDot; //!< Vector part of the quaternion derivative with no frame association
};

/**
 * @brief Stream insertion operator for the Quaternion class, allowing for easy printing of quaternion components.
 *
 * @tparam In_Frame_T The input frame type of the quaternion.
 * @tparam Out_Frame_T The output frame type of the quaternion.
 * @param os The output stream to insert the quaternion into.
 * @param quaternion The quaternion to be inserted into the stream.
 * @return A reference to the output stream after inserting the quaternion.
 */
template <typename In_Frame_T, typename Out_Frame_T>
std::ostream& operator<<(std::ostream& os, const Quaternion<In_Frame_T, Out_Frame_T>& quaternion)
{
    const auto& s = quaternion.get_scalar_part();
    const auto& u = quaternion.get_vector_part();
    os << "[" << s << " | " << u[0] << " , " << u[1] << " , " << u[2] << "]";
    return os;
}

/**
 * @brief Stream insertion operator for the QuaternionPartial class, allowing for easy printing of quaternion derivative components.
 *
 * @tparam In_Frame_T The input frame type of the quaternion derivative.
 * @tparam Out_Frame_T The output frame type of the quaternion derivative.
 * @param os The output stream to insert the quaternion derivative into.
 * @param quaternion The quaternion derivative to be inserted into the stream.
 * @return A reference to the output stream after inserting the quaternion derivative.
 */
template <typename In_Frame_T, typename Out_Frame_T>
std::ostream& operator<<(std::ostream& os, const QuaternionPartial<In_Frame_T, Out_Frame_T>& quaternion)
{
    const auto& sDot = quaternion.get_scalar_part();
    const auto& uDot = quaternion.get_vector_part();
    os << "[" << sDot << " | " << uDot[0] << " , " << uDot[1] << " , " << uDot[2] << "]";
    return os;
}

} // namespace astro
} // namespace astrea

// C++ circular-include bullshit. Can we please just use modules?
#include <astro/state/attitude/instances/EulerAngles.ipp>