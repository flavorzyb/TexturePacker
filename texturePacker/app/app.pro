#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T14:42:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = texturePacker
TEMPLATE = app

INCLUDEPATH +=  $$PWD \
                $$PWD/../

include($$PWD/../common/common.pri)

SOURCES +=  $$PWD/src/main.cpp\
            $$PWD/src/mainwindow.cpp \
            $$PWD/src/aboutme.cpp \
            $$PWD/src/utils.cpp

HEADERS  += $$PWD/include/mainwindow.h \
            $$PWD/include/aboutme.h \
            $$PWD/include/utils.h
