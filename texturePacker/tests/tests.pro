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
    imagetest.cpp \
    pngtest.cpp \
    pvrtest.cpp

INCLUDEPATH +=  $$PWD \
                $$PWD/../

HEADERS += \
    fileutilstest.h \
    publishertest.h \
    imagetest.h \
    pngtest.h \
    pvrtest.h

macx {
    QMAKE_POST_LINK =   rm -rf images && cp -rf $$PWD/images ./ && \
                        rm -rf input && cp -rf $$PWD/input ./ && \
                        rm -rf output && mkdir output
}