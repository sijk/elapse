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
    uint sampleRate() const { return d.sampleRate(); }
    void setSampleRate(uint hz) { d.setSampleRate(hz); }
    AccRange accRange() const { return AccRange(d.accRange()); }
    void setAccRange(AccRange range) { d.setAccRange(range); }
    GyrRange gyrRange() const { return GyrRange(d.gyrRange()); }
    void setGyrRange(GyrRange range) { d.setGyrRange(range); }

public slots:
    void start() { d.start(); }
    void stop() { d.stop(); }

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
    Gain gain() const { return Gain(d.gain()); }
    void setGain(Gain gain) { d.setGain(gain); }
    InputMux inputMux() const
    { return InputMux(stringToEnum<EegChannel>("InputMux", d.inputMux())); }
    void setInputMux(InputMux mux)
    { d.setInputMux(enumToString<EegChannel>("InputMux", mux)); }
    bool enabled() const { return d.enabled(); }
    void setEnabled(bool enabled) { d.setEnabled(enabled); }

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
    hardware::EegChannel *channel(uint i)
    {
        if (_channels.empty()) {
            uint n = nChannels();
            _channels.reserve(n);
            for (uint i = 0; i < n; i++)
                _channels.emplace_back(new EegChannel(i, d.connection()));
        }
        return _channels.at(i).get();
    }
    uint nChannels() const { return d.nChannels(); }
    uint bytesPerChunk() const { return d.bytesPerChunk(); }
    double vref() const { return d.vref(); }
    uint samplesPerChunk() const { return d.samplesPerChunk(); }
    void setSamplesPerChunk(uint samples) { d.setSamplesPerChunk(samples); }
    SampleRate sampleRate() const { return SampleRate(d.sampleRate()); }
    void setSampleRate(SampleRate rate) { d.setSampleRate(rate); }
    bool useRefElec() const { return d.useRefElec(); }
    void setUseRefElec(bool use) { d.setUseRefElec(use); }
    bool enableTestSignal() const { return d.enableTestSignal(); }
    void setEnableTestSignal(bool enable) { d.setEnableTestSignal(enable); }
    LeadOffFreq leadOffFreq() const { return LeadOffFreq(d.leadOffFreq()); }
    void setLeadOffFreq(LeadOffFreq freq) { d.setLeadOffFreq(freq); }
    LeadOffMag leadOffMag() const { return LeadOffMag(d.leadOffMag()); }
    void setLeadOffMag(LeadOffMag mag) { d.setLeadOffMag(mag); }
    bool leadOffSensePos() const { return d.leadOffSensePos(); }
    void setLeadOffSensePos(bool enable) { d.setLeadOffSensePos(enable); }
    bool leadOffSenseNeg() const { return d.leadOffSenseNeg(); }
    void setLeadOffSenseNeg(bool enable) { d.setLeadOffSenseNeg(enable); }

public slots:
    void start() { d.start(); }
    void stop() { d.stop(); }
    void reset() { d.reset(); }
    void setAllChannels(const QVariantMap &properties)
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
    double lowThresh() const { return d.lowThresh(); }
    void setLowThresh(double value) { d.setLowThresh(value); }
    double criticalThresh() const { return d.criticalThresh(); }
    bool isLow() const { return d.isLow(); }
    double voltage() const { return d.voltage(); }

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
    hardware::EegAdc *eeg() { return _eeg; }
    hardware::Camera *camera() { return nullptr; }
    hardware::Imu *imu() { return _imu; }
    hardware::Battery *battery() { return _battery; }

public slots:
    bool isAccessible() const { return d.isAccessible(); }
    void setClientAddress(const QString &address) { d.setClientAddress(address); }
    void startStreaming() { d.startStreaming(); }
    void stopStreaming() { d.stopStreaming(); }

private:
    mutable org::nzbri::elapse::Device d;

    EegAdc *_eeg;
//    Camera *_camera;
    Imu *_imu;
    Battery *_battery;
};

}}} // namespace elapse::client::dbus

#endif // INTERFACES_H
