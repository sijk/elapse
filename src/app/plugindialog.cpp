#include "pluginloader.h"
#include "plugindialog.h"
#include "ui_plugindialog.h"

PluginDialog::PluginDialog(PluginLoader *loader, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDialog)
{
    ui->setupUi(this);

    foreach (QString iid, loader->interfaces()) {
        auto ifaceItem = new QTreeWidgetItem(ui->tree);
        ifaceItem->setText(0, iid);
        ui->tree->setItemExpanded(ifaceItem, true);
        ifaceItem->setFirstColumnSpanned(true);

        QFont boldFont = ifaceItem->font(0);
        boldFont.setBold(true);
        ifaceItem->setFont(0, boldFont);

        foreach (QFileInfo file, loader->filesForInterface(iid)) {
            auto fileItem = new QTreeWidgetItem(ifaceItem);
            QString plugin = loader->infoForFile(file)["className"].toString();
            fileItem->setText(0, plugin);
            fileItem->setText(1, file.fileName());
            ui->tree->setItemExpanded(fileItem, true);

            QFont italicFont = fileItem->font(0);
            italicFont.setItalic(true);
            fileItem->setFont(0, italicFont);
            fileItem->setFont(1, italicFont);
            fileItem->setForeground(1, QBrush(Qt::gray));

            foreach (QString key, loader->keysForFile(file)) {
                auto keyItem = new QTreeWidgetItem(fileItem);
                keyItem->setText(0, key);
                keyItem->setFirstColumnSpanned(true);
            }
        }

        ui->tree->resizeColumnToContents(1);
        int colWidth = ui->tree->width() - ui->tree->columnWidth(1) - 10;
        ui->tree->setColumnWidth(0, colWidth);

        ui->tree->model()->sort(0);
    }
}

PluginDialog::~PluginDialog()
{
    delete ui;
}
