#ifndef DBUS_PATHS_H
#define DBUS_PATHS_H

#include <QString>

namespace elapse { namespace common {

/*!
 * \brief D-Bus definitions common to both the client and server.
 */

namespace dbus {

const QString service     = "org.nzbri.elapse";
const QString rootPath    = "/elapse";
const QString batteryPath = rootPath + "/battery";
const QString eegPath     = rootPath + "/eeg";
const QString eegChanPath = eegPath + "/channel/%1";
const QString imuPath     = rootPath + "/imu";

}}}

#endif // DBUS_PATHS_H
