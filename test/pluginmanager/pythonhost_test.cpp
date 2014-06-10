#include <gtest/gtest.h>
#include <QCoreApplication>

#include "pythonpluginhost.h"

class PythonPluginHostTest : public ::testing::Test
{
public:
    void SetUp()
    {
        QDir pluginDir(qApp->applicationDirPath());
        pluginDir.cdUp();
        pluginDir.cd("test_plugins");

        fooPluginPath = pluginDir.absoluteFilePath("libfooplugin.so");
        barPluginPath = pluginDir.absoluteFilePath("libbarplugin.so");
    }

    PythonPluginHost host;
    QString fooPluginPath;
    QString barPluginPath;
};


TEST_F(PythonPluginHostTest, InfoForFooPlugin)
{
}

TEST_F(PythonPluginHostTest, InfoForBarPlugin)
{
}

TEST_F(PythonPluginHostTest, InstantiateFooEegDecoder)
{
}
