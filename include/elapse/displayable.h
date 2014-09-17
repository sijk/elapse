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
     *
     * The caller of this function takes ownership of the widget and must
     * delete it at the appropriate time.
     *
     * Because the lifetime of the widget is managed externally, it would
     * be wise to store the pointer inside this class as a QPointer. This
     * will automatically null the pointer if the widget is destroyed
     * before the object that created it, preventing a dangling pointer.
     */
    virtual QWidget *getWidget() = 0;
};

} // namespace elapse

#endif // DISPLAYABLE_H
