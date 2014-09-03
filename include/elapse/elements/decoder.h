#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include "elapse/sampletypes.h"

class QByteArray;

namespace elapse {

/*!
 * \brief The SampleDecoder interface is implemented by elements that decode a
 * QByteArray to one or more Sample%s.
 *
 * Each Pipeline has several SampleDecoder%s: one per Signal::Type.
 *
 * You are unlikely to need to implement your own SampleDecoder%s since the
 * ones provided by the \ref core-plugin "core plugin" are already capable
 * of decoding the data streams from the device.
 *
 * \headerfile elapse/elements/decoder.h
 * \ingroup pipeline-elements
 */

class SampleDecoder : public QObject
{
    Q_OBJECT
signals:
    /*! Emitted when a \a sample has been decoded. */
    void newSample(elapse::data::SamplePtr sample);

    /*!
     * Emitted when an error occurs. The \a message is a human-readable string
     * which should be useful for debugging the error.
     */
    void error(QString message);

public slots:
    /*!
     * Configure this SampleDecoder to match the given hardware \a config.
     */
    virtual void configure(QMap<QString, QVariantMap> config) { Q_UNUSED(config); }

    /*!
     * Called when starting the Pipeline. Subclasses may override this method
     * to do any initialisation they require.
     */
    virtual void start() {}

    /*!
     * Called when stopping the Pipeline. Subclasses may override this method
     * to do any cleanup they require.
     */
    virtual void stop() {}

    /*!
     * Executed when \a data is available for decoding. Classes that inherit
     * from SampleDecoder must implement this slot and ensure that newSample()
     * is emitted for every decoded sample. Note that there is not necessarily
     * a one-to-one mapping between the incoming \a data and outgoing Sample%s.
     */
    virtual void onData(QByteArray data) = 0;
};

} // namespace elapse

#endif // DECODER_H
