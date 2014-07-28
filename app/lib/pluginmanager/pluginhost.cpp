#include "pluginhost.h"

QList<PluginData> PluginHost::searchForPluginsIn(QDir &dir)
{
    QList<PluginData> plugins;

    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);

    for (const QFileInfo &item : dir.entryInfoList()) {
        PluginData info = getInfo(item.absoluteFilePath());
        if (!info.plugin.name.isEmpty()) {
            plugins.append(info);
        }
    }

    return plugins;
}
