#ifndef ETCENCODE_H
#define ETCENCODE_H
#include <QString>
#include "include/etc.h"

class ETCEncode
{
public:
    ETCEncode();
    virtual ~ETCEncode();
    ETC * convert(const QString & pngPath);

private:
    ETCEncode(const ETCEncode & etc);
    ETCEncode & operator = (const ETCEncode & etc);
    void createHeader(unsigned int width, unsigned int height);
    void writeBEUint16(unsigned char * pOut, unsigned int data);
    unsigned char * encodeImage(const unsigned char * pIn,
                                  unsigned int width,
                                  unsigned int height,
                                  unsigned int pixelSize,
                                  unsigned int stride);

    void encodeBlock(const unsigned char * pIn,
                     unsigned int inMask,
                     unsigned char * pOut);
public:
    enum{ HEADER_SIZE = 16 };

private:
    static const unsigned int ETC1_PKM_FORMAT_OFFSET;
    static const unsigned int ETC1_PKM_ENCODED_WIDTH_OFFSET;
    static const unsigned int ETC1_PKM_ENCODED_HEIGHT_OFFSET;
    static const unsigned int ETC1_PKM_WIDTH_OFFSET;
    static const unsigned int ETC1_PKM_HEIGHT_OFFSET;
    static const unsigned int ETC1_RGB_NO_MIPMAPS;
private:
    unsigned char _headerData[HEADER_SIZE];
};

#endif // ETCENCODE_H
