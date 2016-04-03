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

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QApplication>
#include <QVariant>
#include <QFile>
#include <QThread>
#include <QPointer>
#include <QSettings>
#include <QxtLogger>
#include <elapse/datatypes.h>
#include "simplerawdatasource.h"

namespace elapse { namespace coreplugin {

using elapse::data::Signal;

static const QString settingsRoot("/plugins/core/simplerawdatasource");
static const QString dataDir(settingsRoot + "/dataDir");


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

    void createWidget();
    QPointer<QWidget> widget;
    QLineEdit *lineEdit;

    bool start();
    void stop();

    QFile file;
    QDataStream stream;
    QMap<QString, QVariantMap> deviceConfig;
    DataLoader loader;
    int startTime;
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
    int signalType;
    QByteArray data;
    bool first = true;
    int elapsedTime = 0;

    while (!d->stream.atEnd() && !stopped)
    {
        d->stream >> dt >> signalType >> data;

        elapsedTime += dt;

        if (first)
            first = false;
        else if (d->startTime > 0 && elapsedTime < d->startTime)
            QThread::msleep(1);
        else
            QThread::msleep(dt);

        if (signalType == Signal::EEG)
            emit eegReady(data);
        else if (signalType == Signal::VIDEO)
            emit videoReady(data);
        else if (signalType == Signal::IMU)
            emit imuReady(data);
        else
            Q_UNREACHABLE();
    }
}


SimpleRawDataSourcePrivate::SimpleRawDataSourcePrivate(SimpleRawDataSource *q) :
    loader(this)
{
    q->connect(&loader, SIGNAL(started()), SIGNAL(started()));
    q->connect(&loader, SIGNAL(finished()), SIGNAL(finished()));
    q->connect(&loader, SIGNAL(videoReady(QByteArray)), SIGNAL(videoReady(QByteArray)));
    q->connect(&loader, SIGNAL(eegReady(QByteArray)), SIGNAL(eegReady(QByteArray)));
    q->connect(&loader, SIGNAL(imuReady(QByteArray)), SIGNAL(imuReady(QByteArray)));

    startTime = QSettings().value(settingsRoot+"/startTime", 0).toInt() * 1000;
    qxtLog->debug("Loader start at", qulonglong(startTime));
}

void SimpleRawDataSourcePrivate::createWidget()
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
                          "Open data file", QSettings().value(dataDir).toString(),
                          "Raw data files (*.dat)"));
    });
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


SimpleRawDataSource::SimpleRawDataSource() :
    d_ptr(new SimpleRawDataSourcePrivate(this))
{
    exposeDeviceInterface();
}

SimpleRawDataSource::~SimpleRawDataSource() { }

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
    if (!d->widget)
        d->createWidget();
    return d->widget;
}

/*!
 * Start loading data from the file.
 */
void SimpleRawDataSource::start()
{
    Q_D(SimpleRawDataSource);
    if (d->start()) {
        QSettings().setValue(dataDir, QFileInfo(d->file.fileName()).absolutePath());
        if (d->widget)
            d->widget->setEnabled(false);
    } else {
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
    if (d->widget)
        d->widget->setEnabled(true);
}

}} // namespace elapse::coreplugin

#include "simplerawdatasource.moc"
