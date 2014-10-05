#include "include/pvr.h"
#include "include/ziputils.h"

PVR::PVR():
    Image()
  , m_pvrTexture(NULL)
{
}

PVR::PVR(const QString & filename):
    Image(filename)
  , m_pvrTexture(NULL)
{
}

PVR::PVR(const PVR &pvr):
    Image(pvr)
  , m_pvrTexture(NULL)
{
}

PVR::~PVR()
{
    if (m_pvrTexture != NULL)
    {
        delete m_pvrTexture;
    }
}

bool PVR::load()
{
    setWidth(0);
    setHeight(0);

    if (!exists(filePath()))
    {
        return false;
    }

    if (m_pvrTexture != NULL)
    {
        delete m_pvrTexture;
        m_pvrTexture = NULL;
    }

    bool result  = false;

    if (isPVRCCZFile(filePath()))
    {
        result = loadPVRCCZ(filePath());
    }
    else
    {
        result = loadPVR(filePath());
    }

    if (result)
    {
        setWidth(m_pvrTexture->getWidth());
        setHeight(m_pvrTexture->getHeight());
    }

    return result;
}

bool PVR::isPVRCCZFile(const QString &filename) const
{
    return filename.toLower().endsWith(".pvr.ccz");
}

bool PVR::loadPVRCCZ(const QString &filename)
{
    unsigned char * out = NULL;
    if (ZipUtils::ccInflateCCZFile(filename.toStdString().c_str(), &out) > 1)
    {
        m_pvrTexture = new pvrtexture::CPVRTexture(out);
        delete [] out;
        return true;
    }

    return false;
}

bool PVR::loadPVR(const QString &filename)
{
    m_pvrTexture = new pvrtexture::CPVRTexture(filename.toStdString().c_str());

    return true;
}
