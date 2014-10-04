HEADERS +=  $$PWD/include/PVRTArray.h \
            $$PWD/include/PVRTDecompress.h \
            $$PWD/include/PVRTError.h \
            $$PWD/include/PVRTGlobal.h \
            $$PWD/include/PVRTMap.h \
            $$PWD/include/PVRTString.h \
            $$PWD/include/PVRTTexture.h \
            $$PWD/include/PVRTexture.h \
            $$PWD/include/PVRTextureDefines.h \
            $$PWD/include/PVRTextureFormat.h \
            $$PWD/include/PVRTextureHeader.h \
            $$PWD/include/PVRTextureUtilities.h \
            $$PWD/include/PVRTextureVersion.h

INCLUDEPATH += $$PWD

macx:   LIBS += -L$$PWD/libs/mac/ -lPVRTexLib
else:unix:   LIBS += -L$$PWD/libs/unix/ -lPVRTexLib
else:win32:  LIBS += -L$$PWD/libs/mac/ -lPVRTexLib

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
