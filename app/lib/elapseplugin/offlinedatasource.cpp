#include "elapse/elements/datasource.h"
#include "common/dbus/adaptor.h"
#include "configproxies.h"


namespace elapse { namespace elements {

class OfflineDataSourcePrivate
{
public:
    OfflineDataSourcePrivate(ConfigManager *config);

    client::config::Device device;
    common::dbus::Adaptor adaptor;
};


OfflineDataSourcePrivate::OfflineDataSourcePrivate(ConfigManager *config) :
    device(config),
    adaptor(&device, true)
{
}


OfflineDataSource::OfflineDataSource() { }

OfflineDataSource::~OfflineDataSource() { }

void OfflineDataSource::exposeDeviceInterface()
{
    d_ptr.reset(new OfflineDataSourcePrivate(this));
}


bool DataSource::isOfflineSource() const
{
    return qobject_cast<const OfflineDataSource*>(this) != nullptr;
}

}} // namespace elapse::elements
