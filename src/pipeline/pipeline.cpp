#include <QVariant>
#include "datasource.h"
#include "eegdecoder.h"
#include "pluginloader.h"
#include "pipeline.h"

Pipeline::Pipeline(QObject *parent) :
    QObject(parent),
    loader(new PluginLoader(this)),
    decoder(new EegDecoder(this))
{
    source = loader->create<DataSource*>("TcpClientEegDataSource");
    Q_ASSERT_X(source, "Pipeline", "Could not create DataSource");
    source->setObjectName("DataSource");
    source->setParent(this);

    // Connect external signals
    connect(source, SIGNAL(started()), this, SIGNAL(started()));
    connect(source, SIGNAL(error(QString)), this, SIGNAL(error(QString)));

    // Connect pipeline elements
    connect(source, SIGNAL(eegReady(QByteArray)),
            decoder, SLOT(onData(QByteArray)));
}

PluginLoader *Pipeline::pluginLoader() const
{ return loader; }

DataSource *Pipeline::dataSource() const
{ return source; }

SampleDecoder *Pipeline::sampleDecoder() const
{ return decoder; }

bool Pipeline::setElementProperty(const QString &name, const char *prop,
                                  const QVariant &value)
{
    QObject *element = findChild<QObject*>(name);
    return element && element->setProperty(prop, value);
}

void Pipeline::start()
{
    source->start();
}

void Pipeline::stop()
{
    source->stop();
    emit stopped();
}
