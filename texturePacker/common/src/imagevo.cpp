#include "include/imagevo.h"

ImageVO::ImageVO(const QSize &size):
    m_sourceSize(size)
  , m_offset(0,0)
  , m_rect(0, 0, 0, 0)
  , m_rotated(false)
  , m_fileName("")
  , m_sourceColorRect(0 ,0, 0, 0)
  , m_size(0, 0)
  , m_md5String("")
{
}

ImageVO::ImageVO(int w, int h):
    m_sourceSize(w, h)
  , m_offset(0,0)
  , m_rect(0, 0, 0, 0)
  , m_rotated(false)
  , m_fileName("")
  , m_sourceColorRect(0 ,0, 0, 0)
  , m_size(0, 0)
  , m_md5String("")
{
}

ImageVO::ImageVO(const ImageVO &ivo):
    m_sourceSize(ivo.m_sourceSize)
  , m_offset(ivo.m_offset)
  , m_rect(ivo.m_rect)
  , m_rotated(ivo.m_rotated)
  , m_fileName(ivo.m_fileName)
  , m_sourceColorRect(ivo.m_sourceColorRect)
  , m_size(ivo.m_size)
  , m_md5String(ivo.m_md5String)
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

void ImageVO::setSourceSize(int width, int height)
{
    m_sourceSize = QSize(width, height);
}
QPoint ImageVO::offset() const
{
    return m_offset;
}

void ImageVO::setOffset(const QPoint &offset)
{
    m_offset = offset;
}

void ImageVO::setOffset(int x, int y)
{
    m_offset = QPoint(x, y);
}
QRect ImageVO::rect() const
{
    return m_rect;
}

void ImageVO::setRect(const QRect &rect)
{
    m_rect = rect;
}

void ImageVO::setRect(int x, int y, int width, int height)
{
    m_rect = QRect(x, y, width, height);
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

const ImageVO & ImageVO::operator=(const ImageVO &ivo)
{
    m_fileName          = ivo.m_fileName;
    m_sourceSize        = ivo.m_sourceSize;
    m_offset            = ivo.m_offset;

    m_rect              = ivo.m_rect;
    m_rotated           = ivo.m_rotated;
    m_sourceColorRect   = ivo.m_sourceColorRect;

    m_size              = ivo.m_size;
    m_md5String         = ivo.m_md5String;

    return (*this);
}
QRect ImageVO::sourceColorRect() const
{
    return m_sourceColorRect;
}

void ImageVO::setSourceColorRect(const QRect &sourceColorRect)
{
    m_sourceColorRect = sourceColorRect;
}

void ImageVO::setSourceColorRect(int x, int y, int width, int height)
{
    m_sourceColorRect = QRect(x, y, width, height);
}
QSize ImageVO::size() const
{
    return m_size;
}

void ImageVO::setSize(const QSize &size)
{
    m_size = size;
}

void ImageVO::setSize(int width, int height)
{
    m_size = QSize(width, height);
}
QString ImageVO::md5String() const
{
    return m_md5String;
}

void ImageVO::setMd5String(const QString &md5String)
{
    m_md5String = md5String;
}



