#ifndef SAMPLETYPES_H
#define SAMPLETYPES_H

#include <QtGlobal>
#include <memory>
#include <vector>
#include <QVector3D>
#include <QByteArray>
#include <QMetaEnum>
#include "timestamps.h"

namespace elapse {

class Signal
{
    Q_GADGET
    Q_ENUMS(Type)
public:
    enum Type { EEG, VIDEO, IMU, INVALID = -1 };

    static const char*toString(Type type)
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

    TimeStamp timestamp;
};


typedef std::shared_ptr<const Sample> SamplePtr;


struct EegSample : Sample
{
    quint32 seqnum;
    quint16 leadOff;
    std::vector<double> values;
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
    TimeStamp startTime;
    std::vector<double> features;

    FeatureVector(Signal::Type signalType, TimeStamp startTime) :
        signalType(signalType), startTime(startTime) {}
};


struct CognitiveState
{
    TimeStamp startTime;
    std::vector<double> state;

    CognitiveState(TimeStamp startTime) : startTime(startTime) {}
};

} // namespace elapse

#endif // SAMPLETYPES_H
