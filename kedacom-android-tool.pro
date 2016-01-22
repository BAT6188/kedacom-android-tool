#-------------------------------------------------
#
# Project created by QtCreator 2016-01-09T11:36:58
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kedacom-android-tool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ksetting.cpp \
    adbprocess.cpp \
    screenshotthread.cpp \
    screenshot.cpp \
    screendockwidget.cpp \
    phonedockwidget.cpp \
    phoneconnectthread.cpp \
    phone.cpp \
    phonemanager.cpp \
    screenform.cpp \
    phonedetailwidget.cpp \
    chartlabel.cpp

HEADERS  += mainwindow.h \
    ksetting.h \
    adbprocess.h \
    screenshotthread.h \
    screenshot.h \
    screendockwidget.h \
    phonedockwidget.h \
    phoneconnectthread.h \
    phone.h \
    phonemanager.h \
    screenform.h \
    phonedetailwidget.h \
    chartlabel.h

FORMS    += mainwindow.ui \
    screenshot.ui \
    phonedockwidget.ui \
    screenform.ui \
    phonedetailwidget.ui

RESOURCES += \
    kt.qrc
