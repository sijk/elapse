#include <QVariant>
#include "datasource.h"
#include "decoder.h"
#include "pluginloader.h"
#include "pipeline.h"

/*!
 * \class Pipeline
 * \ingroup pipeline
 *
 * \brief The Pipeline class manages all of the signal processing elements.
 *
 * It has a PluginLoader for loading signal processing elements from
 * \l{Plugin API Documentation}{plugins} and it manages the connections between
 * these elements.
 */


/*!
 * Construct a new Pipeline as a child of the given \a parent.
 */
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

/*!
 * \return the PluginLoader instance.
 */
PluginLoader *Pipeline::pluginLoader() const
{
    return loader;
}

/*!
 * \return the DataSource instance.
 */
DataSource *Pipeline::dataSource() const
{
    return source;
}

/*!
 * \return the SampleDecoder for the given \a sampleType.
 */
SampleDecoder *Pipeline::sampleDecoder(SampleType sampleType) const
{
    return decoders[sampleType];
}

/*!
 * Set property \a prop of the element with objectName \a name to \a value.
 * \return whether the property was successfully set.
 */
bool Pipeline::setElementProperty(const QString &name, const char *prop,
                                  const QVariant &value)
{
    QObject *element = findChild<QObject*>(name);
    return element && element->setProperty(prop, value);
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    source->start();
}

/*!
 * Stop the pipeline.
 */
void Pipeline::stop()
{
    source->stop();
    emit stopped();
}

/*!
 * \fn Pipeline::started()
 * Emitted when the DataSource has started receiving data from the device.
 */

/*!
 * \fn Pipeline::stopped()
 * Emitted when data has stopped flowing through the pipeline for any reason.
 */

/*!
 * \fn Pipeline::error(const QString &msg)
 * Emitted when an error has occurred somewhere in the pipeline. The \a msg is
 * human readable, suitable for displaying in a dialog box or similar.
 */
