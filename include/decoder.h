#ifndef DECODER_H
#define DECODER_H

#include <QObject>

class QByteArray;
class Sample;

class SampleDecoder : public QObject
{
    Q_OBJECT
public:
    explicit SampleDecoder(QObject *parent = 0) : QObject(parent) {}
    virtual ~SampleDecoder() {}

signals:
    void newSample(const Sample &sample);

public slots:
    virtual void onData(const QByteArray &data) = 0;
};

#endif // DECODER_H
