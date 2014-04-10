#include "elapse/elements/datasource.h"
#include "common/dbus/adaptor.h"
#include "configproxies.h"


namespace elapse {

class OfflineDataSourcePrivate
{
public:
    OfflineDataSourcePrivate(ConfigManager *config);

    config::Device device;
    DeviceDBusAdaptor adaptor;
};

} // namespace elapse


elapse::OfflineDataSourcePrivate::OfflineDataSourcePrivate(ConfigManager *config) :
    device(config),
    adaptor(&device, true)
{
}


/*!
 * Construct a new OfflineDataSource as a child of the given \a parent.
 */
elapse::OfflineDataSource::OfflineDataSource(QObject *parent) :
    DataSource(parent),
    d_ptr(nullptr)
{
}

/*!
 * Destroy this OfflineDataSource.
 */
elapse::OfflineDataSource::~OfflineDataSource()
{
    delete d_ptr;
}

void elapse::OfflineDataSource::exposeDeviceInterface()
{
    d_ptr = new OfflineDataSourcePrivate(this);
}


bool elapse::DataSource::isOfflineSource() const
{
    return qobject_cast<const elapse::OfflineDataSource*>(this) != nullptr;
}

