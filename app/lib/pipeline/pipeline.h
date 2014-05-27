#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "elementset.h"
#include "datasink.h"


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

    ElementSetPtr elements() const;
    DataSink *dataSink() const;

    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void setElements(ElementSetPtr newElements);

    void start();
    void stop();

signals:
    void started();
    void stopped();
    void error(QString msg = QString());

private slots:
    void setStartTime(elapse::SamplePtr sample);

private:
    ElementSetPtr _elements;
    DataSink *_dataSink;
    bool startTimeIsSet;
};


#endif // PIPELINE_H
