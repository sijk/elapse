#ifndef IFACE_DEVICE_H
#define IFACE_DEVICE_H

#include <QObject>

namespace elapse {

/*!
 * \brief Interfaces to the device's sub-systems.
 */

namespace hardware {

class EegAdc;
class Camera;
class Imu;
class Battery;


/*!
 * \brief The Device interface exposes the top-level functionality of the
 * Elapse device.
 *
 * It also provides access to all of the device's subsystems.
 *
 * \headerfile common/hardware/device_iface.h
 */

class Device : public QObject
{
    Q_OBJECT
public:
    /*! Construct a new Device with the given \a parent. */
    explicit Device(QObject *parent = 0) : QObject(parent) {}

    /*! \return the EEG device. */
    virtual EegAdc *eeg() = 0;

    /*! \return the camera. */
    virtual Camera *camera() = 0;

    /*! \return the IMU. */
    virtual Imu *imu() = 0;

    /*! \return the battery monitor. */
    virtual Battery *battery() = 0;

public slots:
    /*! Check whether the caller can access this Device. */
    virtual bool isAccessible() const = 0;

    /*! Set the \a address to which the Device should send data. */
    virtual void setClientAddress(const QString &address) = 0;

    /*! Start streaming data from this Device. */
    virtual void startStreaming() = 0;

    /*! Stop streaming data from this Device. */
    virtual void stopStreaming() = 0;

signals:
    /*!
     * \brief Emitted when any error occurs.
     *
     * The \a msg is a meaningful human-readable description of the error.
     */
    void error(QString msg);
};

}} // namespace elapse::hardware

#endif // IFACE_DEVICE_H
