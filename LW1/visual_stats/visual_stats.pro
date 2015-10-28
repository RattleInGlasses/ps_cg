#-------------------------------------------------
#
# Project created by QtCreator 2015-09-03T20:55:05
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visual_stats
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    statstablemodel.cpp \
    statskeyvaluemodel.cpp \
    statsserializer.cpp \
    statsdocument.cpp \
    aboutdialog.cpp \
    insertrowdialog.cpp \
    customtableview.cpp \
    diagramwindow.cpp

HEADERS  += mainwindow.h \
    statstablemodel.h \
    basekeyvaluemodel.h \
    statskeyvaluemodel.h \
    statsserializer.h \
    statsdocument.h \
    istatsmodelprovider.h \
    aboutdialog.h \
    insertrowdialog.h \
    customtableview.h \
    diagramwindow.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    insertrowdialog.ui
