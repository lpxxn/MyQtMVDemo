#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T10:26:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMVDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itemobject.cpp \
    itemmodel.cpp \
    mylistitemdelegege.cpp

HEADERS  += mainwindow.h \
    itemobject.h \
    itemmodel.h \
    mylistitemdelegege.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resource.qrc
