

# File GeneralPerturbations.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**state**](dir_cf1a4d8122645f8636e977da512a043c.md) **>** [**orbital\_data\_formats**](dir_dce17fbadb9e43f0864b0608daddb5e0.md) **>** [**instances**](dir_8b2b76eceb189c78e8c8535df8f613d6.md) **>** [**GeneralPerturbations.hpp**](GeneralPerturbations_8hpp.md)

[Go to the documentation of this file](GeneralPerturbations_8hpp.md)


```C++

#pragma once

#include <iosfwd>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

namespace astrea {
namespace astro {

struct GeneralPerturbations { // TODO: Right now, units are implied, but they should be used if possible. At least look into

    GeneralPerturbations() = default;

    GeneralPerturbations(const nlohmann::json& data);

    ~GeneralPerturbations() = default;

    int DB_ID;                                    
    std::optional<double> APOAPSIS;               
    std::optional<long double> ARG_OF_PERICENTER; 
    std::optional<long double> BSTAR;             
    std::string CCSDS_OMM_VERS;                   
    std::string CENTER_NAME;                      
    std::optional<char> CLASSIFICATION_TYPE;      
    std::string COMMENT;                          
    std::optional<std::string> COUNTRY_CODE;      
    std::optional<std::string> CREATION_DATE;     
    std::optional<std::string> DECAY_DATE;        
    std::optional<long double> ECCENTRICITY;      
    std::optional<short> ELEMENT_SET_NO;          
    std::optional<short unsigned> EPHEMERIS_TYPE; 
    std::optional<std::string> EPOCH;             
    std::optional<long unsigned> FILE;            
    unsigned GP_ID;                               
    std::optional<long double> INCLINATION;       
    std::optional<std::string> LAUNCH_DATE;       
    std::optional<double> MEAN_ANOMALY;           
    std::string MEAN_ELEMENT_THEORY;              
    std::optional<long double> MEAN_MOTION;       
    std::optional<long double> MEAN_MOTION_DDOT;  
    std::optional<long double> MEAN_MOTION_DOT;   
    unsigned NORAD_CAT_ID;                        
    std::optional<std::string> OBJECT_ID;         
    std::optional<std::string> OBJECT_NAME;       
    std::optional<std::string> OBJECT_TYPE;       
    std::string ORIGINATOR;                       
    std::optional<double> PERIAPSIS;              
    std::optional<double> PERIOD;                 
    std::optional<long double> RA_OF_ASC_NODE;    
    std::optional<std::string> RCS_SIZE;          
    std::string REF_FRAME;                        
    std::optional<unsigned> REV_AT_EPOCH;         
    std::optional<double> SEMIMAJOR_AXIS;         
    std::optional<std::string> SITE;              
    std::string TIME_SYSTEM;                      
    std::optional<std::string> TLE_LINE0;         
    std::optional<std::string> TLE_LINE1;         
    std::optional<std::string> TLE_LINE2;         
};

std::ostream& operator<<(std::ostream& os, const GeneralPerturbations& gp);

} // namespace astro
} // namespace astrea
```


