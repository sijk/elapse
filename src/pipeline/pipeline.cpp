#include <QVariant>
#include "datasource.h"
#include "decoder.h"
#include "pluginloader.h"
#include "pipeline.h"

Pipeline::Pipeline(QObject *parent) :
    QObject(parent),
    loader(new PluginLoader(this))
{
    source = loader->create<DataSource*>("TcpClientEegDataSource");
    Q_ASSERT_X(source, "Pipeline", "Could not create DataSource");
    source->setObjectName("DataSource");
    source->setParent(this);

    decoders[EEG] = loader->create<SampleDecoder*>("EegDecoder");
    Q_ASSERT_X(decoders[EEG], "Pipeline", "Could not create EegDecoder");
    decoders[EEG]->setObjectName("EegDecoder");
    decoders[EEG]->setParent(this);

    // Connect pipeline elements
    connect(source, SIGNAL(eegReady(QByteArray)),
            decoders[EEG], SLOT(onData(QByteArray)));

    // Propagate signals from internal elements
    connect(source, SIGNAL(started()), this, SIGNAL(started()));
    connect(source, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

PluginLoader *Pipeline::pluginLoader() const
{ return loader; }

DataSource *Pipeline::dataSource() const
{ return source; }

SampleDecoder *Pipeline::sampleDecoder(SampleType sampleType) const
{ return decoders[sampleType]; }

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
