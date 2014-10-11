#include "include/imagevo.h"

ImageVO::ImageVO(const QSize &size):
    m_fileName("")
  , m_size(size)
  , m_frames()
{
}

ImageVO::ImageVO(int w, int h):
    m_fileName("")
  , m_size(w, h)
  , m_frames()
{
}

ImageVO::ImageVO(const ImageVO &ivo):
    m_fileName(ivo.m_fileName)
  , m_size(ivo.m_size)
  , m_frames(ivo.m_frames)
{

}

QString ImageVO::fileName() const
{
    return m_fileName;
}

void ImageVO::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

const ImageVO & ImageVO::operator= (const ImageVO &ivo)
{
    m_fileName  = ivo.m_fileName;
    m_size      = ivo.m_size;
    m_frames    = ivo.m_frames;

    return (*this);
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

const QVector<FrameVO> & ImageVO::frames() const
{
    return m_frames;
}

void ImageVO::setFrames(const QVector<FrameVO> &frames)
{
    m_frames = frames;
}

void ImageVO::addFrame(const FrameVO &fvo)
{
    m_frames.push_back(fvo);
}

void ImageVO::chopFrameNamePath(const QString &path)
{
    QVector<FrameVO>::iterator iterator = m_frames.begin();
    for(; iterator != m_frames.end(); iterator++)
    {
        if (iterator->name().startsWith(path))
        {
            iterator->setName(iterator->name().right(iterator->name().length() - path.length() - 1));
        }
    }
}




