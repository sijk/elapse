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


template<typename T>
using sample_ptr = std::shared_ptr<typename std::enable_if<std::is_base_of<Sample, T>::value, T>::type>;

using SamplePtr = sample_ptr<const Sample>;

template<typename T> sample_ptr<const T> static_sample_cast(SamplePtr s)
{
    return std::static_pointer_cast<const T>(s);
}

template<typename T> sample_ptr<const T> dynamic_sample_cast(SamplePtr s)
{
    return std::dynamic_pointer_cast<const T>(s);
}


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
