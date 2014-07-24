#include <QFileDialog>
#include <QxtLogger>
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
        { &dataSourceModel,   ui.dataSource,            "DataSource",       elapse::Signal::INVALID, "DataSource"          },
        { &dataSinkModel,     ui.dataSink,              "DataSinkDelegate", elapse::Signal::INVALID, "DataSinkDelegate"    },
        { &eegDecoderModel,   ui.sampleDecoderEeg,      "SampleDecoder",    elapse::Signal::EEG,     "EegSampleDecoder"    },
        { &vidDecoderModel,   ui.sampleDecoderVideo,    "SampleDecoder",    elapse::Signal::VIDEO,   "VidSampleDecoder"    },
        { &imuDecoderModel,   ui.sampleDecoderImu,      "SampleDecoder",    elapse::Signal::IMU,     "ImuSampleDecoder"    },
        { &eegFeatExModel,    ui.featureExtractorEeg,   "FeatureExtractor", elapse::Signal::EEG,     "EegFeatureExtractor" },
        { &vidFeatExModel,    ui.featureExtractorVideo, "FeatureExtractor", elapse::Signal::VIDEO,   "VidFeatureExtractor" },
        { &imuFeatExModel,    ui.featureExtractorImu,   "FeatureExtractor", elapse::Signal::IMU,     "ImuFeatureExtractor" },
        { &classifierModel,   ui.classifier,            "Classifier",       elapse::Signal::INVALID, "Classifier"          },
        { &outputActionModel, ui.outputAction,          "OutputAction",     elapse::Signal::INVALID, "OutputAction"        },
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

/*!
 * Use every PluginHost to search for plugins in the searchPath. Every file and
 * directory in the searchPath is considered as a potential plugin by each
 * PluginHost.
 */
void PluginManagerPrivate::searchForPlugins()
{
    searchPath.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Readable);
    pluginData.clear();

    for (const QFileInfo &item : searchPath.entryInfoList()) {
        for (PluginHost *host : hosts) {
            PluginData info = host->getInfo(item.absoluteFilePath());
            if (!info.plugin.name.isEmpty()) {
                pluginData.append(info);
                break;
            }
        }
    }
}

/*!
 * Populate the models that list the available implementations for each element.
 */
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

/*!
 * Attach the models to their corresponding tree views in the plugin selection
 * dialog.
 */
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

/*!
 * Inspect the tree views to see which element implementations are selected.
 * \return a map of elementName to the (PluginInfo, ClassInfo) pair that
 * identifies an element implementation.
 */
PluginManagerPrivate::ElementSetInfo PluginManagerPrivate::getSelectedElements() const
{
    ElementSetInfo selectedElements;

    for (const auto &element : elements) {
        auto selected = element.tree->selectionModel()->selection().indexes();
        Q_ASSERT(selected.size() == 1);
        QModelIndex index = selected.first();
        QStandardItem *item = element.model->itemFromIndex(index);

        int classIndex = item->data().toInt();
        int pluginIndex = item->parent()->data().toInt();
        const PluginInfo &plugin = pluginData.at(pluginIndex).plugin;
        const ClassInfo &cls = pluginData.at(pluginIndex).classes.at(classIndex);

        selectedElements.insert(element.elementName, qMakePair(&plugin, &cls));
    }

    return selectedElements;
}

/*!
 * Create an element with base class T using the given \a info and store the
 * result in \a element.
 */
template<class T>
void PluginManagerPrivate::createElement(QSharedPointer<T> &element,
                                         const ElementInfo &info)
{
    const PluginInfo &plugin = *info.first;
    const ClassInfo &cls = *info.second;

    element = hosts[plugin.host]->instantiate<T>(plugin, cls);

    if (element.isNull())
        qxtLog->debug("Failed to instantiate", cls.className, "from", plugin.name);
}

/*!
 * \return a new ElementSet populated with the objects described by \a info.
 */
ElementSetPtr PluginManagerPrivate::createElements(const ElementSetInfo &info)
{
    ElementSetPtr e = ElementSetPtr::create();

    using elapse::Signal;

    createElement(e->dataSource,                       info.value("DataSource"));
    createElement(e->dataSink,                         info.value("DataSinkDelegate"));
    createElement(e->sampleDecoders[Signal::EEG],      info.value("EegSampleDecoder"));
    createElement(e->sampleDecoders[Signal::VIDEO],    info.value("VidSampleDecoder"));
    createElement(e->sampleDecoders[Signal::IMU],      info.value("ImuSampleDecoder"));
    createElement(e->featureExtractors[Signal::EEG],   info.value("EegFeatureExtractor"));
    createElement(e->featureExtractors[Signal::VIDEO], info.value("VidFeatureExtractor"));
    createElement(e->featureExtractors[Signal::IMU],   info.value("ImuFeatureExtractor"));
    createElement(e->classifier,                       info.value("Classifier"));
    createElement(e->action,                           info.value("OutputAction"));

    for (const auto &element : e->allElements()) {
        if (element.isNull()) {
            qxtLog->warning("Failed to load all elements from plugins.");
            return ElementSetPtr();
        }
    }

    return e;
}



/*!
 * Create a new PluginManager as a child of the given \a parent.
 */
PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    d_ptr(new PluginManagerPrivate(this))
{
    connect(this, SIGNAL(accepted()), SLOT(loadElementsFromGuiSelection()));
}

/*!
 * \brief PluginManager::~PluginManager
 */
PluginManager::~PluginManager()
{
    delete d_ptr;
}

/*!
 * \return the absolute path in which plugins will be searched for.
 */
QDir PluginManager::searchPath() const
{
    Q_D(const PluginManager);
    return d->searchPath;
}

/*!
 * Search for plugins in the \a newPath.
 */
void PluginManager::setSearchPath(QDir newPath)
{
    Q_D(PluginManager);
    d->searchPath = newPath;
    d->searchForPlugins();
    d->populateModels();
    d->attachModelViews();
}

/*!
 * Show the element selection dialog to allow the user to select a set of
 * elements to load.
 */
void PluginManager::loadElementsFromGui()
{
    show();
}

/*!
 * Load a previously saved set of elements.
 */
void PluginManager::loadElementsFromSettings()
{

}

/*!
 * Load the elements that the user selected in the GUI. Called when the element
 * selection dialog is accepted.
 */
void PluginManager::loadElementsFromGuiSelection()
{
    Q_D(PluginManager);
    auto info = d->getSelectedElements();
    auto elements = d->createElements(info);
    if (elements) {
        emit elementsLoaded(elements);
    }
}
