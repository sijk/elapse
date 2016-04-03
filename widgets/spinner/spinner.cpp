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

#include <QMovie>
#include "spinner.h"

static void loadResources() { Q_INIT_RESOURCE(spinner); }

namespace elapse { namespace widgets {

/*!
 * Construct a Spinner as a child of the given \a parent.
 */
Spinner::Spinner(QWidget *parent) :
    QLabel(parent),
    animation(new QMovie(":/img/spinner.gif", "GIF", this))
{
    ::loadResources();
}

/*!
 * \return whether the spinner animation is visible and running.
 */
bool Spinner::running() const
{
    return animation->state() == QMovie::Running;
}

/*!
 * Show and run the spinner animation.
 */
void Spinner::start()
{
    setMovie(animation);
    animation->start();
}

/*!
 * Hide and stop the spinner animation.
 */
void Spinner::stop()
{
    animation->stop();
    setText(" ");
}

/*!
 * Set whether the spinner animation is visible and running.
 */
void Spinner::setRunning(bool run)
{
    run ? start() : stop();
}

}} // namespace elapse::widgets
