#include <math/chebyshev_util.hpp>

namespace astrea {
namespace math {

double transform_from_chebyshev_range(const double& x, const double& lb, const double& ub)
{
    return x * 0.5 * (ub - lb) + 0.5 * (ub + lb);
}

double transform_to_chebyshev_range(const double& x, const double& lb, const double& ub)
{
    return (x - 0.5 * (ub + lb)) / (0.5 * (ub - lb));
}

} // namespace math
} // namespace astrea
