#include <QtTest>
#include "pluginloader.h"
#include "producer.h"
#include "consumer.h"
#include "test_plugins.h"

class PluginLoaderTest : public QObject
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
    PluginLoader *loader;
    QFileInfo SINE_PLUGIN, COSINE_PLUGIN, LOGGER_PLUGIN;
};


void PluginLoaderTest::init()
{
    loader = new PluginLoader;
    loader->setSearchPath(qApp->applicationDirPath() + "/../test_plugins");

    auto pluginPath = [&](const QString &name) -> QFileInfo {
        QString libname("lib%1.so");
        return loader->searchPath().absoluteFilePath(libname.arg(name));
    };

    SINE_PLUGIN   = pluginPath("sineplugin");
    COSINE_PLUGIN = pluginPath("cosineplugin");
    LOGGER_PLUGIN = pluginPath("loggerplugin");
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
    QVERIFY(ifaces.contains(ProducerInterface_iid));
    QVERIFY(ifaces.contains(ConsumerInterface_iid));
}

void PluginLoaderTest::canListFilesForProducerInterface()
{
    QFileInfoList files = loader->filesForInterface(ProducerInterface_iid);
    QVERIFY(files.contains(SINE_PLUGIN));
    QVERIFY(files.contains(COSINE_PLUGIN));
    QVERIFY(!files.contains(LOGGER_PLUGIN));
}

void PluginLoaderTest::canListFilesForConsumerInterface()
{
    QFileInfoList files = loader->filesForInterface(ConsumerInterface_iid);
    QVERIFY(!files.contains(SINE_PLUGIN));
    QVERIFY(!files.contains(COSINE_PLUGIN));
    QVERIFY(files.contains(LOGGER_PLUGIN));
}

void PluginLoaderTest::canListKeysForInterfaces()
{
    QStringList keys = loader->keysForInterface(ProducerInterface_iid);
    QCOMPARE(keys.size(), 3);
    QVERIFY(keys.contains("SineProducer"));
    QVERIFY(keys.contains("TcpProducer"));
    QVERIFY(keys.contains("CosineProducer"));

    keys = loader->keysForInterface(ConsumerInterface_iid);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginLoaderTest::canListKeysForFiles()
{
    QStringList keys = loader->keysForFile(SINE_PLUGIN);
    QCOMPARE(keys.size(), 2);
    QVERIFY(keys.contains("SineProducer"));
    QVERIFY(keys.contains("TcpProducer"));

    keys = loader->keysForFile(COSINE_PLUGIN);
    QCOMPARE(keys, QStringList{"CosineProducer"});

    keys = loader->keysForFile(LOGGER_PLUGIN);
    QCOMPARE(keys, QStringList{"LoggerConsumer"});
}

void PluginLoaderTest::canGetInfoForFile_data()
{
    QTest::addColumn<QFileInfo>("file");
    QTest::addColumn<QString>("iid");

    QTest::newRow("libsineplugin.so") << SINE_PLUGIN << ProducerInterface_iid;
    QTest::newRow("libcosineplugin.so") << COSINE_PLUGIN << ProducerInterface_iid;
    QTest::newRow("libloggerplugin.so") << LOGGER_PLUGIN << ConsumerInterface_iid;
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

    QTest::newRow("SineProducer") << "SineProducer" << ProducerInterface_iid;
    QTest::newRow("TcpProducer") << "TcpProducer" << ProducerInterface_iid;
    QTest::newRow("CosineProducer") << "CosineProducer" << ProducerInterface_iid;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << ConsumerInterface_iid;
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

    QTest::newRow("SineProducer") << "SineProducer" << SINE_PLUGIN;
    QTest::newRow("TcpProducer") << "TcpProducer" << SINE_PLUGIN;
    QTest::newRow("CosineProducer") << "CosineProducer" << COSINE_PLUGIN;
    QTest::newRow("LoggerConsumer") << "LoggerConsumer" << LOGGER_PLUGIN;
}

void PluginLoaderTest::canGetFileForKey()
{
    QFETCH(QString, key);
    QFETCH(QFileInfo, file);
    QCOMPARE(loader->fileForKey(key), file);
}

void PluginLoaderTest::canCreateProducerAndCast()
{
    QObject *provider = nullptr;
    provider = loader->create("SineProducer");
    QVERIFY(provider != nullptr);
    QVERIFY(qobject_cast<Producer*>(provider) != nullptr);
    QVERIFY(qobject_cast<Consumer*>(provider) == nullptr);
    delete provider;
}

void PluginLoaderTest::canCreateProducerTemplated()
{
    Producer *provider = nullptr;
    provider = loader->create<Producer*>("SineProducer");
    QVERIFY(provider != nullptr);
    delete provider;

    Consumer *consumer = nullptr;
    consumer = loader->create<Consumer*>("SineProducer");
    QVERIFY(consumer == nullptr);
}

void PluginLoaderTest::emitCreatedKeySignalOnSuccess()
{
    QString key = "SineProducer";
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));

    QObject *provider = loader->create(key);

    QVERIFY(provider != nullptr);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginLoaderTest::emitCreatedKeySignalOnSuccessTemplated()
{
    QString key = "SineProducer";
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));

    Producer *provider = loader->create<Producer*>(key);

    QVERIFY(provider != nullptr);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), key);

    delete provider;
}

void PluginLoaderTest::dontEmitCreatedKeySignalOnFailure()
{
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));
    QObject *obj = loader->create("foo");
    QVERIFY(obj == nullptr);
    QCOMPARE(spy.count(), 0);
}

void PluginLoaderTest::dontEmitCreatedKeySignalOnFailureTemplated()
{
    QSignalSpy spy(loader, SIGNAL(createdKey(QString)));
    Consumer *consumer = loader->create<Consumer*>("SineProducer");
    QVERIFY(consumer == nullptr);
    QCOMPARE(spy.count(), 0);
}

void PluginLoaderTest::changingSearchPathRemovesOldPlugins()
{
    QFileInfoList files = loader->files();
    QCOMPARE(files.size(), 3);

    loader->setSearchPath(qApp->applicationDirPath());
    files = loader->files();
    QCOMPARE(files.size(), 0);
}


QTEST_GUILESS_MAIN(PluginLoaderTest)
#include "tst_pluginloadertest.moc"