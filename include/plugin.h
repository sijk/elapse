#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_base.h"
#include "datasource.h"
#include "decoder.h"


typedef FactoryInterface<DataSource> DataSourceInterface;
#define DataSourceInterface_iid "org.nzbri.elapse.DataSourceInterface"
Q_DECLARE_INTERFACE(DataSourceInterface, DataSourceInterface_iid)

class DataSourcePlugin : public QObject, public BasePlugin<DataSource>
{
    Q_OBJECT
    Q_INTERFACES(DataSourceInterface)
};


typedef FactoryInterface<SampleDecoder> SampleDecoderInterface;
#define SampleDecoderInterface_iid "org.nzbri.elapse.SampleDecoderInterface"
Q_DECLARE_INTERFACE(SampleDecoderInterface, SampleDecoderInterface_iid)

class SampleDecoderPlugin : public QObject, public BasePlugin<SampleDecoder>
{
    Q_OBJECT
    Q_INTERFACES(SampleDecoderInterface)
};


#endif // PLUGIN_H
