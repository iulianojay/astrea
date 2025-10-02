/**
 * @file EarthCentered.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for all (most? common?) body-centered inertial frames.
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/types/DirectionCosineMatrix.hpp>
#include <astro/frames/types/InertialFrame.hpp>

namespace astrea {
namespace astro {
namespace frames {

// Planetary Bodies
struct SunCenteredIcrf final : InertialFrame<CelestialBodyId::SUN, FrameAxis::ICRF> {};
struct MercuryCenteredIcrf final : InertialFrame<CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusCenteredIcrf final : InertialFrame<CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthCenteredIcrf final : InertialFrame<CelestialBodyId::EARTH, FrameAxis::ICRF> {};
struct MoonCenteredIcrf final : InertialFrame<CelestialBodyId::MOON, FrameAxis::ICRF> {};
struct MarsCenteredIcrf final : InertialFrame<CelestialBodyId::MARS, FrameAxis::ICRF> {};
struct PhobosCenteredIcrf final : InertialFrame<CelestialBodyId::PHOBOS, FrameAxis::ICRF> {};
struct DeimosCenteredIcrf final : InertialFrame<CelestialBodyId::DEIMOS, FrameAxis::ICRF> {};
struct JupiterCenteredIcrf final : InertialFrame<CelestialBodyId::JUPITER, FrameAxis::ICRF> {};
struct GanymedeCenteredIcrf final : InertialFrame<CelestialBodyId::GANYMEDE, FrameAxis::ICRF> {};
struct CallistoCenteredIcrf final : InertialFrame<CelestialBodyId::CALLISTO, FrameAxis::ICRF> {};
struct IoCenteredIcrf final : InertialFrame<CelestialBodyId::IO, FrameAxis::ICRF> {};
struct EuropaCenteredIcrf final : InertialFrame<CelestialBodyId::EUROPA, FrameAxis::ICRF> {};
struct SaturnCenteredIcrf final : InertialFrame<CelestialBodyId::SATURN, FrameAxis::ICRF> {};
struct TitanCenteredIcrf final : InertialFrame<CelestialBodyId::TITAN, FrameAxis::ICRF> {};
struct RheaCenteredIcrf final : InertialFrame<CelestialBodyId::RHEA, FrameAxis::ICRF> {};
struct IapetusCenteredIcrf final : InertialFrame<CelestialBodyId::IAPETUS, FrameAxis::ICRF> {};
struct UranusCenteredIcrf final : InertialFrame<CelestialBodyId::URANUS, FrameAxis::ICRF> {};
struct TitaniaCenteredIcrf final : InertialFrame<CelestialBodyId::TITANIA, FrameAxis::ICRF> {};
struct OberonCenteredIcrf final : InertialFrame<CelestialBodyId::OBERON, FrameAxis::ICRF> {};
struct NeptuneCenteredIcrf final : InertialFrame<CelestialBodyId::NEPTUNE, FrameAxis::ICRF> {};
struct TritonCenteredIcrf final : InertialFrame<CelestialBodyId::TRITON, FrameAxis::ICRF> {};

struct SunCenteredJ2000 final : InertialFrame<CelestialBodyId::SUN, FrameAxis::J2000> {};
struct MercuryCenteredJ2000 final : InertialFrame<CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusCenteredJ2000 final : InertialFrame<CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthCenteredJ2000 final : InertialFrame<CelestialBodyId::EARTH, FrameAxis::J2000> {};
struct MoonCenteredJ2000 final : InertialFrame<CelestialBodyId::MOON, FrameAxis::J2000> {};
struct MarsCenteredJ2000 final : InertialFrame<CelestialBodyId::MARS, FrameAxis::J2000> {};
struct PhobosCenteredJ2000 final : InertialFrame<CelestialBodyId::PHOBOS, FrameAxis::J2000> {};
struct DeimosCenteredJ2000 final : InertialFrame<CelestialBodyId::DEIMOS, FrameAxis::J2000> {};
struct JupiterCenteredJ2000 final : InertialFrame<CelestialBodyId::JUPITER, FrameAxis::J2000> {};
struct GanymedeCenteredJ2000 final : InertialFrame<CelestialBodyId::GANYMEDE, FrameAxis::J2000> {};
struct CallistoCenteredJ2000 final : InertialFrame<CelestialBodyId::CALLISTO, FrameAxis::J2000> {};
struct IoCenteredJ2000 final : InertialFrame<CelestialBodyId::IO, FrameAxis::J2000> {};
struct EuropaCenteredJ2000 final : InertialFrame<CelestialBodyId::EUROPA, FrameAxis::J2000> {};
struct SaturnCenteredJ2000 final : InertialFrame<CelestialBodyId::SATURN, FrameAxis::J2000> {};
struct TitanCenteredJ2000 final : InertialFrame<CelestialBodyId::TITAN, FrameAxis::J2000> {};
struct RheaCenteredJ2000 final : InertialFrame<CelestialBodyId::RHEA, FrameAxis::J2000> {};
struct IapetusCenteredJ2000 final : InertialFrame<CelestialBodyId::IAPETUS, FrameAxis::J2000> {};
struct UranusCenteredJ2000 final : InertialFrame<CelestialBodyId::URANUS, FrameAxis::J2000> {};
struct TitaniaCenteredJ2000 final : InertialFrame<CelestialBodyId::TITANIA, FrameAxis::J2000> {};
struct OberonCenteredJ2000 final : InertialFrame<CelestialBodyId::OBERON, FrameAxis::J2000> {};
struct NeptuneCenteredJ2000 final : InertialFrame<CelestialBodyId::NEPTUNE, FrameAxis::J2000> {};
struct TritonCenteredJ2000 final : InertialFrame<CelestialBodyId::TRITON, FrameAxis::J2000> {};

// Barycenteral
struct SolarSystemBarycenterIcrf final : InertialFrame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF> {};
struct MercuryBarycenterIcrf final : InertialFrame<CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusBarycenterIcrf final : InertialFrame<CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthBarycenterIcrf final : InertialFrame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF> {};
struct MarsBarycenterIcrf final : InertialFrame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF> {};
struct JupiterBarycenterIcrf final : InertialFrame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF> {};
struct SaturnBarycenterIcrf final : InertialFrame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF> {};
struct UranusBarycenterIcrf final : InertialFrame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF> {};
struct NeptuneBarycenterIcrf final : InertialFrame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF> {};

struct SolarSystemBarycenterJ2000 final : InertialFrame<CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000> {};
struct MercuryBarycenterJ2000 final : InertialFrame<CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusBarycenterJ2000 final : InertialFrame<CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthBarycenterJ2000 final : InertialFrame<CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000> {};
struct MarsBarycenterJ2000 final : InertialFrame<CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000> {};
struct JupiterBarycenterJ2000 final : InertialFrame<CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000> {};
struct SaturnBarycenterJ2000 final : InertialFrame<CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000> {};
struct UranusBarycenterJ2000 final : InertialFrame<CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000> {};
struct NeptuneBarycenterJ2000 final : InertialFrame<CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000> {};

} // namespace frames


template <typename Frame_T, typename Frame_U>
    requires(Frame_T::get_axis() == FrameAxis::J2000 && Frame_U::get_axis() == FrameAxis::ICRF && HasSameOrigin<Frame_T, Frame_U>)
inline DCM<Frame_T, Frame_U> get_dcm(const Date& date)
{
    using mp_units::si::unit_symbols::deg;
    static const Angle obliquity = Angle(23.43928 * deg); // obliquity at J2000
    return DCM<Frame_T, Frame_U>::X(obliquity);
}


} // namespace astro
} // namespace astrea