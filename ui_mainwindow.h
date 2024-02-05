/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_O;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QWidget *centralwidget;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *SelectButton;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEdit;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *SaveButton;
    QPushButton *ExecuteButton;
    QPushButton *ExitButton;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labela;
    QLineEdit *lineEdit_a;
    QLabel *labelb;
    QLineEdit *lineEdit_b;
    QLabel *labelc;
    QLineEdit *lineEdit_c;
    QLabel *labeld;
    QLineEdit *lineEdit_d;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *imagelabel1;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *comboBox_2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *imagelabel2;
    QPushButton *clearButton;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_E;
    QMenu *menu_B;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1078, 609);
        action_O = new QAction(MainWindow);
        action_O->setObjectName(QStringLiteral("action_O"));
        newAction = new QAction(MainWindow);
        newAction->setObjectName(QStringLiteral("newAction"));
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QStringLiteral("openAction"));
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(9, 9, 471, 521));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        SelectButton = new QPushButton(groupBox);
        SelectButton->setObjectName(QStringLiteral("SelectButton"));

        horizontalLayout->addWidget(SelectButton);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        horizontalLayout_3->addWidget(textEdit);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        SaveButton = new QPushButton(groupBox_3);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));

        horizontalLayout_2->addWidget(SaveButton);

        ExecuteButton = new QPushButton(groupBox_3);
        ExecuteButton->setObjectName(QStringLiteral("ExecuteButton"));

        horizontalLayout_2->addWidget(ExecuteButton);

        ExitButton = new QPushButton(groupBox_3);
        ExitButton->setObjectName(QStringLiteral("ExitButton"));

        horizontalLayout_2->addWidget(ExitButton);


        verticalLayout->addWidget(groupBox_3);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(485, 9, 501, 511));
        verticalLayout_5 = new QVBoxLayout(groupBox_5);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        labela = new QLabel(groupBox_6);
        labela->setObjectName(QStringLiteral("labela"));

        horizontalLayout_4->addWidget(labela);

        lineEdit_a = new QLineEdit(groupBox_6);
        lineEdit_a->setObjectName(QStringLiteral("lineEdit_a"));

        horizontalLayout_4->addWidget(lineEdit_a);

        labelb = new QLabel(groupBox_6);
        labelb->setObjectName(QStringLiteral("labelb"));

        horizontalLayout_4->addWidget(labelb);

        lineEdit_b = new QLineEdit(groupBox_6);
        lineEdit_b->setObjectName(QStringLiteral("lineEdit_b"));

        horizontalLayout_4->addWidget(lineEdit_b);

        labelc = new QLabel(groupBox_6);
        labelc->setObjectName(QStringLiteral("labelc"));

        horizontalLayout_4->addWidget(labelc);

        lineEdit_c = new QLineEdit(groupBox_6);
        lineEdit_c->setObjectName(QStringLiteral("lineEdit_c"));

        horizontalLayout_4->addWidget(lineEdit_c);

        labeld = new QLabel(groupBox_6);
        labeld->setObjectName(QStringLiteral("labeld"));

        horizontalLayout_4->addWidget(labeld);

        lineEdit_d = new QLineEdit(groupBox_6);
        lineEdit_d->setObjectName(QStringLiteral("lineEdit_d"));

        horizontalLayout_4->addWidget(lineEdit_d);


        verticalLayout_5->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(groupBox_5);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_2 = new QVBoxLayout(groupBox_7);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_8 = new QGroupBox(groupBox_7);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_8);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        comboBox = new QComboBox(groupBox_8);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_5->addWidget(comboBox);

        scrollArea = new QScrollArea(groupBox_8);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 419, 159));
        imagelabel1 = new QLabel(scrollAreaWidgetContents);
        imagelabel1->setObjectName(QStringLiteral("imagelabel1"));
        imagelabel1->setGeometry(QRect(0, 0, 391, 161));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_5->addWidget(scrollArea);


        verticalLayout_2->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(groupBox_7);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_9);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        comboBox_2 = new QComboBox(groupBox_9);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_7->addWidget(comboBox_2);

        scrollArea_2 = new QScrollArea(groupBox_9);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setWidgetResizable(false);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 419, 159));
        imagelabel2 = new QLabel(scrollAreaWidgetContents_3);
        imagelabel2->setObjectName(QStringLiteral("imagelabel2"));
        imagelabel2->setGeometry(QRect(0, 0, 391, 161));
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        horizontalLayout_7->addWidget(scrollArea_2);


        verticalLayout_2->addWidget(groupBox_9);

        clearButton = new QPushButton(groupBox_7);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        verticalLayout_2->addWidget(clearButton);


        verticalLayout_5->addWidget(groupBox_7);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1078, 22));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_E = new QMenu(menubar);
        menu_E->setObjectName(QStringLiteral("menu_E"));
        menu_B = new QMenu(menubar);
        menu_B->setObjectName(QStringLiteral("menu_B"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_E->menuAction());
        menubar->addAction(menu_B->menuAction());
        menu_F->addAction(newAction);
        menu_F->addAction(openAction);
        menu_F->addAction(saveAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_O->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", Q_NULLPTR));
        newAction->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", Q_NULLPTR));
        openAction->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", Q_NULLPTR));
        saveAction->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(&F)", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\351\200\211\346\213\251", Q_NULLPTR));
        SelectButton->setText(QApplication::translate("MainWindow", "select", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221\345\214\272", Q_NULLPTR));
        groupBox_3->setTitle(QString());
        SaveButton->setText(QApplication::translate("MainWindow", "Save to", Q_NULLPTR));
        ExecuteButton->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
        ExitButton->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        groupBox_5->setTitle(QString());
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\346\225\260\346\215\256\345\261\225\347\244\272\345\214\272", Q_NULLPTR));
        labela->setText(QApplication::translate("MainWindow", "a:", Q_NULLPTR));
        labelb->setText(QApplication::translate("MainWindow", "b:", Q_NULLPTR));
        labelc->setText(QApplication::translate("MainWindow", "c:", Q_NULLPTR));
        labeld->setText(QApplication::translate("MainWindow", "d:", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "\345\233\276\347\211\207\345\261\225\347\244\272\345\214\272", Q_NULLPTR));
        groupBox_8->setTitle(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "chl1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl8", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl9", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl10", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl11", Q_NULLPTR)
        );
        imagelabel1->setText(QString());
        groupBox_9->setTitle(QString());
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "chl2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl8", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl9", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl10", Q_NULLPTR)
         << QApplication::translate("MainWindow", "chl11", Q_NULLPTR)
        );
        imagelabel2->setText(QString());
        clearButton->setText(QApplication::translate("MainWindow", "clear", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
        menu_E->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", Q_NULLPTR));
        menu_B->setTitle(QApplication::translate("MainWindow", "\346\236\204\345\273\272(&B)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
