#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_base.h"
#include "datasource.h"

typedef FactoryInterface<DataSource> DataSourceInterface;
#define DataSourceInterface_iid "org.nzbri.elapse.DataSourceInterface"
Q_DECLARE_INTERFACE(DataSourceInterface, DataSourceInterface_iid)

class DataSourcePlugin : public QObject, public BasePlugin<DataSource>
{
    Q_OBJECT
    Q_INTERFACES(DataSourceInterface)
};

#endif // PLUGIN_H
