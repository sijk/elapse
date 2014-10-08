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

/*!
 * \brief Data structures that are passed through the Pipeline.
 * \ingroup signal-datatypes
 */
namespace data {

/*!
    \class Signal
    \ingroup signal-datatypes

    \brief The Signal class is a wrapper providing introspection
    of the Signal::Type enum.

    \enum Signal::Type
    \brief The Signal::Type enum lists the types of signals captured
    by the device.

    \fn Signal::toString()
    \return the given \a type as a string.

    \fn Signal::fromString()
    \return the given \a type as a Signal::Type, or -1 if invalid.

    \fn Signal::count()
    \return the number of Signal::Type%s in the enum.
*/

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

    static uint count()
    { return typeEnum().keyCount() - 1; }

private:
    Signal() = delete;
    static QMetaEnum typeEnum()
    {
        int ienum = staticMetaObject.indexOfEnumerator("Type");
        return staticMetaObject.enumerator(ienum);
    }
};


/*!
    \class Sample
    \ingroup signal-datatypes

    \brief The Sample class is the base class for all samples acquired from
    sensors on the device.

    \fn Sample::~Sample()
    \brief Destroy this Sample.

    Providing a virtual destructor means that elements can implement their own
    private subclasses of the different sample types if necessary (to handle
    memory management, etc.).

    \var Sample::timestamp
    \brief The time at which the Sample was captured on the device.

    It is measured in nanoseconds from an arbitrary point in time.
    The timestamps of all Samples captured while the device is powered on are
    relative to the same reference point.
*/

struct Sample
{
    virtual ~Sample() {}

    time::Point timestamp;

protected:
    Sample() = default;
};


/*!
    \brief Shared pointer to a const Sample.

    This is how Sample%s get passed around in the Pipeline.
*/
using SamplePtr = std::shared_ptr<const Sample>;


namespace detail {

/*!
    The BaseSample struct uses the CRTP to add factory methods to
    subclasses of Sample.
*/
template<class SubType>
struct BaseSample : Sample
{
private:
    /*!
        A sneaky trick to make SubType's protected constructor available
        to create(). Constructible's public default ctor calls SubType's
        protected default ctor.
    */
    struct Constructible : SubType {};

public:
    /*! \brief Shared pointer to a SubType instance */
    using ptr = std::shared_ptr<SubType>;

    /*! \brief Shared pointer to a const SubType instance */
    using const_ptr = std::shared_ptr<const SubType>;

    /*!
        \brief Create an instance of SubType.
        \return a SubType::ptr to the instance.
    */
    static ptr create()
    {
        return std::make_shared<Constructible>();
    }

    /*!
        \brief Create an instance of T which is a subclass of SubType.

        This allows you to inherit from Sample subclasses as in the following
        snippet:

        \code
        struct MyVideoSample : VideoSample { ... }
        auto sample = VideoSample::createSubClass<MyVideoSample>();
        \endcode

        Arguments to this method are forwarded to T's constructor.

        \return a SubType::ptr to the instance.
    */
    template<class T, class... Args>
    static ptr createSubClass(Args&&... args)
    {
        Q_STATIC_ASSERT((std::is_base_of<SubType, T>::value));
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    /*! \brief Statically cast a SamplePtr to a SubType::const_ptr. */
    static const_ptr staticCastFrom(SamplePtr s)
    {
        return std::static_pointer_cast<const SubType>(s);
    }

    /*! \brief Dynamically cast a SamplePtr to a SubType::const_ptr. */
    static const_ptr dynamicCastFrom(SamplePtr s)
    {
        return std::dynamic_pointer_cast<const SubType>(s);
    }
};

} // namespace detail


/*!
    \class EegSample
    \ingroup signal-datatypes

    \brief The EegSample class holds the data for one multi-channel sample of
    EEG.

    \var EegSample::seqnum
    \brief A monotonically increasing sequence number.

    The seqnum of each EegSample should be exactly 1 greater than the seqnum of
    the previous sample, except for the first sample after the Pipeline is
    started. A discontinuity in the seqnum indicates that an EegSample got lost
    somewhere between the device and the SampleDecoder.

    \var EegSample::leadOff
    \brief Bit mask indicating the lead-off status (1 = off).

    \var EegSample::values
    \brief The voltage readings in microvolts.
*/

struct EegSample : detail::BaseSample<EegSample>
{
    quint32 seqnum;
    quint16 leadOff;
    std::vector<double> values;

protected:
    EegSample() = default;
};


/*!
    \class VideoSample
    \ingroup signal-datatypes

    \brief The VideoSample class holds the data for one frame of video.

    \var VideoSample::w
    \brief The width of the frame in pixels.

    \var VideoSample::h
    \brief The height of the frame in pixels.

    \var VideoSample::data
    \brief The video frame data.

    The data format is 8 bits per pixel greyscale in row-major order.
*/

struct VideoSample : detail::BaseSample<VideoSample>
{
    int w, h;
    QByteArray data;

protected:
    VideoSample() = default;
};


/*!
    \class ImuSample
    \ingroup signal-datatypes

    \brief The ImuSample class holds the data for one 6-axis sample from
    the IMU.

    \var ImuSample::acc
    \brief The linear accelerations in \e g.

    \var ImuSample::gyr
    \brief The angular rates in degrees per second.
*/

struct ImuSample : detail::BaseSample<ImuSample>
{
    QVector3D acc;
    QVector3D gyr;

protected:
    ImuSample() = default;
};


/*!
    \class FeatureVector
    \ingroup signal-datatypes

    \brief The FeatureVector struct holds a set of meaningful values extracted
    from a sequence of Sample%s.

    Each FeatureExtractor outputs a FeatureVector for each window of Sample%s
    that it analyses. The number of elements and the meaning of each element
    in the vector is left entirely up to each feature extractor (which will, of
    course, document these in detail).

    \var FeatureVector::signalType
    \brief The type of signal the features were extracted from.

    \var FeatureVector::startTime
    \brief The start time of the window from which the features were extracted.

    \var FeatureVector::features
    \brief The list of extracted features.

    The number and meaning of features in this list are left up to each
    FeatureExtractor.
*/

struct FeatureVector
{
    Signal::Type signalType;
    time::Point startTime;
    std::vector<double> features;

    FeatureVector(Signal::Type signalType, time::Point startTime) :
        signalType(signalType), startTime(startTime) {}

    using ptr = std::shared_ptr<FeatureVector>;
    using const_ptr = std::shared_ptr<const FeatureVector>;
};


/*!
    \class CognitiveState
    \ingroup signal-datatypes

    \brief The CognitiveState class holds a set of values representing
    the user's cognitive state.

    A Classifier calculates the CognitiveState from a set of FeatureVector%s.
    The number of fields and the meaning of each field in the CognitiveState
    data structure is left entirely up to each Classifier implementation (which
    will, of course, document these in detail).

    \var CognitiveState::startTime
    \brief The start time of the window from which the FeatureVector%s were
    extracted.

    \var CognitiveState::state
    \brief Values representing the user's cognitive state.

    The number and meaning of items in this list are left up to each
    Classifier.
*/

struct CognitiveState
{
    time::Point startTime;
    std::vector<double> state;

    CognitiveState(time::Point startTime) : startTime(startTime) {}

    using ptr = std::shared_ptr<CognitiveState>;
    using const_ptr = std::shared_ptr<const CognitiveState>;
};

}} // namespace elapse::data

#endif // SAMPLETYPES_H
