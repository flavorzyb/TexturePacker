#include "include/pvr.h"
#include "include/PVRTDecompress.h"
#include "include/PVRTexture.h"
#include "include/PVRTextureUtilities.h"

PVR::PVR():Image()
{
}

PVR::PVR(QString filename):Image(filename)
{
}

PVR::PVR(const PVR &pvr):Image(pvr)
{
}

bool PVR::load()
{
    if (!exists(filePath()))
    {
        return false;
    }

    return true;
}
