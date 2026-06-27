

# File TraceConfig.hpp

[**File List**](files.md) **>** [**analysis**](dir_46c4498db40ce3dbd9ced60b5dc27dd1.md) **>** [**TraceConfig.hpp**](TraceConfig_8hpp.md)

[Go to the documentation of this file](TraceConfig_8hpp.md)


```C++

#pragma once

#include <string>

#include <mp-units/systems/angular.h>
#include <mp-units/systems/si.h>
#include <nlohmann/json.hpp>

#include <astro/astro.hpp>
#include <units/units.hpp>

#include <trace/types/typedefs.hpp>

namespace astrea {
namespace trace {

struct AnalysisSettings {
    Time simTime;      
    Time resolution;   
    astro::Date epoch; 

    AnalysisSettings() = default;

    AnalysisSettings(const nlohmann::json& json)
    {
        using mp_units::non_si::day;
        using mp_units::si::unit_symbols::min;

        simTime    = json.at("sim_time_days").get<double>() * day;
        resolution = json.at("resolution_min").get<double>() * min;
        epoch      = astro::Date(json.at("epoch").get<std::string>());
    }
};

struct ConstellationSettings {
    Distance altitude;       
    Angle inclination;       
    std::size_t nSats;       
    std::size_t nPlanes;     
    Unitless phasing;        
    Angle anchorRaan;        
    Angle anchorTrueAnomaly; 

    ConstellationSettings() = default;

    ConstellationSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;
        using mp_units::si::unit_symbols::km;

        altitude          = json.at("altitude_km").get<double>() * km;
        inclination       = json.at("inclination_deg").get<double>() * deg;
        nSats             = json.at("n_sats").get<std::size_t>();
        nPlanes           = json.at("n_planes").get<std::size_t>();
        phasing           = json.at("phasing").get<double>() * one;
        anchorRaan        = json.at("anchor_raan_deg").get<double>() * deg;
        anchorTrueAnomaly = json.at("anchor_true_anomaly_deg").get<double>() * deg;
    }
};

struct SensorSettings {
    std::string name;                                        
    std::string type;                                        
    Angle halfConeAngle;                                     
    astro::Direction<astro::frames::dynamic::ric> boresight; 

    SensorSettings() = default;

    SensorSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;

        name          = json.at("name").get<std::string>();
        type          = json.at("fov").at("type").get<std::string>();
        halfConeAngle = json.at("fov").at("half_cone_angle_deg").get<double>() * deg;
        if (json.contains("boresight")) {
            const auto& boresightArray = json.at("boresight");
            if (boresightArray.is_array() && boresightArray.size() == 3) {
                boresight = astro::Direction<astro::frames::dynamic::ric>{ boresightArray[0].get<double>() * one,
                                                                           boresightArray[1].get<double>() * one,
                                                                           boresightArray[2].get<double>() * one };
            }
            else {
                throw std::runtime_error("Boresight must be an array of 3 elements.");
            }
        }
    }
};

struct GridSettings {
    std::string type;  
    Angle spacing;     
    LatRange latRange; 
    LonRange lonRange; 

    GridSettings() = default;

    GridSettings(const nlohmann::json& json)
    {
        using namespace mp_units;
        using mp_units::angular::unit_symbols::deg;

        type    = json.at("type").get<std::string>();
        spacing = json.at("spacing_deg").get<double>() * deg;
        if (json.contains("lat_range_deg") && json.at("lat_range_deg").is_array() && json.at("lat_range_deg").size() == 2) {
            latRange = LatRange{ json.at("lat_range_deg")[0].get<double>() * deg, json.at("lat_range_deg")[1].get<double>() * deg };
        }
        if (json.contains("lon_range_deg") && json.at("lon_range_deg").is_array() && json.at("lon_range_deg").size() == 2) {
            lonRange = LonRange{ json.at("lon_range_deg")[0].get<double>() * deg, json.at("lon_range_deg")[1].get<double>() * deg };
        }
    }
};

struct GroundSettings {
    GridSettings gridSettings; 

    GroundSettings() = default;

    GroundSettings(const nlohmann::json& json) { gridSettings = GridSettings(json.at("grids")[0]); }
};

struct OutputSettings {
    std::string outdir; 
    std::string dbName; 
    bool printProgress; 
    bool runPlotter;    
    bool saveResults;   

    OutputSettings() = default;

    OutputSettings(const nlohmann::json& json)
    {
        outdir        = json.at("outdir").get<std::string>();
        dbName        = json.at("db_name").get<std::string>();
        printProgress = json.at("print_progress").get<bool>();
        runPlotter    = json.at("run_plotter").get<bool>();
        saveResults   = json.at("save_results").get<bool>();
    }
};

struct TraceConfig {
    AnalysisSettings analysisSettings;
    ConstellationSettings constellationSettings;
    SensorSettings sensorSettings;
    GroundSettings groundSettings;
    OutputSettings outputSettings;

    TraceConfig() = default;

    TraceConfig(const nlohmann::json& json)
    {
        analysisSettings      = AnalysisSettings(json.at("analysis"));
        constellationSettings = ConstellationSettings(json.at("constellation"));
        sensorSettings        = SensorSettings(json.at("sensors")[0]);
        groundSettings        = GroundSettings(json.at("grounds"));
        outputSettings        = OutputSettings(json.at("output"));
    }
};

} // namespace trace
} // namespace astrea
```


