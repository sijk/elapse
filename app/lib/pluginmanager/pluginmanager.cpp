#include <QFileDialog>
#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "nativepluginhost.h"
#include "pythonpluginhost.h"


PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    q_ptr(q)
{
    ui.setupUi(q);

    hosts[PluginHostID::Native] = new NativePluginHost;
    hosts[PluginHostID::Python] = new PythonPluginHost;

    elements = {
        { &dataSourceModel,   ui.dataSource,            "DataSource",       elapse::Signal::INVALID },
        { &dataSinkModel,     ui.dataSink,              "DataSink",         elapse::Signal::INVALID },
        { &eegDecoderModel,   ui.sampleDecoderEeg,      "SampleDecoder",    elapse::Signal::EEG     },
        { &vidDecoderModel,   ui.sampleDecoderVideo,    "SampleDecoder",    elapse::Signal::VIDEO   },
        { &imuDecoderModel,   ui.sampleDecoderImu,      "SampleDecoder",    elapse::Signal::IMU     },
        { &eegFeatExModel,    ui.featureExtractorEeg,   "FeatureExtractor", elapse::Signal::EEG     },
        { &vidFeatExModel,    ui.featureExtractorVideo, "FeatureExtractor", elapse::Signal::VIDEO   },
        { &imuFeatExModel,    ui.featureExtractorImu,   "FeatureExtractor", elapse::Signal::IMU     },
        { &classifierModel,   ui.classifier,            "Classifier",       elapse::Signal::INVALID },
        { &outputActionModel, ui.outputAction,          "OutputAction",     elapse::Signal::INVALID },
    };

    QObject::connect(ui.pathButton, &QPushButton::clicked, [q]{
        QString dir = QFileDialog::getExistingDirectory(q, "Plugin path");
        if (!dir.isEmpty())
            q->setSearchPath(dir);
    });
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    qDeleteAll(hosts);
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
        foreach (PluginHost *host, hosts) {
            PluginData info = host->getInfo(item.absoluteFilePath());
            if (!info.plugin.name.isEmpty()) {
                pluginData.append(info);
                break;
            }
        }
    }
}

void PluginManagerPrivate::populateModels()
{
    for (const auto &element : elements) {
        element.model->clear();

        for (int i = 0; i < pluginData.size(); i++) {
            const PluginData &info = pluginData.at(i);
            QStandardItem *pluginItem = nullptr;

            for (int j = 0; j < info.classes.size(); j++) {
                const ClassInfo &cls = info.classes.at(j);

                bool classMatches = cls.elementClass == element.elementClass;
                bool signalTypeMatches = (cls.signalType == element.signalType)
                        || (cls.signalType == elapse::Signal::INVALID)
                        || (element.signalType == elapse::Signal::INVALID);

                if (classMatches && signalTypeMatches) {
                    if (!pluginItem) {
                        pluginItem = new QStandardItem(info.plugin.name);
                        pluginItem->setData(i);
                        pluginItem->setSelectable(false);
                        pluginItem->setEditable(false);
                        QFont font = pluginItem->font();
                        font.setItalic(true);
                        pluginItem->setFont(font);
                        element.model->appendRow(pluginItem);
                    }
                    QStandardItem *elementItem = new QStandardItem(cls.className);
                    elementItem->setData(j);
                    elementItem->setEditable(false);
                    pluginItem->appendRow(elementItem);
                }
            }
        }
    };
}

void PluginManagerPrivate::attachModelViews()
{
    for (const auto &element : elements) {
        element.tree->setModel(element.model);
        element.tree->expandAll();

        // Select the first item by default
        auto first = element.model->index(0,0).child(0,0);
        element.tree->selectionModel()->select(first, QItemSelectionModel::SelectCurrent);

        // Ensure something is always selected
        QObject::connect(element.tree->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            [=](const QItemSelection &current, const QItemSelection &prev){
                if (current.indexes().isEmpty() && !prev.indexes().isEmpty())
                    element.tree->selectionModel()->select(prev, QItemSelectionModel::SelectCurrent);
            });
    };
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

void PluginManager::loadPluginsFromGui()
{
    show();
}

void PluginManager::loadPluginsFromSettings()
{

}

void PluginManager::loadPluginsFromGuiSelection()
{

}
