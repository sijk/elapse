#ifndef SPINNER_H
#define SPINNER_H

#include <QLabel>
class QMovie;

class Spinner : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning)

public:
    Spinner(QWidget *parent = nullptr);

    bool running() const;

public slots:
    void setRunning(bool run);

private:
    QMovie *animation;
};

#endif // SPINNER_H
