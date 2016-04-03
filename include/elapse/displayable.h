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

#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

class QWidget;

namespace elapse {

/*!
 * \brief The Displayable interface can be implemented by any class that wants
 * to expose a GUI widget.
 * \headerfile elapse/displayable.h
 */

class Displayable
{
public:
    /*!
     * Classes implementing the Displayable interface should implement this
     * method to return a widget that depicts the state of the object.
     *
     * The caller of this function takes ownership of the widget and must
     * delete it at the appropriate time.
     *
     * Because the lifetime of the widget is managed externally, it would
     * be wise to store the pointer inside this class as a QPointer. This
     * will automatically null the pointer if the widget is destroyed
     * before the object that created it, preventing a dangling pointer.
     */
    virtual QWidget *getWidget() = 0;
};

} // namespace elapse

#endif // DISPLAYABLE_H
