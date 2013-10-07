#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>

class PluginLoader;

namespace Ui {
class PluginDialog;
}

class PluginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDialog(PluginLoader *loader, QWidget *parent = 0);
    ~PluginDialog();

private:
    Ui::PluginDialog *ui;
};

#endif // PLUGINDIALOG_H
