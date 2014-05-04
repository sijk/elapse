#include <QStringListModel>
#include <QSettings>
#include <QShortcut>
#include <QKeyEvent>
#include <QxtLogger>
#include "tablemodelloggerengine.h"
#include "logfilterproxymodel.h"
#include "logview.h"
#include "ui_logview.h"


static QStringListModel levelNames{{
    "Trace", "Debug", "Info", "Warning", "Error", "Critical", "Fatal",
}};

static const QList<QxtLogger::LogLevel> levels{
    QxtLogger::TraceLevel, QxtLogger::DebugLevel, QxtLogger::InfoLevel,
    QxtLogger::WarningLevel, QxtLogger::ErrorLevel, QxtLogger::CriticalLevel,
    QxtLogger::FatalLevel,
};


/*!
 * Construct a new LogView as a child of the given \a parent.
 *
 * Instantiates the TableModelLoggerEngine and connects its model
 * to the table view.
 */
LogView::LogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogView),
    engine(new TableModelLoggerEngine),
    proxyModel(new LogFilterProxyModel(this))
{
    ui->setupUi(this);

    proxyModel->setSourceModel(engine->model());
    ui->tableView->setModel(proxyModel);

    connect(proxyModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(scrollToBottom()));

    ui->comboBox->setModel(&levelNames);
    ui->comboBox->setCurrentIndex(levels.indexOf(proxyModel->minimumLogLevel()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setFilterLevel(int)));

    connect(ui->searchText, SIGNAL(textChanged(QString)),
            proxyModel, SLOT(setFilterRegExp(QString)));

    QShortcut *findShortcut = new QShortcut(QKeySequence::Find, this);
    connect(findShortcut, SIGNAL(activated()),
            ui->searchText, SLOT(setFocus()));

    if (QSettings().value("logview/show", false).toBool())
        QMetaObject::invokeMethod(this, "show", Qt::QueuedConnection);
}

/*!
 * Delete this LogView.
 */
LogView::~LogView()
{
    delete engine;
    delete ui;
}

/*!
 * \return the TableModelLoggerEngine.
 */
QxtLoggerEngine *LogView::loggerEngine()
{
    return engine;
}

/*!
 * Set the LogFilterProxyModel::minimumLogLevel() to the \a idx'th level.
 */
void LogView::setFilterLevel(int idx)
{
    proxyModel->setMinimumLogLevel(levels[idx]);
}

/*!
 * \fn void LogView::visibilityChanged(bool visible)
 * Emitted when the visibility of the window changes.
 */

/*!
 * Save the visibility of the LogView and emit visibilityChanged().
 */
void LogView::showEvent(QShowEvent *)
{
    QSettings settings;
    settings.setValue("logview/show", true);
    restoreGeometry(settings.value("logview/geometry").toByteArray());
    emit visibilityChanged(true);
}

/*!
 * Save the visibility of the LogView and emit visibilityChanged().
 */
void LogView::hideEvent(QHideEvent *)
{
    QSettings settings;
    settings.setValue("logview/show", false);
    settings.setValue("logview/geometry", saveGeometry());
    emit visibilityChanged(false);
}

/*!
 * Don't reject() when Esc is pressed.
 */
void LogView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Escape)
        QDialog::keyPressEvent(event);
}
