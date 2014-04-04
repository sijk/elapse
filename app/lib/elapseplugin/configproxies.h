#ifndef CONFIGPROXIES_H
#define CONFIGPROXIES_H

#include "common/interface/device_iface.h"
#include "common/interface/battery_iface.h"
#include "common/interface/eegadc_iface.h"
#include "common/interface/camera_iface.h"
#include "common/interface/imu_iface.h"

#include "elapse/elements/datasource.h"


/*!
 * The config namespace contains implementations of the interfaces in the
 * \c iface namespace that pass calls through to a elapse::ConfigManager.
 * Only calls to const methods are passed through; non-const methods are
 * marked as unreachable.
 *
 * \code
 * D-Bus → QDBusAbstractAdaptor → config::Foo (iface::Foo) → ConfigManager
 * \endcode
 */

namespace config {

class Imu : public iface::Imu
{
    Q_OBJECT
public:
    Imu(elapse::ConfigManager *config, QObject *parent = nullptr) :
        iface::Imu(parent), config(config)
    { }

public:
    uint sampleRate() const
    { return config->get("imu", "sampleRate").toUInt(); }
    AccRange accRange() const
    { return AccRange(config->get("imu", "accRange").toInt()); }
    GyrRange gyrRange() const
    { return GyrRange(config->get("imu", "gyrRange").toInt()); }
    void setSampleRate(uint hz) { Q_UNUSED(hz) Q_UNREACHABLE(); }
    void setAccRange(AccRange range) { Q_UNUSED(range) Q_UNREACHABLE(); }
    void setGyrRange(GyrRange range) { Q_UNUSED(range) Q_UNREACHABLE(); }

public slots:
    void start() { Q_UNREACHABLE(); }
    void stop() { Q_UNREACHABLE(); }

private:
    elapse::ConfigManager *config;
};


class EegChannel : public iface::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, elapse::ConfigManager *config, QObject *parent = 0) :
        iface::EegChannel(parent), config(config),
        chan(QString("eeg/channel/%1").arg(i))
    { }

public:
    Gain gain() const
    { return Gain(config->get(chan, "gain").toInt()); }
    InputMux inputMux() const {
        QString mux = config->get(chan, "inputMux").toString();
        return InputMux(stringToEnum<EegChannel>("InputMux", mux));
    }
    bool enabled() const
    { return config->get(chan, "enabled").toBool(); }
    void setGain(Gain gain) { Q_UNUSED(gain) Q_UNREACHABLE(); }
    void setInputMux(InputMux mux) { Q_UNUSED(mux) Q_UNREACHABLE(); }
    void setEnabled(bool enabled) { Q_UNUSED(enabled) Q_UNREACHABLE(); }

private:
    elapse::ConfigManager *config;
    const QString chan;
};


class EegAdc : public iface::EegAdc
{
    Q_OBJECT
public:
    EegAdc(elapse::ConfigManager *config, QObject *parent = 0) :
        iface::EegAdc(parent), config(config)
    {
    }

public:
    uint nChannels() const
    { return config->get("eeg", "nChannels").toUInt(); }
    uint bytesPerChunk() const
    { return config->get("eeg", "bytesPerChunk").toUInt(); }
    double vref() const
    { return config->get("eeg", "vref").toDouble(); }
    uint samplesPerChunk() const
    { return config->get("eeg", "samplesPerChunk").toUInt(); }
    SampleRate sampleRate() const
    { return SampleRate(config->get("eeg", "sampleRate").toInt()); }
    bool useRefElec() const
    { return config->get("eeg", "useRefElec").toBool(); }

    iface::EegChannel *channel(uint i)
    {
        if (iface_channels.empty()) {
            for (uint i = 0; i < nChannels(); i++)
                iface_channels.append(new EegChannel(i, config, this));
        }
        return iface_channels.at(i);
    }

    void setSamplesPerChunk(uint samples) { Q_UNUSED(samples) Q_UNREACHABLE(); }
    void setSampleRate(SampleRate rate) { Q_UNUSED(rate) Q_UNREACHABLE(); }
    void setUseRefElec(bool use) { Q_UNUSED(use) Q_UNREACHABLE(); }

public slots:
    void start() { Q_UNREACHABLE(); }
    void stop() { Q_UNREACHABLE(); }
    void reset() { Q_UNREACHABLE(); }
    void setAllChannels(const QVariantMap &properties)
    { Q_UNUSED(properties) Q_UNREACHABLE(); }

private:
    elapse::ConfigManager *config;
    QList<config::EegChannel*> iface_channels;
};


class Battery : public iface::Battery
{
    Q_OBJECT
public:
    Battery(elapse::ConfigManager *config, QObject *parent = 0) :
        iface::Battery(parent), config(config)
    { }

public:
    double lowThresh() const
    { return config->get("battery", "lowThresh").toDouble(); }
    double criticalThresh() const
    { return config->get("battery", "criticalThresh").toDouble(); }
    bool isLow() const
    { return config->get("battery", "isLow").toBool(); }
    double voltage() const
    { return config->get("battery", "voltage").toDouble(); }
    void setLowThresh(double value) { Q_UNUSED(value) Q_UNREACHABLE(); }

private:
    elapse::ConfigManager *config;
};


class Device : public iface::Device
{
    Q_OBJECT
public:
    Device(elapse::ConfigManager *config, QObject *parent = 0) :
        iface::Device(parent), config(config),
        iface_eeg(new EegAdc(config, this)),
//        iface_camera(new Camera(config, this)),
        iface_imu(new Imu(config, this)),
        iface_battery(new Battery(config, this))
    { }

public:
    iface::EegAdc *eeg() { return iface_eeg; }
    iface::Camera *camera() { return nullptr; }
    iface::Imu *imu() { return iface_imu; }
    iface::Battery *battery() { return iface_battery; }

public slots:
    void setClientAddress(const QString &address)
    { Q_UNUSED(address) Q_UNREACHABLE(); }
    void startStreaming() { Q_UNREACHABLE(); }
    void stopStreaming() { Q_UNREACHABLE(); }

private:
    elapse::ConfigManager *config;
    config::EegAdc *iface_eeg;
//    offline::Camera *iface_camera;
    config::Imu *iface_imu;
    config::Battery *iface_battery;
};

} // namespace config

#endif // CONFIGPROXIES_H
