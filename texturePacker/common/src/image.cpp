#include <QFile>

#include "include/image.h"


Image::Image():
    m_filePath("")
  , m_width(0)
  , m_height(0)
{
}

Image::Image(QString filename):
    m_filePath(filename)
  , m_width(0)
  , m_height(0)
{

}

Image::Image(const Image &img):
    m_filePath(img.m_filePath)
  , m_width(img.m_width)
  , m_height(img.m_height)
{
}

bool Image::load(QString filename)
{
    setFilePath(filename);
    return load();
}

int Image::width() const
{
    return m_width;
}

void Image::setWidth(int width)
{
    m_width = width;
}
int Image::height() const
{
    return m_height;
}

void Image::setHeight(int height)
{
    m_height = height;
}

const QString & Image::filePath() const
{
    return m_filePath;
}

bool Image::exists(QString filename) const
{
    QFile file(filename);

    return file.exists();
}

void Image::setFilePath(const QString &filePath)
{
    m_filePath = filePath;
}
