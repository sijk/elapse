#ifndef DATASINKDELEGATE_H
#define DATASINKDELEGATE_H

#include <QObject>
#include "elapse/sampletypes.h"

namespace elapse {

/*!
 * \brief The DataSinkDelegate interface is implemented by classes that save
 * the data flowing through the pipeline to disk.
 *
 * A DataSinkDelegate can save data at any point in the pipeline — raw bytes,
 * Sample%s, FeatureVector%s, and CognitiveState. Note, however, that any given
 * DataSinkDelegate implementation does not necessarily support saving all of
 * these types of data; if you try to save an unsupported data type a warning
 * will be logged at runtime.
 *
 * Associated with a DataSinkDelegate is the concept of \e "capture info".
 * This allows DataSinkDelegate implementations to store arbitrary metadata
 * alongside the saved data. For more details, see getCaptureInfo() and
 * needsNewCaptureInfo().
 *
 * \headerfile elapse/elements/datasinkdelegate.h
 * \ingroup pipeline-elements
 */

class DataSinkDelegate : public QObject
{
    Q_OBJECT
public:
    explicit DataSinkDelegate(QObject *parent = nullptr);

    /*!
     * Start saving data. This may involve, for example, creating a new file
     * named according to the current capture info.
     * \return whether starting succeeded.
     */
    virtual bool start() = 0;

    /*!
     * Stop saving data. This may involve, for example, closing a file.
     */
    virtual void stop() = 0;

    /*!
     * \return whether this DataSinkDelegate needs getCaptureInfo() to be
     * called before the next call to start().
     */
    virtual bool needsNewCaptureInfo() = 0;

public slots:
    /*!
     * Allow the user to set any metadata about the data that will be captured
     * the next time start() is called. This will normally be done by
     * presenting a dialog box to the user.
     *
     * The metadata required is up to each DataSinkDelegate implementation.
     * For a simple DataSinkDelegate that dumps raw data to a file, this
     * might be a format string that will be used to generate a filename
     * from the date/time at which data capture starts. For a more complex
     * DataSinkDelegate that saves Sample%s to GDF, this might include
     * information like a subject ID, recording conditions, whether the
     * user is sleep-deprived, and so on.
     *
     * If a DataSinkDelegate needsNewCaptureInfo(), getCaptureInfo() will be
     * called before start(). If this method returns \c false, start() will
     * not be called.
     *
     * \return whether valid capture info was obtained.
     */
    virtual bool getCaptureInfo() = 0;

public:
    /*!
     * Called when the device's current \a config needs to be saved.
     */
    virtual void saveDeviceConfig(const QMap<QString, QVariantMap> &config) = 0;

    /*!
     * Called when there is raw \a data of the given \a signalType to be saved.
     */
    virtual void saveData(Signal::Type signalType, QByteArray data);

    /*!
     * Called when there is a \a sample of the given \a signalType to be saved.
     */
    virtual void saveSample(Signal::Type signalType, SamplePtr sample);

    /*!
     * Called when there is a \a featureVector to be saved.
     *
     * Derived classes may inspect FeatureVector::signalType to find the
     * type of the signal from which the \a featureVector was extracted.
     */
    virtual void saveFeatureVector(FeatureVector featureVector);

    /*!
     * Called when there is a new cognitive \a state to be saved.
     */
    virtual void saveCognitiveState(CognitiveState state);
};

} // namespace elapse

#endif // DATASINKDELEGATE_H
