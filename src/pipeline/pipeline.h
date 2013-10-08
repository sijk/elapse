#ifndef PIPELINE_H
#define PIPELINE_H

#include <QObject>
#include "sampletypes.h"

class PluginLoader;
class DataSource;
class SampleDecoder;


class Pipeline : public QObject
{
    Q_OBJECT
public:
    explicit Pipeline(QObject *parent = 0);

    PluginLoader *pluginLoader() const;
    DataSource *dataSource() const;
    SampleDecoder *sampleDecoder(SampleType sampleType) const;

    bool setElementProperty(const QString &name, const char *prop,
                            const QVariant &value);

signals:
    void started();
    void stopped();
    void error(const QString &msg);

public slots:
    void start();
    void stop();

private:
    PluginLoader *loader;
    DataSource *source;
    SampleDecoder *decoders[N_SAMPLE_TYPES];
    // other decoders...
    // feature extractors
    // classifier
};


#endif // PIPELINE_H
