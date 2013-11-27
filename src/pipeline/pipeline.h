#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>

class ElementSet;


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
