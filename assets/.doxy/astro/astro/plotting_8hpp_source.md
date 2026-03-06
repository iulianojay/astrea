

# File plotting.hpp

[**File List**](files.md) **>** [**astrea**](dir_b5324400686b7cece921533bb760c87a.md) **>** [**astro**](dir_1d4dcf10fc541574a93624f5c09a3d6f.md) **>** [**astro**](dir_84db6e3c60e44147f5214c05dc45afc2.md) **>** [**utilities**](dir_68b93ce2887c47fc193a24ece16ebbe5.md) **>** [**plotting.hpp**](plotting_8hpp.md)

[Go to the documentation of this file](plotting_8hpp.md)


```C++

#include <filesystem>
#include <string>
#include <vector>

#include <matplot/matplot.h>

#include <astro/astro.fwd.hpp>

namespace astrea {
namespace astro {
namespace plotting {

void plot_orbital_elements(const StateHistory& trajectory, const std::filesystem::path& outfile);

void plot_trajectory(const StateHistory& trajectory, const std::filesystem::path& outfile);

void compare_orbital_elements(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& labels, const std::filesystem::path& outfile);
void compare_trajectories(const std::vector<StateHistory>& trajectories, const std::vector<std::string>& labels, const std::filesystem::path& outfile);

void plot_difference_orbital_elements(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& labels,
    const std::filesystem::path& outfile
);
void plot_difference_trajectories(
    const StateHistory expected,
    const std::vector<StateHistory>& trajectories,
    const std::vector<std::string>& labels,
    const std::filesystem::path& outfile
);

} // namespace plotting
} // namespace astro
} // namespace astrea
```


