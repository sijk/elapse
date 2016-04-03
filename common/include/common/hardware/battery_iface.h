#ifndef IFACE_BATTERY_H
#define IFACE_BATTERY_H

#include <QObject>

namespace elapse { namespace hardware {

/*!
 * \brief The Battery interface exposes the device's battery and power switch.
 * \headerfile common/hardware/battery_iface.h
 */

class Battery : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double lowThresh READ lowThresh WRITE setLowThresh)
    Q_PROPERTY(double criticalThresh READ criticalThresh)
    Q_PROPERTY(bool isLow READ isLow NOTIFY batteryLow)
    Q_PROPERTY(double voltage READ voltage)

public:
    /*!
     * Create a Battery as a child of the given \a parent.
     */
    explicit Battery(QObject *parent = 0) : QObject(parent) {}

    /*!
     * \return the battery voltage at which the batteryLow() signal will
     * be emitted, in volts.
     */
    virtual double lowThresh() const = 0;

    /*!
     * Set the low battery threshold to \a value volts.
     */
    virtual void setLowThresh(double value) = 0;

    /*!
     * \return the battery voltage at which the batteryCritical() signal will
     * be emitted, in volts.
     */
    virtual double criticalThresh() const = 0;

    /*!
     * \return whether the battery has crossed the low voltage threshold.
     */
    virtual bool isLow() const = 0;

    /*!
     * \return the last measured battery voltage in volts.
     */
    virtual double voltage() const = 0;

signals:
    /*!
     * Emitted when the battery voltage drops below lowThresh().
     * Indicates that the device should be powered off soon.
     */
    void batteryLow();

    /*!
     * Emitted when the battery voltage is critically low.
     * Indicates that the device must be shut down and powered off immediately.
     */
    void batteryCritical();

    /*!
     * Emitted when the power switch is switched off.
     * Indicates that the device must be shut down and powered off.
     */
    void switchedOff();
};

}} // namespace elapse::hardware

#endif // IFACE_BATTERY_H
