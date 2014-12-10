#ifndef INTERFACES_H
#define INTERFACES_H

#include <memory>
#include <QxtLogger>
#include "common/qenum-utils.h"
#include "common/dbus/paths.h"
#include "common/hardware.h"

// Generated headers
#include "deviceinterface.h"
#include "batteryinterface.h"
#include "eegadcinterface.h"
#include "eegchannelinterface.h"
#include "imuinterface.h"


namespace elapse { namespace client {

/*!
 * \brief Adaptors between generated D-Bus interfaces and elapse::hardware
 * interfaces.
 *
 * The dbus namespace contains implementations of the interfaces in the
 * elapse::hardware namespace that pass calls through to QDBusAbstractInterface
 * subclasses generated from the XML interface definitions.
 *
 * These classes are necessary because Qt prevents diamond inheritance from
 * QObject. (The QObject internals use static_cast which doesn't work with
 * diamond inheritance, be it virtual or otherwise.) Both the elapse::hardware
 * interfaces and the generated D-Bus interfaces inherit from QObject, so
 * it's not possible to just have a class that inherits from both. The
 * work-around is to make the D-Bus interface a private member of these
 * classes and manually forward all of the method calls. Yuck.
 *
 * \code
 * Client → dbus::Foo (hardware::Foo) → org::nzbri::elapse::Foo (QDBusAbstractInterface) → D-Bus
 * \endcode
 */

namespace dbus {

/*!
 * \brief The Imu class makes a generated IMU D-Bus interface look like
 * an hardware::Imu.
 */

class Imu : public hardware::Imu
{
    Q_OBJECT
public:
    Imu(const QDBusConnection &connection, QObject *parent = 0) :
        hardware::Imu(parent),
        d(common::dbus::service, common::dbus::imuPath, connection)
    { }

public:
    uint sampleRate() const override { return d.sampleRate(); }
    void setSampleRate(uint hz) override { d.setSampleRate(hz); }
    AccRange accRange() const override { return AccRange(d.accRange()); }
    void setAccRange(AccRange range) override { d.setAccRange(range); }
    GyrRange gyrRange() const override { return GyrRange(d.gyrRange()); }
    void setGyrRange(GyrRange range) override { d.setGyrRange(range); }

public slots:
    void start() override { d.start(); }
    void stop() override { d.stop(); }

private:
    org::nzbri::elapse::Imu d;
};


/*!
 * \brief The EegChannel class makes a generated EEG channel D-Bus interface
 * look like an hardware::EegChannel.
 */

class EegChannel : public hardware::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, const QDBusConnection &connection, QObject *parent = 0) :
        hardware::EegChannel(parent),
        d(common::dbus::service, common::dbus::eegChanPath.arg(i), connection)
    { }

public:
    Gain gain() const override { return Gain(d.gain()); }
    void setGain(Gain gain) override { d.setGain(gain); }
    InputMux inputMux() const override
    { return InputMux(stringToEnum<EegChannel>("InputMux", d.inputMux())); }
    void setInputMux(InputMux mux) override
    { d.setInputMux(enumToString<EegChannel>("InputMux", mux)); }
    bool enabled() const override { return d.enabled(); }
    void setEnabled(bool enabled) override { d.setEnabled(enabled); }

private:
    org::nzbri::elapse::Eeg::EegChannel d;
};


/*!
 * \brief The EegAdc class makes a generated EEG ADC D-Bus interface look like
 * an hardware::EegAdc.
 */

class EegAdc : public hardware::EegAdc
{
    Q_OBJECT
public:
    EegAdc(const QDBusConnection &connection, QObject *parent = 0) :
        hardware::EegAdc(parent),
        d(common::dbus::service, common::dbus::eegPath, connection)
    { }

public:
    hardware::EegChannel *channel(uint i) override
    {
        if (_channels.empty()) {
            uint n = nChannels();
            _channels.reserve(n);
            for (uint i = 0; i < n; i++)
                _channels.emplace_back(new EegChannel(i, d.connection()));
        }
        return _channels.at(i).get();
    }
    uint nChannels() const override { return d.nChannels(); }
    uint bytesPerChunk() const override { return d.bytesPerChunk(); }
    double vref() const override { return d.vref(); }
    uint samplesPerChunk() const override { return d.samplesPerChunk(); }
    void setSamplesPerChunk(uint samples) override { d.setSamplesPerChunk(samples); }
    SampleRate sampleRate() const override { return SampleRate(d.sampleRate()); }
    void setSampleRate(SampleRate rate) override { d.setSampleRate(rate); }
    bool useRefElec() const override { return d.useRefElec(); }
    void setUseRefElec(bool use) override { d.setUseRefElec(use); }
    bool enableTestSignal() const override { return d.enableTestSignal(); }
    void setEnableTestSignal(bool enable) override { d.setEnableTestSignal(enable); }
    LeadOffFreq leadOffFreq() const override { return LeadOffFreq(d.leadOffFreq()); }
    void setLeadOffFreq(LeadOffFreq freq) override { d.setLeadOffFreq(freq); }
    LeadOffMag leadOffMag() const override { return LeadOffMag(d.leadOffMag()); }
    void setLeadOffMag(LeadOffMag mag) override { d.setLeadOffMag(mag); }
    bool leadOffSensePos() const override { return d.leadOffSensePos(); }
    void setLeadOffSensePos(bool enable) override { d.setLeadOffSensePos(enable); }
    bool leadOffSenseNeg() const override { return d.leadOffSenseNeg(); }
    void setLeadOffSenseNeg(bool enable) override { d.setLeadOffSenseNeg(enable); }

public slots:
    void start() override { d.start(); }
    void stop() override { d.stop(); }
    void reset() override { d.reset(); }
    void setAllChannels(const QVariantMap &properties) override
    { d.setAllChannels(properties); }

private:
    org::nzbri::elapse::Eeg::EegAdc d;
    std::vector<std::unique_ptr<EegChannel>> _channels;
};


/*!
 * \brief The Battery class makes a generated battery D-Bus interface look like
 * a hardware::Battery.
 */

class Battery : public hardware::Battery
{
    Q_OBJECT
public:
    Battery(const QDBusConnection &connection, QObject *parent = 0) :
        hardware::Battery(parent),
        d(common::dbus::service, common::dbus::batteryPath, connection)
    { }

public:
    double lowThresh() const override { return d.lowThresh(); }
    void setLowThresh(double value) override { d.setLowThresh(value); }
    double criticalThresh() const override { return d.criticalThresh(); }
    bool isLow() const override { return d.isLow(); }
    double voltage() const override { return d.voltage(); }

private:
    org::nzbri::elapse::Battery d;
};


/*!
 * \brief The Device class makes a generated device D-Bus interface look like
 * a hardware::Device.
 */

class Device : public hardware::Device
{
    Q_OBJECT
public:
    Device(const QDBusConnection &connection, QObject *parent = 0) :
        hardware::Device(parent),
        d(common::dbus::service, common::dbus::rootPath, connection),
        _eeg(new EegAdc(connection, this)),
        _imu(new Imu(connection, this)),
        _battery(new Battery(connection, this))
    { }

    /*!
     * Call isAccessible() and log any D-Bus errors if it fails.
     * \return whether the device is accessible.
     */
    bool checkConnected()
    {
        auto reply = d.isAccessible();
        reply.waitForFinished();
        if (!reply.isError())
            return true;

        qxtLog->error("The root dbus object is not accessible");
        qxtLog->error("Interface:", d.lastError().message());
        qxtLog->error("Server:", reply.error().message());
        return false;
    }

public:
    hardware::EegAdc *eeg() override { return _eeg; }
    hardware::Camera *camera() override { return nullptr; }
    hardware::Imu *imu() override { return _imu; }
    hardware::Battery *battery() override { return _battery; }

public slots:
    bool isAccessible() const override { return d.isAccessible(); }
    void setClientAddress(const QString &address) override { d.setClientAddress(address); }
    void startStreaming() override { d.startStreaming(); }
    void stopStreaming() override { d.stopStreaming(); }

private:
    mutable org::nzbri::elapse::Device d;

    EegAdc *_eeg;
//    Camera *_camera;
    Imu *_imu;
    Battery *_battery;
};

}}} // namespace elapse::client::dbus

#endif // INTERFACES_H
