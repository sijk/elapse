#ifndef IFACE_IMU_H
#define IFACE_IMU_H

#include <QObject>

namespace elapse { namespace hardware {

/*!
 * \brief The Imu interface exposes the 6-axis inertial measurement unit.
 * \headerfile common/hardware/imu_iface.h
 */

class Imu : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint sampleRate READ sampleRate WRITE setSampleRate)
    Q_PROPERTY(AccRange accRange READ accRange WRITE setAccRange)
    Q_PROPERTY(GyrRange gyrRange READ gyrRange WRITE setGyrRange)
    Q_ENUMS(AccRange GyrRange)

public:
    /*!
     * Create an Imu as a child of the given \a parent.
     */
    explicit Imu(QObject *parent = 0) : QObject(parent) {}

    /*!
     * \return the current IMU sampling rate in Hz.
     */
    virtual uint sampleRate() const = 0;

    /*!
     * Set the IMU sampling rate in \a hz.
     */
    virtual void setSampleRate(uint hz) = 0;

    /*!
     * Valid accelerometer full-scale ranges in \e g.
     */
    enum AccRange { G2 = 2, G4 = 4, G8 = 8, G16 = 16 };

    /*!
     * \return the current full-scale accelerometer range in \e g.
     */
    virtual AccRange accRange() const = 0;

    /*!
     * Set the full-scale accelerometer range in \e g.
     */
    virtual void setAccRange(AccRange range) = 0;

    /*!
     * Valid gyroscope full-scale ranges in degrees per second.
     */
    enum GyrRange { DPS250 = 250, DPS500 = 500, DPS2000 = 2000 };

    /*!
     * \return the current full-scale gyroscope range in degrees per second.
     */
    virtual GyrRange gyrRange() const = 0;

    /*!
     * Set the full-scale gyroscope range in degrees per second.
     */
    virtual void setGyrRange(GyrRange range) = 0;

public slots:
    /*!
     * Start taking measurements.
     */
    virtual void start() = 0;

    /*!
     * Stop taking measurements.
     */
    virtual void stop() = 0;
};

}} // namespace elapse::hardware

#endif // IFACE_IMU_H
