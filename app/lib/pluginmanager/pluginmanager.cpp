#include <QFileDialog>
#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "nativepluginhost.h"
#include "pythonpluginhost.h"


PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    q_ptr(q)
{
    ui.setupUi(q);

    hosts[NATIVE] = new NativePluginHost;
    hosts[PYTHON] = new PythonPluginHost;

    QObject::connect(ui.pathButton, &QPushButton::clicked, [=]{
        QString dir = QFileDialog::getExistingDirectory(q, "Plugin path");
        if (!dir.isEmpty())
            q->setSearchPath(dir);
    });
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    for (uint i = 0; i < N_PLUGIN_HOSTS; i++)
        delete hosts[i];
}

PluginManagerPrivate *PluginManagerPrivate::expose(PluginManager *manager)
{
    return manager->d_func();
}

void PluginManagerPrivate::searchForPlugins()
{
    searchPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    pluginData.clear();

    foreach (const QFileInfo &item, searchPath.entryInfoList()) {
        for (uint i = 0; i < N_PLUGIN_HOSTS; i++) {
            PluginData info = hosts[i]->getInfo(item.absoluteFilePath());
            if (!info.plugin.name.isEmpty()) {
                pluginData.append(info);
                break;
            }
        }
    }
}

void PluginManagerPrivate::populateModels()
{
    auto populateModel =
        [=](QStandardItemModel *model, const QString &elementClass,
            elapse::Signal::Type signalType = elapse::Signal::INVALID) {
        model->clear();

        for (int i = 0; i < pluginData.size(); i++) {
            const PluginData &info = pluginData.at(i);
            QStandardItem *pluginItem = nullptr;

            for (int j = 0; j < info.classes.size(); j++) {
                const ClassInfo &cls = info.classes.at(j);

                bool classMatches = cls.elementClass == elementClass;
                bool signalTypeMatches = (cls.signalType == signalType)
                        || (cls.signalType == elapse::Signal::INVALID)
                        || (signalType == elapse::Signal::INVALID);

                if (classMatches && signalTypeMatches) {
                    if (!pluginItem) {
                        pluginItem = new QStandardItem(info.plugin.name);
                        pluginItem->setData(i);
                        pluginItem->setSelectable(false);
                        pluginItem->setEditable(false);
                        QFont font = pluginItem->font();
                        font.setItalic(true);
                        pluginItem->setFont(font);
                        model->appendRow(pluginItem);
                    }
                    QStandardItem *element = new QStandardItem(cls.className);
                    element->setData(j);
                    element->setEditable(false);
                    pluginItem->appendRow(element);
                }
            }
        }
    };

    populateModel(&dataSourceModel,   "DataSource");
    populateModel(&dataSinkModel,     "DataSink");
    populateModel(&eegDecoderModel,   "SampleDecoder",    elapse::Signal::EEG);
    populateModel(&vidDecoderModel,   "SampleDecoder",    elapse::Signal::VIDEO);
    populateModel(&imuDecoderModel,   "SampleDecoder",    elapse::Signal::IMU);
    populateModel(&eegFeatExModel,    "FeatureExtractor", elapse::Signal::EEG);
    populateModel(&vidFeatExModel,    "FeatureExtractor", elapse::Signal::VIDEO);
    populateModel(&imuFeatExModel,    "FeatureExtractor", elapse::Signal::IMU);
    populateModel(&classifierModel,   "Classifier");
    populateModel(&outputActionModel, "OutputAction");
}

void PluginManagerPrivate::attachModelViews()
{
    auto attach = [](QTreeView *tree, QStandardItemModel &model) {
        tree->setModel(&model);
        tree->expandAll();
    };

    attach(ui.dataSource,            dataSourceModel);
    attach(ui.dataSink,              dataSinkModel);
    attach(ui.sampleDecoderEeg,      eegDecoderModel);
    attach(ui.sampleDecoderVideo,    vidDecoderModel);
    attach(ui.sampleDecoderImu,      imuDecoderModel);
    attach(ui.featureExtractorEeg,   eegFeatExModel);
    attach(ui.featureExtractorVideo, vidFeatExModel);
    attach(ui.featureExtractorImu,   imuFeatExModel);
    attach(ui.classifier,            classifierModel);
    attach(ui.outputAction,          outputActionModel);
}


PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    d_ptr(new PluginManagerPrivate(this))
{
}

PluginManager::~PluginManager()
{
    delete d_ptr;
}

QDir PluginManager::searchPath() const
{
    Q_D(const PluginManager);
    return d->searchPath;
}

void PluginManager::setSearchPath(QDir newPath)
{
    Q_D(PluginManager);
    d->searchPath = newPath;
    d->searchForPlugins();
    d->populateModels();
    d->attachModelViews();
}

void PluginManager::selectPluginsToLoad()
{
    show();
}

void PluginManager::loadPluginsFromSettings()
{

}

void PluginManager::loadPluginsFromSelection()
{

}
