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

#ifndef EEGDECODER_H
#define EEGDECODER_H

#include <QScopedPointer>
#include <elapse/elements/decoder.h>
#include <elapse/displayable.h>

namespace elapse { namespace coreplugin {

class EegDecoderPrivate;


/*!
 * \brief The EegDecoder class decodes the byte stream from the EEG hardware.
 *
 * \ingroup core-plugin
 */

class EegDecoder : public elements::SampleDecoder,
                   public elapse::Displayable
{
    Q_OBJECT
    Q_CLASSINFO("SignalType", "EEG")

public:
    Q_INVOKABLE EegDecoder();
    ~EegDecoder();

    void configure(QMap<QString, QVariantMap> config) override;

    QWidget *getWidget() override;

public slots:
    void onData(QByteArray data) override;

private:
    const QScopedPointer<EegDecoderPrivate> d_ptr;
    Q_DECLARE_PRIVATE(EegDecoder)
};

}} // namespace elapse::coreplugin

#endif // EEGDECODER_H
