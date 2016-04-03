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

#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <elapse/plugin.h>
#include "udpdatasource.h"
#include "simplerawdatasource.h"
#include "eegdecoder.h"
#include "videodecoder.h"
#include "imudecoder.h"
#include "dummyeegfeatureextractor.h"
#include "dummyvideofeatureextractor.h"
#include "dummyimufeatureextractor.h"
#include "dummyclassifier.h"
#include "dummyaction.h"
#include "blackholedatasink.h"
#include "simplerawdatasink.h"

namespace elapse {

/*!
 * \brief Default implementations of elapse::elements.
 * \ingroup core-plugin
 */
namespace coreplugin {

/*!
 * \brief The CorePlugin class encapsulates the default element implementations
 * as a Plugin.
 *
 * It provides placeholder implementations for some elements and fully
 * functioning implementations for others.
 *
 * \ingroup core-plugin
 */

class CorePlugin : public QObject, public elapse::plugin::Interface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
    Q_INTERFACES(elapse::plugin::Interface)
    ELAPSE_EXPORT_CLASSES(
        UdpDataSource,
        SimpleRawDataSource,
        EegDecoder,
        VideoDecoder,
        ImuDecoder,
        DummyEegFeatureExtractor,
        DummyVideoFeatureExtractor,
        DummyImuFeatureExtractor,
        DummyClassifier,
        DummyAction,
        BlackHoleDataSink,
        SimpleRawDataSink
    )
};

}} // namespace elapse::coreplugin

#endif // COREPLUGIN_H
