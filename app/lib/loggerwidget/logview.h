#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <memory>
#include <QDialog>

class QxtLoggerEngine;
namespace Ui { class LogView; }

namespace elapse {

/*!
 * \brief Logging utilities.
 * \ingroup logging
 */

namespace log {

class TableModelLoggerEngine;
class LogFilterProxyModel;


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
    std::unique_ptr<Ui::LogView> ui;
    std::unique_ptr<TableModelLoggerEngine> engine;
    std::unique_ptr<LogFilterProxyModel> proxyModel;
};

}} // namespace elapse::log

#endif // LOGVIEW_H
