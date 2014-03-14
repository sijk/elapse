#ifndef ELEMENTLOADER_H
#define ELEMENTLOADER_H

#include "elementset.h"
#include "pluginmanager_def.h"

class ElementSelectionStrategy;


/*!
 * \brief The ElementSetFactory class loads elements from plugins.
 *
 * It uses an ElementSelectionStrategy to find out which element classes
 * to load from plugins.
 *
 * \ingroup plugins-int
 */

class ElementSetFactory
{
public:
    static ElementSetPtr loadUsingStrategy(ElementSelectionStrategy *strategy);

protected:
    template<class ElementType>
    static void loadElement(ElementType &element, ClassInfo info);
};


/*!
 * \brief The ElementSelectionStrategy class finds the ClassInfo of classes to
 * load from plugins given some external selection information.
 *
 * \ingroup plugins-int
 */

class ElementSelectionStrategy
{
public:
    virtual bool canLoadElements() { return true; }
    virtual ClassInfo getElementInfo(const char *elementName) = 0;
};


/*!
 * \brief The SelectElementsFromSettings strategy retrieves elements details
 * from QSettings.
 *
 * \ingroup plugins-int
 */

class SelectElementsFromSettings : public ElementSelectionStrategy
{
    bool canLoadElements();
    ClassInfo getElementInfo(const char *elementName);
};


/*!
 * \brief The SelectElementsFromGui strategy retrieves element details
 * from the PluginManager GUI.
 *
 * \ingroup plugins-int
 */

class SelectElementsFromGui : public ElementSelectionStrategy
{
public:
    SelectElementsFromGui(const QWidget *ui);
    ClassInfo getElementInfo(const char *elementName);

private:
    const QWidget *ui;
};


#endif // ELEMENTLOADER_H
