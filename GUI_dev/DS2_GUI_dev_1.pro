#-------------------------------------------------
#
# Project created by QtCreator 2024-01-17T22:20:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS2_GUI_dev_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DESTDIR = $$PWD/../DS2_GUI_issue

INCLUDEPATH += F:\python380\include

LIBS += -LF:\python380\libs\
-l_tkinter\
-lpython3\
-lpython38

DISTFILES += \
    ../build-DS2_GUI_dev_1-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug/predict.py \
    ../build-DS2_GUI_dev_1-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug/ds2_output.py \
    load_model.py

RESOURCES += \
    ds2_ico.qrc

RC_ICONS = ds2_ico_hd.ico
