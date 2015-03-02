#include "interpolate.h"
#include <unsupported/Eigen/Splines>

using namespace Eigen;

ArrayXd splinterp(const ArrayXd &x1, const ArrayXd &y1, const ArrayXd &x2)
{
    using Spline2d = Spline<double, 2>;
    using KnotVector = Spline2d::KnotVectorType;
    using ControlPointVector = Spline2d::ControlPointVectorType;

    const auto n1 = x1.size();
    const auto n2 = x2.size();

    auto uvalues = [&](const ArrayXd &t) -> KnotVector {
        const auto min = x1.minCoeff();
        const auto max = x1.maxCoeff();
        return (t - min) / (max - min);
    };

    const auto knots = uvalues(x1);
    const auto u2 = uvalues(x2);

    auto ctrls = ControlPointVector(2, n1);
    ctrls << x1.transpose(), y1.transpose();
    const auto spline = SplineFitting<Spline2d>::Interpolate(ctrls, 3, knots);

    auto y2 = ArrayXd(n2);
    for (ArrayXd::Index i = 0; i < n2; ++i)
        y2[i] = spline(u2[i])[1];

    return y2;
}
