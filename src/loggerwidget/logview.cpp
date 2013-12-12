#include <QxtLogger>
#include "tablemodelloggerengine.h"
#include "logview.h"
#include "ui_logview.h"

/*!
 * Construct a new LogView as a child of the given \a parent.
 *
 * Instantiates the TableModelLoggerEngine and connects its model
 * to the table view.
 */
LogView::LogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogView),
    engine(new TableModelLoggerEngine)
{
    ui->setupUi(this);
    ui->tableView->setModel(engine->model());

    connect(engine->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(resizeColumnsToContents()));
    connect(engine->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(scrollToBottom()));
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
