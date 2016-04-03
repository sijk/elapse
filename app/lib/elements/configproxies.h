/*
 * Elapse Client
 * Copyright (C) 2015 Simon Knopp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Additional permission under GNU GPL version 3 section 7:
 *
 * The licensors of this Program grant you additional permission to link
 * this Program with other modules by means of the provided plugin
 * interface and to convey the resulting work, regardless of the license
 * terms of the other modules.
 */

#ifndef CONFIGPROXIES_H
#define CONFIGPROXIES_H

#include "common/hardware.h"
#include "elapse/elements/datasource.h"


namespace elapse { namespace client {

/*!
 * \brief Adaptors between a \ref elements::ConfigManager "ConfigManager"
 * and elapse::hardware interfaces.
 *
 * The config namespace contains implementations of the interfaces in the
 * elapse::hardware namespace that pass calls through to a ConfigManager.
 * Only calls to const methods are passed through; non-const methods are NOPs.
 *
 * \code
 * D-Bus → FooAdaptor (QDBusAbstractAdaptor) → config::Foo (hardware::Foo) → ConfigManager
 * \endcode
 */

namespace config {

using elapse::elements::ConfigManager;

/*!
 * \brief The Imu class makes a ConfigManager look like an hardware::Imu.
 */

class Imu : public hardware::Imu
{
    Q_OBJECT
public:
    Imu(ConfigManager *config, QObject *parent = nullptr) :
        hardware::Imu(parent), config(config)
    { }

public:
    uint sampleRate() const override
    { return config->get("imu", "sampleRate").toUInt(); }
    AccRange accRange() const override
    { return AccRange(config->get("imu", "accRange").toInt()); }
    GyrRange gyrRange() const override
    { return GyrRange(config->get("imu", "gyrRange").toInt()); }
    void setSampleRate(uint hz) override { Q_UNUSED(hz) }
    void setAccRange(AccRange range) override { Q_UNUSED(range) }
    void setGyrRange(GyrRange range) override { Q_UNUSED(range) }

public slots:
    void start() override { }
    void stop() override { }

private:
    ConfigManager *config;
};


/*!
 * \brief The EegChannel class makes a ConfigManager look like
 * an hardware::EegChannel.
 */

class EegChannel : public hardware::EegChannel
{
    Q_OBJECT
public:
    EegChannel(uint i, ConfigManager *config, QObject *parent = 0) :
        hardware::EegChannel(parent), config(config),
        chan(QString("eeg/channel/%1").arg(i))
    { }

public:
    Gain gain() const override
    { return Gain(config->get(chan, "gain").toInt()); }
    InputMux inputMux() const override {
        QString mux = config->get(chan, "inputMux").toString();
        return InputMux(stringToEnum<EegChannel>("InputMux", mux));
    }
    bool enabled() const override
    { return config->get(chan, "enabled").toBool(); }
    void setGain(Gain gain) override { Q_UNUSED(gain) }
    void setInputMux(InputMux mux) override { Q_UNUSED(mux) }
    void setEnabled(bool enabled) override { Q_UNUSED(enabled) }

private:
    ConfigManager *config;
    const QString chan;
};


/*!
 * \brief The EegAdc class makes a ConfigManager look like
 * an hardware::EegAdc.
 */

class EegAdc : public hardware::EegAdc
{
    Q_OBJECT
public:
    EegAdc(ConfigManager *config, QObject *parent = 0) :
        hardware::EegAdc(parent), config(config)
    { }

public:
    uint nChannels() const override
    { return config->get("eeg", "nChannels").toUInt(); }
    uint bytesPerChunk() const override
    { return config->get("eeg", "bytesPerChunk").toUInt(); }
    double vref() const override
    { return config->get("eeg", "vref").toDouble(); }
    uint samplesPerChunk() const override
    { return config->get("eeg", "samplesPerChunk").toUInt(); }
    SampleRate sampleRate() const override
    { return SampleRate(config->get("eeg", "sampleRate").toInt()); }
    bool useRefElec() const override
    { return config->get("eeg", "useRefElec").toBool(); }
    bool enableTestSignal() const override
    { return config->get("eeg", "enableTestSignal").toBool(); }
    LeadOffFreq leadOffFreq() const override
    { return LeadOffFreq(config->get("eeg", "leadOffFreq").toInt()); }
    LeadOffMag leadOffMag() const override
    { return LeadOffMag(config->get("eeg", "leadOffMag").toInt()); }
    bool leadOffSensePos() const override
    { return config->get("eeg", "leadOffSensePos").toBool(); }
    bool leadOffSenseNeg() const override
    { return config->get("eeg", "leadOffSenseNeg").toBool(); }

    hardware::EegChannel *channel(uint i) override
    {
        if (_channels.empty()) {
            uint n = nChannels();
            for (uint i = 0; i < n; i++)
                _channels.append(new EegChannel(i, config, this));
        }
        return _channels.at(i);
    }

    void setSamplesPerChunk(uint samples) override { Q_UNUSED(samples) }
    void setSampleRate(SampleRate rate) override { Q_UNUSED(rate) }
    void setUseRefElec(bool use) override { Q_UNUSED(use) }
    void setEnableTestSignal(bool enable) override { Q_UNUSED(enable) }
    void setLeadOffFreq(LeadOffFreq freq) override { Q_UNUSED(freq) }
    void setLeadOffMag(LeadOffMag mag) override { Q_UNUSED(mag) }
    void setLeadOffSensePos(bool enable) override { Q_UNUSED(enable) }
    void setLeadOffSenseNeg(bool enable) override { Q_UNUSED(enable) }

public slots:
    void start() override { }
    void stop() override { }
    void reset() override { }
    void setAllChannels(const QVariantMap &properties) override
    { Q_UNUSED(properties) }

private:
    ConfigManager *config;
    QList<config::EegChannel*> _channels;
};


/*!
 * \brief The Battery class makes a ConfigManager look like
 * a hardware::Battery.
 */

class Battery : public hardware::Battery
{
    Q_OBJECT
public:
    Battery(ConfigManager *config, QObject *parent = 0) :
        hardware::Battery(parent), config(config)
    { }

public:
    double lowThresh() const override
    { return config->get("battery", "lowThresh").toDouble(); }
    double criticalThresh() const override
    { return config->get("battery", "criticalThresh").toDouble(); }
    bool isLow() const override
    { return config->get("battery", "isLow").toBool(); }
    double voltage() const override
    { return config->get("battery", "voltage").toDouble(); }
    void setLowThresh(double value) override { Q_UNUSED(value) }

private:
    ConfigManager *config;
};


/*!
 * \brief The Device class makes a ConfigManager look like
 * a hardware::Device.
 */

class Device : public hardware::Device
{
    Q_OBJECT
public:
    Device(ConfigManager *config, QObject *parent = 0) :
        hardware::Device(parent), config(config),
        _eeg(new EegAdc(config, this)),
//        _camera(new Camera(config, this)),
        _imu(new Imu(config, this)),
        _battery(new Battery(config, this))
    { }

public:
    hardware::EegAdc *eeg() override { return _eeg; }
    hardware::Camera *camera() override { return nullptr; }
    hardware::Imu *imu() override { return _imu; }
    hardware::Battery *battery() override { return _battery; }

public slots:
    bool isAccessible() const override { return true; }
    void setClientAddress(const QString &address) override { Q_UNUSED(address) }
    void startStreaming() override { }
    void stopStreaming() override { }

private:
    ConfigManager *config;
    config::EegAdc *_eeg;
//    offline::Camera *_camera;
    config::Imu *_imu;
    config::Battery *_battery;
};

}}} // namespace elapse::client::config

#endif // CONFIGPROXIES_H
