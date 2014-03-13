#include <gtest/gtest.h>
#include <QCoreApplication>
#include "pluginmanager.h"

class PluginManagerTest : public ::testing::Test
{
public:
    void SetUp()
    {
        manager = new PluginManager;
        manager->setSearchPath(qApp->applicationDirPath() + "/../test_plugins");

        auto pluginPath = [&](const QString &name) -> QFileInfo {
            QString libname("lib%1.so");
            return manager->searchPath().absoluteFilePath(libname.arg(name));
        };

        FOO_PLUGIN = pluginPath("fooplugin");
        BAR_PLUGIN = pluginPath("barplugin");
    }

    void TearDown()
    {
        delete manager;
    }

    PluginManager *manager;
    QFileInfo FOO_PLUGIN, BAR_PLUGIN;
};

#if 0
class PluginManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void canSetSearchPath();
    void canFindPluginFiles();
    void canListInterfaces();
    void canListFilesForProducerInterface();
    void canListFilesForConsumerInterface();
    void canListKeysForInterfaces();
    void canListKeysForFiles();
    void canGetInfoForFile_data();
    void canGetInfoForFile();
    void canGetInfoForKey_data();
    void canGetInfoForKey();
    void canGetFileForKey_data();
    void canGetFileForKey();
    void canCreateProducerAndCast();
    void canCreateProducerTemplated();
    void emitCreatedKeySignalOnSuccess();
    void emitCreatedKeySignalOnSuccessTemplated();
    void dontEmitCreatedKeySignalOnFailure();
    void dontEmitCreatedKeySignalOnFailureTemplated();
    void changingSearchPathRemovesOldPlugins();

private:
    PluginManager *manager;
    QFileInfo SINE_PLUGIN, COSINE_PLUGIN, LOGGER_PLUGIN;
};
#endif


TEST_F(PluginManagerTest, CanSetSearchPath)
{
    QDir newPath("/tmp");
    this->manager->setSearchPath(newPath);
    EXPECT_EQ(manager->searchPath(), newPath);
}

//TEST(PluginManagerTest, CanFindPluginFiles)
//{
//    QFileInfoList files = manager->files();
//    EXPECT_EQ(files.size(), 3);
//    EXPECT_TRUE(files.contains(SINE_PLUGIN));
//    EXPECT_TRUE(files.contains(COSINE_PLUGIN));
//    EXPECT_TRUE(files.contains(LOGGER_PLUGIN));
//}

#if 0
void PluginManagerTest::canListInterfaces()
{
    QStringList ifaces = manager->interfaces();
    QCOMPARE(ifaces.size(), 2);
    QVERIFY(ifaces.contains(ProducerInterface_iid));
    QVERIFY(ifaces.contains(ConsumerInterface_iid));
}

void PluginManagerTest::canListFilesForProducerInterface()
{
    QFileInfoList files = manager->filesForInterface(ProducerInterface_iid);
    QVERIFY(files.contains(SINE_PLUGIN));
    QVERIFY(files.contains(COSINE_PLUGIN));
    QVERIFY(!files.contains(LOGGER_PLUGIN));
}

void PluginManagerTest::canListFilesForConsumerInterface()
{
    QFileInfoList files = manager->filesForInterface(ConsumerInterface_iid);
    QVERIFY(!files.contains(SINE_PLUGIN));
    QVERIFY(!files.contains(COSINE_PLUGIN));
    QVERIFY(files.contains(LOGGER_PLUGIN));
}

void PluginManagerTest::canListKeysForInterfaces()
{
    QStringList keys = manager->keysForInterface(ProducerInterface_iid);
    QCOMPARE(keys.size(), 3);
    QVERIFY(keys.contains("SineProducer"));
    QVERIFY(keys.contains("TcpProducer"));
    QVERIFY(keys.contains("CosineProducer"));

    keys = manager->keysForInterface(ConsumerInterface_iid);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginManagerTest::canListKeysForFiles()
{
    QStringList keys = manager->keysForFile(SINE_PLUGIN);
    QCOMPARE(keys.size(), 2);
    QVERIFY(keys.contains("SineProducer"));
    QVERIFY(keys.contains("TcpProducer"));

    keys = manager->keysForFile(COSINE_PLUGIN);
    QCOMPARE(keys, QStringList{"CosineProducer"});

    keys = manager->keysForFile(LOGGER_PLUGIN);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginManagerTest::canGetInfoForFile_data()
{
    QTest::addColumn<QFileInfo>("file");
    QTest::addColumn<QString>("iid");

    QTest::newRow("libsineplugin.so") << SINE_PLUGIN << ProducerInterface_iid;
    QTest::newRow("libcosineplugin.so") << COSINE_PLUGIN << ProducerInterface_iid;
    QTest::newRow("libloggerplugin.so") << LOGGER_PLUGIN << ConsumerInterface_iid;
}

void PluginManagerTest::canGetInfoForFile()
{
    QFETCH(QFileInfo, file);
    QFETCH(QString, iid);
    QCOMPARE(manager->infoForFile(file)["IID"].toString(), iid);
}

void PluginManagerTest::canGetInfoForKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("iid");

    QTest::newRow("SineProducer") << "SineProducer" << ProducerInterface_iid;
    QTest::newRow("TcpProducer") << "TcpProducer" << ProducerInterface_iid;
    QTest::newRow("CosineProducer") << "CosineProducer" << ProducerInterface_iid;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << ConsumerInterface_iid;
}

void PluginManagerTest::canGetInfoForKey()
{
    QFETCH(QString, key);
    QFETCH(QString, iid);
    QCOMPARE(manager->infoForKey(key)["IID"].toString(), iid);
}

void PluginManagerTest::canGetFileForKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QFileInfo>("file");

    QTest::newRow("SineProducer") << "SineProducer" << SINE_PLUGIN;
    QTest::newRow("TcpProducer") << "TcpProducer" << SINE_PLUGIN;
    QTest::newRow("CosineProducer") << "CosineProducer" << COSINE_PLUGIN;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << LOGGER_PLUGIN;
}

void PluginManagerTest::canGetFileForKey()
{
    QFETCH(QString, key);
    QFETCH(QFileInfo, file);
    QCOMPARE(manager->fileForKey(key), file);
}

void PluginManagerTest::canCreateProducerAndCast()
{
    QObject *provider = nullptr;
    provider = manager->create("SineProducer");
    QVERIFY(provider != nullptr);
    QVERIFY(qobject_cast<Producer*>(provider) != nullptr);
    QVERIFY(qobject_cast<Consumer*>(provider) == nullptr);
    delete provider;
}

void PluginManagerTest::canCreateProducerTemplated()
{
    Producer *provider = nullptr;
    provider = manager->create<Producer*>("SineProducer");
    QVERIFY(provider != nullptr);
    delete provider;

    Consumer *consumer = nullptr;
    consumer = manager->create<Consumer*>("SineProducer");
    QVERIFY(consumer == nullptr);
}

void PluginManagerTest::emitCreatedKeySignalOnSuccess()
{
    QString key = "SineProducer";
    QSignalSpy spy(manager, SIGNAL(createdKey(QString)));

    QObject *provider = manager->create(key);

    QVERIFY(provider != nullptr);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginManagerTest::emitCreatedKeySignalOnSuccessTemplated()
{
    QString key = "SineProducer";
    QSignalSpy spy(manager, SIGNAL(createdKey(QString)));

    Producer *provider = manager->create<Producer*>(key);

    QVERIFY(provider != nullptr);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginManagerTest::dontEmitCreatedKeySignalOnFailure()
{
    QSignalSpy spy(manager, SIGNAL(createdKey(QString)));
    QObject *obj = manager->create("foo");
    QVERIFY(obj == nullptr);
    QCOMPARE(spy.count(), 0);
}

void PluginManagerTest::dontEmitCreatedKeySignalOnFailureTemplated()
{
    QSignalSpy spy(manager, SIGNAL(createdKey(QString)));
    Consumer *consumer = manager->create<Consumer*>("SineProducer");
    QVERIFY(consumer == nullptr);
    QCOMPARE(spy.count(), 0);
}

void PluginManagerTest::changingSearchPathRemovesOldPlugins()
{
    QFileInfoList files = manager->files();
    QCOMPARE(files.size(), 3);

    manager->setSearchPath(qApp->applicationDirPath());
    files = manager->files();
    QCOMPARE(files.size(), 0);
}
#endif

