

# File main.cpp



[**FileList**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**snapshot**](dir_ad01b7a66bf2103e1e551598d7ba094a.md) **>** [**snapshot**](dir_d7d302d432d8a6ab561803ec6eec1eed.md) **>** [**drivers**](dir_aa0888f3e9fa4d362dbefaddf806e79b.md) **>** [**main.cpp**](main_8cpp.md)

[Go to the source code of this file](main_8cpp_source.md)



* `#include <algorithm>`
* `#include <fstream>`
* `#include <iostream>`
* `#include <sqlite3.h>`
* `#include <stdexcept>`
* `#include <string>`
* `#include <nlohmann/json.hpp>`
* `#include <sqlite_orm/sqlite_orm.h>`
* `#include <astro/state/orbital_data_formats/GeneralPerturbations.hpp>`
* `#include <astro/time/Date.hpp>`
* `#include <utilities/ProgressBar.hpp>`
* `#include <snapshot/database/Database.hpp>`
* `#include <snapshot/http-queries/spacetrack/SpaceTrackClient.hpp>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**main**](#function-main) (int argc, char \*\* argv) <br>_Main entry point for the SpaceTrack data retrieval application. This will query SpaceTrack using the provided credentials, retrieve all available General Perturbations (GP) data, and store it in a local SQLite database._  |




























## Public Functions Documentation




### function main 

_Main entry point for the SpaceTrack data retrieval application. This will query SpaceTrack using the provided credentials, retrieve all available General Perturbations (GP) data, and store it in a local SQLite database._ 
```C++
int main (
    int argc,
    char ** argv
) 
```





**Parameters:**


* `argc` Command line argument count 
* `argv` Command line argument vector, where argv[1] is the SpaceTrack username and argv[2] is the password 



**Returns:**

int Exit status code (0 for success) 





        

<hr>

------------------------------
The documentation for this class was generated from the following file `astrea/snapshot/snapshot/drivers/main.cpp`

