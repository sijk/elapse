/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

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
