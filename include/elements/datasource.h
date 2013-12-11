#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
class QByteArray;


/*!
 * \brief The DataSource class is the base class for elements that receive data
 * from the device over the network.
 *
 * Each Pipeline has one DataSource which provides data to several
 * \ref SampleDecoder "SampleDecoders".
 *
 * \ingroup pipeline-elements
 */

class DataSource : public QObject
{
    Q_OBJECT

    /*! The device's host name. */
    Q_PROPERTY(QString host MEMBER _host)

public:
    /*! Construct a new DataSource as a child of the given \a parent. */
    explicit DataSource(QObject *parent = nullptr) : QObject(parent) {}

    /*! Destroy this DataSource. */
    virtual ~DataSource() {}

signals:
    /*! Emitted when video \a data arrives from the device. */
    void videoReady(QByteArray data);

    /*! Emitted when EEG \a data arrives from the device. */
    void eegReady(QByteArray data);

    /*! Emitted when IMU \a data arrives from the device. */
    void imuReady(QByteArray data);

    /*!
     * Emitted when the DataSource has succesfully connected to the device
     * and is ready to receive data.
     * \sa start()
     */
    void started();

    /*!
     * Emitted when an error occurs. The \a message is a human-readable string
     * which should be useful for debugging the error.
     */
    void error(QString message);

public slots:
    /*!
     * Start receiving data from the device. Classes inheriting from DataSource
     * must implement this method and ensure that started() is emitted at the
     * appropriate time.
     * \sa started()
    */
    virtual void start() = 0;

    /*!
     * Stop receiving data from the device. Classes inheriting from DataSource
     * must implement this method.
    */
    virtual void stop() = 0;

protected:
    QString _host;
};

#endif // DATASOURCE_H
