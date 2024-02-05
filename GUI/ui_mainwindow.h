/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *Select_Patient_Box;
    QPushButton *selectPatientButton;
    QLineEdit *pt_fileName;
    QPushButton *icPatientButton;
    QLabel *label_2;
    QLineEdit *ch_number;
    QLabel *label_3;
    QLineEdit *measurement;
    QLabel *label_4;
    QLineEdit *data_size;
    QLabel *label_5;
    QLineEdit *s_f;
    QLabel *label_6;
    QLineEdit *time_total;
    QLineEdit *re_sys;
    QLabel *label_7;
    QLineEdit *pt_check;
    QGroupBox *Select_Model_Box;
    QPushButton *selectModelButton;
    QLineEdit *model_fileName;
    QPushButton *icModelButton;
    QLineEdit *model_check;
    QLineEdit *label_d;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *model_k;
    QLineEdit *feature_d;
    QLabel *label;
    QLineEdit *label_k3;
    QLineEdit *label_k4;
    QLabel *label_13;
    QLineEdit *label_k5;
    QLabel *label_14;
    QLabel *label_16;
    QLineEdit *label_k1;
    QLineEdit *label_k2;
    QLabel *label_15;
    QFrame *line;
    QGroupBox *Diagnoses_Box;
    QLabel *label_11;
    QLineEdit *result;
    QLabel *label_12;
    QLineEdit *conf;
    QPushButton *exportButton;
    QPushButton *testButton;
    QPushButton *pushButton_clear;
    QGroupBox *Select_Mode_Box;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *PSD_GM_Box;
    QLabel *label_psd_dm;
    QGroupBox *Signal_TD_Box;
    QComboBox *comboBox_up;
    QComboBox *comboBox_down;
    QScrollArea *scrollArea_ch_up;
    QWidget *scrollAreaWidgetContents_2;
    QLabel *label_ch_up;
    QScrollArea *scrollArea_ch_down;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *label_ch_down;
    QGroupBox *PSD_FM_Box;
    QScrollArea *scrollArea_psd_fm;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_psd_fm;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1260, 720);
        MainWindow->setMouseTracking(false);
        MainWindow->setAutoFillBackground(true);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Select_Patient_Box = new QGroupBox(centralWidget);
        Select_Patient_Box->setObjectName(QString::fromUtf8("Select_Patient_Box"));
        Select_Patient_Box->setGeometry(QRect(10, 70, 291, 261));
        selectPatientButton = new QPushButton(Select_Patient_Box);
        selectPatientButton->setObjectName(QString::fromUtf8("selectPatientButton"));
        selectPatientButton->setGeometry(QRect(10, 20, 81, 21));
        pt_fileName = new QLineEdit(Select_Patient_Box);
        pt_fileName->setObjectName(QString::fromUtf8("pt_fileName"));
        pt_fileName->setGeometry(QRect(100, 20, 181, 21));
        icPatientButton = new QPushButton(Select_Patient_Box);
        icPatientButton->setObjectName(QString::fromUtf8("icPatientButton"));
        icPatientButton->setGeometry(QRect(10, 50, 111, 20));
        label_2 = new QLabel(Select_Patient_Box);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 80, 121, 21));
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setLineWidth(1);
        label_2->setTextFormat(Qt::AutoText);
        label_2->setMargin(0);
        ch_number = new QLineEdit(Select_Patient_Box);
        ch_number->setObjectName(QString::fromUtf8("ch_number"));
        ch_number->setGeometry(QRect(150, 80, 131, 21));
        ch_number->setReadOnly(true);
        label_3 = new QLabel(Select_Patient_Box);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 110, 121, 21));
        label_3->setTextFormat(Qt::AutoText);
        measurement = new QLineEdit(Select_Patient_Box);
        measurement->setObjectName(QString::fromUtf8("measurement"));
        measurement->setGeometry(QRect(150, 110, 131, 21));
        measurement->setReadOnly(true);
        label_4 = new QLabel(Select_Patient_Box);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 140, 121, 21));
        label_4->setTextFormat(Qt::AutoText);
        data_size = new QLineEdit(Select_Patient_Box);
        data_size->setObjectName(QString::fromUtf8("data_size"));
        data_size->setGeometry(QRect(150, 140, 131, 21));
        data_size->setReadOnly(true);
        label_5 = new QLabel(Select_Patient_Box);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 170, 121, 21));
        label_5->setTextFormat(Qt::AutoText);
        s_f = new QLineEdit(Select_Patient_Box);
        s_f->setObjectName(QString::fromUtf8("s_f"));
        s_f->setGeometry(QRect(150, 170, 131, 21));
        s_f->setReadOnly(true);
        label_6 = new QLabel(Select_Patient_Box);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 200, 121, 21));
        label_6->setTextFormat(Qt::AutoText);
        time_total = new QLineEdit(Select_Patient_Box);
        time_total->setObjectName(QString::fromUtf8("time_total"));
        time_total->setGeometry(QRect(150, 200, 131, 21));
        time_total->setReadOnly(true);
        re_sys = new QLineEdit(Select_Patient_Box);
        re_sys->setObjectName(QString::fromUtf8("re_sys"));
        re_sys->setGeometry(QRect(150, 230, 131, 21));
        re_sys->setReadOnly(true);
        label_7 = new QLabel(Select_Patient_Box);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 230, 121, 21));
        label_7->setTextFormat(Qt::AutoText);
        pt_check = new QLineEdit(Select_Patient_Box);
        pt_check->setObjectName(QString::fromUtf8("pt_check"));
        pt_check->setGeometry(QRect(150, 50, 131, 21));
        pt_check->setReadOnly(true);
        Select_Model_Box = new QGroupBox(centralWidget);
        Select_Model_Box->setObjectName(QString::fromUtf8("Select_Model_Box"));
        Select_Model_Box->setGeometry(QRect(10, 340, 291, 321));
        selectModelButton = new QPushButton(Select_Model_Box);
        selectModelButton->setObjectName(QString::fromUtf8("selectModelButton"));
        selectModelButton->setGeometry(QRect(10, 20, 81, 21));
        model_fileName = new QLineEdit(Select_Model_Box);
        model_fileName->setObjectName(QString::fromUtf8("model_fileName"));
        model_fileName->setGeometry(QRect(100, 20, 181, 21));
        icModelButton = new QPushButton(Select_Model_Box);
        icModelButton->setObjectName(QString::fromUtf8("icModelButton"));
        icModelButton->setGeometry(QRect(10, 50, 111, 20));
        model_check = new QLineEdit(Select_Model_Box);
        model_check->setObjectName(QString::fromUtf8("model_check"));
        model_check->setGeometry(QRect(150, 50, 131, 21));
        model_check->setReadOnly(true);
        label_d = new QLineEdit(Select_Model_Box);
        label_d->setObjectName(QString::fromUtf8("label_d"));
        label_d->setGeometry(QRect(150, 290, 131, 21));
        label_d->setReadOnly(true);
        label_8 = new QLabel(Select_Model_Box);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 290, 121, 21));
        label_8->setTextFormat(Qt::AutoText);
        label_9 = new QLabel(Select_Model_Box);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 260, 121, 21));
        label_9->setTextFormat(Qt::AutoText);
        label_10 = new QLabel(Select_Model_Box);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 80, 121, 21));
        label_10->setTextFormat(Qt::AutoText);
        model_k = new QLineEdit(Select_Model_Box);
        model_k->setObjectName(QString::fromUtf8("model_k"));
        model_k->setGeometry(QRect(150, 80, 131, 21));
        model_k->setReadOnly(true);
        feature_d = new QLineEdit(Select_Model_Box);
        feature_d->setObjectName(QString::fromUtf8("feature_d"));
        feature_d->setGeometry(QRect(150, 260, 131, 21));
        feature_d->setReadOnly(true);
        label = new QLabel(Select_Model_Box);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 170, 121, 21));
        label_k3 = new QLineEdit(Select_Model_Box);
        label_k3->setObjectName(QString::fromUtf8("label_k3"));
        label_k3->setGeometry(QRect(150, 170, 131, 21));
        label_k3->setReadOnly(true);
        label_k4 = new QLineEdit(Select_Model_Box);
        label_k4->setObjectName(QString::fromUtf8("label_k4"));
        label_k4->setGeometry(QRect(150, 200, 131, 21));
        label_k4->setReadOnly(true);
        label_13 = new QLabel(Select_Model_Box);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 200, 121, 21));
        label_k5 = new QLineEdit(Select_Model_Box);
        label_k5->setObjectName(QString::fromUtf8("label_k5"));
        label_k5->setGeometry(QRect(150, 230, 131, 21));
        label_k5->setReadOnly(true);
        label_14 = new QLabel(Select_Model_Box);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 230, 121, 21));
        label_16 = new QLabel(Select_Model_Box);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 110, 121, 21));
        label_k1 = new QLineEdit(Select_Model_Box);
        label_k1->setObjectName(QString::fromUtf8("label_k1"));
        label_k1->setGeometry(QRect(150, 110, 131, 21));
        label_k1->setReadOnly(true);
        label_k2 = new QLineEdit(Select_Model_Box);
        label_k2->setObjectName(QString::fromUtf8("label_k2"));
        label_k2->setGeometry(QRect(150, 140, 131, 21));
        label_k2->setReadOnly(true);
        label_15 = new QLabel(Select_Model_Box);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 140, 121, 21));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(300, 10, 31, 651));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        Diagnoses_Box = new QGroupBox(centralWidget);
        Diagnoses_Box->setObjectName(QString::fromUtf8("Diagnoses_Box"));
        Diagnoses_Box->setGeometry(QRect(330, 10, 920, 51));
        label_11 = new QLabel(Diagnoses_Box);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 51, 21));
        label_11->setTextFormat(Qt::AutoText);
        result = new QLineEdit(Diagnoses_Box);
        result->setObjectName(QString::fromUtf8("result"));
        result->setGeometry(QRect(70, 20, 111, 21));
        result->setReadOnly(true);
        label_12 = new QLabel(Diagnoses_Box);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(210, 20, 71, 21));
        label_12->setTextFormat(Qt::AutoText);
        conf = new QLineEdit(Diagnoses_Box);
        conf->setObjectName(QString::fromUtf8("conf"));
        conf->setGeometry(QRect(290, 20, 121, 21));
        conf->setReadOnly(true);
        exportButton = new QPushButton(Diagnoses_Box);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(700, 20, 81, 21));
        testButton = new QPushButton(Diagnoses_Box);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        testButton->setGeometry(QRect(580, 20, 81, 21));
        pushButton_clear = new QPushButton(Diagnoses_Box);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setGeometry(QRect(820, 20, 80, 20));
        Select_Mode_Box = new QGroupBox(centralWidget);
        Select_Mode_Box->setObjectName(QString::fromUtf8("Select_Mode_Box"));
        Select_Mode_Box->setGeometry(QRect(10, 10, 291, 51));
        Select_Mode_Box->setFlat(false);
        radioButton = new QRadioButton(Select_Mode_Box);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 20, 121, 18));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(Select_Mode_Box);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(150, 20, 121, 18));
        PSD_GM_Box = new QGroupBox(centralWidget);
        PSD_GM_Box->setObjectName(QString::fromUtf8("PSD_GM_Box"));
        PSD_GM_Box->setGeometry(QRect(330, 70, 920, 156));
        label_psd_dm = new QLabel(PSD_GM_Box);
        label_psd_dm->setObjectName(QString::fromUtf8("label_psd_dm"));
        label_psd_dm->setGeometry(QRect(2, 21, 920, 138));
        Signal_TD_Box = new QGroupBox(centralWidget);
        Signal_TD_Box->setObjectName(QString::fromUtf8("Signal_TD_Box"));
        Signal_TD_Box->setGeometry(QRect(330, 230, 920, 231));
        comboBox_up = new QComboBox(Signal_TD_Box);
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->addItem(QString());
        comboBox_up->setObjectName(QString::fromUtf8("comboBox_up"));
        comboBox_up->setGeometry(QRect(10, 60, 72, 22));
        comboBox_down = new QComboBox(Signal_TD_Box);
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->addItem(QString());
        comboBox_down->setObjectName(QString::fromUtf8("comboBox_down"));
        comboBox_down->setGeometry(QRect(10, 170, 72, 22));
        scrollArea_ch_up = new QScrollArea(Signal_TD_Box);
        scrollArea_ch_up->setObjectName(QString::fromUtf8("scrollArea_ch_up"));
        scrollArea_ch_up->setGeometry(QRect(90, 18, 830, 100));
        scrollArea_ch_up->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_ch_up->setWidgetResizable(false);
        scrollArea_ch_up->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 898, 98));
        scrollArea_ch_up->setWidget(scrollAreaWidgetContents_2);
        label_ch_up = new QLabel(Signal_TD_Box);
        label_ch_up->setObjectName(QString::fromUtf8("label_ch_up"));
        label_ch_up->setGeometry(QRect(20, 40, 0, 0));
        scrollArea_ch_down = new QScrollArea(Signal_TD_Box);
        scrollArea_ch_down->setObjectName(QString::fromUtf8("scrollArea_ch_down"));
        scrollArea_ch_down->setGeometry(QRect(90, 130, 830, 100));
        scrollArea_ch_down->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_ch_down->setWidgetResizable(false);
        scrollArea_ch_down->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 908, 98));
        scrollArea_ch_down->setWidget(scrollAreaWidgetContents_3);
        label_ch_down = new QLabel(Signal_TD_Box);
        label_ch_down->setObjectName(QString::fromUtf8("label_ch_down"));
        label_ch_down->setGeometry(QRect(20, 200, 0, 0));
        PSD_FM_Box = new QGroupBox(centralWidget);
        PSD_FM_Box->setObjectName(QString::fromUtf8("PSD_FM_Box"));
        PSD_FM_Box->setGeometry(QRect(330, 470, 920, 190));
        scrollArea_psd_fm = new QScrollArea(PSD_FM_Box);
        scrollArea_psd_fm->setObjectName(QString::fromUtf8("scrollArea_psd_fm"));
        scrollArea_psd_fm->setGeometry(QRect(0, 18, 920, 170));
        scrollArea_psd_fm->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea_psd_fm->setWidgetResizable(false);
        scrollArea_psd_fm->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 998, 201));
        scrollArea_psd_fm->setWidget(scrollAreaWidgetContents);
        label_psd_fm = new QLabel(PSD_FM_Box);
        label_psd_fm->setObjectName(QString::fromUtf8("label_psd_fm"));
        label_psd_fm->setGeometry(QRect(150, 0, 0, 0));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1260, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setIconSize(QSize(32, 32));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Epilepsy Detection", nullptr));
        Select_Patient_Box->setTitle(QApplication::translate("MainWindow", "Select Patient", nullptr));
        selectPatientButton->setText(QApplication::translate("MainWindow", "Select file", nullptr));
        icPatientButton->setText(QApplication::translate("MainWindow", "Input and Check", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Number of Channels:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Measurement:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Size of Data:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Sampling Frequency:", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Total Duration:", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Reference System:", nullptr));
        Select_Model_Box->setTitle(QApplication::translate("MainWindow", "Select Model", nullptr));
        selectModelButton->setText(QApplication::translate("MainWindow", "Select file", nullptr));
        icModelButton->setText(QApplication::translate("MainWindow", "Input and Check", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Label Dimension:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Feature Dimension:", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Kernel of Model:", nullptr));
        label->setText(QApplication::translate("MainWindow", "Sub-Kernel 3", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Sub-Kernel 4", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Sub-Kernel 5", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Sub-Kernel 1", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Sub-Kernel 2", nullptr));
        Diagnoses_Box->setTitle(QApplication::translate("MainWindow", "Diagnoses", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Result:", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Confidence:", nullptr));
        exportButton->setText(QApplication::translate("MainWindow", "Export", nullptr));
        testButton->setText(QApplication::translate("MainWindow", "Test", nullptr));
        pushButton_clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        Select_Mode_Box->setTitle(QApplication::translate("MainWindow", "Select Mode", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "Single Diagnosis", nullptr));
        radioButton_2->setText(QApplication::translate("MainWindow", "Multi Diagnosis", nullptr));
        PSD_GM_Box->setTitle(QApplication::translate("MainWindow", "PSD Gradient Map", nullptr));
        label_psd_dm->setText(QApplication::translate("MainWindow", "PSD_GM", nullptr));
        Signal_TD_Box->setTitle(QApplication::translate("MainWindow", "Signal - Time Domain ", nullptr));
        comboBox_up->setItemText(0, QApplication::translate("MainWindow", "ch_1", nullptr));
        comboBox_up->setItemText(1, QApplication::translate("MainWindow", "ch_2", nullptr));
        comboBox_up->setItemText(2, QApplication::translate("MainWindow", "ch_3", nullptr));
        comboBox_up->setItemText(3, QApplication::translate("MainWindow", "ch_4", nullptr));
        comboBox_up->setItemText(4, QApplication::translate("MainWindow", "ch_5", nullptr));
        comboBox_up->setItemText(5, QApplication::translate("MainWindow", "ch_6", nullptr));
        comboBox_up->setItemText(6, QApplication::translate("MainWindow", "ch_7", nullptr));
        comboBox_up->setItemText(7, QApplication::translate("MainWindow", "ch_8", nullptr));
        comboBox_up->setItemText(8, QApplication::translate("MainWindow", "ch_9", nullptr));

        comboBox_down->setItemText(0, QApplication::translate("MainWindow", "ch_2", nullptr));
        comboBox_down->setItemText(1, QApplication::translate("MainWindow", "ch_1", nullptr));
        comboBox_down->setItemText(2, QApplication::translate("MainWindow", "ch_3", nullptr));
        comboBox_down->setItemText(3, QApplication::translate("MainWindow", "ch_4", nullptr));
        comboBox_down->setItemText(4, QApplication::translate("MainWindow", "ch_5", nullptr));
        comboBox_down->setItemText(5, QApplication::translate("MainWindow", "ch_6", nullptr));
        comboBox_down->setItemText(6, QApplication::translate("MainWindow", "ch_7", nullptr));
        comboBox_down->setItemText(7, QApplication::translate("MainWindow", "ch_8", nullptr));
        comboBox_down->setItemText(8, QApplication::translate("MainWindow", "ch_9", nullptr));

        label_ch_up->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_ch_down->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        PSD_FM_Box->setTitle(QApplication::translate("MainWindow", "PSD - Frequency Domain", nullptr));
        label_psd_fm->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
