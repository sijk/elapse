#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
class QByteArray;

namespace elapse {

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
 * \ingroup pipeline-elements
 * \sa OfflineDataSource
 */

class DataSource : public QObject
{
    Q_OBJECT
public:
    /*! Construct a new DataSource as a child of the given \a parent. */
    explicit DataSource(QObject *parent = nullptr) : QObject(parent) {}

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
 * interface to D-Bus via the ::config classes.
 */

class OfflineDataSource : public DataSource, public ConfigManager
{
    Q_OBJECT
public:
    explicit OfflineDataSource(QObject *parent = nullptr);
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
    OfflineDataSourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(OfflineDataSource)
};

} // namespace elapse

#endif // DATASOURCE_H
