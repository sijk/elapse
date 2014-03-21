#ifndef SAMPLETYPES_H
#define SAMPLETYPES_H

#include <QtGlobal>
#include <QVector>
#include <QVector3D>
#include <QByteArray>
#include <QSharedPointer>
#include <QMetaEnum>

namespace elapse {

class Signal
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    enum Type { EEG, VIDEO, IMU, INVALID = -1 };

    static QString toString(Type type)
    { return typeEnum().valueToKey(type); }

    static Type fromString(const char *type)
    { return Type(typeEnum().keyToValue(type)); }

    static int count()
    { return typeEnum().keyCount() - 1; }

private:
    Signal() = delete;
    static QMetaEnum typeEnum()
    {
        int ienum = staticMetaObject.indexOfEnumerator("Type");
        return staticMetaObject.enumerator(ienum);
    }
};


struct Sample
{
    virtual ~Sample() {}

    quint64 timestamp;
};


typedef QSharedPointer<const Sample> SamplePtr;


struct EegSample : Sample
{
    quint32 seqnum;
    quint16 leadOff;
    QVector<double> values;
};


struct VideoSample : Sample
{
    int w, h;
    QByteArray data;
};


struct ImuSample : Sample
{
    QVector3D acc;
    QVector3D gyr;
};


struct FeatureVector
{
    Signal::Type signalType;
    quint64 startTime;
    QVector<double> features;

    FeatureVector(Signal::Type signalType, quint64 startTime) :
        signalType(signalType), startTime(startTime) {}
};


struct CognitiveState
{
    quint64 startTime;
    QVector<double> state;

    CognitiveState(quint64 startTime) : startTime(startTime) {}
};

} // namespace elapse

#endif // SAMPLETYPES_H
