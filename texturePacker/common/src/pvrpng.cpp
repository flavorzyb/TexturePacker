#include <QFile>

#include "include/pvrpng.h"

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



    return true;
}
