#include <QFile>
#include "include/png.h"

PNG::PNG():Image()
    , m_pImg(NULL)
{
}

PNG::PNG(QString filename):Image(filename)
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
    QFile file(filePath());
    if (!file.exists())
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
