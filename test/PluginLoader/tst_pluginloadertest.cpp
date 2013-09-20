#include <QtTest>
#include "pluginloader.h"

class PluginLoaderTest : public QObject
{
    Q_OBJECT

private slots:
    void searchPathCanBeSet();

private:
    PluginLoader loader;
};


void PluginLoaderTest::searchPathCanBeSet()
{
    QDir newPath("/tmp");
    loader.setSearchPath(newPath);
    QCOMPARE(loader.searchPath(), newPath);
}


QTEST_GUILESS_MAIN(PluginLoaderTest)
#include "tst_pluginloadertest.moc"
