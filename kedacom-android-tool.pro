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
    phonedockwidget.cpp

HEADERS  += mainwindow.h \
    ksetting.h \
    adbprocess.h \
    screenshotthread.h \
    screenshot.h \
    screendockwidget.h \
    phonedockwidget.h

FORMS    += mainwindow.ui \
    screenshot.ui \
    screendockwidget.ui \
    phonedockwidget.ui

RESOURCES += \
    kt.qrc
