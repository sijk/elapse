#include "elapse/elements/datasource.h"
#include "common/dbus/adaptor.h"
#include "configproxies.h"


namespace elapse {

class ConfigManagerPrivate
{
public:
    ConfigManagerPrivate(ConfigManager *config);

    config::Device device;
    DeviceDBusAdaptor adaptor;
};

} // namespace elapse


elapse::ConfigManagerPrivate::ConfigManagerPrivate(ConfigManager *config) :
    device(config),
    adaptor(&device, true)
{
}

elapse::ConfigManager::ConfigManager() :
    d_ptr(new ConfigManagerPrivate(this))
{
}

elapse::ConfigManager::~ConfigManager()
{
    delete d_ptr;
}

