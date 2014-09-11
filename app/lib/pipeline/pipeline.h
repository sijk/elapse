#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "elementset.h"

namespace elapse { namespace client {

/*!
 * \brief The Pipeline class manages a set of signal processing elements.
 *
 * It is responsible for managing the state of and connections between the
 * elements in an ElementSet.
 *
 * All connections between elements are \c Qt::AutoConnection%s. This means
 * that even if an element uses worker threads internally, signal propagation
 * to other elements will still be handled through Qt's main loop. In other
 * words, an element is allowed to emit signals directly from background
 * threads; the connected slots will be called from the main loop.
 *
 * \ingroup signal-pipeline
 * \see \ref pipeline-arch for an illustration of the pipeline's structure.
 */

class Pipeline : public QObject
{
    Q_OBJECT
public:
    explicit Pipeline(QObject *parent = nullptr);

    elements::ElementSetPtr elements() const;

    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void setElements(elapse::elements::ElementSetPtr newElements);
    void setDeviceConfig(QMap<QString, QVariantMap> config);

    void start();
    void stop();

signals:
    void started();
    void stopped();
    void error(QString msg = QString());

private slots:
    void setStartTime(elapse::data::SamplePtr sample);

private:
    elements::ElementSetPtr _elements;
    bool startTimeIsSet;
};

}} // namespace elapse::client

#endif // PIPELINE_H
