#include <QImage>
#include <QProcess>
#include "include/etcencode.h"
#include "include/fileutils.h"

static const char PKM_HEADER[] = { 'P', 'K', 'M', ' ', '1', '0' };

static const unsigned short KYMASK[] = { 0x0, 0xf,      0xff,   0xfff,  0xffff };
static const unsigned short KXMASK[] = { 0x0, 0x1111,   0x3333, 0x7777, 0xffff };
static const int kModifierTable[] = {
/* 0 */2, 8, -2, -8,
/* 1 */5, 17, -5, -17,
/* 2 */9, 29, -9, -29,
/* 3 */13, 42, -13, -42,
/* 4 */18, 60, -18, -60,
/* 5 */24, 80, -24, -80,
/* 6 */33, 106, -33, -106,
/* 7 */47, 183, -47, -183 };

const unsigned int ETCEncode::ETC1_PKM_FORMAT_OFFSET = 6;
const unsigned int ETCEncode::ETC1_PKM_ENCODED_WIDTH_OFFSET = 8;
const unsigned int ETCEncode::ETC1_PKM_ENCODED_HEIGHT_OFFSET = 10;
const unsigned int ETCEncode::ETC1_PKM_WIDTH_OFFSET = 12;
const unsigned int ETCEncode::ETC1_PKM_HEIGHT_OFFSET = 14;
const unsigned int ETCEncode::ETC1_RGB_NO_MIPMAPS = 0;

#define ETC1_ENCODED_BLOCK_SIZE 8
#define ETC1_DECODED_BLOCK_SIZE 48

static inline int convert4To8(int b)
{
    int c = b & 0xf;
    return (c << 4) | c;
}

static inline int convert5To8(int b)
{
    int c = b & 0x1f;
    return (c << 3) | (c >> 2);
}

static inline int convert6To8(int b)
{
    int c = b & 0x3f;
    return (c << 2) | (c >> 4);
}
static inline int divideBy255(int d)
{
    return (d + 128 + (d >> 8)) >> 8;
}

static inline int convert8To4(int b)
{
    int c = b & 0xff;
    return divideBy255(c * 15);
}

static inline int convert8To5(int b)
{
    int c = b & 0xff;
    return divideBy255(c * 31);
}

static inline void take_best(etc_compressed* a, const etc_compressed* b)
{
    if (a->score > b->score)
    {
        *a = *b;
    }
}

static inline int square(int x)
{
    return x * x;
}

static inline unsigned char clamp(int x)
{
    return (unsigned char) (x >= 0 ? (x < 255 ? x : 255) : 0);
}

static inline bool inRange4bitSigned(int color)
{
    return color >= -4 && color <= 3;
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

    QString outPath = FileUtils::createImageTempFolder();

    QProcess process;
    QString cmd = "etcpack " + FileUtils::getAbsoluteFilePath(pngPath) + " " + outPath + " -s fast -c etc1 -aa";
    process.start(cmd);
    process.waitForFinished();

    QString pkmFileName = outPath + "/" + FileUtils::getFileBaseName(pngPath) + ".pkm";

    if (FileUtils::isFile(pkmFileName) == false)
    {
        return NULL;
    }

    ETC *result = new ETC(pkmFileName);
    if (!result->load())
    {
        FileUtils::unlink(pkmFileName);
        return NULL;
    }

    FileUtils::unlink(pkmFileName);
    return result;
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
                              unsigned int stride,
                              unsigned long * size)
{
    *size = 0;
    if (pixelSize < 2 || pixelSize > 3)
    {
            return NULL;
    }

    unsigned char block[ETC1_DECODED_BLOCK_SIZE];
    unsigned char encoded[ETC1_ENCODED_BLOCK_SIZE];

    unsigned int encodedWidth = (width + 3) & ~3;
    unsigned int encodedHeight = (height + 3) & ~3;
    if ((encodedHeight < 1) || (encodedWidth < 1))
    {
        return NULL;
    }

    *size = encodedHeight * encodedWidth;
    unsigned char * result = new unsigned char[*size];

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

            encodeBlock(block, mask, encoded);
            memcpy(result, encoded, sizeof(encoded));
            result += sizeof(encoded);
        }
    }

    return result;
}

void ETCEncode::encodeBlock(const unsigned char * pIn,
                 unsigned int inMask,
                 unsigned char * pOut)
{
    unsigned char colors[6];
    unsigned char flippedColors[6];
    averageColorsSubblock(pIn, inMask, colors, false, false);
    averageColorsSubblock(pIn, inMask, colors + 3, false, true);
    averageColorsSubblock(pIn, inMask, flippedColors, true, false);
    averageColorsSubblock(pIn, inMask, flippedColors + 3, true, true);

    etc_compressed a, b;
    encodeBlockHelper(pIn, inMask, colors, &a, false);
    encodeBlockHelper(pIn, inMask, flippedColors, &b, true);
    take_best(&a, &b);
    writeBigEndian(pOut, a.high);
    writeBigEndian(pOut + 4, a.low);
}

void ETCEncode::averageColorsSubblock(const unsigned char * pIn, unsigned int inMask, unsigned char * pColors, bool flipped, bool second)
{
    int r = 0;
    int g = 0;
    int b = 0;

    if (flipped)
    {
        int by = 0;
        if (second)
        {
            by = 2;
        }

        for (int y = 0; y < 2; y++)
        {
            int yy = by + y;
            for (int x = 0; x < 4; x++)
            {
                int i = x + 4 * yy;
                if (inMask & (1 << i))
                {
                    const unsigned char* p = pIn + i * 3;
                    r += *(p++);
                    g += *(p++);
                    b += *(p++);
                }
            }
        }
    }
    else
    {
        int bx = 0;
        if (second)
        {
            bx = 2;
        }

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                int xx = bx + x;
                int i = xx + 4 * y;
                if (inMask & (1 << i))
                {
                    const unsigned char * p = pIn + i * 3;
                    r += *(p++);
                    g += *(p++);
                    b += *(p++);
                }
            }
        }
    }

    pColors[0] = (unsigned char)((r + 4) >> 3);
    pColors[1] = (unsigned char)((g + 4) >> 3);
    pColors[2] = (unsigned char)((b + 4) >> 3);
}

void ETCEncode::writeBigEndian(unsigned char * pOut, unsigned int d)
{
    pOut[0] = (unsigned char)(d >> 24);
    pOut[1] = (unsigned char)(d >> 16);
    pOut[2] = (unsigned char)(d >> 8);
    pOut[3] = (unsigned char) d;
}

void ETCEncode::encodeBlockHelper(const unsigned char* pIn,
                                  unsigned int inMask,
                                  const unsigned char* pColors,
                                  etc_compressed* pCompressed,
                                  bool flipped)
{
    pCompressed->score = ~0;
    pCompressed->high = (flipped ? 1 : 0);
    pCompressed->low = 0;

    unsigned char pBaseColors[6];

    encodeBaseColors(pBaseColors, pColors, pCompressed);

    int originalHigh = pCompressed->high;

    const int* pModifierTable = kModifierTable;
    for (int i = 0; i < 8; i++, pModifierTable += 4) {
        etc_compressed temp;
        temp.score = 0;
        temp.high = originalHigh | (i << 5);
        temp.low = 0;
        encodeSubBlockHelper(pIn, inMask, &temp, flipped, false,
                pBaseColors, pModifierTable);
        take_best(pCompressed, &temp);
    }
    pModifierTable = kModifierTable;
    etc_compressed firstHalf = *pCompressed;
    for (int i = 0; i < 8; i++, pModifierTable += 4) {
        etc_compressed temp;
        temp.score = firstHalf.score;
        temp.high = firstHalf.high | (i << 2);
        temp.low = firstHalf.low;
        encodeSubBlockHelper(pIn, inMask, &temp, flipped, true,
                pBaseColors + 3, pModifierTable);
        if (i == 0) {
            *pCompressed = temp;
        } else {
            take_best(pCompressed, &temp);
        }
    }
}

void ETCEncode::encodeSubBlockHelper(const unsigned char * pIn,
                          unsigned int inMask,
                          etc_compressed* pCompressed,
                          bool flipped,
                          bool second,
                          const unsigned char * pBaseColors,
                          const int* pModifierTable)
{
    int score = pCompressed->score;
    if (flipped)
    {
        int by = 0;
        if (second)
        {
            by = 2;
        }

        for (int y = 0; y < 2; y++)
        {
            int yy = by + y;
            for (int x = 0; x < 4; x++)
            {
                int i = x + 4 * yy;
                if (inMask & (1 << i))
                {
                    score += chooseModifier(pBaseColors, pIn + i * 3,
                            &pCompressed->low, yy + x * 4, pModifierTable);
                }
            }
        }
    }
    else
    {
        int bx = 0;
        if (second)
        {
            bx = 2;
        }

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 2; x++)
            {
                int xx = bx + x;
                int i = xx + 4 * y;
                if (inMask & (1 << i))
                {
                    score += chooseModifier(pBaseColors, pIn + i * 3,
                            &pCompressed->low, y + xx * 4, pModifierTable);
                }
            }
        }
    }

    pCompressed->score = score;
}

unsigned int ETCEncode::chooseModifier(const unsigned char * pBaseColors,
                                       const unsigned char* pIn,
                                       unsigned int *pLow,
                                       int bitIndex,
                                       const int* pModifierTable)
{
    unsigned int bestScore = ~0;
    int bestIndex = 0;
    int pixelR = pIn[0];
    int pixelG = pIn[1];
    int pixelB = pIn[2];
    int r = pBaseColors[0];
    int g = pBaseColors[1];
    int b = pBaseColors[2];
    for (int i = 0; i < 4; i++)
    {
        int modifier = pModifierTable[i];
        int decodedG = clamp(g + modifier);
        unsigned int score = (unsigned int) (6 * square(decodedG - pixelG));
        if (score >= bestScore)
        {
            continue;
        }
        int decodedR = clamp(r + modifier);
        score += (unsigned int) (3 * square(decodedR - pixelR));
        if (score >= bestScore)
        {
            continue;
        }
        int decodedB = clamp(b + modifier);
        score += (unsigned int) square(decodedB - pixelB);
        if (score < bestScore)
        {
            bestScore = score;
            bestIndex = i;
        }
    }

    unsigned int lowMask = (((bestIndex >> 1) << 16) | (bestIndex & 1)) << bitIndex;
    *pLow |= lowMask;
    return bestScore;
}

void ETCEncode::encodeBaseColors(unsigned char* pBaseColors,
                      const unsigned char* pColors,
                      etc_compressed* pCompressed)
{
    int r1, g1, b1, r2, g2, b2; // 8 bit base colors for sub-blocks
    bool differential;
    {
        int r51 = convert8To5(pColors[0]);
        int g51 = convert8To5(pColors[1]);
        int b51 = convert8To5(pColors[2]);
        int r52 = convert8To5(pColors[3]);
        int g52 = convert8To5(pColors[4]);
        int b52 = convert8To5(pColors[5]);

        r1 = convert5To8(r51);
        g1 = convert5To8(g51);
        b1 = convert5To8(b51);

        int dr = r52 - r51;
        int dg = g52 - g51;
        int db = b52 - b51;

        differential = inRange4bitSigned(dr) && inRange4bitSigned(dg)
                && inRange4bitSigned(db);
        if (differential) {
            r2 = convert5To8(r51 + dr);
            g2 = convert5To8(g51 + dg);
            b2 = convert5To8(b51 + db);
            pCompressed->high |= (r51 << 27) | ((7 & dr) << 24) | (g51 << 19)
                    | ((7 & dg) << 16) | (b51 << 11) | ((7 & db) << 8) | 2;
        }
    }

    if (!differential) {
        int r41 = convert8To4(pColors[0]);
        int g41 = convert8To4(pColors[1]);
        int b41 = convert8To4(pColors[2]);
        int r42 = convert8To4(pColors[3]);
        int g42 = convert8To4(pColors[4]);
        int b42 = convert8To4(pColors[5]);
        r1 = convert4To8(r41);
        g1 = convert4To8(g41);
        b1 = convert4To8(b41);
        r2 = convert4To8(r42);
        g2 = convert4To8(g42);
        b2 = convert4To8(b42);
        pCompressed->high |= (r41 << 28) | (r42 << 24) | (g41 << 20) | (g42
                << 16) | (b41 << 12) | (b42 << 8);
    }
    pBaseColors[0] = r1;
    pBaseColors[1] = g1;
    pBaseColors[2] = b1;
    pBaseColors[3] = r2;
    pBaseColors[4] = g2;
    pBaseColors[5] = b2;
}
