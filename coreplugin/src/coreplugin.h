#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <elapse/plugin.h>
#include "udpdatasource.h"
#include "dummyeegsource.h"
#include "eegdecoder.h"
#include "videodecoder.h"
#include "imudecoder.h"
#include "dummyeegfeatureextractor.h"
#include "dummyvideofeatureextractor.h"
#include "dummyimufeatureextractor.h"
#include "dummyclassifier.h"


/*!
 * \brief The CorePlugin class encapsulates the default element implementations
 * as a Plugin.
 *
 * It provides placeholder implementations for some elements and fully
 * functioning implementations for others.
 *
 * \ingroup core-plugin
 */

class CorePlugin : public elapse::Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ElapsePluginInterface_iid)
public:
    ClassList classes()
    {
        return {
            UdpDataSource::staticMetaObject,
            DummyEegSource::staticMetaObject,

            EegDecoder::staticMetaObject,
            VideoDecoder::staticMetaObject,
            ImuDecoder::staticMetaObject,

            DummyEegFeatureExtractor::staticMetaObject,
            DummyVideoFeatureExtractor::staticMetaObject,
            DummyImuFeatureExtractor::staticMetaObject,

            DummyClassifier::staticMetaObject
        };
    }
};

#endif // COREPLUGIN_H
