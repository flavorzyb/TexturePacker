#include "include/pvr.h"
#include "include/ziputils.h"
#include "include/fileutils.h"
#include <unistd.h>

PVR::PVR():
    Image()
  , m_pvrTexture(NULL)
  , m_imagevo(0, 0)
{
}

PVR::PVR(const QString & filename):
    Image(filename)
  , m_pvrTexture(NULL)
  , m_imagevo(0, 0)
{
}

PVR::PVR(const PVR &pvr):
    Image(pvr)
  , m_pvrTexture(NULL)
  , m_imagevo(pvr.m_imagevo)
{
    if (pvr.m_pvrTexture != NULL)
    {
        m_pvrTexture = new pvrtexture::CPVRTexture(*pvr.m_pvrTexture);
    }
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

    if (result && m_pvrTexture)
    {
        setWidth(m_pvrTexture->getWidth());
        setHeight(m_pvrTexture->getHeight());
    }

    return result;
}

bool PVR::save(const QString & filename)
{
    if (m_pvrTexture == NULL)
    {
        return false;
    }

    return m_pvrTexture->saveFile(filename.toStdString().c_str());
}

bool PVR::saveCCZ(const QString & filename)
{
    QString path = FileUtils::createImageTempFolder() + "/" + FileUtils::getRandFileNameString() + ".pvr";
    if (save(path))
    {
        unsigned long fileSize = 0;
        unsigned char * pvrdata = FileUtils::getFileData(path.toStdString().c_str(), "rb", &fileSize);
        unlink(path.toStdString().c_str());

        if ((pvrdata != NULL) && (fileSize > 0))
        {
            if (ZipUtils::ccDeflateCCZFile(filename.toStdString().c_str(), pvrdata, fileSize))
            {
                delete []pvrdata;
                return true;
            }
        }

        delete []pvrdata;
    }

    return false;
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
ImageVO PVR::imagevo() const
{
    return m_imagevo;
}

void PVR::setImagevo(const ImageVO & imagevo)
{
    m_imagevo = imagevo;
}

