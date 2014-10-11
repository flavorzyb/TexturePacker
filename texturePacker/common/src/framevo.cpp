#include "include/framevo.h"

FrameVO::FrameVO(const QSize &size):
    m_name("")
  , m_md5String("")
  , m_rect(0, 0, 0, 0)
  , m_offset(0,0)
  , m_rotated(false)
  , m_sourceColorRect(0 ,0, 0, 0)
  , m_sourceSize(size)
{

}

FrameVO::FrameVO(int width, int height):
    m_name("")
  , m_md5String("")
  , m_rect(0, 0, 0, 0)
  , m_offset(0,0)
  , m_rotated(false)
  , m_sourceColorRect(0 ,0, 0, 0)
  , m_sourceSize(width, height)
{

}

FrameVO::FrameVO(const FrameVO &fvo):
    m_name(fvo.m_name)
  , m_md5String(fvo.m_md5String)
  , m_rect(fvo.m_rect)
  , m_offset(fvo.m_offset)
  , m_rotated(fvo.m_rotated)
  , m_sourceColorRect(fvo.m_sourceColorRect)
  , m_sourceSize(fvo.m_sourceSize)
{
}

const FrameVO & FrameVO::operator= (const FrameVO &ivo)
{
    m_name              = ivo.m_name;
    m_md5String         = ivo.m_md5String;

    m_rect              = ivo.m_rect;
    m_offset            = ivo.m_offset;

    m_rotated           = ivo.m_rotated;
    m_sourceColorRect   = ivo.m_sourceColorRect;

    m_sourceSize        = ivo.m_sourceSize;

    return (*this);
}

QString FrameVO::name() const
{
    return m_name;
}

void FrameVO::setName(const QString &name)
{
    m_name = name;
}

QString FrameVO::md5String() const
{
    return m_md5String;
}

void FrameVO::setMd5String(const QString &md5String)
{
    m_md5String = md5String;
}

QRect FrameVO::rect() const
{
    return m_rect;
}

void FrameVO::setRect(const QRect &rect)
{
    m_rect = rect;
}

void FrameVO::setRect(int x, int y, int width, int height)
{
    m_rect = QRect(x, y, width, height);
}

QPoint FrameVO::offset() const
{
    return m_offset;
}

void FrameVO::setOffset(const QPoint &offset)
{
    m_offset = offset;
}

void FrameVO::setOffset(int x, int y)
{
    m_offset = QPoint(x, y);
}

bool FrameVO::rotated() const
{
    return m_rotated;
}

void FrameVO::setRotated(bool rotated)
{
    m_rotated = rotated;
}

QRect FrameVO::sourceColorRect() const
{
    return m_sourceColorRect;
}

void FrameVO::setSourceColorRect(const QRect &sourceColorRect)
{
    m_sourceColorRect = sourceColorRect;
}

void FrameVO::setSourceColorRect(int x, int y, int width, int height)
{
    m_sourceColorRect = QRect(x, y, width, height);
}

QSize FrameVO::sourceSize() const
{
    return m_sourceSize;
}

void FrameVO::setSourceSize(const QSize &sourceSize)
{
    m_sourceSize = sourceSize;
}

void FrameVO::setSourceSize(int width, int height)
{
    m_sourceSize = QSize(width, height);
}
