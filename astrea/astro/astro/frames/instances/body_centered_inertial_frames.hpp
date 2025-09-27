/**
 * @file EarthCentered.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Header file for the EarthCentered struct in the astro namespace
 * @version 0.1
 * @date 2025-08-05
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/types/InertialFrame.hpp>

namespace astrea {
namespace astro {
namespace frames {

// Planetary Bodies
struct SunCenteredIcrf final : InertialFrame<SunCenteredIcrf, CelestialBodyId::SUN, FrameAxis::ICRF> {};
struct MercuryCenteredIcrf final : InertialFrame<MercuryCenteredIcrf, CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusCenteredIcrf final : InertialFrame<VenusCenteredIcrf, CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthCenteredIcrf final : InertialFrame<EarthCenteredIcrf, CelestialBodyId::EARTH, FrameAxis::ICRF> {};
struct MoonCenteredIcrf final : InertialFrame<MoonCenteredIcrf, CelestialBodyId::MOON, FrameAxis::ICRF> {};
struct MarsCenteredIcrf final : InertialFrame<MarsCenteredIcrf, CelestialBodyId::MARS, FrameAxis::ICRF> {};
struct PhobosCenteredIcrf final : InertialFrame<PhobosCenteredIcrf, CelestialBodyId::PHOBOS, FrameAxis::ICRF> {};
struct DeimosCenteredIcrf final : InertialFrame<DeimosCenteredIcrf, CelestialBodyId::DEIMOS, FrameAxis::ICRF> {};
struct JupiterCenteredIcrf final : InertialFrame<JupiterCenteredIcrf, CelestialBodyId::JUPITER, FrameAxis::ICRF> {};
struct GanymedeCenteredIcrf final : InertialFrame<GanymedeCenteredIcrf, CelestialBodyId::GANYMEDE, FrameAxis::ICRF> {};
struct CallistoCenteredIcrf final : InertialFrame<CallistoCenteredIcrf, CelestialBodyId::CALLISTO, FrameAxis::ICRF> {};
struct IoCenteredIcrf final : InertialFrame<IoCenteredIcrf, CelestialBodyId::IO, FrameAxis::ICRF> {};
struct EuropaCenteredIcrf final : InertialFrame<EuropaCenteredIcrf, CelestialBodyId::EUROPA, FrameAxis::ICRF> {};
struct SaturnCenteredIcrf final : InertialFrame<SaturnCenteredIcrf, CelestialBodyId::SATURN, FrameAxis::ICRF> {};
struct TitanCenteredIcrf final : InertialFrame<TitanCenteredIcrf, CelestialBodyId::TITAN, FrameAxis::ICRF> {};
struct RheaCenteredIcrf final : InertialFrame<RheaCenteredIcrf, CelestialBodyId::RHEA, FrameAxis::ICRF> {};
struct IapetusCenteredIcrf final : InertialFrame<IapetusCenteredIcrf, CelestialBodyId::IAPETUS, FrameAxis::ICRF> {};
struct UranusCenteredIcrf final : InertialFrame<UranusCenteredIcrf, CelestialBodyId::URANUS, FrameAxis::ICRF> {};
struct TitaniaCenteredIcrf final : InertialFrame<TitaniaCenteredIcrf, CelestialBodyId::TITANIA, FrameAxis::ICRF> {};
struct OberonCenteredIcrf final : InertialFrame<OberonCenteredIcrf, CelestialBodyId::OBERON, FrameAxis::ICRF> {};
struct NeptuneCenteredIcrf final : InertialFrame<NeptuneCenteredIcrf, CelestialBodyId::NEPTUNE, FrameAxis::ICRF> {};
struct TritonCenteredIcrf final : InertialFrame<TritonCenteredIcrf, CelestialBodyId::TRITON, FrameAxis::ICRF> {};

struct SunCenteredJ2000 final : InertialFrame<SunCenteredJ2000, CelestialBodyId::SUN, FrameAxis::J2000> {};
struct MercuryCenteredJ2000 final : InertialFrame<MercuryCenteredJ2000, CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusCenteredJ2000 final : InertialFrame<VenusCenteredJ2000, CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthCenteredJ2000 final : InertialFrame<EarthCenteredJ2000, CelestialBodyId::EARTH, FrameAxis::J2000> {};
struct MoonCenteredJ2000 final : InertialFrame<MoonCenteredJ2000, CelestialBodyId::MOON, FrameAxis::J2000> {};
struct MarsCenteredJ2000 final : InertialFrame<MarsCenteredJ2000, CelestialBodyId::MARS, FrameAxis::J2000> {};
struct PhobosCenteredJ2000 final : InertialFrame<PhobosCenteredJ2000, CelestialBodyId::PHOBOS, FrameAxis::J2000> {};
struct DeimosCenteredJ2000 final : InertialFrame<DeimosCenteredJ2000, CelestialBodyId::DEIMOS, FrameAxis::J2000> {};
struct JupiterCenteredJ2000 final : InertialFrame<JupiterCenteredJ2000, CelestialBodyId::JUPITER, FrameAxis::J2000> {};
struct GanymedeCenteredJ2000 final : InertialFrame<GanymedeCenteredJ2000, CelestialBodyId::GANYMEDE, FrameAxis::J2000> {};
struct CallistoCenteredJ2000 final : InertialFrame<CallistoCenteredJ2000, CelestialBodyId::CALLISTO, FrameAxis::J2000> {};
struct IoCenteredJ2000 final : InertialFrame<IoCenteredJ2000, CelestialBodyId::IO, FrameAxis::J2000> {};
struct EuropaCenteredJ2000 final : InertialFrame<EuropaCenteredJ2000, CelestialBodyId::EUROPA, FrameAxis::J2000> {};
struct SaturnCenteredJ2000 final : InertialFrame<SaturnCenteredJ2000, CelestialBodyId::SATURN, FrameAxis::J2000> {};
struct TitanCenteredJ2000 final : InertialFrame<TitanCenteredJ2000, CelestialBodyId::TITAN, FrameAxis::J2000> {};
struct RheaCenteredJ2000 final : InertialFrame<RheaCenteredJ2000, CelestialBodyId::RHEA, FrameAxis::J2000> {};
struct IapetusCenteredJ2000 final : InertialFrame<IapetusCenteredJ2000, CelestialBodyId::IAPETUS, FrameAxis::J2000> {};
struct UranusCenteredJ2000 final : InertialFrame<UranusCenteredJ2000, CelestialBodyId::URANUS, FrameAxis::J2000> {};
struct TitaniaCenteredJ2000 final : InertialFrame<TitaniaCenteredJ2000, CelestialBodyId::TITANIA, FrameAxis::J2000> {};
struct OberonCenteredJ2000 final : InertialFrame<OberonCenteredJ2000, CelestialBodyId::OBERON, FrameAxis::J2000> {};
struct NeptuneCenteredJ2000 final : InertialFrame<NeptuneCenteredJ2000, CelestialBodyId::NEPTUNE, FrameAxis::J2000> {};
struct TritonCenteredJ2000 final : InertialFrame<TritonCenteredJ2000, CelestialBodyId::TRITON, FrameAxis::J2000> {};

// Barycenteral
struct SolarSystemBarycenterIcrf final
    : InertialFrame<SolarSystemBarycenterIcrf, CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF> {};
struct MercuryBarycenterIcrf final : InertialFrame<MercuryBarycenterIcrf, CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusBarycenterIcrf final : InertialFrame<VenusBarycenterIcrf, CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthBarycenterIcrf final : InertialFrame<EarthBarycenterIcrf, CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF> {};
struct MarsBarycenterIcrf final : InertialFrame<MarsBarycenterIcrf, CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF> {};
struct JupiterBarycenterIcrf final
    : InertialFrame<JupiterBarycenterIcrf, CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF> {};
struct SaturnBarycenterIcrf final : InertialFrame<SaturnBarycenterIcrf, CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF> {};
struct UranusBarycenterIcrf final : InertialFrame<UranusBarycenterIcrf, CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF> {};
struct NeptuneBarycenterIcrf final
    : InertialFrame<NeptuneBarycenterIcrf, CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF> {};

struct SolarSystemBarycenterJ2000 final
    : InertialFrame<SolarSystemBarycenterJ2000, CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000> {};
struct MercuryBarycenterJ2000 final : InertialFrame<MercuryBarycenterJ2000, CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusBarycenterJ2000 final : InertialFrame<VenusBarycenterJ2000, CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthBarycenterJ2000 final : InertialFrame<EarthBarycenterJ2000, CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000> {};
struct MarsBarycenterJ2000 final : InertialFrame<MarsBarycenterJ2000, CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000> {};
struct JupiterBarycenterJ2000 final
    : InertialFrame<JupiterBarycenterJ2000, CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000> {};
struct SaturnBarycenterJ2000 final : InertialFrame<SaturnBarycenterJ2000, CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000> {
};
struct UranusBarycenterJ2000 final : InertialFrame<UranusBarycenterJ2000, CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000> {
};
struct NeptuneBarycenterJ2000 final
    : InertialFrame<NeptuneBarycenterJ2000, CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000> {};

} // namespace frames
} // namespace astro
} // namespace astrea