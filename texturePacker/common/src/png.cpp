#include "include/png.h"
#include "include/imageutils.h"

PNG::PNG():Image()
    , m_pImg(NULL)
{
}

PNG::PNG(const QString & filename):Image(filename)
    , m_pImg(NULL)
{
}

PNG::~PNG()
{
    if (m_pImg != NULL)
    {
        delete m_pImg;
    }
}

bool PNG::load()
{
    if (!exists(filePath()))
    {
        return false;
    }

    if (m_pImg != NULL)
    {
        delete m_pImg;
    }

    m_pImg = new QImage(filePath(), "PNG");
    setWidth(m_pImg->width());
    setHeight(m_pImg->height());

    return true;
}

PVR * PNG::convertToPVR()
{
    if (m_pImg == NULL)
    {
        return NULL;
    }

    int pw = ImageUtils::getMinPowOf2(width());
    int ph = ImageUtils::getMinPowOf2(height());

    printf("widht: %d pw:%d height:%d ph:%d\n", width(), pw, height(), ph);
    return NULL;
}

bool PNG::save(const QString &filename)
{
    if (m_pImg == NULL)
    {
        return false;
    }

    return m_pImg->save(filename, "PNG");
}
