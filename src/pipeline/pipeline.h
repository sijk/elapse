#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>

class ElementSet;


/*!
 * \brief The Pipeline class manages a set of signal processing elements.
 *
 * It is responsible for managing the state of and connections between the
 * elements in an ElementSet.
 *
 * \ingroup signal-pipeline
 */

class Pipeline : public QObject
{
    Q_OBJECT
public:
    explicit Pipeline(QObject *parent = 0);
    ~Pipeline();

    ElementSet *elements() const;
    void setElements(ElementSet *newElements);

signals:
    void started();
    void stopped();
    void error(const QString &msg);

public slots:
    void start();
    void stop();

private:
    ElementSet *_elements;
};


#endif // PIPELINE_H
