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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QScopedPointer>
class QByteArray;

namespace elapse { namespace elements {

class OfflineDataSource;
class OfflineDataSourcePrivate;


/*!
 * \brief The DataSource interface is implemented by elements that provide
 * data from the device, either live or from a file.
 *
 * This data may be received live from the device over the network, or loaded
 * from a file.
 *
 * Each Pipeline has one DataSource which provides data to several
 * SampleDecoder%s.
 *
 * \headerfile elapse/elements/datasource.h
 * \ingroup pipeline-elements
 * \sa OfflineDataSource
 */

class DataSource : public QObject
{
    Q_OBJECT
public:
    /*! \return whether this is an OfflineDataSource. */
    bool isOfflineSource() const;

signals:
    /*! Emitted when video \a data is available. */
    void videoReady(QByteArray data);

    /*! Emitted when EEG \a data is available. */
    void eegReady(QByteArray data);

    /*! Emitted when IMU \a data is available. */
    void imuReady(QByteArray data);

    /*!
     * Emitted when the DataSource produces its first piece of data.
     * \sa start()
     */
    void started();

    /*!
     * Emitted after the DataSource produces its last piece of data.
     */
    void finished();

    /*!
     * Emitted when an error occurs. The \a message is a human-readable string
     * which should be useful for debugging the error.
     */
    void error(QString message);

public slots:
    /*!
     * Start producing data. DataSource%s must implement this method and
     * ensure that started() is emitted at the appropriate time.
     */
    virtual void start() = 0;

    /*!
     * Stop producing data.
    */
    virtual void stop() = 0;
};


/*!
 * \brief The ConfigManager interface provides access to configuration values
 * from some data store.
 *
 * The data is arranged as properties grouped into sub-systems, both
 * identified by strings.
 *
 * \headerfile elapse/elements/datasource.h
 */

class ConfigManager
{
public:
    /*!
     * \return the value of the given \a property of the \a subSystem.
     */
    virtual QVariant get(const QString &subSystem, const QString &property) = 0;
};


/*!
 * \brief The OfflineDataSource class is the base class for elements that load
 * data from disk, rather than from the device itself.
 *
 * OfflineDataSource%s implement the ConfigManager interface and expose this
 * interface to D-Bus via the elapse::client::config classes.
 *
 * \headerfile elapse/elements/datasource.h
 * \ingroup pipeline-elements
 */

class OfflineDataSource : public DataSource, public ConfigManager
{
    Q_OBJECT
public:
    OfflineDataSource();
    ~OfflineDataSource();

protected:
    /*!
     * Expose the ConfigManager interface to D-Bus.
     *
     * \note This method \e must be called as the last statement in the
     * constructor of OfflineDataSource subclasses.
     */
    void exposeDeviceInterface();

private:
    QScopedPointer<OfflineDataSourcePrivate> d_ptr;
    Q_DECLARE_PRIVATE(OfflineDataSource)
};

}} // namespace elapse::elements

#endif // DATASOURCE_H
