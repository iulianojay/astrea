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

#include <astro/state/frames/Frame.hpp>

namespace astrea {
namespace astro {
namespace frames {

// Planetary Bodies
struct SunCenteredIcrf final : Frame<SunCenteredIcrf, CelestialBodyId::SUN, FrameAxis::ICRF> {};
struct MercuryCenteredIcrf final : Frame<MercuryCenteredIcrf, CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusCenteredIcrf final : Frame<VenusCenteredIcrf, CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthCenteredIcrf final : Frame<EarthCenteredIcrf, CelestialBodyId::EARTH, FrameAxis::ICRF> {};
struct MoonCenteredIcrf final : Frame<MoonCenteredIcrf, CelestialBodyId::MOON, FrameAxis::ICRF> {};
struct MarsCenteredIcrf final : Frame<MarsCenteredIcrf, CelestialBodyId::MARS, FrameAxis::ICRF> {};
struct PhobosCenteredIcrf final : Frame<PhobosCenteredIcrf, CelestialBodyId::PHOBOS, FrameAxis::ICRF> {};
struct DeimosCenteredIcrf final : Frame<DeimosCenteredIcrf, CelestialBodyId::DEIMOS, FrameAxis::ICRF> {};
struct JupiterCenteredIcrf final : Frame<JupiterCenteredIcrf, CelestialBodyId::JUPITER, FrameAxis::ICRF> {};
struct GanymedeCenteredIcrf final : Frame<GanymedeCenteredIcrf, CelestialBodyId::GANYMEDE, FrameAxis::ICRF> {};
struct CallistoCenteredIcrf final : Frame<CallistoCenteredIcrf, CelestialBodyId::CALLISTO, FrameAxis::ICRF> {};
struct IoCenteredIcrf final : Frame<IoCenteredIcrf, CelestialBodyId::IO, FrameAxis::ICRF> {};
struct EuropaCenteredIcrf final : Frame<EuropaCenteredIcrf, CelestialBodyId::EUROPA, FrameAxis::ICRF> {};
struct SaturnCenteredIcrf final : Frame<SaturnCenteredIcrf, CelestialBodyId::SATURN, FrameAxis::ICRF> {};
struct TitanCenteredIcrf final : Frame<TitanCenteredIcrf, CelestialBodyId::TITAN, FrameAxis::ICRF> {};
struct RheaCenteredIcrf final : Frame<RheaCenteredIcrf, CelestialBodyId::RHEA, FrameAxis::ICRF> {};
struct IapetusCenteredIcrf final : Frame<IapetusCenteredIcrf, CelestialBodyId::IAPETUS, FrameAxis::ICRF> {};
struct UranusCenteredIcrf final : Frame<UranusCenteredIcrf, CelestialBodyId::URANUS, FrameAxis::ICRF> {};
struct TitaniaCenteredIcrf final : Frame<TitaniaCenteredIcrf, CelestialBodyId::TITANIA, FrameAxis::ICRF> {};
struct OberonCenteredIcrf final : Frame<OberonCenteredIcrf, CelestialBodyId::OBERON, FrameAxis::ICRF> {};
struct NeptuneCenteredIcrf final : Frame<NeptuneCenteredIcrf, CelestialBodyId::NEPTUNE, FrameAxis::ICRF> {};
struct TritonCenteredIcrf final : Frame<TritonCenteredIcrf, CelestialBodyId::TRITON, FrameAxis::ICRF> {};

struct SunCenteredJ2000 final : Frame<SunCenteredJ2000, CelestialBodyId::SUN, FrameAxis::J2000> {};
struct MercuryCenteredJ2000 final : Frame<MercuryCenteredJ2000, CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusCenteredJ2000 final : Frame<VenusCenteredJ2000, CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthCenteredJ2000 final : Frame<EarthCenteredJ2000, CelestialBodyId::EARTH, FrameAxis::J2000> {};
struct MoonCenteredJ2000 final : Frame<MoonCenteredJ2000, CelestialBodyId::MOON, FrameAxis::J2000> {};
struct MarsCenteredJ2000 final : Frame<MarsCenteredJ2000, CelestialBodyId::MARS, FrameAxis::J2000> {};
struct PhobosCenteredJ2000 final : Frame<PhobosCenteredJ2000, CelestialBodyId::PHOBOS, FrameAxis::J2000> {};
struct DeimosCenteredJ2000 final : Frame<DeimosCenteredJ2000, CelestialBodyId::DEIMOS, FrameAxis::J2000> {};
struct JupiterCenteredJ2000 final : Frame<JupiterCenteredJ2000, CelestialBodyId::JUPITER, FrameAxis::J2000> {};
struct GanymedeCenteredJ2000 final : Frame<GanymedeCenteredJ2000, CelestialBodyId::GANYMEDE, FrameAxis::J2000> {};
struct CallistoCenteredJ2000 final : Frame<CallistoCenteredJ2000, CelestialBodyId::CALLISTO, FrameAxis::J2000> {};
struct IoCenteredJ2000 final : Frame<IoCenteredJ2000, CelestialBodyId::IO, FrameAxis::J2000> {};
struct EuropaCenteredJ2000 final : Frame<EuropaCenteredJ2000, CelestialBodyId::EUROPA, FrameAxis::J2000> {};
struct SaturnCenteredJ2000 final : Frame<SaturnCenteredJ2000, CelestialBodyId::SATURN, FrameAxis::J2000> {};
struct TitanCenteredJ2000 final : Frame<TitanCenteredJ2000, CelestialBodyId::TITAN, FrameAxis::J2000> {};
struct RheaCenteredJ2000 final : Frame<RheaCenteredJ2000, CelestialBodyId::RHEA, FrameAxis::J2000> {};
struct IapetusCenteredJ2000 final : Frame<IapetusCenteredJ2000, CelestialBodyId::IAPETUS, FrameAxis::J2000> {};
struct UranusCenteredJ2000 final : Frame<UranusCenteredJ2000, CelestialBodyId::URANUS, FrameAxis::J2000> {};
struct TitaniaCenteredJ2000 final : Frame<TitaniaCenteredJ2000, CelestialBodyId::TITANIA, FrameAxis::J2000> {};
struct OberonCenteredJ2000 final : Frame<OberonCenteredJ2000, CelestialBodyId::OBERON, FrameAxis::J2000> {};
struct NeptuneCenteredJ2000 final : Frame<NeptuneCenteredJ2000, CelestialBodyId::NEPTUNE, FrameAxis::J2000> {};
struct TritonCenteredJ2000 final : Frame<TritonCenteredJ2000, CelestialBodyId::TRITON, FrameAxis::J2000> {};

// Barycenteral
struct SolarSystemBarycenterIcrf final
    : Frame<SolarSystemBarycenterIcrf, CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::ICRF> {};
struct MercuryBarycenterIcrf final : Frame<MercuryBarycenterIcrf, CelestialBodyId::MERCURY, FrameAxis::ICRF> {};
struct VenusBarycenterIcrf final : Frame<VenusBarycenterIcrf, CelestialBodyId::VENUS, FrameAxis::ICRF> {};
struct EarthBarycenterIcrf final : Frame<EarthBarycenterIcrf, CelestialBodyId::EARTH_BARYCENTER, FrameAxis::ICRF> {};
struct MarsBarycenterIcrf final : Frame<MarsBarycenterIcrf, CelestialBodyId::MARS_BARYCENTER, FrameAxis::ICRF> {};
struct JupiterBarycenterIcrf final : Frame<JupiterBarycenterIcrf, CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::ICRF> {};
struct SaturnBarycenterIcrf final : Frame<SaturnBarycenterIcrf, CelestialBodyId::SATURN_BARYCENTER, FrameAxis::ICRF> {};
struct UranusBarycenterIcrf final : Frame<UranusBarycenterIcrf, CelestialBodyId::URANUS_BARYCENTER, FrameAxis::ICRF> {};
struct NeptuneBarycenterIcrf final : Frame<NeptuneBarycenterIcrf, CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::ICRF> {};

struct SolarSystemBarycenterJ2000 final
    : Frame<SolarSystemBarycenterJ2000, CelestialBodyId::SOLAR_SYSTEM_BARYCENTER, FrameAxis::J2000> {};
struct MercuryBarycenterJ2000 final : Frame<MercuryBarycenterJ2000, CelestialBodyId::MERCURY, FrameAxis::J2000> {};
struct VenusBarycenterJ2000 final : Frame<VenusBarycenterJ2000, CelestialBodyId::VENUS, FrameAxis::J2000> {};
struct EarthBarycenterJ2000 final : Frame<EarthBarycenterJ2000, CelestialBodyId::EARTH_BARYCENTER, FrameAxis::J2000> {};
struct MarsBarycenterJ2000 final : Frame<MarsBarycenterJ2000, CelestialBodyId::MARS_BARYCENTER, FrameAxis::J2000> {};
struct JupiterBarycenterJ2000 final : Frame<JupiterBarycenterJ2000, CelestialBodyId::JUPITER_BARYCENTER, FrameAxis::J2000> {};
struct SaturnBarycenterJ2000 final : Frame<SaturnBarycenterJ2000, CelestialBodyId::SATURN_BARYCENTER, FrameAxis::J2000> {};
struct UranusBarycenterJ2000 final : Frame<UranusBarycenterJ2000, CelestialBodyId::URANUS_BARYCENTER, FrameAxis::J2000> {};
struct NeptuneBarycenterJ2000 final : Frame<NeptuneBarycenterJ2000, CelestialBodyId::NEPTUNE_BARYCENTER, FrameAxis::J2000> {};

} // namespace frames
} // namespace astro
} // namespace astrea