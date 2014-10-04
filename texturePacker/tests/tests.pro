#-------------------------------------------------
#
# Project created by QtCreator 2014-10-02T11:37:01
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($$PWD/../common/common.pri)

include($$PWD/../library/pvr/pvr.pri)

SOURCES += \
    fileutilstest.cpp \
    publishertest.cpp \
    main.cpp \
    pvrabstracttest.cpp \
    pvrpngtest.cpp

INCLUDEPATH +=  $$PWD \
                $$PWD/../

HEADERS += \
    fileutilstest.h \
    publishertest.h \
    pvrabstracttest.h \
    pvrpngtest.h
