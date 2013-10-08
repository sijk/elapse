#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Pipeline;
class EegSample;
class QMovie;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDataReady(const EegSample &sample);
    void onPipelineError(const QString &message);

    void on_pushButton_toggled(bool checked);
    void on_actionPlugins_triggered();

    void showSpinner();
    void hideSpinner();

private:
    Ui::MainWindow *ui;
    QMovie *spinner;
    Pipeline *pipeline;
};

#endif // MAINWINDOW_H
