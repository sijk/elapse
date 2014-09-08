#include <QMovie>
#include "spinner.h"

namespace elapse { namespace widgets {

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
 * Show and run the spinner animation.
 */
void Spinner::start()
{
    setMovie(animation);
    animation->start();
}

/*!
 * Hide and stop the spinner animation.
 */
void Spinner::stop()
{
    animation->stop();
    setText(" ");
}

/*!
 * Set whether the spinner animation is visible and running.
 */
void Spinner::setRunning(bool run)
{
    run ? start() : stop();
}

}} // namespace elapse::widgets
