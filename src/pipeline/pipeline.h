#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "elements.h"


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
    void setElements(ElementSetPtr newElements);

signals:
    void started();
    void stopped();
    void error(QString msg);

public slots:
    void start();
    void stop();

private:
    ElementSetPtr _elements;
};


#endif // PIPELINE_H
