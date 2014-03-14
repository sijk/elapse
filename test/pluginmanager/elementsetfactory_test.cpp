#include <QCoreApplication>
#include <gtest/gtest.h>
#include "elementsetfactory.h"


ClassInfo getClass(const char *plugin, const char *className)
{
    QString path("/../test_plugins/lib%1.so");
    QDir pluginPath = qApp->applicationDirPath() + path.arg(plugin);
    return { pluginPath.canonicalPath(), className };
}


class TestFactory : public ElementSetFactory
{
public:
    // Make loadElement() public se we can test it
    using ElementSetFactory::loadElement;
};


TEST(ElementSetFactoryTest, LoadInvalidPluginReturnsNull)
{
    DataSource *dataSource;
    TestFactory::loadElement(dataSource, getClass("invalid", "FooDummySource"));
    ASSERT_EQ(dataSource, nullptr);
}

TEST(ElementSetFactoryTest, LoadInvalidClassReturnsNull)
{
    DataSource *dataSource;
    TestFactory::loadElement(dataSource, getClass("fooplugin", "InvalidClass"));
    ASSERT_EQ(dataSource, nullptr);
}

TEST(ElementSetFactoryTest, LoadWithInvalidCastReturnsNull)
{
    DataSource *dataSource;
    TestFactory::loadElement(dataSource, getClass("fooplugin", "FooEegDecoder"));
    ASSERT_EQ(dataSource, nullptr);
}

TEST(ElementSetFactoryTest, LoadFooDummySource)
{
    DataSource *dataSource;
    TestFactory::loadElement(dataSource, getClass("fooplugin", "FooDummySource"));
    ASSERT_NE(dataSource, nullptr);
    delete dataSource;
}

