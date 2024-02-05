#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();



    void on_SelectButton_clicked();

    void on_SaveButton_clicked();

    void on_ExecuteButton_clicked();

    void on_ExitButton_clicked();


    void onPythonScriptFinished(int exitCode, QProcess::ExitStatus exitStatus);


    void onPythonScriptError(QProcess::ProcessError error);

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);



    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QString pythonScriptPath; 
    QProcess *pythonProcess;
};
#endif // MAINWINDOW_H
