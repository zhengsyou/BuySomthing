#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T17:08:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BuyCoin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cznetworkaccessmanager.cpp \
    czorgnerve.cpp \
    czexception.cpp \
    czworkthread.cpp \
    cznetworkorgnerve.cpp

HEADERS  += mainwindow.h \
    cznetworkaccessmanager.h \
    czorgnerve.h \
    czexception.h \
    czworkthread.h \
    cznetworkorgnerve.h

FORMS    += mainwindow.ui
