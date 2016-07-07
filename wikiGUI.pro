#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T22:04:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wikiGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wikipage.cpp \
    progresswindow.cpp \
    compilethread.cpp \
    shared_data.cpp \
    direct_struct.cpp

HEADERS  += mainwindow.h \
    wikipage.h \
    progresswindow.h \
    compilethread.h \
    shared_data.h \
    direct_struct.h

FORMS    += mainwindow.ui \
    progresswindow.ui

DISTFILES += \
    ../wikiclassify/site/wikiclassify/images/logo.svg
