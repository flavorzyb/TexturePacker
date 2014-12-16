#include "include/etcheader.h"

ETCHeader::ETCHeader(const unsigned char *data)
{
    _paddedWidthMSB = data[8];
    _paddedWidthLSB = data[9];
    _paddedHeightMSB = data[10];
    _paddedHeightLSB = data[11];
    _widthMSB = data[12];
    _widthLSB = data[13];
    _heightMSB = data[14];
    _heightLSB = data[15];
}
unsigned short ETCHeader::getWidth(void)
{
    return (_widthMSB << 8) | _widthLSB;
}

unsigned short ETCHeader::getHeight(void)
{
    return (_heightMSB << 8) | _heightLSB;
}

unsigned short ETCHeader::getPaddedWidth(void)
{
    return (_paddedWidthMSB << 8) | _paddedWidthLSB;
}

unsigned short ETCHeader::getPaddedHeight(void)
{
    return (_paddedHeightMSB << 8) | _paddedHeightLSB;
}

#if GLES_VERSION == 2
GLsizei ETCHeader::getSize(GLenum internalFormat)
{
    return (getPaddedWidth() * getPaddedHeight());
}
#elif GLES_VERSION == 3
GLsizei ETCHeader::getSize(GLenum internalFormat)
{
    if (internalFormat != GL_COMPRESSED_RG11_EAC       && internalFormat != GL_COMPRESSED_SIGNED_RG11_EAC &&
        internalFormat != GL_COMPRESSED_RGBA8_ETC2_EAC && internalFormat != GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC)
    {
        return (getPaddedWidth() * getPaddedHeight()) >> 1;
    }
    else
    {
        return (getPaddedWidth() * getPaddedHeight());
    }
}
#endif
