#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QVariant>
#include <QFile>
#include <QThread>
#include <QxtLogger>
#include <elapse/sampletypes.h>
#include "simplerawdatasource.h"


class DataLoader : public QThread
{
    Q_OBJECT
public:
    DataLoader(SimpleRawDataSourcePrivate *d) : d(d) {}
    void stop() { stopped = true; }

protected:
    void run();

signals:
    void videoReady(QByteArray data);
    void eegReady(QByteArray data);
    void imuReady(QByteArray data);

private:
    SimpleRawDataSourcePrivate *d;
    bool stopped;
};


class SimpleRawDataSourcePrivate
{
public:
    SimpleRawDataSourcePrivate(SimpleRawDataSource *q);

    QWidget *createWidget();
    QWidget *widget;
    QLineEdit *lineEdit;

    bool start();
    void stop();

    QFile file;
    QDataStream stream;
    QMap<QString, QVariantMap> deviceConfig;
    DataLoader loader;
};


/*!
 * Load data from file in a background thread and emit the appropriate
 * fooReady signals. The data is emitted at approximately the same rate
 * as it was originally received.
 */
void DataLoader::run()
{
    stopped = false;

    int dt;
    elapse::Signal::Type signalType;
    QByteArray data;
    bool first = true;

    while (!d->stream.atEnd() && !stopped)
    {
        d->stream >> dt >> (int&)signalType >> data;

        if (first)
            first = false;
        else
            QThread::msleep(dt);

        if (signalType == elapse::Signal::EEG)
            emit eegReady(data);
        else if (signalType == elapse::Signal::VIDEO)
            emit videoReady(data);
        else if (signalType == elapse::Signal::IMU)
            emit imuReady(data);
        else
            Q_UNREACHABLE();
    }
}


SimpleRawDataSourcePrivate::SimpleRawDataSourcePrivate(SimpleRawDataSource *q) :
    widget(nullptr),
    loader(this)
{
    q->connect(&loader, SIGNAL(started()), SIGNAL(started()));
    q->connect(&loader, SIGNAL(finished()), SIGNAL(finished()));
    q->connect(&loader, SIGNAL(videoReady(QByteArray)), SIGNAL(videoReady(QByteArray)));
    q->connect(&loader, SIGNAL(eegReady(QByteArray)), SIGNAL(eegReady(QByteArray)));
    q->connect(&loader, SIGNAL(imuReady(QByteArray)), SIGNAL(imuReady(QByteArray)));
}

QWidget *SimpleRawDataSourcePrivate::createWidget()
{
    widget = new QWidget;
    auto layout = new QHBoxLayout(widget);
    auto label = new QLabel("Data file");
    lineEdit = new QLineEdit;
    auto button = new QPushButton("Browse");
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [=]{
        lineEdit->setText(QFileDialog::getOpenFileName(qApp->activeWindow(),
                          "Open data file", "", "Raw data files (*.dat)"));
    });

    return widget;
}

bool SimpleRawDataSourcePrivate::start()
{
    Q_ASSERT(!file.isOpen());
    file.setFileName(lineEdit->text());
    if (!file.open(QIODevice::ReadOnly))
        return false;
    stream.setDevice(&file);
    stream >> deviceConfig;
    loader.start();
    return true;
}

void SimpleRawDataSourcePrivate::stop()
{
    loader.stop();
    loader.wait();
    file.close();
}


/*!
 * Construct a new SimpleRawDataSource as a child of the given \a parent.
 */
SimpleRawDataSource::SimpleRawDataSource(QObject *parent) :
    OfflineDataSource(parent),
    d_ptr(new SimpleRawDataSourcePrivate(this))
{
    exposeDeviceInterface();
}

/*!
 * Destroy this SimpleRawDataSource.
 */
SimpleRawDataSource::~SimpleRawDataSource()
{
    delete d_ptr;
}

/*!
 * Get device configuration values that had been saved to the data file.
 */
QVariant SimpleRawDataSource::get(const QString &subSystem,
                                  const QString &property)
{
    Q_D(SimpleRawDataSource);
    return d->deviceConfig.value(subSystem).value(property);
}

/*!
 * \return a widget allowing the user to enter the path to a data file.
 */
QWidget *SimpleRawDataSource::getWidget()
{
    Q_D(SimpleRawDataSource);
    return d->widget ? d->widget : d->createWidget();
}

/*!
 * Start loading data from the file.
 */
void SimpleRawDataSource::start()
{
    Q_D(SimpleRawDataSource);
    if (!d->start()) {
        auto fileName = d->file.fileName();
        if (fileName.isEmpty())
            emit error("Please choose a data file to load.");
        else
            emit error("Could not open " + fileName);
    }
}

/*!
 * Stop loading data from the file.
 */
void SimpleRawDataSource::stop()
{
    Q_D(SimpleRawDataSource);
    d->stop();
}

#include "simplerawdatasource.moc"

