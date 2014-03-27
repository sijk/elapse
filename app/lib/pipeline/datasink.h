#ifndef DATASINK_H
#define DATASINK_H

#include <QObject>
#include <QPointer>
#include "elapse/sampletypes.h"

namespace elapse { class DataSinkDelegate; }


/*!
 * \brief The DataSink class provides the ability to save data to disk.
 *
 * The Pipeline has one DataSink. The DataSink watches for data at each
 * connection between elements in the Pipeline. When data passes through
 * these connections, the DataSink passes that data on to a
 * elapse::DataSinkDelegate which handles the actual saving to disk.
 *
 * By default, the DataSink will not pass any data to its
 * elapse::DataSinkDelegate. You must individually enable which types of
 * data (raw bytes, Sample%s, FeatureVector%s, CognitiveState) you want
 * to be saved by calling the setSaveXXX() methods.
 *
 * \ingroup signal-pipeline
 */

class DataSink : public QObject
{
    Q_OBJECT
public:
    explicit DataSink(QObject *parent = nullptr);

    void setDelegate(elapse::DataSinkDelegate *delegate);

    bool start();
    void stop();

    void setSaveData(bool save);
    void setSaveSamples(bool save);
    void setSaveFeatureVectors(bool save);
    void setSaveCognitiveState(bool save);

public slots:
    void onData(QByteArray data);
    void onSample(elapse::SamplePtr sample);
    void onFeatureVector(elapse::FeatureVector featureVector);
    void onCognitiveState(elapse::CognitiveState state);

private:
    bool saveDataEnabled;
    bool saveSamplesEnabled;
    bool saveFeaturesEnabled;
    bool saveCogStateEnabled;

    QPointer<elapse::DataSinkDelegate> delegate;
};


#endif // DATASINK_H
