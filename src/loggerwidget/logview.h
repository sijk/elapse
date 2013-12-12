#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

class TableModelLoggerEngine;
class QxtLoggerEngine;

namespace Ui {
class LogView;
}


/*!
 * \brief The LogView class provides a dialog for viewing log messages.
 * \ingroup widgets
 * \ingroup logging
 */

class LogView : public QDialog
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = 0);
    ~LogView();

    QxtLoggerEngine *loggerEngine();

private:
    Ui::LogView *ui;
    TableModelLoggerEngine *engine;
};

#endif // LOGVIEW_H
