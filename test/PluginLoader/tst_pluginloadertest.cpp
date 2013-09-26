#include <QtTest>
#include "pluginloader.h"
#include "dataprovider.h"
#include "dataconsumer.h"

class PluginLoaderTest : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void canSetSearchPath();
    void canFindPluginFiles();
    void canListInterfaces();
    void listsCorrectFilesForDataProviderInterface();
    void listsCorrectFilesForDataConsumerInterface();
    void listsCorrectKeysForInterfaces();
    void listsCorrectKeysForFiles();
    void canGetInfoForFile_data();
    void canGetInfoForFile();
    void canGetInfoForKey_data();
    void canGetInfoForKey();
    void canGetFileForKey_data();
    void canGetFileForKey();
    void canCreateDataProviderAndCast();
    void canCreateDataProviderTemplated();
    void emitCreatedKeySignalOnSuccess();
    void emitCreatedKeySignalOnSuccessTemplated();
    void dontEmitCreatedKeySignalOnFailure();
    void dontEmitCreatedKeySignalOnFailureTemplated();

private:
    PluginLoader *loader;
    QFileInfo SINE_PLUGIN, COSINE_PLUGIN, LOGGER_PLUGIN;
};


void PluginLoaderTest::init()
{
    loader = new PluginLoader;
    loader->setSearchPath(qApp->applicationDirPath() + "/../test_plugins");

    auto pluginPath = [&](const QString &fname) -> QFileInfo {
        return loader->searchPath().absolutePath() + "/" + fname;
    };

    SINE_PLUGIN   = pluginPath("libsineplugin.so");
    COSINE_PLUGIN = pluginPath("libcosineplugin.so");
    LOGGER_PLUGIN = pluginPath("libloggerplugin.so");
}

void PluginLoaderTest::cleanup()
{
    delete loader;
}

void PluginLoaderTest::canSetSearchPath()
{
    QDir newPath("/tmp");
    loader->setSearchPath(newPath);
    QCOMPARE(loader->searchPath(), newPath);
}

void PluginLoaderTest::canFindPluginFiles()
{
    QFileInfoList files = loader->files();
    QCOMPARE(files.size(), 3);
    QVERIFY(files.contains(SINE_PLUGIN));
    QVERIFY(files.contains(COSINE_PLUGIN));
    QVERIFY(files.contains(LOGGER_PLUGIN));
}

void PluginLoaderTest::canListInterfaces()
{
    QStringList ifaces = loader->interfaces();
    QCOMPARE(ifaces.size(), 2);
    QVERIFY(ifaces.contains(DataProviderInterface_iid));
    QVERIFY(ifaces.contains(DataConsumerInterface_iid));
}

void PluginLoaderTest::listsCorrectFilesForDataProviderInterface()
{
    QFileInfoList files = loader->filesForInterface(DataProviderInterface_iid);
    QVERIFY(files.contains(SINE_PLUGIN));
    QVERIFY(files.contains(COSINE_PLUGIN));
    QVERIFY(!files.contains(LOGGER_PLUGIN));
}

void PluginLoaderTest::listsCorrectFilesForDataConsumerInterface()
{
    QFileInfoList files = loader->filesForInterface(DataConsumerInterface_iid);
    QVERIFY(!files.contains(SINE_PLUGIN));
    QVERIFY(!files.contains(COSINE_PLUGIN));
    QVERIFY(files.contains(LOGGER_PLUGIN));
}

void PluginLoaderTest::listsCorrectKeysForInterfaces()
{
    QStringList keys = loader->keysForInterface(DataProviderInterface_iid);
    QCOMPARE(keys.size(), 3);
    QVERIFY(keys.contains("SineProvider"));
    QVERIFY(keys.contains("TcpProvider"));
    QVERIFY(keys.contains("CosineProvider"));

    keys = loader->keysForInterface(DataConsumerInterface_iid);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginLoaderTest::listsCorrectKeysForFiles()
{
    QStringList keys = loader->keysForFile(SINE_PLUGIN);
    QCOMPARE(keys.size(), 2);
    QVERIFY(keys.contains("SineProvider"));
    QVERIFY(keys.contains("TcpProvider"));

    keys = loader->keysForFile(COSINE_PLUGIN);
    QCOMPARE(keys, QStringList{"CosineProvider"});

    keys = loader->keysForFile(LOGGER_PLUGIN);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginLoaderTest::canGetInfoForFile_data()
{
    QTest::addColumn<QFileInfo>("file");
    QTest::addColumn<QString>("iid");

    QTest::newRow("libsineplugin.so") << SINE_PLUGIN << DataProviderInterface_iid;
    QTest::newRow("libcosineplugin.so") << COSINE_PLUGIN << DataProviderInterface_iid;
    QTest::newRow("libloggerplugin.so") << LOGGER_PLUGIN << DataConsumerInterface_iid;
}

void PluginLoaderTest::canGetInfoForFile()
{
    QFETCH(QFileInfo, file);
    QFETCH(QString, iid);
    QCOMPARE(loader->infoForFile(file)["IID"].toString(), iid);
}

void PluginLoaderTest::canGetInfoForKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QString>("iid");

    QTest::newRow("SineProvider") << "SineProvider" << DataProviderInterface_iid;
    QTest::newRow("TcpProvider") << "TcpProvider" << DataProviderInterface_iid;
    QTest::newRow("CosineProvider") << "CosineProvider" << DataProviderInterface_iid;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << DataConsumerInterface_iid;
}

void PluginLoaderTest::canGetInfoForKey()
{
    QFETCH(QString, key);
    QFETCH(QString, iid);
    QCOMPARE(loader->infoForKey(key)["IID"].toString(), iid);
}

void PluginLoaderTest::canGetFileForKey_data()
{
    QTest::addColumn<QString>("key");
    QTest::addColumn<QFileInfo>("file");

    QTest::newRow("SineProvider") << "SineProvider" << SINE_PLUGIN;
    QTest::newRow("TcpProvider") << "TcpProvider" << SINE_PLUGIN;
    QTest::newRow("CosineProvider") << "CosineProvider" << COSINE_PLUGIN;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << LOGGER_PLUGIN;
}

void PluginLoaderTest::canGetFileForKey()
{
    QFETCH(QString, key);
    QFETCH(QFileInfo, file);
    QCOMPARE(loader->fileForKey(key), file);
}

void PluginLoaderTest::canCreateDataProviderAndCast()
{
    QObject *provider = 0;
    provider = loader->create("SineProvider");
    QVERIFY(provider != 0);
    QVERIFY(qobject_cast<DataProvider*>(provider) != 0);
    QVERIFY(qobject_cast<DataConsumer*>(provider) == 0);
    delete provider;
}

void PluginLoaderTest::canCreateDataProviderTemplated()
{
    DataProvider *provider = 0;
    provider = loader->create<DataProvider*>("SineProvider");
    QVERIFY(provider != 0);
    delete provider;

    DataConsumer *consumer = 0;
    consumer = loader->create<DataConsumer*>("SineProvider");
    QVERIFY(consumer == 0);
    delete consumer;
}

void PluginLoaderTest::emitCreatedKeySignalOnSuccess()
{
    QString key = "SineProvider";
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));

    QObject *provider = loader->create(key);

    QVERIFY(provider != 0);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginLoaderTest::emitCreatedKeySignalOnSuccessTemplated()
{
    QString key = "SineProvider";
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));

    DataProvider *provider = loader->create<DataProvider*>(key);

    QVERIFY(provider != 0);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginLoaderTest::dontEmitCreatedKeySignalOnFailure()
{
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));
    QObject *obj = loader->create("foo");
    QCOMPARE(obj, static_cast<QObject*>(0));
    QCOMPARE(spy.count(), 0);
}

void PluginLoaderTest::dontEmitCreatedKeySignalOnFailureTemplated()
{
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));
    DataConsumer *consumer = loader->create<DataConsumer*>("SineProvider");
    QCOMPARE(consumer, static_cast<DataConsumer*>(0));
    QCOMPARE(spy.count(), 0);
}


QTEST_GUILESS_MAIN(PluginLoaderTest)
#include "tst_pluginloadertest.moc"
