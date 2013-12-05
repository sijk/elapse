#include <QMovie>
#include "spinner.h"

/*!
 * Construct a Spinner as a child of the given \a parent.
 */
Spinner::Spinner(QWidget *parent) :
    QLabel(parent),
    animation(new QMovie(":/img/spinner.gif", "GIF", this))
{
}

/*!
 * \return whether the spinner animation is visible and running.
 */
bool Spinner::running() const
{
    return animation->state() == QMovie::Running;
}

/*!
 * Set whether the spinner animation is visible and running.
 */
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
