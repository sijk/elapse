#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_base.h"
#include "datasource.h"
#include "decoder.h"


#define PluginInterface_iid "org.nzbri.elapse.PluginInterface"
class Plugin : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
};


typedef PluginInterface<DataSource> DataSourceInterface;
#define DataSourceInterface_iid "org.nzbri.elapse.DataSourceInterface"
Q_DECLARE_INTERFACE(DataSourceInterface, DataSourceInterface_iid)

class DataSourcePlugin : public QObject, public DataSourceInterface
{
    Q_OBJECT
    Q_INTERFACES(DataSourceInterface)
};


typedef PluginInterface<SampleDecoder> SampleDecoderInterface;
#define SampleDecoderInterface_iid "org.nzbri.elapse.SampleDecoderInterface"
Q_DECLARE_INTERFACE(SampleDecoderInterface, SampleDecoderInterface_iid)

class SampleDecoderPlugin : public QObject, public SampleDecoderInterface
{
    Q_OBJECT
    Q_INTERFACES(SampleDecoderInterface)
};


// TODO
class FeatureExtractor : public QObject { Q_OBJECT };
class Classifier : public QObject { Q_OBJECT };


typedef PluginInterface<FeatureExtractor> FeatureExtractorInterface;
#define FeatureExtractorInterface_iid "org.nzbri.elapse.FeatureExtractorInterface"
Q_DECLARE_INTERFACE(FeatureExtractorInterface, FeatureExtractorInterface_iid)

class FeatureExtractorPlugin : public QObject, public FeatureExtractorInterface
{
    Q_OBJECT
    Q_INTERFACES(FeatureExtractorInterface)
};


typedef PluginInterface<Classifier> ClassifierInterface;
#define ClassifierInterface_iid "org.nzbri.elapse.ClassifierInterface"
Q_DECLARE_INTERFACE(ClassifierInterface, ClassifierInterface_iid)

class ClassifierPlugin : public QObject, public ClassifierInterface
{
    Q_OBJECT
    Q_INTERFACES(ClassifierInterface)
};


#endif // PLUGIN_H
