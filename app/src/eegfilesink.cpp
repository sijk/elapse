#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QxtLogger>
#include "eegfilesink.h"


EegFileSink::EegFileSink(QObject *parent) :
    QObject(parent),
    recording(false)
{
}

EegFileSink::~EegFileSink()
{
    if (recording) {
        qxtLog->warning("Emergency closing eeg file sink!");
        stopRecording();
    }
}

void EegFileSink::startRecording()
{
    Q_ASSERT(!recording);

    // Create output directory
    QDir dataDir(qApp->applicationDirPath());
    dataDir.cdUp();
    if (!dataDir.exists("data")) {
        if (!dataDir.mkdir("data")) {
            qxtLog->error("Error creating data directory!");
            return;
        }
    }
    dataDir.cd("data");

    // Create output file
    QDateTime now = QDateTime::currentDateTime();
    QString fname = now.toString("yyyyMMdd-hhmmss") + ".eeg";
    file = new QFile(dataDir.filePath(fname));

    Q_ASSERT_X(!file->exists(), "EegFileSink", "file already exists");

    if (!file->open(QIODevice::WriteOnly)) {
        qxtLog->error("Error opening", file->fileName(), "for writing.");
        return;
    }

    recording = true;
    emit recordingStarted(fname);
}

void EegFileSink::onData(QByteArray bytes)
{
    Q_ASSERT_X(recording, "EegFileSink", "received data when not recording");
    file->write(bytes);
}

void EegFileSink::stopRecording()
{
    Q_ASSERT(recording);

    emit recordingFinished(file->fileName());
    recording = false;
    delete file;
}
