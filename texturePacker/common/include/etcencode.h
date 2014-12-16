#ifndef ETCENCODE_H
#define ETCENCODE_H
#include <QString>
#include "include/etc.h"

typedef struct {
    unsigned int high;
    unsigned int low;
    unsigned int score; // Lower is more accurate
} etc_compressed;

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
                                  unsigned int stride, unsigned long * size);

    void encodeBlock(const unsigned char * pIn,
                     unsigned int inMask,
                     unsigned char * pOut);

    void averageColorsSubblock(const unsigned char * pIn,
                               unsigned int inMask,
                               unsigned char * pColors,
                               bool flipped,
                               bool second);

    void writeBigEndian(unsigned char * pOut, unsigned int d);

    void encodeBlockHelper(const unsigned char * pIn,
                           unsigned int inMask,
                           const unsigned char* pColors,
                           etc_compressed* pCompressed,
                           bool flipped);

    void encodeSubBlockHelper(const unsigned char * pIn,
                              unsigned int inMask,
                              etc_compressed* pCompressed,
                              bool flipped,
                              bool second,
                              const unsigned char * pBaseColors,
                              const int* pModifierTable);

    unsigned int chooseModifier(const unsigned char * pBaseColors,
                                const unsigned char* pIn,
                                unsigned int *pLow,
                                int bitIndex,
                                const int* pModifierTable);

    void encodeBaseColors(unsigned char* pBaseColors,
                          const unsigned char* pColors,
                          etc_compressed* pCompressed);
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
