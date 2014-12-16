#include "include/etc.h"
#include "include/etcheader.h"
#include "include/fileutils.h"
#include "include/ziputils.h"

ETC::ETC():
    BipImage()
  , m_data(NULL)
  , m_size(0)
{
}

ETC::ETC(const QString & filename):
    BipImage(filename)
  , m_data(NULL)
  , m_size(0)
{
}

#define FREE_ETC_DATA() \
    do{ \
        if (m_data != NULL) \
        { \
            delete [] m_data; \
        } \
        m_data = NULL; \
        m_size = 0; \
    } \
    while(0)

ETC::~ETC()
{
    FREE_ETC_DATA();
}

bool ETC::load()
{
    setWidth(0);
    setHeight(0);

    if (!exists(filePath()))
    {
        return false;
    }

    return loadETC(filePath());
}

bool ETC::loadData(const unsigned char * pData, unsigned long size)
{
    if ((NULL != pData) && (size > 0))
    {
        ETCHeader header(pData);
        if (header.getWidth() < 1 || header.getWidth() < 1)
        {
            return false;
        }

        FREE_ETC_DATA();

        m_data = new unsigned char [size];
        memcpy(m_data, pData, size);
        m_size = size;

        setWidth(header.getWidth());
        setHeight(header.getHeight());

        return true;
    }

    return false;
}

bool ETC::loadCCZData(const unsigned char * pData, unsigned long size)
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

bool ETC::save(const QString & filename)
{
    if ((m_data != NULL) && (m_size > 16))
    {
        return FileUtils::writeFile(filename, "wb", m_data, m_size);
    }
    return false;
}

bool ETC::saveCCZ(const QString & filename)
{
    if ((m_data != NULL) && (m_size > 16))
    {
        return ZipUtils::ccDeflateCCZFile(filename,
                                          m_data, m_size);
    }

    return false;
}

unsigned char * ETC::saveCCZToBuffer(unsigned long *size)
{
    *size = 0;
    if ((m_data != NULL) && (m_size > 16))
    {
        unsigned char * result = NULL;
        *size = ZipUtils::ccDeflateCCZData(m_data, m_size, &result);

        if ((*size) > 1)
        {
            return result;
        }

        *size = 0;
    }

    return NULL;
}

bool ETC::loadETC(const QString & filename)
{
    FREE_ETC_DATA();

    m_data = FileUtils::getFileData(filename, "rb", &m_size);

    if ((m_size > 16) && (m_data != NULL))
    {
        ETCHeader header(m_data);
        if (header.getWidth() < 1 || header.getWidth() < 1)
        {
            FREE_ETC_DATA();
            return false;
        }

        setWidth(header.getWidth());
        setHeight(header.getHeight());

        return true;
    }

    FREE_ETC_DATA();
    return false;
}

#undef FREE_ETC_DATA
