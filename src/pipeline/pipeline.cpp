#include <QVariant>
#include "elements.h"
#include "pipeline.h"

/*!
 * \class Pipeline
 * \ingroup signal-pipeline
 * \inmodule elapse-core
 *
 * \brief The Pipeline class manages all of the signal processing elements.
 *
 * It has a PluginLoader for loading signal processing elements from
 * \l{Plugin API}{plugins} and it manages the connections between
 * these elements.
 */


/*!
 * Construct a new Pipeline as a child of the given \a parent.
 */
Pipeline::Pipeline(QObject *parent) :
    QObject(parent),
    _elements(nullptr)
{
//    // Connect pipeline elements
//    connect(source, SIGNAL(eegReady(QByteArray)),
//            decoders[EEG], SLOT(onData(QByteArray)));

//    // Propagate signals from internal elements
//    connect(source, SIGNAL(started()), this, SIGNAL(started()));
//    connect(source, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
}

Pipeline::~Pipeline()
{
    if (_elements)
        delete _elements;
}

ElementSet *Pipeline::elements() const
{
    return _elements;
}

void Pipeline::setElements(ElementSet *newElements)
{
    if (_elements)
        delete _elements;

    _elements = newElements;

    // TODO: Connect them all up...
}

/*!
 * Start the pipeline.
 */
void Pipeline::start()
{
    Q_ASSERT(_elements);
    _elements->dataSource->start();
}

/*!
 * Stop the pipeline.
 */
void Pipeline::stop()
{
    _elements->dataSource->stop();
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
