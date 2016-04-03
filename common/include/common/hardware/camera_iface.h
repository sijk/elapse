#ifndef IFACE_CAMERA_H
#define IFACE_CAMERA_H

#include <QObject>

namespace elapse { namespace hardware {

/*!
 * \brief The Camera interface exposes the eye video camera.
 * \headerfile common/hardware/camera_iface.h
 */

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0) : QObject(parent) {}
};

}} // namespace elapse::hardware

#endif // IFACE_CAMERA_H
