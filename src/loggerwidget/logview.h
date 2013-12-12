#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

class ModelLoggerEngine;
class QxtLoggerEngine;

namespace Ui {
class LogView;
}

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = 0);
    ~LogView();

    QxtLoggerEngine *loggerEngine();

private:
    Ui::LogView *ui;
    ModelLoggerEngine *engine;
};

#endif // LOGVIEW_H
