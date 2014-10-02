#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T11:37:01
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_teststest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($$PWD/../common/common.pri)

SOURCES += \
    fileutilstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH +=  $$PWD \
                $$PWD/../

HEADERS += \
    fileutilstest.h
