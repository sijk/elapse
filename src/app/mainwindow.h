#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Pipeline;
class Sample;
class QStateMachine;
class QMovie;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool showSpinner READ showSpinner WRITE showSpinner)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_EegDecoder_newSample(const Sample &sample);
    void on_actionPlugins_triggered();

    void showErrorMessage(const QString &message);
    bool showSpinner() const;
    void showSpinner(bool show);

private:
    void buildStateMachine();

    Ui::MainWindow *ui;
    QMovie *spinner;
    QStateMachine *machine;
    Pipeline *pipeline;
};

#endif // MAINWINDOW_H
