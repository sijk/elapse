#ifndef INTERFACES_H
#define INTERFACES_H

#include <QxtLogger>
#include "common/qenum-utils.h"
#include "common/dbus/paths.h"
#include "common/interfaces.h"

// Generated headers
#include "elapse_interface.h"
#include "eeg_interface.h"
#include "imu_interface.h"


/*!
 * \brief Adaptors between generated D-Bus interfaces and ::iface interfaces.
 *
 * The ::dbus namespace contains implementations of the interfaces in the
 * ::iface namespace that pass calls through to QDBusAbstractInterface
 * subclasses generated from the XML interface definitions.
 *
 * \code
 * Client → dbus::Foo (iface::Foo) → org::nzbri::elapse::Foo (QDBusAbstractInterface) → D-Bus
 * \endcode
 */

namespace dbus {

/*!
 * \brief The Imu class makes a generated IMU D-Bus interface look like
 * an iface::Imu.
 */

class Imu : public iface::Imu
{
    Q_OBJECT
public:
    Imu(const QDBusConnection &connection, QObject *parent = 0) :
        iface::Imu(parent),
        d(dbus::service, dbus::imuPath, connection)
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
 * look like an iface::EegChannel.
 */

class EegChannel : public iface::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, const QDBusConnection &connection, QObject *parent = 0) :
        iface::EegChannel(parent),
        d(dbus::service, dbus::eegChanPath.arg(i), connection)
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
 * an iface::EegAdc.
 */

class EegAdc : public iface::EegAdc
{
    Q_OBJECT
public:
    EegAdc(const QDBusConnection &connection, QObject *parent = 0) :
        iface::EegAdc(parent),
        d(dbus::service, dbus::eegPath, connection)
    { }

    ~EegAdc() { qDeleteAll(iface_channels); }

public:
    iface::EegChannel *channel(uint i)
    {
        if (iface_channels.isEmpty()) {
            uint n = nChannels();
            for (uint i = 0; i < n; i++)
                iface_channels.append(new EegChannel(i, d.connection()));
        }
        return iface_channels.at(i);
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


/*!
 * \brief The Battery class makes a generated battery D-Bus interface look like
 * a iface::Battery.
 */

class Battery : public iface::Battery
{
    Q_OBJECT
public:
    Battery(const QDBusConnection &connection, QObject *parent = 0) :
        iface::Battery(parent),
        d(dbus::service, dbus::batteryPath, connection)
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
 * a iface::Device.
 */

class Device : public iface::Device
{
    Q_OBJECT
public:
    Device(const QDBusConnection &connection, QObject *parent = 0) :
        iface::Device(parent),
        d(dbus::service, dbus::rootPath, connection),
        iface_eeg(new EegAdc(connection, this)),
        iface_imu(new Imu(connection, this)),
        iface_battery(new Battery(connection, this))
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
    iface::EegAdc *eeg() { return iface_eeg; }
    iface::Camera *camera() { return nullptr; }
    iface::Imu *imu() { return iface_imu; }
    iface::Battery *battery() { return iface_battery; }

public slots:
    bool isAccessible() const { return d.isAccessible(); }
    void setClientAddress(const QString &address) { d.setClientAddress(address); }
    void startStreaming() { d.startStreaming(); }
    void stopStreaming() { d.stopStreaming(); }

private:
    mutable org::nzbri::elapse::Device d;

    dbus::EegAdc *iface_eeg;
//    dbus::Camera *iface_camera;
    dbus::Imu *iface_imu;
    dbus::Battery *iface_battery;
};

} // namespace dbus

#endif // INTERFACES_H
