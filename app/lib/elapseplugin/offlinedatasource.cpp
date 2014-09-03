#include "elapse/elements/datasource.h"
#include "common/dbus/adaptor.h"
#include "configproxies.h"


namespace elapse { namespace elements {

class OfflineDataSourcePrivate
{
public:
    OfflineDataSourcePrivate(ConfigManager *config);

    config::Device device;
    DeviceDBusAdaptor adaptor;
};


OfflineDataSourcePrivate::OfflineDataSourcePrivate(ConfigManager *config) :
    device(config),
    adaptor(&device, true)
{
}


/*!
 * Construct a new OfflineDataSource.
 */
OfflineDataSource::OfflineDataSource() :
    d_ptr(nullptr)
{
}

/*!
 * Destroy this OfflineDataSource.
 */
OfflineDataSource::~OfflineDataSource()
{
    delete d_ptr;
}

void OfflineDataSource::exposeDeviceInterface()
{
    d_ptr = new OfflineDataSourcePrivate(this);
}


bool DataSource::isOfflineSource() const
{
    return qobject_cast<const OfflineDataSource*>(this) != nullptr;
}

}} // namespace elapse::elements
