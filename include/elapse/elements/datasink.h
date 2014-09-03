#ifndef DATASINK_H
#define DATASINK_H

#include <QObject>
#include "elapse/datatypes.h"


namespace elapse {

/*!
 * \brief The DataSink class provides the ability to save data to disk.
 *
 * The DataSink watches for data at each connection between elements in
 * the Pipeline. When data passes through these connections, the DataSink
 * calls its virtual \c saveXXX() methods which handle the actual saving
 * to disk.
 *
 * Each Pipeline has one DataSink.
 *
 * \headerfile elapse/elements/datasink.h
 * \ingroup pipeline-elements
 */

class DataSink : public QObject
{
    Q_OBJECT

public:
    bool start();
    void stop();

public slots:
    void onEegData(QByteArray data);
    void onVideoData(QByteArray data);
    void onImuData(QByteArray data);
    void onEegSample(elapse::data::SamplePtr sample);
    void onVideoSample(elapse::data::SamplePtr sample);
    void onImuSample(elapse::data::SamplePtr sample);
    void onFeatureVector(elapse::data::FeatureVector featureVector);
    void onCognitiveState(elapse::data::CognitiveState state);

    /*!
     * Allow the user to set any metadata about the data that will be captured
     * from the device. This will normally be done by presenting a dialog box
     * to the user.
     *
     * The metadata required is up to each DataSink implementation.
     * For a simple DataSink that dumps raw data to a file, this
     * might be a format string that will be used to generate a filename
     * from the date/time at which data capture starts. For a more complex
     * DataSink that saves Sample%s to GDF, this might include
     * information like a subject ID, recording conditions, whether the
     * user is sleep-deprived, and so on.
     *
     * If a DataSink needsNewCaptureInfo(), getCaptureInfo() will be
     * called before start(). If this method returns \c false, start() will
     * not be called.
     *
     * \return whether valid capture info was obtained.
     */
    virtual bool getCaptureInfo() = 0;

protected:
    /*!
     * \return whether getCaptureInfo() needs to be called before the next
     * call to start().
     */
    virtual bool needsNewCaptureInfo() = 0;

    /*!
     * Start saving data. This may involve, for example, creating a new file
     * named according to the current capture info.
     * \return whether starting succeeded.
     */
    virtual bool startSaving() = 0;

    /*!
     * Stop saving data. This may involve, for example, closing a file.
     */
    virtual void stopSaving() = 0;

    /*!
     * Called when there is raw \a data of the given \a signalType to be saved.
     */
    virtual void saveData(data::Signal::Type signalType, QByteArray data);

    /*!
     * Called when there is a \a sample of the given \a signalType to be saved.
     */
    virtual void saveSample(data::Signal::Type signalType, data::SamplePtr sample);

    /*!
     * Called when there is a \a featureVector to be saved.
     *
     * Derived classes may inspect FeatureVector::signalType to find the
     * type of the signal from which the \a featureVector was extracted.
     */
    virtual void saveFeatureVector(data::FeatureVector featureVector);

    /*!
     * Called when there is a new cognitive \a state to be saved.
     */
    virtual void saveCognitiveState(data::CognitiveState state);

public:
    /*!
     * Called when the device's current \a config needs to be saved.
     */
    virtual void saveDeviceConfig(const QMap<QString, QVariantMap> &config) = 0;

};

} // namespace elapse

#endif // DATASINK_H
