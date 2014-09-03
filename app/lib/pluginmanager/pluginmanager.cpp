#include <QFileDialog>
#include <QSettings>
#include <QxtLogger>
#include "pluginmanager.h"
#include "pluginmanager_p.h"

#include "staticpluginhost.h"
#include "nativepluginhost.h"
#include "pythonpluginhost.h"

using elapse::data::Signal;

const QString pluginSetting("elements/%1/plugin-path");
const QString classSetting("elements/%1/class-name");


PluginManagerPrivate::PluginManagerPrivate(PluginManager *q) :
    q_ptr(q)
{
    ui.setupUi(q);

    hosts[PluginHostID::Static] = new StaticPluginHost;
    hosts[PluginHostID::Native] = new NativePluginHost;
    hosts[PluginHostID::Python] = new PythonPluginHost;

    elements = {
        { &dataSourceModel,   ui.dataSource,            "DataSource",       Signal::INVALID, "DataSource"          },
        { &dataSinkModel,     ui.dataSink,              "DataSink",         Signal::INVALID, "DataSink"            },
        { &eegDecoderModel,   ui.sampleDecoderEeg,      "SampleDecoder",    Signal::EEG,     "EegSampleDecoder"    },
        { &vidDecoderModel,   ui.sampleDecoderVideo,    "SampleDecoder",    Signal::VIDEO,   "VidSampleDecoder"    },
        { &imuDecoderModel,   ui.sampleDecoderImu,      "SampleDecoder",    Signal::IMU,     "ImuSampleDecoder"    },
        { &eegFeatExModel,    ui.featureExtractorEeg,   "FeatureExtractor", Signal::EEG,     "EegFeatureExtractor" },
        { &vidFeatExModel,    ui.featureExtractorVideo, "FeatureExtractor", Signal::VIDEO,   "VidFeatureExtractor" },
        { &imuFeatExModel,    ui.featureExtractorImu,   "FeatureExtractor", Signal::IMU,     "ImuFeatureExtractor" },
        { &classifierModel,   ui.classifier,            "Classifier",       Signal::INVALID, "Classifier"          },
        { &outputActionModel, ui.outputAction,          "OutputAction",     Signal::INVALID, "OutputAction"        },
    };

    QObject::connect(ui.pathButton, &QPushButton::clicked, [this]{
        QString dir = QFileDialog::getExistingDirectory(q_ptr, "Plugin path", searchPath.absolutePath());
        if (!dir.isEmpty())
            q_ptr->setSearchPath(dir);
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
 * Use every PluginHost to search for plugins in the searchPath.
 */
void PluginManagerPrivate::searchForPlugins()
{
    pluginData.clear();

    for (PluginHost *host : hosts) {
        auto plugins = host->searchForPluginsIn(searchPath);
        pluginData.append(plugins);
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
                        || (cls.signalType == Signal::INVALID)
                        || (element.signalType == Signal::INVALID);

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
 * Load a set of element info from the settings file.
 * \return the info if a complete set was saved in the settings file, otherwise
 * an empty map.
 */
PluginManagerPrivate::ElementSetInfo PluginManagerPrivate::getSavedElements() const
{
    ElementSetInfo savedElements;
    QSettings settings;

    for (const ElementData &element : elements) {
        const QString &pluginPath = settings.value(pluginSetting.arg(element.elementName)).toString();
        const QString &className = settings.value(classSetting.arg(element.elementName)).toString();

        for (const PluginData &info : pluginData) {
            if (info.plugin.path == pluginPath) {
                for (const ClassInfo &cls : info.classes) {
                    if (cls.className == className) {
                        savedElements.insert(element.elementName, qMakePair(&info.plugin, &cls));
                        qxtLog->debug("Using saved element", className, "from", info.plugin.name);
                        break;
                    }
                }
            }
        }
    }

    // Only return the saved elements if we have a full set of info
    if (savedElements.size() == elements.size())
        return savedElements;

    return ElementSetInfo();
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

    createElement(e->dataSource,                       info.value("DataSource"));
    createElement(e->dataSink,                         info.value("DataSink"));
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
 * Select the elements described by the given \a info in the tree views.
 */
void PluginManagerPrivate::selectElements(const ElementSetInfo &info)
{
    for (auto i = info.cbegin(); i != info.cend(); i++) {
        const QString &elementName = i.key();
        const PluginInfo *plugin = i.value().first;
        const ClassInfo *cls = i.value().second;

        // Find the index of the given PluginInfo
        const int pluginIndex = std::distance(pluginData.cbegin(),
            std::find_if(pluginData.cbegin(), pluginData.cend(),
                [=](const PluginData &p){ return &p.plugin == plugin; }));

        // Find the index of the given ClassInfo
        const QList<ClassInfo> &classes = pluginData.at(pluginIndex).classes;
        const int classIndex = std::distance(classes.cbegin(),
            std::find_if(classes.cbegin(), classes.cend(),
                [=](const ClassInfo &c){ return &c == cls; }));

        // Find the ElementData of the element we're working with
        const ElementData &element =
            *std::find_if(elements.cbegin(), elements.cend(),
                [=](const ElementData &e){ return e.elementName == elementName; });

        // Select the model item with the given indices
        auto item = findItemWithIndices(element.model, pluginIndex, classIndex);
        Q_ASSERT(item);
        auto index = element.model->indexFromItem(item);
        element.tree->selectionModel()->select(index, QItemSelectionModel::SelectCurrent);
    }
}

/*!
 * Save the given set of element \a info.
 */
void PluginManagerPrivate::saveElements(const ElementSetInfo &info)
{
    QSettings settings;

    for (auto i = info.cbegin(); i != info.cend(); i++) {
        const QString &elementName = i.key();
        const PluginInfo *plugin = i.value().first;
        const ClassInfo *cls = i.value().second;

        settings.setValue(pluginSetting.arg(elementName), plugin->path);
        settings.setValue(classSetting.arg(elementName), cls->className);

        qxtLog->debug("Saving element", cls->className, "from", plugin->name);
    }

    qxtLog->info("Saved current element selection.");
}

/*!
 * Find the item in the given \a model which correspond to the class
 * at \a classIndex in the plugin at \a pluginIndex in the pluginData list.
 */
QStandardItem *PluginManagerPrivate::findItemWithIndices(const QStandardItemModel *model,
                                                         int pluginIndex, int classIndex)
{
    const QStandardItem *root = model->invisibleRootItem();
    for (int prow = 0; prow < root->rowCount(); prow++) {
        QStandardItem *plugin = root->child(prow);
        if (plugin->data().toInt() == pluginIndex) {
            for (int crow = 0; crow < plugin->rowCount(); crow++) {
                QStandardItem *cls = plugin->child(crow);
                if (cls->data().toInt() == classIndex)
                    return cls;
            }
        }
    }
    return nullptr;
}


/*!
 * Create a new PluginManager as a child of the given \a parent.
 */
PluginManager::PluginManager(QWidget *parent) :
    QDialog(parent),
    d_ptr(new PluginManagerPrivate(this))
{
    connect(this, SIGNAL(accepted()), SLOT(loadElementsFromGuiSelection()));
    setSearchPath(QSettings().value("plugins-path").toString());
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
    if (newPath == d->searchPath && !d->pluginData.isEmpty()) {
        qxtLog->debug("Plugin search path was set to the current value. "
                      "Not doing anything...");
        return;
    }

    d->searchPath = newPath;
    d->searchForPlugins();
    d->populateModels();
    d->attachModelViews();

    QSettings().setValue("plugins-path", d->searchPath.absolutePath());
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
    Q_D(PluginManager);
    auto info = d->getSavedElements();
    if (info.isEmpty()) return;
    auto elements = d->createElements(info);
    if (elements) {
        d->selectElements(info);
        emit elementsLoaded(elements);
    }
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
        d->saveElements(info);
        emit elementsLoaded(elements);
    }
}
