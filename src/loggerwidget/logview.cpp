#include <QStringListModel>
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
            ui->tableView, SLOT(resizeColumnsToContents()));
    connect(proxyModel, SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(scrollToBottom()));

    ui->comboBox->setModel(&levelNames);
    ui->comboBox->setCurrentIndex(levels.indexOf(proxyModel->minimumLogLevel()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setFilterLevel(int)));
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
