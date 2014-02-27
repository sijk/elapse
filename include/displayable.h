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
    virtual QWidget *getWidget() = 0;
};

#endif // DISPLAYABLE_H
