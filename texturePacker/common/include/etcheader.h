#ifndef ETCHEADER_H
#define ETCHEADER_H
#include <gl.h>
class ETCHeader
{
public:
    explicit ETCHeader(const unsigned char * data);
    unsigned short getWidth(void);
    unsigned short getHeight(void);
    unsigned short getPaddedWidth(void);
    unsigned short getPaddedHeight(void);
    GLsizei getSize(GLenum internalFormat);

private:
    ETCHeader(const ETCHeader & header);

private:
    unsigned char _paddedWidthMSB;
    unsigned char _paddedWidthLSB;
    unsigned char _paddedHeightMSB;
    unsigned char _paddedHeightLSB;
    unsigned char _widthMSB;
    unsigned char _widthLSB;
    unsigned char _heightMSB;
    unsigned char _heightLSB;
};

#endif // ETCHEADER_H
