#include "include/reader.h"
#include "include/ioutils.h"

//static bool isBig = CC_HOST_IS_BIG_ENDIAN;
//inline static void orderData(unsigned char *str, unsigned int len)
//{
//    if (!isBig)
//    {
//        unsigned char *data = new unsigned char [len];
//        for (unsigned int i = 0; i< len; i++)
//        {
//            *(data+i) = *(str+len-i-1);
//        }

//        memcpy(str, data, len);

//        delete [] data;
//    }
//}

Reader::Reader(unsigned char *pData, unsigned long nSize):
    m_pData(pData)
  , m_nSize(nSize)
  , m_offset(0)
{
}

Reader::~Reader()
{
    if (NULL != m_pData)
    {
        delete [] m_pData;
    }
}

unsigned char Reader::readByte()
{
    unsigned char result;
    memcpy(&result, m_pData+m_offset, sizeof(unsigned char));
    m_offset++;
    return result;
}

bool Reader::readBoolean()
{
    return (0 == readByte() ? false : true);
}

unsigned int Reader::readUnsignedInt()
{
    IOUtils::orderData(m_pData+m_offset, sizeof(unsigned int));
    unsigned int result = 0;
    memcpy(&result, m_pData+m_offset, sizeof(unsigned int));

    m_offset+=4;

    return result;
}

int Reader::readInt()
{
    IOUtils::orderData(m_pData+m_offset, sizeof(int));
    int result = 0;
    memcpy(&result, m_pData+m_offset, sizeof(int));

    m_offset+=4;

    return result;
}

float Reader::readFloat()
{
    IOUtils::orderData(m_pData+m_offset, sizeof(float));
    float result = 0;
    memcpy(&result, m_pData+m_offset, sizeof(float));
    m_offset+=4;

    return result;
}

QString Reader::readString()
{
    int b0  = *(m_pData+m_offset);
    int b1  = *(m_pData+1+m_offset);
    int len = b0 << 8 | b1;

    char *outData = new char[len+1];
    memset(outData, 0, len+1);
    memcpy(outData, m_pData+2+m_offset, len);
    m_offset +=2+len;

    QString result(outData);
    delete [] outData;

    return result;
}

short Reader::readShort()
{
    IOUtils::orderData(m_pData+m_offset, sizeof(short));
    short result = 0;
    memcpy(&result, m_pData+m_offset, sizeof(short));
    m_offset+=2;

    return result;
}

void Reader::skip(int offset)
{
    m_offset +=offset;
}

bool Reader::isUTF8BOM()
{
    return (194== *m_pData);
}

void Reader::skipUTF8BOM()
{
    if (isUTF8BOM())
    {
        skip(1);
    }
}
