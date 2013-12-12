#include <QxtLogger>
#include "modelloggerengine.h"
#include "logview.h"
#include "ui_logview.h"

LogView::LogView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogView),
    engine(new ModelLoggerEngine)
{
    ui->setupUi(this);
    ui->tableView->setModel(engine->model());

    connect(engine->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(resizeColumnsToContents()));
    connect(engine->model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView, SLOT(scrollToBottom()));
}

LogView::~LogView()
{
    delete engine;
    delete ui;
}

QxtLoggerEngine *LogView::loggerEngine()
{
    return engine;
}
