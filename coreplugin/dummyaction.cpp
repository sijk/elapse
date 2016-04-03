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

#include <QxtLogger>
#include "dummyaction.h"

namespace elapse { namespace coreplugin {

/*!
 * Create a new DummyAction.
 */
DummyAction::DummyAction()
{
}

/*!
 * Ignore the received \a state.
 */
void DummyAction::onState(data::CognitiveState::const_ptr state)
{
    Q_UNUSED(state)
    qxtLog->debug("Updated cognitive state");
}

}} // namespace elapse::coreplugin
