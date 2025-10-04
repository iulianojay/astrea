/**
 * @file typedefs.hpp
 * @author Jay Iuliano (iuliano.jay@gmail.com)
 * @brief Definitions and shorthand for frames.
 * @version 0.1
 * @date 2025-10-02
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <astro/frames/instances.fwd.hpp>

namespace astrea {
namespace astro {
namespace frames {

namespace dynamic {
using lvlh      = LocalHorizontalLocalVertical;
using ric       = RadialInTrackCrossTrack;
using vnb       = VelocityNormalBinormal;
using perifocal = Perifocal;
} // namespace dynamic

namespace sun {
using icrf      = SunCenteredIcrf;
using j2000     = SunCenteredJ2000;
using sun_fixed = SunCenteredSunFixed;
} // namespace sun

namespace mercury {
using icrf          = MercuryCenteredIcrf;
using j2000         = MercuryCenteredJ2000;
using mercury_fixed = MercuryCenteredMercuryFixed;
} // namespace mercury

namespace venus {
using icrf        = VenusCenteredIcrf;
using j2000       = VenusCenteredJ2000;
using venus_fixed = VenusCenteredVenusFixed;
} // namespace venus

namespace earth {
using icrf        = EarthCenteredIcrf;  // GCRF frame, sometimes ECI
using j2000       = EarthCenteredJ2000; // EME2000 frame, sometimes ECI
using earth_fixed = EarthCenteredEarthFixed;
} // namespace earth

namespace moon {
using icrf       = MoonCenteredIcrf;
using j2000      = MoonCenteredJ2000;
using moon_fixed = MoonCenteredMoonFixed;
} // namespace moon

namespace mars {
using icrf       = MarsCenteredIcrf;
using j2000      = MarsCenteredJ2000;
using mars_fixed = MarsCenteredMarsFixed;
} // namespace mars

namespace phobos {
using icrf         = PhobosCenteredIcrf;
using j2000        = PhobosCenteredJ2000;
using phobos_fixed = PhobosCenteredPhobosFixed;
} // namespace phobos

namespace deimos {
using icrf         = DeimosCenteredIcrf;
using j2000        = DeimosCenteredJ2000;
using deimos_fixed = DeimosCenteredDeimosFixed;
} // namespace deimos

namespace jupiter {
using icrf          = JupiterCenteredIcrf;
using j2000         = JupiterCenteredJ2000;
using jupiter_fixed = JupiterCenteredJupiterFixed;
} // namespace jupiter

namespace ganymede {
using icrf           = GanymedeCenteredIcrf;
using j2000          = GanymedeCenteredJ2000;
using ganymede_fixed = GanymedeCenteredGanymedeFixed;
} // namespace ganymede

namespace callisto {
using icrf           = CallistoCenteredIcrf;
using j2000          = CallistoCenteredJ2000;
using callisto_fixed = CallistoCenteredCallistoFixed;
} // namespace callisto

namespace io {
using icrf     = IoCenteredIcrf;
using j2000    = IoCenteredJ2000;
using io_fixed = IoCenteredIoFixed;
} // namespace io

namespace europa {
using icrf         = EuropaCenteredIcrf;
using j2000        = EuropaCenteredJ2000;
using europa_fixed = EuropaCenteredEuropaFixed;
} // namespace europa

namespace saturn {
using icrf         = SaturnCenteredIcrf;
using j2000        = SaturnCenteredJ2000;
using saturn_fixed = SaturnCenteredSaturnFixed;
} // namespace saturn

namespace titan {
using icrf        = TitanCenteredIcrf;
using j2000       = TitanCenteredJ2000;
using titan_fixed = TitanCenteredTitanFixed;
} // namespace titan

namespace rhea {
using icrf       = RheaCenteredIcrf;
using j2000      = RheaCenteredJ2000;
using rhea_fixed = RheaCenteredRheaFixed;
} // namespace rhea

namespace iapetus {
using icrf          = IapetusCenteredIcrf;
using j2000         = IapetusCenteredJ2000;
using iapetus_fixed = IapetusCenteredIapetusFixed;
} // namespace iapetus

namespace uranus {
using icrf         = UranusCenteredIcrf;
using j2000        = UranusCenteredJ2000;
using uranus_fixed = UranusCenteredUranusFixed;
} // namespace uranus

namespace titania {
using icrf          = TitaniaCenteredIcrf;
using j2000         = TitaniaCenteredJ2000;
using titania_fixed = TitaniaCenteredTitaniaFixed;
} // namespace titania

namespace oberon {
using icrf         = OberonCenteredIcrf;
using j2000        = OberonCenteredJ2000;
using oberon_fixed = OberonCenteredOberonFixed;
} // namespace oberon

namespace neptune {
using icrf          = NeptuneCenteredIcrf;
using j2000         = NeptuneCenteredJ2000;
using neptune_fixed = NeptuneCenteredNeptuneFixed;
} // namespace neptune

namespace triton {
using icrf         = TritonCenteredIcrf;
using j2000        = TritonCenteredJ2000;
using triton_fixed = TritonCenteredTritonFixed;
} // namespace triton

namespace solar_system_barycenter {
using icrf  = SolarSystemBarycenterIcrf; // Generally, the ICRF frame
using j2000 = SolarSystemBarycenterJ2000;
} // namespace solar_system_barycenter

namespace mercury_barycenter {
using icrf  = MercuryBarycenterIcrf;
using j2000 = MercuryBarycenterJ2000;
} // namespace mercury_barycenter

namespace venus_barycenter {
using icrf  = VenusBarycenterIcrf;
using j2000 = VenusBarycenterJ2000;
} // namespace venus_barycenter

namespace earth_barycenter {
using icrf  = EarthBarycenterIcrf;
using j2000 = EarthBarycenterJ2000;
} // namespace earth_barycenter

namespace mars_barycenter {
using icrf  = MarsBarycenterIcrf;
using j2000 = MarsBarycenterJ2000;
} // namespace mars_barycenter

namespace jupiter_barycenter {
using icrf  = JupiterBarycenterIcrf;
using j2000 = JupiterBarycenterJ2000;
} // namespace jupiter_barycenter

namespace saturn_barycenter {
using icrf  = SaturnBarycenterIcrf;
using j2000 = SaturnBarycenterJ2000;
} // namespace saturn_barycenter

namespace uranus_barycenter {
using icrf  = UranusBarycenterIcrf;
using j2000 = UranusBarycenterJ2000;
} // namespace uranus_barycenter

namespace neptune_barycenter {
using icrf  = NeptuneBarycenterIcrf;
using j2000 = NeptuneBarycenterJ2000;
} // namespace neptune_barycenter

} // namespace frames
} // namespace astro
} // namespace astrea