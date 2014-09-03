#ifndef CONFIGPROXIES_H
#define CONFIGPROXIES_H

#include "common/interfaces.h"
#include "elapse/elements/datasource.h"


/*!
 * \brief Adaptors between a \ref elapse::elements::ConfigManager "ConfigManager"
 * and ::iface interfaces.
 *
 * The config namespace contains implementations of the interfaces in the
 * ::iface namespace that pass calls through to a ConfigManager.
 * Only calls to const methods are passed through; non-const methods are NOPs.
 *
 * \code
 * D-Bus → FooAdaptor (QDBusAbstractAdaptor) → config::Foo (iface::Foo) → ConfigManager
 * \endcode
 */

namespace config {

using elapse::elements::ConfigManager;

/*!
 * \brief The Imu class makes a ConfigManager look like an iface::Imu.
 */

class Imu : public iface::Imu
{
    Q_OBJECT
public:
    Imu(ConfigManager *config, QObject *parent = nullptr) :
        iface::Imu(parent), config(config)
    { }

public:
    uint sampleRate() const
    { return config->get("imu", "sampleRate").toUInt(); }
    AccRange accRange() const
    { return AccRange(config->get("imu", "accRange").toInt()); }
    GyrRange gyrRange() const
    { return GyrRange(config->get("imu", "gyrRange").toInt()); }
    void setSampleRate(uint hz) { Q_UNUSED(hz) }
    void setAccRange(AccRange range) { Q_UNUSED(range) }
    void setGyrRange(GyrRange range) { Q_UNUSED(range) }

public slots:
    void start() { }
    void stop() { }

private:
    ConfigManager *config;
};


/*!
 * \brief The EegChannel class makes a ConfigManager look like
 * an iface::EegChannel.
 */

class EegChannel : public iface::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, ConfigManager *config, QObject *parent = 0) :
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
    void setGain(Gain gain) { Q_UNUSED(gain) }
    void setInputMux(InputMux mux) { Q_UNUSED(mux) }
    void setEnabled(bool enabled) { Q_UNUSED(enabled) }

private:
    ConfigManager *config;
    const QString chan;
};


/*!
 * \brief The EegAdc class makes a ConfigManager look like
 * an iface::EegAdc.
 */

class EegAdc : public iface::EegAdc
{
    Q_OBJECT
public:
    EegAdc(ConfigManager *config, QObject *parent = 0) :
        iface::EegAdc(parent), config(config)
    { }

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
    bool enableTestSignal() const
    { return config->get("eeg", "enableTestSignal").toBool(); }
    LeadOffFreq leadOffFreq() const
    { return LeadOffFreq(config->get("eeg", "leadOffFreq").toInt()); }
    LeadOffMag leadOffMag() const
    { return LeadOffMag(config->get("eeg", "leadOffMag").toInt()); }
    bool leadOffSensePos() const
    { return config->get("eeg", "leadOffSensePos").toBool(); }
    bool leadOffSenseNeg() const
    { return config->get("eeg", "leadOffSenseNeg").toBool(); }

    iface::EegChannel *channel(uint i)
    {
        if (iface_channels.empty()) {
            uint n = nChannels();
            for (uint i = 0; i < n; i++)
                iface_channels.append(new EegChannel(i, config, this));
        }
        return iface_channels.at(i);
    }

    void setSamplesPerChunk(uint samples) { Q_UNUSED(samples) }
    void setSampleRate(SampleRate rate) { Q_UNUSED(rate) }
    void setUseRefElec(bool use) { Q_UNUSED(use) }
    void setEnableTestSignal(bool enable) { Q_UNUSED(enable) }
    void setLeadOffFreq(LeadOffFreq freq) { Q_UNUSED(freq) }
    void setLeadOffMag(LeadOffMag mag) { Q_UNUSED(mag) }
    void setLeadOffSensePos(bool enable) { Q_UNUSED(enable) }
    void setLeadOffSenseNeg(bool enable) { Q_UNUSED(enable) }

public slots:
    void start() { }
    void stop() { }
    void reset() { }
    void setAllChannels(const QVariantMap &properties) { Q_UNUSED(properties) }

private:
    ConfigManager *config;
    QList<config::EegChannel*> iface_channels;
};


/*!
 * \brief The Battery class makes a ConfigManager look like
 * a iface::Battery.
 */

class Battery : public iface::Battery
{
    Q_OBJECT
public:
    Battery(ConfigManager *config, QObject *parent = 0) :
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
    void setLowThresh(double value) { Q_UNUSED(value) }

private:
    ConfigManager *config;
};


/*!
 * \brief The Device class makes a ConfigManager look like
 * a iface::Device.
 */

class Device : public iface::Device
{
    Q_OBJECT
public:
    Device(ConfigManager *config, QObject *parent = 0) :
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
    bool isAccessible() const { return true; }
    void setClientAddress(const QString &address) { Q_UNUSED(address) }
    void startStreaming() { }
    void stopStreaming() { }

private:
    ConfigManager *config;
    config::EegAdc *iface_eeg;
//    offline::Camera *iface_camera;
    config::Imu *iface_imu;
    config::Battery *iface_battery;
};

} // namespace config

#endif // CONFIGPROXIES_H
