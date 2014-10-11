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

macx: LIBS += -L$$PWD/libs/mac/ -lPVRTexLib

CONFIG(32bit){
    unix: LIBS += -L$$PWD/libs/linux_32/ -lPVRTexLib
}

CONFIG(64bit) {
    unix: LIBS += -L$$PWD/libs/linux_64/ -lPVRTexLib
}

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs
