#include <QDateTime>
#include <QFileDialog>
#include <QxtLogger>
#include "simplerawdatasinkdelegate.h"


/*!
 * Create a new SimpleRawDataSinkDelegate as a child of the given \a parent.
 */
SimpleRawDataSinkDelegate::SimpleRawDataSinkDelegate(QObject *parent) :
    DataSinkDelegate(parent)
{
}

/*!
 * Create a file named with the current date and time.
 */
bool SimpleRawDataSinkDelegate::start()
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss");
    QString fileName = dataDir.absoluteFilePath(dateTime + ".dat");
    file.setFileName(fileName);

    if (file.exists())
        return false;

    if (!file.open(QIODevice::WriteOnly))
        return false;

    stream.setDevice(&file);
    return true;
}

/*!
 * Close the current data file.
 */
void SimpleRawDataSinkDelegate::stop()
{
    stream.setDevice(nullptr);
    file.close();
}

/*!
 * \return true if getSessionData() hasn't been called or if the chosen data
 * directory doesn't exist.
 */
bool SimpleRawDataSinkDelegate::needsNewSessionData()
{
    return dataDir == QDir() || !dataDir.exists();
}

/*!
 * Show a dialog for the user to select the directory into which the
 * data files will be saved.
 * \return whether the user selected a valid directory.
 */
bool SimpleRawDataSinkDelegate::getSessionData()
{
    QString dir = getDirectory();
    if (dir.isEmpty())
        return false;

    dataDir.setPath(dir);
    dataDir.makeAbsolute();
    return dataDir.exists();
}

// Implemented as a virtual method for testability
QString SimpleRawDataSinkDelegate::getDirectory() const
{
    return QFileDialog::getExistingDirectory();
}

/*!
 * Dump the \a config to the currently-open data file via a QDataStream.
 */
void SimpleRawDataSinkDelegate::saveDeviceConfig(const QMap<QString, QVariantMap> &config)
{
    Q_ASSERT(file.isOpen());
    stream << config;
}

/*!
 * Dump the \a signalType and \a data to the currently-open data file
 * via a QDataStream.
 */
void SimpleRawDataSinkDelegate::saveData(elapse::Signal::Type signalType,
                                         QByteArray data)
{
    Q_ASSERT(file.isOpen());
    stream << signalType << data;
}

