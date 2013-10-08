#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Pipeline;
class EegSample;
class QStateMachine;
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
    void showErrorMessage(const QString &message);

    void on_actionPlugins_triggered();

    void showSpinner();
    void hideSpinner();

private:
    void buildStateMachine();

    Ui::MainWindow *ui;
    QMovie *spinner;
    QStateMachine *machine;
    Pipeline *pipeline;
};

#endif // MAINWINDOW_H
