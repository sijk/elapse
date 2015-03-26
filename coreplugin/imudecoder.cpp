#include <QDataStream>
#include <QVector>
#include <QtEndian>
#include <QxtLogger>
#include <boost/circular_buffer.hpp>
#include <algorithm>
#include <Eigen/Dense>
#include <elapse/datatypes.h>
#include <elapse/timestamps.h>
#include "imudecoder.h"
#include "util/interpolate.h"

using elapse::data::ImuSample;

namespace elapse { namespace coreplugin {

class ImuDecoderPrivate
{
    ImuDecoder * const q_ptr;
    Q_DECLARE_PUBLIC(ImuDecoder)

    template<typename Value>
    struct Sample
    {
        quint64 time;
        Value x, y, z;
    };

    using AccSample = Sample<qint16>;
    using GyrSample = Sample<qint32>;

    boost::circular_buffer<AccSample> acc;
    boost::circular_buffer<GyrSample> gyr;

    void extractSamplesFrom(const QByteArray &bytes);
    QVector<ImuSample::ptr> interpolateSamples();

    template<class Value>
    void extractSamples(const uchar *buff, int size, qint64 time,
                        boost::circular_buffer<Sample<Value>> &queue);

public:
    uint samplePeriod;

    ImuDecoderPrivate(ImuDecoder *q);
    void handleBytes(const QByteArray &bytes);
};


ImuDecoderPrivate::ImuDecoderPrivate(ImuDecoder *q) :
    q_ptr(q),
    acc(32),
    gyr(32),
    samplePeriod(0)
{
}

/*!
 * Parse the sample data from the given \a bytes, interpolate the gyro data
 * to match the accelerometer timestamps, and emit ImuSample%s.
 */
void ImuDecoderPrivate::handleBytes(const QByteArray &bytes)
{
    Q_Q(ImuDecoder);

    extractSamplesFrom(bytes);
    const auto samples = interpolateSamples();

    for (auto sample : samples)
        emit q->newSample(sample);
}

/*!
 * The passed \a bytes array contains several 3-axis samples from either the
 * accelerometer or the gyroscope, along with the timestamp of the most
 * recent sample in the block. Extract these samples from the byte array
 * and populate the timestamps of all of the samples given the final
 * timestamp and the known sampling rate. These samples are pushed into
 * the internal queue of acc or gyr samples as appropriate.
 *
 * See the documentation for the LSM330DLC driver for details of the binary
 * data structure.
 */
void ImuDecoderPrivate::extractSamplesFrom(const QByteArray &bytes)
{
    Q_ASSERT(samplePeriod != 0);
    const uchar *buff = reinterpret_cast<const uchar*>(bytes.data());

    char blockType = bytes[0];
    buff++;

    qint64 blockTime = qFromLittleEndian<qint64>(buff);
    buff += 8;

    if (blockType == 'A')
        extractSamples(buff, bytes.size(), blockTime, acc);
    else
        extractSamples(buff, bytes.size(), blockTime, gyr);
}

template<typename Value>
void ImuDecoderPrivate::extractSamples(const uchar *buff, int size, qint64 blockTime,
                                       boost::circular_buffer<Sample<Value>> &queue)
{
    int nSamples = (size - 9) / (3 * sizeof(Value));

    for (int i = 0; i < nSamples; i++) {
        Sample<Value> s;
        s.time = blockTime - (nSamples - i - 1) * samplePeriod;
        s.x = qFromLittleEndian<Value>(buff); buff += sizeof(Value);
        s.y = qFromLittleEndian<Value>(buff); buff += sizeof(Value);
        s.z = qFromLittleEndian<Value>(buff); buff += sizeof(Value);
        queue.push_back(std::move(s));
    }
}

/*!
 * Given the queued 3-axis acc and gyr samples (at different sampling rates),
 * interpolate the gyro samples to match the timestamps of the accelerometer
 * samples, then create 6-axis ImuSample%s from the pairs.
 *
 * The interpolating spline is fitted to the 32 most recent gyro samples
 * in all cases, regardless of how many samples are being interpolated. This
 * is perhaps not the most efficient implementation but it means we can just
 * use a circular buffer and be done with it.
 *
 * \return a vector of the interpolated samples.
 */
QVector<ImuSample::ptr> ImuDecoderPrivate::interpolateSamples()
{
    QVector<ImuSample::ptr> samples;

    if (acc.empty() || gyr.size() < 6)
        return {};

    // Ignore acc samples from before the first gyr sample because we can only
    // interpolate, not extrapolate.
    while (acc.front().time < gyr.front().time)
        acc.pop_front();

    // Find the number of acc samples within the temporal range of
    // the queued gyr samples.
    int nGyr = gyr.size();
    int nAcc;
    {
        const auto gyrEnd = gyr.back().time;
        auto lastAcc = std::find_if(acc.rbegin(), acc.rend(),
            [=](const AccSample &a){
                return a.time <= gyrEnd;
            });
        nAcc = std::distance(acc.begin(), lastAcc.base());
    }

    // Interpolate the gyro samples at the acc timestamps.
    Eigen::ArrayXd gix, giy, giz;
    {
        Eigen::ArrayXd tg(nGyr), gx(nGyr), gy(nGyr), gz(nGyr);
        Eigen::ArrayXd ta(nAcc);

        for (int i = 0; i < nGyr; i++) {
            GyrSample &g = gyr[i];
            tg[i] = g.time;
            gx[i] = g.x;
            gy[i] = g.y;
            gz[i] = g.z;
        }

        for (int i = 0; i < nAcc; i++)
            ta[i] = acc[i].time;

        gix = splinterp(tg, gx, ta);
        giy = splinterp(tg, gy, ta);
        giz = splinterp(tg, gz, ta);
    }

    // Create ImuSamples from the interpolated data.
    // Note that the axes assigned to the head by the Elapse framework
    // are different to those on the hardware:
    //     [0 0 1] [x]   [z]
    //     [1 0 0] [y] = [x]
    //     [0 1 0] [z]   [y]
    for (int i = 0; i < nAcc; i++) {
        auto sample = ImuSample::create();

        sample->timestamp = acc[i].time;
        sample->acc.setX(acc[i].z / 1e3);
        sample->acc.setY(acc[i].x / 1e3);
        sample->acc.setZ(acc[i].y / 1e3);
        sample->gyr.setX(giz[i] / 1e3);
        sample->gyr.setY(gix[i] / 1e3);
        sample->gyr.setZ(giy[i] / 1e3);

        samples.append(sample);
    }

    acc.erase_begin(nAcc);

    return samples;
}


/*!
 * Create a new ImuDecoder.
 */
ImuDecoder::ImuDecoder() :
    d_ptr(new ImuDecoderPrivate(this))
{
}

ImuDecoder::~ImuDecoder()
{
}

/*!
 * Store the IMU's sampleRate so that we can interpolate timestamps.
 */
void ImuDecoder::configure(QMap<QString, QVariantMap> config)
{
    Q_D(ImuDecoder);
    using namespace time::literals;
    d->samplePeriod = 1_s / config["imu"]["sampleRate"].toUInt();
}

/*!
 * Decode the given \a data and emit data::ImuSample%s.
 */
void ImuDecoder::onData(QByteArray data)
{
    Q_D(ImuDecoder);
    d->handleBytes(data);
}

}} // namespace elapse::coreplugin
