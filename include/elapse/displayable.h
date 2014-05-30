#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

class QWidget;

namespace elapse {

/*!
 * \brief The Displayable interface can be implemented by any class that wants
 * to expose a GUI widget.
 * \headerfile elapse/displayable.h
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

} // namespace elapse

#endif // DISPLAYABLE_H
