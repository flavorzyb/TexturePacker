########################################
#
########################################

HEADERS +=  $$PWD/include/config.h \
            $$PWD/include/settingsvo.h \
            $$PWD/include/publisher.h \
            $$PWD/include/fileutils.h \
            $$PWD/include/pvrabstract.h \
            $$PWD/include/pvrpng.h

SOURCES +=  $$PWD/src/config.cpp \
            $$PWD/src/settingsvo.cpp \
            $$PWD/src/publisher.cpp \
            $$PWD/src/fileutils.cpp \
            $$PWD/src/pvrabstract.cpp \
            $$PWD/src/pvrpng.cpp

INCLUDEPATH += $$PWD
