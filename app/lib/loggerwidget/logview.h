#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDialog>

class TableModelLoggerEngine;
class LogFilterProxyModel;
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

signals:
    void visibilityChanged(bool visible);

private slots:
    void setFilterLevel(int idx);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::LogView *ui;
    TableModelLoggerEngine *engine;
    LogFilterProxyModel *proxyModel;
};

#endif // LOGVIEW_H
