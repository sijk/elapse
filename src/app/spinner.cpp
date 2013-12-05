#include <QMovie>
#include "spinner.h"

/*!
 * \class Spinner
 * \ingroup app
 * \inmodule elapse-core
 *
 * \brief The Spinner class provides a loading/waiting animation.
 *
 * When the Spinner is running() the animation is shown. When it is not
 * running() the animation is stopped and hidden.
 */

/*!
 * Construct a Spinner as a child of the given parent.
 */
Spinner::Spinner(QWidget *parent) :
    QLabel(parent),
    animation(new QMovie(":/img/spinner.gif", "GIF", this))
{
}

/*!
 * \property Spinner::running
 * \brief whether the spinner animation is visible.
 */
bool Spinner::running() const
{
    return animation->state() == QMovie::Running;
}

void Spinner::setRunning(bool run)
{
    if (run) {
        setMovie(animation);
        animation->start();
    } else {
        animation->stop();
        setText(" ");
    }
}
