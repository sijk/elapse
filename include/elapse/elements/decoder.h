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

#ifndef DECODER_H
#define DECODER_H

#include <QObject>
#include "elapse/datatypes.h"

class QByteArray;

namespace elapse { namespace elements {

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

}} // namespace elapse::elements

#endif // DECODER_H
