#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <Eigen/Dense>

/*!
 * \file
 * Spline interpolation.
 */

/*!
 * Interpolate the y-values y2 at x-coordinates x2 by fitting a cubic spline to
 * the points (x1, y1).
 *
 *     y2 = splinterp(x1, y1, x2);
 *
 * Requires:
 *  - x1.size() == y1.size()
 *  - x2.minCoeff() >= x1.minCoeff()
 *  - x2.maxCoeff() <= x1.maxCoeff()
 */

Eigen::ArrayXd splinterp(const Eigen::ArrayXd &x1, const Eigen::ArrayXd &y1,
                         const Eigen::ArrayXd &x2);

#endif // INTERPOLATE_H
