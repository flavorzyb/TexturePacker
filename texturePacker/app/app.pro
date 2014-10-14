#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T14:42:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BipPacker
TEMPLATE = app

include($$PWD/../common/common.pri)

HEADERS  += $$PWD/include/mainwindow.h \
            $$PWD/include/aboutme.h \
            $$PWD/include/utils.h \
            $$PWD/include/publishthread.h \
            $$PWD/include/tpapplication.h \
            $$PWD/include/viewwindow.h \
            $$PWD/include/tpconsoleapplication.h

SOURCES +=  $$PWD/src/main.cpp\
            $$PWD/src/mainwindow.cpp \
            $$PWD/src/aboutme.cpp \
            $$PWD/src/utils.cpp \
            $$PWD/src/publishthread.cpp \
            $$PWD/src/tpapplication.cpp \
            $$PWD/src/viewwindow.cpp \
            $$PWD/src/tpconsoleapplication.cpp

INCLUDEPATH +=  $$PWD \
                $$PWD/../
macx {
    ICON = $$PWD/../resources/icon/tp.icns
    QMAKE_INFO_PLIST = $$PWD/../resources/Info.plist
    ##LIBS += -framework CoreFoundation
}
