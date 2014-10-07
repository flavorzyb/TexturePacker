#include "include/imagevo.h"

ImageVO::ImageVO(const QSize &size):
    m_sourceSize(size)
  , m_offset(0,0)
  , m_rect(0, 0, 0, 0)
  , m_rotated(false)
  , m_fileName("")
{
}

ImageVO::ImageVO(int w, int h):
    m_sourceSize(w, h)
  , m_offset(0,0)
  , m_rect(0, 0, 0, 0)
  , m_rotated(false)
  , m_fileName("")
{
}

ImageVO::ImageVO(const ImageVO &ivo):
    m_sourceSize(ivo.m_sourceSize)
  , m_offset(ivo.m_offset)
  , m_rect(ivo.m_rect)
  , m_rotated(ivo.m_rotated)
  , m_fileName(ivo.m_fileName)
{

}
QSize ImageVO::sourceSize() const
{
    return m_sourceSize;
}

void ImageVO::setSourceSize(const QSize &sourceSize)
{
    m_sourceSize = sourceSize;
}
QSize ImageVO::offset() const
{
    return m_offset;
}

void ImageVO::setOffset(const QSize &offset)
{
    m_offset = offset;
}
QRect ImageVO::rect() const
{
    return m_rect;
}

void ImageVO::setRect(const QRect &rect)
{
    m_rect = rect;
}
bool ImageVO::rotated() const
{
    return m_rotated;
}

void ImageVO::setRotated(bool rotated)
{
    m_rotated = rotated;
}
QString ImageVO::fileName() const
{
    return m_fileName;
}

void ImageVO::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}
