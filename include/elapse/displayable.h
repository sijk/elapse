#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

class QWidget;

/*!
 * \brief The Displayable interface can be implemented by any class that wants
 * to expose a GUI widget.
 */

class Displayable
{
public:
    /*!
     * Classes implementing the Displayable interface should implement this
     * method to return a widget that depicts the state of the object.
     */
    virtual QWidget *getWidget() = 0;
};

#endif // DISPLAYABLE_H
