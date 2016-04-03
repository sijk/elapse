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
