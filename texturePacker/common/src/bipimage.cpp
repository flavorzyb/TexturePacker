#include "include/bipimage.h"

BipImage::BipImage():
    Image()
  , m_imagevo(0,0)
{
}

BipImage::BipImage(const QString & filename):
    Image(filename)
  , m_imagevo(0,0)
{
}

BipImage::~BipImage()
{
}

const ImageVO BipImage::getImageVO() const
{
    return m_imagevo;
}

void BipImage::setImageVO(const ImageVO & imagevo)
{
    m_imagevo = imagevo;
}
