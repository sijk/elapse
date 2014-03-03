#ifndef EEGFILESINK_H
#define EEGFILESINK_H

#include <QObject>

class QFile;

class EegFileSink : public QObject
{
    Q_OBJECT
public:
    explicit EegFileSink(QObject *parent = nullptr);
    ~EegFileSink();

signals:
    void recordingStarted(QString fname);
    void recordingFinished(QString fname);

public slots:
    void startRecording();
    void onData(QByteArray bytes);
    void stopRecording();

private:
    QFile *file;
    bool recording;
};

#endif // EEGFILESINK_H
