#ifndef SPINNER_H
#define SPINNER_H

#include <QLabel>
class QMovie;

namespace elapse { namespace widgets {

/*!
 * \brief The Spinner class provides a loading/waiting animation.
 *
 * When the Spinner is running() the animation is shown. When it is not
 * running() the animation is stopped and hidden.
 *
 * \headerfile elapse/widgets/spinner.h
 * \ingroup widgets
 */

class Spinner : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning)

public:
    Spinner(QWidget *parent = nullptr);

    bool running() const;

public slots:
    void start();
    void stop();
    void setRunning(bool run);

private:
    QMovie *animation;
};

}} // namespace elapse::widgets

#endif // SPINNER_H
