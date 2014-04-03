#ifndef INTERFACES_H
#define INTERFACES_H

#include <QxtLogger>

#include "common/qenum-utils.h"
#include "common/dbus/paths.h"

#include "common/interface/device_iface.h"
#include "common/interface/battery_iface.h"
#include "common/interface/eegadc_iface.h"
#include "common/interface/camera_iface.h"
#include "common/interface/imu_iface.h"

#include "elapse_interface.h"
#include "eeg_interface.h"
#include "imu_interface.h"


/*!
 * The dbus namespace contains implementations of the interfaces in the
 * \c iface namespace that pass calls through to QDBusAbstractInterface
 * subclasses generated from the XML interface definitions.
 */

namespace dbus {

class Imu : public iface::Imu
{
    Q_OBJECT
public:
    Imu(const QDBusConnection &connection, QObject *parent = 0) :
        d(dbus::service, dbus::imuPath, connection, parent)
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


class EegChannel : public iface::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, const QDBusConnection &connection, QObject *parent = 0) :
        d(dbus::service, dbus::eegChanPath.arg(i), connection, parent)
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


class EegAdc : public iface::EegAdc
{
    Q_OBJECT
public:
    EegAdc(const QDBusConnection &connection, QObject *parent = 0) :
        d(dbus::service, dbus::eegPath, connection, parent)
    {
        for (uint i = 0; i < nChannels(); i++)
            iface_channels.append(new EegChannel(i, connection, this));
    }

public:
    iface::EegChannel *channel(uint i) { return iface_channels.at(i); }
    uint nChannels() const { return d.nChannels(); }
    uint bytesPerChunk() const { return d.bytesPerChunk(); }
    double vref() const { return d.vref(); }
    uint samplesPerChunk() const { return d.samplesPerChunk(); }
    void setSamplesPerChunk(uint samples) { d.setSamplesPerChunk(samples); }
    SampleRate sampleRate() const { return SampleRate(d.sampleRate()); }
    void setSampleRate(SampleRate rate) { d.setSampleRate(rate); }
    bool useRefElec() const { return d.useRefElec(); }
    void setUseRefElec(bool use) { d.setUseRefElec(use); }

public slots:
    void start() { d.start(); }
    void stop() { d.stop(); }
    void reset() { d.reset(); }
    void setAllChannels(const QVariantMap &properties)
    { d.setAllChannels(properties); }

private:
    org::nzbri::elapse::Eeg::EegAdc d;
    QList<dbus::EegChannel*> iface_channels;
};


class Battery : public iface::Battery
{
    Q_OBJECT
public:
    Battery(const QDBusConnection &connection, QObject *parent = 0) :
        d(dbus::service, dbus::batteryPath, connection, parent)
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


class Device : public iface::Device
{
    Q_OBJECT
public:
    Device(const QDBusConnection &connection, QObject *parent = 0) :
        d(dbus::service, dbus::rootPath, connection, parent),
        iface_eeg(new EegAdc(connection, this)),
        iface_imu(new Imu(connection, this)),
        iface_battery(new Battery(connection, this))
    { }

    ~Device()
    {
        qxtLog->info("dbus::Device destroyed");
    }

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
    iface::EegAdc *eeg() { return iface_eeg; }
    iface::Camera *camera() { return nullptr; }
    iface::Imu *imu() { return iface_imu; }
    iface::Battery *battery() { return iface_battery; }

public slots:
    void setClientAddress(const QString &address) { d.setClientAddress(address); }
    void startStreaming() { d.startStreaming(); }
    void stopStreaming() { d.stopStreaming(); }

private:
    org::nzbri::elapse::Device d;

    dbus::EegAdc *iface_eeg;
//    dbus::Camera *iface_camera;
    dbus::Imu *iface_imu;
    dbus::Battery *iface_battery;
};

} // namespace dbus

#endif // INTERFACES_H
