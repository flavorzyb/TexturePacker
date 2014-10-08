########################################
#
########################################

QT += gui


include($$PWD/../library/pvr/pvr.pri)

HEADERS +=  $$PWD/include/config.h \
            $$PWD/include/settingsvo.h \
            $$PWD/include/publisher.h \
            $$PWD/include/fileutils.h \
            $$PWD/include/image.h \
            $$PWD/include/png.h \
            $$PWD/include/pvr.h \
            $$PWD/include/jpeg.h \
            $$PWD/include/ziputils.h \
            $$PWD/include/macros.h \
            $$PWD/include/imageutils.h \
            $$PWD/include/imagevo.h \
            $$PWD/include/reader.h \
            $$PWD/include/writer.h

SOURCES +=  $$PWD/src/config.cpp \
            $$PWD/src/settingsvo.cpp \
            $$PWD/src/publisher.cpp \
            $$PWD/src/fileutils.cpp \
            $$PWD/src/image.cpp \
            $$PWD/src/png.cpp \
            $$PWD/src/pvr.cpp \
            $$PWD/src/jpeg.cpp \
            $$PWD/src/ziputils.cpp \
            $$PWD/src/imageutils.cpp \
            $$PWD/src/imagevo.cpp \
            $$PWD/src/reader.cpp \
            $$PWD/src/writer.cpp

INCLUDEPATH += $$PWD

LIBS += -lz
