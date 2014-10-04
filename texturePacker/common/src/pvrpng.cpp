#include <QFile>
#include <QImage>

#include "include/pvrpng.h"
#include "include/PVRTexture.h"
#include "include/PVRTDecompress.h"
#include "include/PVRTextureUtilities.h"

PVRPNG::PVRPNG():PVRAbstract()
{
}

PVRPNG::PVRPNG(QString filename):PVRAbstract(filename)
{
}

bool PVRPNG::load()
{
    QFile file(filePath());
    if (!file.exists())
    {
        return false;
    }

    QImage image(filePath(), "PNG");
    setWidth(image.width());
    setHeight(image.height());

    return true;
}

bool PVRPNG::save2Pvr()
{
    return true;
}
