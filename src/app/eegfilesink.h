#ifndef EEGFILESINK_H
#define EEGFILESINK_H

#include <QObject>

class QFile;

class EegFileSink : public QObject
{
    Q_OBJECT
public:
    explicit EegFileSink(QObject *parent = 0);
    ~EegFileSink();

signals:
    void recordingStarted(const QString &fname);
    void recordingFinished(const QString &fname);

public slots:
    void startRecording();
    void onData(const QByteArray &bytes);
    void stopRecording();

private:
    QFile *file;
    bool recording;
};

#endif // EEGFILESINK_H
