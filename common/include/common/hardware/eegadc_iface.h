#ifndef IFACE_EEGADC_H
#define IFACE_EEGADC_H

#include <QObject>
#include "common/qenum-utils.h"

namespace elapse { namespace hardware {

class EegChannel;


/*!
 * \brief The EegAdc interface exposes the EEG acquisition device.
 * \headerfile common/hardware/eegadc_iface.h
 */

class EegAdc : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint nChannels READ nChannels)
    Q_PROPERTY(uint bytesPerChunk READ bytesPerChunk)
    Q_PROPERTY(uint samplesPerChunk READ samplesPerChunk WRITE setSamplesPerChunk)
    Q_PROPERTY(double vref READ vref)
    Q_PROPERTY(SampleRate sampleRate READ sampleRate WRITE setSampleRate)
    Q_PROPERTY(bool useRefElec READ useRefElec WRITE setUseRefElec)
    Q_PROPERTY(bool enableTestSignal READ enableTestSignal WRITE setEnableTestSignal)
    Q_PROPERTY(LeadOffFreq leadOffFreq READ leadOffFreq WRITE setLeadOffFreq)
    Q_PROPERTY(LeadOffMag leadOffMag READ leadOffMag WRITE setLeadOffMag)
    Q_PROPERTY(bool leadOffSensePos READ leadOffSensePos WRITE setLeadOffSensePos)
    Q_PROPERTY(bool leadOffSenseNeg READ leadOffSenseNeg WRITE setLeadOffSenseNeg)
    Q_ENUMS(SampleRate LeadOffFreq LeadOffMag)

public:
    /*!
     * Construct an EegAdc as a child of the given \a parent.
     */
    explicit EegAdc(QObject *parent = 0) : QObject(parent) {}

    /*!
     * \return the channel at index \a i.
     */
    virtual EegChannel *channel(uint i) = 0;

    /*!
     * \return the number of channels this device has.
     */
    virtual uint nChannels() const = 0;

    /*!
     * \return the number of bytes in each chunk of data read from the device.
     */
    virtual uint bytesPerChunk() const = 0;

    /*!
     * \return the current ADC reference voltage in microvolts.
     */
    virtual double vref() const = 0;

    /*!
     * \return the number of samples in each chunk of data read from the device.
     */
    virtual uint samplesPerChunk() const = 0;

    /*!
     * Set the number of \a samples in each chunk of data read from the device.
     */
    virtual void setSamplesPerChunk(uint samples) = 0;

    /*!
     * Valid ADC sampling rates
     */
    enum SampleRate { Hz16k = 16000, Hz8k = 8000, Hz4k = 4000, Hz2k = 2000,
                      Hz1k = 1000, Hz500 = 500, Hz250 = 250 };

    /*!
     * \return the current ADC sampling rate in Hz.
     */
    virtual SampleRate sampleRate() const = 0;

    /*!
     * Set the current ADC sampling \a rate in Hz.
     */
    virtual void setSampleRate(SampleRate rate) = 0;

    /*!
     * \return whether to mux the reference electrode (\c SRB1) to the negative
     * terminal of all of the input amplifiers.
     */
    virtual bool useRefElec() const = 0;

    /*!
     * Set whether to mux the reference electrode (\c SRB1) to the negative
     * terminal of all of the input amplifiers.
     */
    virtual void setUseRefElec(bool use) = 0;

    /*!
     * \return whether the internal test signal generator is enabled.
     */
    virtual bool enableTestSignal() const = 0;

    /*!
     * Set whether to \a enable the internal test signal generator.
     */
    virtual void setEnableTestSignal(bool enable) = 0;

    /*!
     * Lead-off detection signal frequency.
     */
    enum LeadOffFreq { DC = 0, AC_8 = 8, AC_31 = 31, AC_QUARTER_FDR = 62 };

    /*!
     * \return the current lead-off detection signal frequency.
     */
    virtual LeadOffFreq leadOffFreq() const = 0;

    /*!
     * Set the lead-off detection signal \a freq.
     */
    virtual void setLeadOffFreq(LeadOffFreq freq) = 0;

    /*!
     * Lead-off detection signal current magnitude.
     */
    enum LeadOffMag { nA_6 = 6, nA_24 = 24, uA_6 = 6000, uA_24 = 24000 };

    /*!
     * \return the lead-off detection signal current magnitude.
     */
    virtual LeadOffMag leadOffMag() const = 0;

    /*!
     * Set the lead-off detection signal \a mag.
     */
    virtual void setLeadOffMag(LeadOffMag mag) = 0;

    /*!
     * \return whether to monitor the lead-off status of positive electrodes.
     */
    virtual bool leadOffSensePos() const = 0;

    /*!
     * Set whether to \a enable lead-off status monitoring for positive
     * electrodes.
     */
    virtual void setLeadOffSensePos(bool enable) = 0;

    /*!
     * \return whether to monitor the lead-off status of negative electrodes.
     */
    virtual bool leadOffSenseNeg() const = 0;

    /*!
     * Set whether to \a enable lead-off status monitoring for negative
     * electrodes.
     */
    virtual void setLeadOffSenseNeg(bool enable) = 0;

public slots:
    /*!
     * \brief Start continuous data capture.
     */
    virtual void start() = 0;

    /*!
     * \brief Stop continuous data capture.
     */
    virtual void stop() = 0;

    /*!
     * \brief Reset the device configuration to its power-on state.
     */
    virtual void reset() = 0;

    /*!
     * Set the given \a properties of every channel.
     */
    virtual void setAllChannels(const QVariantMap &properties) = 0;
};


/*!
 * \brief The EegChannel interface exposes one channel of the EegAdc.
 * \headerfile common/hardware/eegadc_iface.h
 */

class EegChannel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Gain gain READ gain WRITE setGain)
    Q_PROPERTY(QString inputMux READ inputMuxAsString WRITE setInputMux)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)
    Q_ENUMS(Gain InputMux)

public:
    /*!
     * Construct an EegChannel as a child of the given \a parent.
     */
    explicit EegChannel(QObject *parent = 0) : QObject(parent) {}

    /*!
     * ADC input amplifier gain settings.
     */
    enum Gain { x1 = 1, x2 = 2, x4 = 4, x6 = 6, x8 = 8, x12 = 12, x24 = 24 };

    /*!
     * \return the gain of this channel's input amplifier.
     */
    virtual Gain gain() const = 0;

    /*!
     * Set the gain of this channel's input amplifier.
     */
    virtual void setGain(Gain gain) = 0;

    /*!
     * ADC input multiplexer configurations.
     */
    enum InputMux { Normal, InputShort, BiasMeas, MVDD, Temp, Test,
                    BiasDrP, BiasDrN };

    /*!
     * \return this channel's input mux configuration.
     */
    virtual InputMux inputMux() const = 0;

    /*!
     * Set this channel's input mux configuration.
     */
    virtual void setInputMux(InputMux mux) = 0;

    /*!
     * \return this channel's input mux configuration as a string.
     */
    QString inputMuxAsString() const
    {
        return enumToString<EegChannel>("InputMux", inputMux());
    }

    /*!
     * Set this channel's input mux configuration.
     */
    void setInputMux(QString mux)
    {
        int value = stringToEnum<EegChannel>("InputMux", mux);
        setInputMux(InputMux(value));
    }

    /*!
     * \return whether this channel is enabled.
     */
    virtual bool enabled() const = 0;

    /*!
     * Enable/disable this channel.
     */
    virtual void setEnabled(bool enabled) = 0;
};

}} // namespace elapse::hardware

#endif // IFACE_EEGADC_H
