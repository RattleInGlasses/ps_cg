#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T13:46:25
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Walk3D
TEMPLATE = app


SOURCES += main.cpp \
    ui/window3d.cpp \
    nodes/coloredcube.cpp \
    gl/scenenode.cpp \
    gl/basescene.cpp \
    gameapplication.cpp \
    gl/glhelper.cpp \
    gl/rotatingcamera.cpp \
    gl/freecamera.cpp \
    gl/viewcontorller.cpp \
    nodes/cylinder.cpp

HEADERS  += \
    ui/window3d.h \
    gl/scenenode.h \
    nodes/coloredcube.h \
    gl/basescene.h \
    gameapplication.h \
    gl/iscenecamera.h \
    gl/glhelper.h \
    gl/rotatingcamera.h \
    gl/freecamera.h \
    gl/viewcontorller.h \
    nodes/cylinder.h

FORMS    +=

LIBS += -lopengl32
