#include <QPluginLoader>
#include <QTreeView>
#include "plugin.h"
#include "elementsetfactory.h"


/*!
 * Create an ElementSet, ask the given \a strategy for the ClassInfo of the
 * selected classes, and load those classes from plugins. If everything
 * succeeded, return the ElementSet, otherwise return \c NULL.
 */
ElementSetPtr ElementSetFactory::loadUsingStrategy(ElementSelectionStrategy *strategy)
{
    if (!strategy->canLoadElements())
        return ElementSetPtr();

    auto elements = ElementSetPtr::create();

    loadElement(elements->dataSource,                       strategy->getElementInfo("dataSource"));
    loadElement(elements->sampleDecoders[Signal::EEG],      strategy->getElementInfo("sampleDecoderEeg"));
    loadElement(elements->sampleDecoders[Signal::VIDEO],    strategy->getElementInfo("sampleDecoderVideo"));
    loadElement(elements->sampleDecoders[Signal::IMU],      strategy->getElementInfo("sampleDecoderImu"));
    loadElement(elements->featureExtractors[Signal::EEG],   strategy->getElementInfo("featureExtractorEeg"));
    loadElement(elements->featureExtractors[Signal::VIDEO], strategy->getElementInfo("featureExtractorVideo"));
    loadElement(elements->featureExtractors[Signal::IMU],   strategy->getElementInfo("featureExtractorImu"));
    loadElement(elements->classifier,                       strategy->getElementInfo("classifier"));

    foreach (QObject *element, elements->allElements()) {
        if (!element) {
            qxtLog->warning("Failed to load all elements from plugins.");
            return ElementSetPtr();
        }
    }

    qxtLog->info("Successfully loaded all elements from plugins.");
    return elements;
}

/*!
 * Load the plugin from \a info.pluginPath and instantiate an object of class
 * \a info.className. If the plugin cannot be loaded, the class cannot be
 * instantiated, or casting the instance to the requested ElementType fails,
 * \a element will be \c NULL. Otherwise \a element will hold the newly-created
 * element.
 */
template<class ElementType>
void ElementSetFactory::loadElement(ElementType &element, ClassInfo info)
{
    Q_STATIC_ASSERT(std::is_pointer<ElementType>::value);

    element = nullptr;

    if (info.pluginPath.isEmpty() || info.className.isEmpty())
        return;

    QPluginLoader loader(info.pluginPath);
    Plugin *plugin = static_cast<Plugin*>(loader.instance());

    if (!plugin) {
        qxtLog->debug("Could not load plugin", info.pluginPath);
        return;
    }

    foreach (const QMetaObject &obj, plugin->classes()) {
        if (obj.className() == info.className) {
            QObject *instance = obj.newInstance();
            element = qobject_cast<ElementType>(instance);
            if (instance && !element)
                delete instance;
            break;
        }
    }

    qxtLog->trace(element ? "Loaded" : "Failed to load", info.className,
                  "from", QFileInfo(info.pluginPath).fileName());
}


/*!
 * \fn ElementSelectionStrategy::canLoadElements()
 *
 * \return whether this ElementSelectionStrategy is able to retrieve element
 * selection information (default = \c true).
 *
 * This can be overriden by subclasses if they are able to figure out in
 * advance that they will not be able to retrieve the necessary information.
 */

/*!
 * \fn ElementSelectionStrategy::getElementInfo()
 *
 * Subclasses should implement this method to provide an element selection
 * strategy. The \a elementName argument refers to one 'slot' in the ElementSet
 * which needs to be filled by an element — e.g., "sampleDecoderEeg" refers to
 * ElementSet::sampleDecoders[Signal::EEG].
 *
 * \return the ClassInfo of an element that can take the given place in the
 * ElementSet.
 */


/*!
 * \return \c true iff the QSettings file contains element details.
 */
bool SelectElementsFromSettings::canLoadElements()
{
    return QSettings().childGroups().contains("elements");
}

/*!
 * \return the ClassInfo of the given \a elementName as stored in QSettings.
 */
ClassInfo SelectElementsFromSettings::getElementInfo(const char *elementName)
{
    ClassInfo info;

    QSettings settings;
    info.pluginPath = settings.value(pathSetting.arg(elementName)).toString();
    info.className = settings.value(classSetting.arg(elementName)).toString();

    return info;
}


/*!
 * Instantiate the LoadElementsFromSelection strategy. The getElementInfo()
 * method will retrieve selection information from QTreeViews that are children
 * of the given \a ui.
 */
SelectElementsFromGui::SelectElementsFromGui(const QWidget *ui) :
    ui(ui)
{
}

/*!
 * \return the ClassInfo of the given \a elementName that's selected in the
 * corresponding QTreeView in the UI.
 */
ClassInfo SelectElementsFromGui::getElementInfo(const char *elementName)
{
    ClassInfo info;

    auto tree = ui->findChild<QTreeView*>(elementName);
    Q_ASSERT(tree);

    QModelIndexList idxs = tree->selectionModel()->selection().indexes();
    Q_ASSERT(idxs.size() == 1);
    QModelIndex index = idxs.at(0);

    info.className = index.data().toString();
    info.pluginPath = index.parent().data(FILEPATH_ROLE).toString();

    return info;
}

