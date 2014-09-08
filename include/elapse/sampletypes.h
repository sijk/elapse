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

protected:
    Sample() = default;
};


using SamplePtr = std::shared_ptr<const Sample>;


namespace detail {

template<class SubType>
struct BaseSample : Sample
{
private:
    struct Constructible : SubType {};  // Make SubType's default ctor public

public:
    using ptr = std::shared_ptr<SubType>;
    using const_ptr = std::shared_ptr<const SubType>;

    static ptr create()
    {
        return std::make_shared<Constructible>();
    }

    template<class T, class... Args>
    static ptr createSubClass(Args&&... args)
    {
        Q_STATIC_ASSERT((std::is_base_of<SubType, T>::value));
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    static const_ptr staticCastFrom(SamplePtr s)
    {
        return std::static_pointer_cast<const SubType>(s);
    }

    static const_ptr dynamicCastFrom(SamplePtr s)
    {
        return std::dynamic_pointer_cast<const SubType>(s);
    }
};

} // namespace detail


struct EegSample : detail::BaseSample<EegSample>
{
    quint32 seqnum;
    quint16 leadOff;
    std::vector<double> values;

protected:
    EegSample() = default;
};


struct VideoSample : detail::BaseSample<VideoSample>
{
    int w, h;
    QByteArray data;

protected:
    VideoSample() = default;
};


struct ImuSample : detail::BaseSample<ImuSample>
{
    QVector3D acc;
    QVector3D gyr;

protected:
    ImuSample() = default;
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
