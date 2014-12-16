#include "include/pvr.h"
#include "include/ziputils.h"
#include "include/fileutils.h"
#include "include/png.h"

PVR::PVR():
    BipImage()
  , m_pvrTexture(NULL)
{
}

PVR::PVR(const QString & filename):
    BipImage(filename)
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

    if (result && m_pvrTexture)
    {
        setWidth(m_pvrTexture->getWidth());
        setHeight(m_pvrTexture->getHeight());
    }

    return result;
}

bool PVR::loadData(const unsigned char *pData, unsigned long size)
{
    if ((NULL != pData) && (size > 0))
    {
        m_pvrTexture = new pvrtexture::CPVRTexture(pData);
        if (NULL != m_pvrTexture)
        {
            setWidth(m_pvrTexture->getWidth());
            setHeight(m_pvrTexture->getHeight());
            return true;
        }
    }

    return false;
}

bool PVR::loadCCZData(const unsigned char *pData, unsigned long size)
{
    unsigned char * out = NULL;
    int len = ZipUtils::ccInflateCCZData(pData, size, &out);

    if ((len > 0) && (out != NULL))
    {
        bool result = loadData(out, len);
        delete []out;
        return result;
    }

    return false;
}

bool PVR::save(const QString & filename)
{
    if (m_pvrTexture == NULL)
    {
        return false;
    }

    return m_pvrTexture->saveFile(filename.toStdString().c_str());
}

unsigned char * PVR::saveToBuffer(unsigned long *size)
{
    QString path = FileUtils::createImageTempFolder() + "/" + FileUtils::getRandFileNameString() + ".pvr";
    *size = 0;
    if (!save(path))
    {
        return NULL;
    }

    unsigned char * result = FileUtils::getFileData(path.toStdString().c_str(), "rb", size);

    FileUtils::unlink(path);

    return result;
}

bool PVR::saveCCZ(const QString & filename)
{
    unsigned long fileSize = 0;
    unsigned char * pvrData = saveToBuffer(&fileSize);
    if (pvrData != NULL)
    {
        bool result = false;
        if (ZipUtils::ccDeflateCCZFile(filename.toStdString().c_str(), pvrData, fileSize))
        {
            result = true;
        }

        delete [] pvrData;

        return result;
    }

    return false;
}

unsigned char * PVR::saveCCZToBuffer(unsigned long *size)
{
    unsigned long fileSize = 0;
    *size = 0;

    unsigned char * pvrData = saveToBuffer(&fileSize);
    if (pvrData != NULL)
    {
        unsigned char * out = NULL;
        *size = ZipUtils::ccDeflateCCZData(pvrData, fileSize, &out);
        if ((*size) > 1)
        {
            return out;
        }
    }

    return NULL;
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

PNG *PVR::convertToPng()
{
    if (NULL == m_pvrTexture)
    {
        return NULL;
    }

    int len = 4 * width() * height();
    if (len > 4)
    {
        unsigned char * buffer = new unsigned char [len];
        if (PVRTDecompressPVRTC(m_pvrTexture->getDataPtr(), 0, width(), height(), buffer) < 1)
        {
            delete [] buffer;
            return NULL;
        }

        PNG * result = new PNG;

        if (result->loadData(buffer, width(), height()))
        {
            delete [] buffer;
            return result;
        }

        delete []buffer;
        delete result;
    }
    return NULL;
}

