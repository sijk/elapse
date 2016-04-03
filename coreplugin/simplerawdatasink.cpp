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

#include <QDateTime>
#include <QFileDialog>
#include <QSettings>
#include <QxtLogger>
#include "simplerawdatasink.h"

namespace elapse { namespace coreplugin {

static const QString dataDirKey("plugins/core/simplerawdatasink/dataDir");

/*!
 * Create a new SimpleRawDataSink.
 */
SimpleRawDataSink::SimpleRawDataSink()
{
    dataDir = QSettings().value(dataDirKey).toString();
}

/*!
 * Create a file named with the current date and time.
 */
bool SimpleRawDataSink::startSaving()
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
    QString fileName = dataDir.absoluteFilePath(dateTime + ".dat");
    file.setFileName(fileName);

    if (file.exists())
        return false;

    if (!file.open(QIODevice::WriteOnly))
        return false;

    stream.setDevice(&file);
    time.start();
    return true;
}

/*!
 * Close the current data file.
 */
void SimpleRawDataSink::stopSaving()
{
    stream.setDevice(nullptr);
    file.close();
}

/*!
 * \return true if getCaptureInfo() hasn't been called or if the chosen data
 * directory doesn't exist.
 */
bool SimpleRawDataSink::needsNewCaptureInfo()
{
    return dataDir == QDir() || !dataDir.exists();
}

/*!
 * Show a dialog for the user to select the directory into which the
 * data files will be saved.
 * \return whether the user selected a valid directory.
 */
bool SimpleRawDataSink::getCaptureInfo()
{
    QString dir = getDirectory();
    if (dir.isEmpty())
        return false;

    dataDir.setPath(dir);
    dataDir.makeAbsolute();
    if (dataDir.exists()) {
        QSettings().setValue(dataDirKey, dataDir.absolutePath());
        return true;
    }

    return false;
}

// Implemented as a virtual method for testability
QString SimpleRawDataSink::getDirectory() const
{
    return QFileDialog::getExistingDirectory();
}

/*!
 * Dump the \a config to the currently-open data file via a QDataStream.
 */
void SimpleRawDataSink::saveDeviceConfig(const QMap<QString, QVariantMap> &config)
{
    Q_ASSERT(file.isOpen());
    stream << config;
}

/*!
 * Dump the \a signalType and \a data to the currently-open data file
 * via a QDataStream.
 */
void SimpleRawDataSink::saveData(data::Signal::Type signalType,
                                 QByteArray data)
{
    Q_ASSERT(file.isOpen());
    stream << time.restart() << signalType << data;
}

}} // namespace elapse::coreplugin
