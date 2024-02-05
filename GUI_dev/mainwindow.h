#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Python.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <iomanip>
#include <iostream>
#include <QProcess>
#include <QLabel>
#include <QProgressBar>
#include <QScrollBar>
#include <QScrollArea>
#include <QPalette>

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
    void on_selectPatientButton_clicked();

    void on_icPatientButton_clicked();

    void on_selectModelButton_clicked();

    void on_icModelButton_clicked();

    void on_testButton_clicked();

    void on_exportButton_clicked();

    void on_comboBox_up_activated(int index);

    void on_comboBox_down_activated(int index);

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
    QProgressBar *pro;
    QLabel *statusLog;
};

void show_image_scrollArea(QString path, QLabel* label_show, QScrollArea* scra_show);

void show_image_qLabel(QString path, QLabel* label_show);

#endif // MAINWINDOW_H
