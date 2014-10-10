#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T17:55:34
#
#-------------------------------------------------
QT       += core
QT       -= gui
TARGET = texturePacker
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include($$PWD/../common/common.pri)

SOURCES += main.cpp

INCLUDEPATH +=  $$PWD \
                $$PWD/../

DEFINES +=TP_CMD_MODE=1
