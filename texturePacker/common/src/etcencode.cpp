#include <QImage>

#include "include/etcencode.h"
#include "include/fileutils.h"

static const char PKM_HEADER[] = { 'P', 'K', 'M', ' ', '1', '0' };

static const unsigned short KYMASK[] = { 0x0, 0xf,      0xff,   0xfff,  0xffff };
static const unsigned short KXMASK[] = { 0x0, 0x1111,   0x3333, 0x7777, 0xffff };

const unsigned int ETCEncode::ETC1_PKM_FORMAT_OFFSET = 6;
const unsigned int ETCEncode::ETC1_PKM_ENCODED_WIDTH_OFFSET = 8;
const unsigned int ETCEncode::ETC1_PKM_ENCODED_HEIGHT_OFFSET = 10;
const unsigned int ETCEncode::ETC1_PKM_WIDTH_OFFSET = 12;
const unsigned int ETCEncode::ETC1_PKM_HEIGHT_OFFSET = 14;
const unsigned int ETCEncode::ETC1_RGB_NO_MIPMAPS = 0;

#define ETC1_ENCODED_BLOCK_SIZE 8
#define ETC1_DECODED_BLOCK_SIZE 48

typedef struct {
    unsigned int high;
    unsigned int low;
    unsigned int score; // Lower is more accurate
} etc_compressed;

static inline void take_best(etc_compressed* a, const etc_compressed* b)
{
    if (a->score > b->score)
    {
        *a = *b;
    }
}

ETCEncode::ETCEncode()
{
}

ETCEncode::~ETCEncode()
{
}

ETC * ETCEncode::convert(const QString & pngPath)
{
    if (FileUtils::isFile(pngPath) == false)
    {
        return NULL;
    }

//    QImage pngImage(pngPath, "PNG");
//    if ((pngImage.width() < 1) || (pngImage.height() < 1))
//    {
//        return NULL;
//    }

//    createHeader(pngImage.width(), pngImage.height() * 2);



    return NULL;
}

void ETCEncode::writeBEUint16(unsigned char * pOut, unsigned int data)
{
    pOut[0] = (unsigned char ) (data >> 8);
    pOut[1] = (unsigned char ) data;
}

void ETCEncode::createHeader(unsigned int width, unsigned int height)
{
    memcpy(_headerData, PKM_HEADER, sizeof(PKM_HEADER));
    unsigned int encodedWidth = (width + 3) & ~3;
    unsigned int encodedHeight = (height + 3) & ~3;

    writeBEUint16(_headerData + ETC1_PKM_FORMAT_OFFSET, ETC1_RGB_NO_MIPMAPS);
    writeBEUint16(_headerData + ETC1_PKM_ENCODED_WIDTH_OFFSET, encodedWidth);
    writeBEUint16(_headerData + ETC1_PKM_ENCODED_HEIGHT_OFFSET, encodedHeight);
    writeBEUint16(_headerData + ETC1_PKM_WIDTH_OFFSET, width);
    writeBEUint16(_headerData + ETC1_PKM_HEIGHT_OFFSET, height);
}

unsigned char * ETCEncode::encodeImage(const unsigned char* pIn,
                              unsigned int width,
                              unsigned int height,
                              unsigned int pixelSize,
                              unsigned int stride)
{
    if (pixelSize < 2 || pixelSize > 3)
    {
            return NULL;
    }

    unsigned int block[ETC1_DECODED_BLOCK_SIZE];
    unsigned int encoded[ETC1_ENCODED_BLOCK_SIZE];

    unsigned int encodedWidth = (width + 3) & ~3;
    unsigned int encodedHeight = (height + 3) & ~3;

    for (unsigned int y = 0; y < encodedHeight; y += 4)
    {
        unsigned int yEnd = height - y;
        if (yEnd > 4)
        {
            yEnd = 4;
        }

        int ymask = KYMASK[yEnd];
        for (unsigned int x = 0; x < encodedWidth; x += 4)
        {
            unsigned int xEnd = width - x;
            if (xEnd > 4)
            {
                xEnd = 4;
            }

            int mask = ymask & KXMASK[xEnd];
            for (unsigned int cy = 0; cy < yEnd; cy++)
            {
                unsigned char * q = block + (cy * 4) * 3;
                const unsigned char * p = pIn + pixelSize * x + stride * (y + cy);
                if (pixelSize == 3)
                {
                    memcpy(q, p, xEnd * 3);
                }
                else
                {
                    for (unsigned int cx = 0; cx < xEnd; cx++)
                    {
                        int pixel = (p[1] << 8) | p[0];
                        *q++ = convert5To8(pixel >> 11);
                        *q++ = convert6To8(pixel >> 5);
                        *q++ = convert5To8(pixel);
                        p += pixelSize;
                    }
                }
            }

            etc1_encode_block(block, mask, encoded);
            memcpy(pOut, encoded, sizeof(encoded));
            pOut += sizeof(encoded);
        }
    }
}

void ETCEncode::encodeBlock(const unsigned char * pIn,
                 unsigned int inMask,
                 unsigned char * pOut)
{
    unsigned char colors[6];
    unsigned char flippedColors[6];
    etc_average_colors_subblock(pIn, inMask, colors, false, false);
    etc_average_colors_subblock(pIn, inMask, colors + 3, false, true);
    etc_average_colors_subblock(pIn, inMask, flippedColors, true, false);
    etc_average_colors_subblock(pIn, inMask, flippedColors + 3, true, true);

    etc_compressed a, b;
    etc_encode_block_helper(pIn, inMask, colors, &a, false);
    etc_encode_block_helper(pIn, inMask, flippedColors, &b, true);
    take_best(&a, &b);
    writeBigEndian(pOut, a.high);
    writeBigEndian(pOut + 4, a.low);
}
