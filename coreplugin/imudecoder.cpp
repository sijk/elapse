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

    struct Sample
    {
        quint64 time;
        qint16 x, y, z;
    };

    boost::circular_buffer<Sample> acc;
    boost::circular_buffer<Sample> gyr;

    void extractSamplesFrom(const QByteArray &bytes);
    QVector<ImuSample::ptr> interpolateSamples();

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

void ImuDecoderPrivate::handleBytes(const QByteArray &bytes)
{
    Q_Q(ImuDecoder);

    extractSamplesFrom(bytes);
    const auto samples = interpolateSamples();

    for (auto sample : samples)
        emit q->newSample(sample);
}

void ImuDecoderPrivate::extractSamplesFrom(const QByteArray &bytes)
{
    Q_ASSERT(samplePeriod != 0);
    const uchar *buff = reinterpret_cast<const uchar*>(bytes.data());

    char blockType = bytes[0];
    buff++;

    qint64 blockTime = qFromLittleEndian<qint64>(buff);
    buff += 8;

    int nSamples = (bytes.size() - 9) / (3 * sizeof(qint16));
    auto &q = (blockType == 'A') ? acc : gyr;

    for (int i = 0; i < nSamples; i++) {
        Sample s;
        s.time = blockTime - (nSamples - i - 1) * samplePeriod;
        s.x = qFromLittleEndian<qint16>(buff); buff += 2;
        s.y = qFromLittleEndian<qint16>(buff); buff += 2;
        s.z = qFromLittleEndian<qint16>(buff); buff += 2;
        q.push_back(std::move(s));
    }
}

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
            [=](const Sample &a){
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
            Sample &g = gyr[i];
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
    for (int i = 0; i < nAcc; i++) {
        auto sample = ImuSample::create();

        sample->timestamp = acc[i].time;
        sample->acc.setX(acc[i].x);
        sample->acc.setY(acc[i].y);
        sample->acc.setZ(acc[i].z);
        sample->gyr.setX(gix[i]);
        sample->gyr.setY(giy[i]);
        sample->gyr.setZ(giz[i]);

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

void ImuDecoder::configure(QMap<QString, QVariantMap> config)
{
    Q_D(ImuDecoder);
    using namespace time::literals;
    d->samplePeriod = 1_s / config["imu"]["sampleRate"].toUInt();
    qxtLog->debug("IMU sample period =", d->samplePeriod);
}

/*!
 * Decode the given \a data and emit ImuSample%s.
 */
void ImuDecoder::onData(QByteArray data)
{
    Q_D(ImuDecoder);
    d->handleBytes(data);
}

}} // namespace elapse::coreplugin
