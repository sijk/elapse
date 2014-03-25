#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "elementset.h"

class DataSink;


/*!
 * \brief The Pipeline class manages a set of signal processing elements.
 *
 * It is responsible for managing the state of and connections between the
 * elements in an ElementSet.
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

    void setWindowLength(uint ms);
    void setWindowStep(uint ms);

public slots:
    void setElements(ElementSetPtr newElements);

    void start();
    void stop();

signals:
    void started();
    void stopped();
    void error(QString msg);

private slots:
    void setStartTime(elapse::SamplePtr sample);

private:
    ElementSetPtr _elements;
    DataSink *dataSink;
};


#endif // PIPELINE_H
